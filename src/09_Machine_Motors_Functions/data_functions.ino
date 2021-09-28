void copyInputs() {
  // Copy all values one by one
  for (int i = 0; i < NUM_PINS_DIGITAL + NUM_PINS_ANALOG; i++)
    inputValuesOld[i] = inputValues[i];
}

boolean inputEvent() {
  boolean result = false;

  // Check all values one by one
  for (int i = 0; i < NUM_PINS_DIGITAL + NUM_PINS_ANALOG; i++)
    if (pinEvent(i))
      result = true;

  return result;
}

boolean pinEvent(int i) {
  boolean result = false;

  if (inputValues[i] != inputValuesOld[i])
      result = true;

  return result;
}

void readInputs() {
  // Read digital inputs
  for (int i = 0; i < NUM_PINS_DIGITAL; i++)
    if (inputButtons[i].pressed())
      inputValues[i] = PRESSED;
    else if (inputButtons[i].released())
      inputValues[i] = RELEASED;
    else if (inputButtons[i].held())
      inputValues[i] = HELD;
    else {} // inputValues[i] = FREE;

  // Read analog inputs
  // used the trick of comparing to 1024 so that the value 2
  // is never reached
  // 0 means manual mode, 1 means automatic one
  for (int i = 0; i < NUM_PINS_ANALOG; i++)
    inputValues[NUM_PINS_DIGITAL + i] = floor(map(analogRead(INPUTS_ANALOG[i]), 0, 1024, 0, 2));
}
