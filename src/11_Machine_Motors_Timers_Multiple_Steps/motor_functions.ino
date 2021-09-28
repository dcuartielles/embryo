// Move motor up to the initial position
/*void moveInit() {
  // move up until reaching the top or the emergency button being pressed
  while(inputButtons[5] == RELEASED && !(inputButtons[7] == PRESSED || inputButtons[7] == HELD)) {
    moveUp();
  }

  // move down a little
  while(inputButtons[5] == PRESSED || inputButtons[5] == HELD) {
    moveDown();
  }
  }
*/

// Move up one step, but make sure you don't move beyond the end stop
void moveUp() {
  // Set direction
  digitalWrite(OUTPUTS[3], HIGH);

  // Send pulse
  pulseMotor();
}

// Move down one step, but make sure you don't move beyond the end stop
void moveDown() {
  // Set direction
  digitalWrite(OUTPUTS[3], LOW);

  // Send pulse
  pulseMotor();
}

// Generate the pulse on the motor based on the set speed
/*void pulseMotor() {
  // Set pulse
  if (micros() - timerSpeedWatchdog > timerSpeed) {
    motorPulseState = !motorPulseState;
    timerSpeedWatchdog = micros();
    digitalWrite(OUTPUTS[4], motorPulseState);
  }
  }*/
// This version of pulseMotor uses a delay, which is not optimal,
// but avoids using yet another timer to run an interrupt. The
// strategy of substracting times works but it is not nice as the
// times are not precise and the motors produce audible artifacts
void pulseMotor() {
  switch (currentOperationState) {
    case AUTO_UP:
      stepsCount--;
      break;
    case AUTO_DOWN:
      stepsCount++;
      break;
    default:
      break;
  }

  // These three lines result in 1/2 step:
  motorPulseState = !motorPulseState;
  digitalWrite(OUTPUTS[4], motorPulseState);
  delayMicroseconds(timerSpeed);
}

// The timer friendly version of pulseMotor
bool pulseMotor(void *) {
  switch (currentOperationState) {
    case AUTO_UP:
      stepsCount--;
      break;
    case AUTO_DOWN:
      stepsCount++;
      break;
    default:
      break;
  }

  // These three lines result in 1/2 step:
  motorPulseState = !motorPulseState;
  digitalWrite(OUTPUTS[4], motorPulseState);
  return true;
}
