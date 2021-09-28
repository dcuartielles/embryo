/*
   EMBRYO Control system v2.0

   Machine control using an event driven approach and designing
   a state machine around the different inputs and outputs

   Test 05: Firmware Versioning
   Introduces the idea of versioning to help people monitor which
   software version they have in their machine. Two new system
   variables are introduced: VERSION and VERSION_NAME as well as
   two new serial commands: a
   
   This example runs a simple state machine looking at the
   functionality of some of the inputs and prints out the
   current mode of operation

   Notes: revised names for END_STOPs, now there are called
   PIN_END_STOP_TOP, and PIN_END_STOP_BOTTOM, making it
   easier to follow the code. Moved printInputs to
   serialPrintInputs

   The state machine responds to the following diagram:

               +---------+
               |         |
        +------>  RESET  |
        |      |         |               +------------+
        |      +----+----+     AUTO      |            |
        |           |  +-----------------+  END LOOP  |
        |           |  |                 |            |
        |    -INIT- |  |                 +------^-----+
        |    BUTTON |  |                        |
        |           |  |                        | END STOP
        |           |  |                        | SWITCHES
        |           |  |                        |
        |      +----v--v-+               +------+------+
        |      |         |  L+R BUTTONS  |             |
        |      |  INIT   +--------------->  OPERATION  |
        |      |         |               |             |
        |      +---------+               +------+------+
        |                                       |
    +---+---------+                             |
    |+-----------+|                             |
    || EMERGENCY ||                             |
    ||   STOP    ||   EMERGENCY STOP BUTTON     |
    ||           |<-----------------------------+
    |+-----------+|
    +-------------+

   This code is in the public domain

   2021 D. Cuartielles

*/

// Include the machine's architecture
#include "architecture.h"
#include "states.h"

// Include the sensor / actuator handling library
#include <EduIntro.h>

// Shall we debug the code?
const int DEBUG = true;

// Array to store input values
int inputValuesOld[NUM_PINS_DIGITAL + NUM_PINS_ANALOG];
int inputValues[NUM_PINS_DIGITAL + NUM_PINS_ANALOG];

// Array to store the output values
int outputValues[NUM_PINS_OUTPUT];

// Array for all of the buttons
// unfortunately this cannot be declared automatically
// like with
//  for (int i = 0; i < NUM_PINS_DIGITAL; i++)
//    inputButtons[i] = new Button(INPUTS_DIGITAL[i]);
// and therefore cannot be automated :-(
Button inputButtons[] {
  Button(INPUTS_DIGITAL[0], PULL_DOWN),
  Button(INPUTS_DIGITAL[1], PULL_DOWN),
  Button(INPUTS_DIGITAL[2], PULL_DOWN),
  Button(INPUTS_DIGITAL[3], PULL_DOWN),
  Button(INPUTS_DIGITAL[4], PULL_DOWN),
  Button(INPUTS_DIGITAL[5], PULL_DOWN),
  Button(INPUTS_DIGITAL[6], PULL_DOWN),
  Button(INPUTS_DIGITAL[7], PULL_UP),
};

// State machine variables
int currentState = RESET;
int currentOperationState = STOP;
int currentOperationMode = MANUAL;

// used in automatic mode to detect whether the cycle is done
// 1  - done
// 0  - not done
// -1 - forced init cycle (in the unlikely case the machine stopped half way)
int firstCycle = 1;

// Machine movement variables
long speed = 0; // XXX not used

void setup() {
  // Initialise serial communication
  Serial.begin(115200);

  // Do not start until computer is connected
  while (!Serial) {};

  // Status prints
  if (DEBUG) {
    serialSystemVars();
  }

  // Declare outputs as such
  for (int i = 0; i < NUM_PINS_OUTPUT; i++)
    pinMode(OUTPUTS[i], OUTPUT);
}

