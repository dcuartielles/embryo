/*
   EMBRYO Control system v2.0

   Machine control using an event driven approach and designing
   a state machine around the different inputs and outputs

   Test 08: Test Motor Init State
   Send serial command 'i' to tell the motor to
   move back to the initial state, added some of
   the variables from the main program to ensure
   later compatibility

   This code is in the public domain

   2021 D. Cuartielles

*/

const bool DEBUG = true;

const int dirPin = 11;
const int stepPin = 10;
const int endStop = 3;
const int endStopBottom = A2;

// simulate the part of the outputs array in the machine
const int OUTPUTS [] = {0, 0 , 0, dirPin, stepPin};

long timerSpeed = 350; // limited between TIMER_SPEED_MAX and MIN, uSeconds
//long timerSpeedWatchdog = 0; // to check the times
byte motorPulseState = LOW; // goes between HIGH and LOW every timerSpeed uS

long stepCount = 0; // counts the steps made to move the motor from any position to init

void setup() {
  // Init Serial
  Serial.begin(115200);

  // Declare pins as in/output:
  pinMode(OUTPUTS[4], OUTPUT);
  pinMode(OUTPUTS[3], OUTPUT);
  pinMode(endStop, INPUT);
  pinMode(endStopBottom, INPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int serVar = Serial.read();

    // Move 1 clock tick
    if (serVar == 'u')
      moveUp();

    if (serVar == 'd')
      moveDown();

    // Move multiple clock ticks
    if (serVar == 'U')
      for (int i = 0; i < 100; i++)
        moveUp();

    if (serVar == 'D')
      for (int i = 0; i < 100; i++)
        moveDown();

    if (serVar == 'i') {
      stepCount = 0;
      moveInit();
    }

    if (serVar == 'e') {
      moveInit();
      stepCount = 0;
      moveEnd();
    }
  }
}

void moveInit() {
  // move up until reaching the top
  while (digitalRead(endStop) == LOW) {
    moveUp();
    stepCount++;
  }

  // move down a little
  while (digitalRead(endStop) == HIGH) {
    moveDown();
  }

  // send the number of steps back
  Serial.print("Steps to init: ");
  Serial.println(stepCount);
}

void moveEnd() {
  // move up until reaching the top
  while (digitalRead(endStopBottom) == LOW) {
    moveDown();
    stepCount++;
  }

  // move down a little
  while (digitalRead(endStop) == HIGH) {
    moveUp();
  }

  // send the number of steps back
  Serial.print("Steps to end: ");
  Serial.println(stepCount);
}

void moveUp() {
  // Set the spinning direction CW/CCW:
  digitalWrite(OUTPUTS[3], HIGH);

  // move the motor up
  pulseMotor();
}

void moveDown() {
  // Set the spinning direction CW/CCW:
  digitalWrite(OUTPUTS[3], LOW);

  // move the motor down
  pulseMotor();
}

void pulseMotor() {
  // These three lines result in 1/2 step:
  motorPulseState = !motorPulseState;
  digitalWrite(OUTPUTS[4], motorPulseState);  //}
  delayMicroseconds(timerSpeed);
}
