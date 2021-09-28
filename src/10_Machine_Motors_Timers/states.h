// Define different states for state machines and others

const int ERROR = -1;

// States for buttons
const int FREE     = 0;
const int PRESSED  = 1;
const int HELD     = 2;
const int RELEASED = 3;

// States for state machine
const int RESET          = 0;
const int INIT           = 1;
const int OPERATION      = 2;
const int END_LOOP       = 3;
const int EMERGENCY_STOP = 4; 

// State names (to be used when reporting back)
const char * stateNames[] = {
  "RESET",
  "INIT",
  "OPERATION",
  "END_LOOP",
  "EMERGENCY_STOP"
};

// Types of states of usage for the machine
const int MANUAL    = 0;
const int AUTOMATIC = 1;

// Operation modes (to be used when reporting back)
const char * modeNames [] = {
  "MANUAL",
  "AUTOMATIC"
};

// States for the Automatic mode
const int STOP = 0;
const int AUTO_UP   = 1;
const int AUTO_DOWN = 2;

// States for the Manual mode 
// note: both operation sub-state-machines get mixed into one
//       therefore numbers should not be repeated
const int MAN_UP   = 3;
const int MAN_DOWN = 4;

// Operation states (to be used when reporting back)
const char * operationNames [] = {
  "STOP",
  "AUTO UP",
  "AUTO DOWN",
  "MANUAL UP",
  "MANUAL DOWN"
};
