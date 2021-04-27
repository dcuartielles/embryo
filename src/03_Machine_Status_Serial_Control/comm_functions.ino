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
  Serial.println(F("-rrom: read config from eeprom"));
  Serial.println(F("-wrom: write config to eeprom"));
  Serial.println(F("-tXXX: change timer to XXX\n"));
  Serial.println(F("**********************************"));
  Serial.println(F("        2021 - Arduino - EIT"));
  Serial.println(F("**********************************\n"));
  Serial.flush();
}

void serialSystemVars() {
  Serial.println(F("**********************************"));
  Serial.println(F("        EMBRYO system vars"));
  Serial.println(F("**********************************\n"));
  Serial.print(F("Size of digital input array: "));
  Serial.println(NUM_PINS_DIGITAL);
  Serial.print(F("Size of analog input array: "));
  Serial.println(NUM_PINS_ANALOG);
  Serial.print(F("Size of output array: "));
  Serial.println(NUM_PINS_OUTPUT);
  Serial.println(F("**********************************\n"));
  Serial.flush();
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

    //if (sIn.indexOf("buzz") >= 0)
    //playMelody();

    //if (sIn.indexOf("rrom") >= 0)
    //readEEPROM();

    //if (sIn.indexOf("wrom") >= 0)
    //writeEEPROM();

    if (sIn.indexOf("vars") >= 0)
      serialSystemVars();

    if (sIn.indexOf("t") == 0) {
      long num = serialGetLong(sIn);
      Serial.println(num);
    }
  }

}