void loop() {
  // Check the inputs
  readInputs();

  // Serial terminal
  serialCheck();

  // There is an event, process the state machine
  if (inputEvent()) {
    // Print out the inputs if there is an event
    if (DEBUG) serialPrintInputs();

    // for the handling of inputs, remember that the
    // array of inputValues goes as follows:
    //  0     1      2   3     4       5    6     7          8
    // {LEFT, RIGHT, UP, DOWN, BOTTOM, TOP, INIT, EMERGENCY, AUTO/MANUAL}

    switch ( currentState ) {
      case RESET:
        // if the init button is pressed enter init state
        if (inputValues[6] == PRESSED) currentState = INIT;
        break;
      case INIT:
        // set operation mode
        currentOperationMode = inputValues[8];

        // in this state the system waits until L + R are HELD to
        // continue to the OPERATION state
        if (inputValues[0] == HELD && inputValues[1] == HELD) {
          firstCycle = -1;  // configure a possible AUTOMATIC cycle reboot
          currentOperationState = STOP;
          currentState = OPERATION;
        }
        break;
      case OPERATION:
        // jump to the operation sub-state machine
        processOperation();
        break;
      case END_LOOP:
        break;
      case EMERGENCY_STOP:
        break;
      default:
        break;
    }
  }

  // Copy arrays of inputs to check state changes
  copyInputs();
}

/* Process operation

   First check whether we operate automatic or manual mode, distinguish
   between two different sub-state-machines for the operation state:
   automatic or manual (see diagrams in the code)

   For the handling of inputs, remember that the
   array of inputValues goes as follows:
    0     1      2   3     4       5    6     7          8
   {LEFT, RIGHT, UP, DOWN, BOTTOM, TOP, INIT, EMERGENCY, AUTO/MANUAL}
*/
void processOperation() {
  if (currentOperationMode == AUTOMATIC) {
    processAutomaticOperation();
  } else {
    processManualOperation();
  }
}

void processAutomaticOperation() {
  /** AUTOMATIC MODE OF OPERATION **

                                        +-----+
                                        |     |!ENDSTOP
    +------------+   L + R    +---------+--+  | BOTTOM
    |            +------------>            |<-+
    |    STOP    |            |   A_DOWN   |
    |            <------------+            |
    +------^-----+  !L + !R   +---------+--+
           |                            |
           |                            |ENDSTOP
           |                            |BOTTOM
           |                            |
           |                  +---------v--+
           |                  |            |
           +------------------+    A_UP    |
                 !L + !R +    |            |<-+
                 ENDSTOP TOP  +---------+--+  |!ENDSTOP
                                        |     | TOP
                                        +-----+

  */

  switch (currentOperationState) {
    case STOP:
      // will operate only if there have been no automatic cycles
      // done, otherwise, the user will have to release the buttons
      if (firstCycle != 0) {
        // Move down if LEFT, RIGHT and TOP are HELD
        if (inputValues[0] == HELD && inputValues[1] == HELD &&
            inputValues[5] == HELD) {
          currentOperationState = AUTO_DOWN;
        }
        // Move up if LEFT, and RIGHT are HELD and TOP and BOTTOM are RELEASED
        if (inputValues[0] == HELD && inputValues[1] == HELD &&
            inputValues[4] == RELEASED && inputValues[5] == RELEASED) {
          currentOperationState = AUTO_UP;
          firstCycle = -1; // mark this as a configuration cycle
        }
      }
      break;
    case AUTO_UP:
      // move up for as long as LEFT, and RIGHT are HELD and TOP is not pressed
      if (inputValues[0] == HELD && inputValues[1] == HELD &&
          inputValues[5] == RELEASED) {
        if (DEBUG) Serial.println(F("** MOVING UP **"));
      } else {
        currentOperationState = STOP;
        if (DEBUG) Serial.println(F("** STOP **"));
        if (inputValues[5] == PRESSED || inputValues[5] == HELD) {
          if (DEBUG) Serial.println(F("** REASON: reached top **"));

          // if it was a config cycle then consider it the first cycle
          // otherwise consider the job done
          if (firstCycle == -1) {
            firstCycle = 1;
          } else {
            firstCycle = 0;
          }
        } else {
          if (DEBUG) Serial.println(F("** REASON: buttons released **"));

          // here we should leave the operation mode and go back to init mode
          currentState = INIT;
        }
      }
      break;
    case AUTO_DOWN:
      // move down for as long as LEFT, and RIGHT are HELD and BOTTOM is not pressed
      if (inputValues[0] == HELD && inputValues[1] == HELD &&
          inputValues[4] == RELEASED) {
        if (DEBUG) Serial.println(F("** MOVING DOWN **"));
      } else {
        currentOperationState = AUTO_UP;
        if (DEBUG) Serial.println(F("** STOP - and UP**"));
        if (inputValues[4] == PRESSED || inputValues[4] == HELD) {
          if (DEBUG) Serial.println(F("** REASON: reached bottom **"));
        } else {
          if (DEBUG) Serial.println(F("** REASON: buttons released **"));

          // here we should leave the operation mode and go back to init mode
          currentState = INIT;
        }
      }
      break;
  }
}

