/*
   EMBRYO Control system v2.0

   Machine control using an event driven approach and designing
   a state machine around the different inputs and outputs

   Test 02: Machine Status Potentiometer as Switch

   This example checks the different inputs and outputs, as
   well as it establishes the different mechanisms for reading
   all inputs and activating all outputs

   This example checks the potentiometer and depending on its 
   angle will determine whether the machine should work in 
   manual or automatic mode. This will be processed using the
   map function 

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
// and theefore cannot be automated :-(
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

void setup() {
  // Initialise serial communication
  Serial.begin(115200);

  // Do not start until computer is connected
  while (!Serial) {};

  // Status prints
  if (DEBUG) {
    Serial.print(F("Size of digital input array: "));
    Serial.println(NUM_PINS_DIGITAL);
    Serial.print(F("Size of analog input array: "));
    Serial.println(NUM_PINS_ANALOG);
    Serial.print(F("Size of output array: "));
    Serial.println(NUM_PINS_OUTPUT);
  }

  // Declare outputs as such
  for (int i = 0; i < NUM_PINS_OUTPUT; i++)
    pinMode(OUTPUTS[i], OUTPUT);
}

void loop() {
  // Check the inputs
  readInputs();

  // Print out the inputs if there is an event
  if (inputEvent()) {
    printInputs();
  }

  // Copy arrays of inputs to check state changes
  copyInputs();
}
