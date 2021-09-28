// Sends back a help message for the whole system
void serialHelp() {
  Serial.println(F("**********************************"));
  Serial.println(F("        EMBRYO Metal Press"));
  Serial.println(F("**********************************\n"));
  Serial.println(F("Type any of the following commands"));
  Serial.println(F("on the terminal and press send:\n"));
  Serial.println(F("-help: displays this help message"));
  Serial.println(F("-buzz: play a tune to your ears"));
  Serial.println(F("-vars: print the system variables"));
  Serial.println(F("-vnum: print version number"));
  Serial.println(F("-vnam: print version name"));
  Serial.println(F("-stat: print current state"));
  Serial.println(F("-oper: print current operation state"));
  Serial.println(F("-mode: print current operation mode"));
  Serial.println(F("-rrom: read config from eeprom"));
  Serial.println(F("-wrom: write config to eeprom"));
  Serial.println(F("-tXXX: change timer to XXX\n"));
  Serial.println(F("**********************************"));
  Serial.println(F("        2021 - Arduino - EIT"));
  Serial.println(F("**********************************\n"));
  Serial.flush();
}

// Display information about the variables
void serialSystemVars(int verbosity = FULL) {
  Serial.println(F("**********************************"));
  Serial.println(F("        EMBRYO system vars"));
  Serial.println(F("**********************************\n"));
  if (verbosity == FULL) {
    Serial.print(F("Size of digital input array: "));
    Serial.println(NUM_PINS_DIGITAL);
    Serial.print(F("Size of analog input array: "));
    Serial.println(NUM_PINS_ANALOG);
    Serial.print(F("Size of output array: "));
    Serial.println(NUM_PINS_OUTPUT);
  }
  Serial.print(F("Operation mode: "));
  Serial.println(modeNames[currentOperationMode]);
  Serial.print(F("Operation state: "));
  Serial.println(operationNames[currentOperationState]);
  Serial.print(F("Machine state: "));
  Serial.println(stateNames[currentState]);
  Serial.println(F("**********************************\n"));
  Serial.flush();
}

// Display information about the inputs
void serialPrintInputs() {
  // Print out all values separated by blank spaces
  for (int i = 0; i < NUM_PINS_DIGITAL + NUM_PINS_ANALOG; i++) {
    Serial.print(inputValues[i]);
    Serial.print(" ");
  }

  Serial.println();
}

// return a number if there is one after the first character
// in the string passed as parameter
long serialGetLong(String sIn) {
  long num = -1;
  boolean breakNumber = false;

  for (int i = 1; i < sizeof(sIn); i++) {
    if (sIn[i] >= '0' && sIn[i] <= '9' && !breakNumber) {
      // Need the -1 to detect errors, but here we found
      // a number, so initialise it
      if (num == -1)
        num = 0;

      // increase the num variable
      num = num * 10 + sIn[i] - '0';

    } else
      breakNumber = true;
  }

  return num;
}

// Check the serial port for the arrival of any commands
void serialCheck() {
  if (Serial.available() > 0) {
    String sIn = Serial.readStringUntil('\n');

    // print based on the message
    if (sIn.indexOf("help") >= 0)
      serialHelp();

    if (sIn.indexOf("buzz") >= 0)
      piezo.beep(NOTE_A4, 500);
    //you can explore the piezo.play() function to perform whatever melody

    //if (sIn.indexOf("rrom") >= 0)
    //readEEPROM();

    //if (sIn.indexOf("wrom") >= 0)
    //writeEEPROM();

    if (sIn.indexOf("vars") >= 0)
      serialSystemVars();

    if (sIn.indexOf("vnum") >= 0)
      Serial.println(VERSION);

    if (sIn.indexOf("vnam") >= 0)
      Serial.println(VERSION_NAME);

    if (sIn.indexOf("stat") >= 0)
      Serial.println(stateNames[currentState]);

    if (sIn.indexOf("oper") >= 0)
      Serial.println(operationNames[currentOperationState]);

    if (sIn.indexOf("mode") >= 0)
      Serial.println(modeNames[currentOperationMode]);

    if (sIn.indexOf("t") == 0) {
      long num = serialGetLong(sIn);
      Serial.println(num);
    }
  }

}