void processManualOperation() {
  /** MANUAL MODE OF OPERATION **


            +------------+  L + R + UP    +------------+
            |            +---------------->            |
            |    STOP    |                |    M_UP    |
            |            <----------------+            |<-+
            +--^------+--+  !L + !R +     +---------+--+  |!ENDSTOP
               |      |     !UP +                   |     | TOP
               |      |     ENDSTOP TOP             +-----+
      !L + !R +|      |
      !DOWN +  |      |
      ENDSTOP  |      |L + R +
      BOTTOM   |      |DOWN
               |      |
               |      |
            +--+------v--+
            |            |
            |   M_DOWN   |
            |            |<-+
            +---------+--+  |!ENDSTOP
                      |     | BOTTOM
                      +-----+

  */

  switch (currentOperationState) {
    case STOP:
      // Move up if L + R + UP are HELD and TOP is RELEASED
      if (inputValues[0] == HELD && inputValues[1] == HELD &&
          inputValues[2] == HELD && inputValues[5] == RELEASED) {
        currentOperationMode = MAN_UP;
      }
      // Move down if L + R + DOWN are HELD and BOTTOM is RELEASED
      if (inputValues[0] == HELD && inputValues[1] == HELD &&
          inputValues[3] == HELD && inputValues[4] == RELEASED) {
        currentOperationMode = MAN_DOWN;
      }
      break;
    case MAN_UP:
      // move up for as long as LEFT, RIGHT, and UP are HELD and TOP is not pressed
      if (inputValues[0] == HELD && inputValues[1] == HELD &&
          inputValues[2] == HELD && inputValues[5] == RELEASED) {
        if (DEBUG) Serial.println(F("** MOVING UP **"));
      } else {
        currentOperationMode = STOP;
        if (DEBUG) Serial.println(F("** STOP **"));
        if (inputValues[5] == PRESSED || inputValues[5] == HELD) {
          if (DEBUG) Serial.println(F("** REASON: reached top **"));
        } else {
          if (DEBUG) Serial.println(F("** REASON: buttons released **"));

          if (inputValues[0] == RELEASED || inputValues[1] == RELEASED) {
            // here we should leave the operation mode and go back to init mode
            currentState = INIT;
          }
        }
      }
      break;
    case MAN_DOWN:
      // move down for as long as LEFT, RIGHT, and DOWN are HELD and BOTTOM is not pressed
      if (inputValues[0] == HELD && inputValues[1] == HELD &&
          inputValues[3] == HELD && inputValues[4] == RELEASED) {
        if (DEBUG) Serial.println(F("** MOVING DOWN **"));
      } else {
        currentOperationMode = STOP;
        if (DEBUG) Serial.println(F("** STOP **"));
        if (inputValues[5] == PRESSED || inputValues[4] == HELD) {
          if (DEBUG) Serial.println(F("** REASON: reached bottom **"));
        } else {
          if (DEBUG) Serial.println(F("** REASON: buttons released **"));

          if (inputValues[0] == RELEASED || inputValues[1] == RELEASED) {
            // here we should leave the operation mode and go back to init mode
            currentState = INIT;
          }
        }
      }
      break;
  }
}
