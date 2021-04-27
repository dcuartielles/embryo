void copyInputs() {
  // Copy all values one by one
  for (int i = 0; i < NUM_PINS_DIGITAL + NUM_PINS_ANALOG; i++)
    inputValuesOld[i] = inputValues[i];
}

void printInputs() {
  // Print out all values separated by blank spaces
  for (int i = 0; i < NUM_PINS_DIGITAL + NUM_PINS_ANALOG; i++) {
    Serial.print(inputValues[i]);
    Serial.print(" ");
  }
  
  Serial.println();
}

boolean inputEvent() {
  boolean result = false;

  // Check all values one by one
  for (int i = 0; i < NUM_PINS_DIGITAL + NUM_PINS_ANALOG; i++)
    if (inputValues[i] != inputValuesOld[i])
      result = true;

  return result;
}

void readInputs() {
  // Read digital inputs
  for (int i = 0; i < NUM_PINS_DIGITAL; i++)
    inputValues[i] = digitalRead(INPUTS_DIGITAL[i]);

  // Read analog inputs
  for (int i = 0; i < NUM_PINS_ANALOG; i++)
    inputValues[NUM_PINS_DIGITAL + i] = analogRead(INPUTS_ANALOG[i]);
}
