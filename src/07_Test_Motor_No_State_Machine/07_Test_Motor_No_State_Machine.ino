/*
   EMBRYO Control system v2.0

   Machine control using an event driven approach and designing
   a state machine around the different inputs and outputs

   Test 07: Test Motor No State Machine
   This is just to test that the motors work
   and respond to serial commands


   This code is in the public domain

   2021 D. Cuartielles

*/

#define dirPin 11
#define stepPin 10

void setup() {
  // Init Serial
  Serial.begin(115200);

  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int serVar = Serial.read();

    if (serVar == 'u')
      moveUp();

    if (serVar == 'd')
      moveDown();
  }
}

void moveUp() {
  // Set the spinning direction CW/CCW:
  digitalWrite(dirPin, HIGH);

  // move the motor up
  for (int i = 0; i < 10; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
}

void moveDown() {
  // Set the spinning direction CW/CCW:
  digitalWrite(dirPin, LOW);

  // move the motor down
  for (int i = 0; i < 10; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
}
