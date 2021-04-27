/*
   EMBRYO Control system v2.0

   Machine control using an event driven approach and designing
   a state machine around the different inputs and outputs

   Test 00: Machine Status

   This example checks the different inputs and outputs, as
   well as it establishes the different mechanisms for reading
   all inputs and actiating all outputs

   This code is in the public domain

   2021 D. Cuartielles

*/

// Include the machine's architecture
#include "architecture.h"

// Include the sensor / actuator handling library
#include <EduIntro.h>

// Shall we debug the code?
const int DEBUG = true;

// Array to store input values
int inputValuesOld[NUM_PINS_DIGITAL + NUM_PINS_ANALOG];
int inputValues[NUM_PINS_DIGITAL + NUM_PINS_ANALOG];

// Array to store the output values
int outputValues[NUM_PINS_OUTPUT];

void setup() {
  // Initialise serial communication
  Serial.begin(115200);

  // Do not start until computer is connected
  while (!Serial) {};

  // Status prints
  if (DEBUG) {
    Serial.print("Size of digital input array: ");
    Serial.println(NUM_PINS_DIGITAL);
    Serial.print("Size of analog input array: ");
    Serial.println(NUM_PINS_ANALOG);
    Serial.print("Size of output array: ");
    Serial.println(NUM_PINS_OUTPUT);
  }

  // Declare inputs and outputs as such
  for (int i = 0; i < NUM_PINS_DIGITAL; i++)
    pinMode(INPUTS_DIGITAL[i], INPUT);
  for (int i = 0; i < NUM_PINS_OUTPUT; i++)
    pinMode(OUTPUTS[i], OUTPUT);
}

void loop() {
  // Check the inputs
  readInputs();

  // Printout the inputs if there is an event
  if (inputEvent()) {
    printInputs();
  }

  // Copy arrays of inputs to check state changes
  copyInputs();
}
