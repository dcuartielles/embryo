// Machine architecture
// * Versioning number
const float VERSION = 0.5;
String VERSION_NAME = "Haparanda";

// * Timers (microseconds)
const int TIMER_SPEED_MAX = 20000;
const int TIMER_SPEED_MIN = 350; // beyond 350 the motor will not move

// * Steps for motors
const int STEPS_MAX = 3600; // estimated amount of steps, use example 8 for your machine

// * Verbosity level
const int LITE = 0;
const int FULL = 1;

// * Inputs
const int PIN_BUTTON_LEFT = 6;     
const int PIN_BUTTON_RIGHT = 5;    
const int PIN_BUTTON_UP = 7;       
const int PIN_BUTTON_DOWN = 2;     

const int PIN_END_STOP_BOTTOM = A2;       
const int PIN_END_STOP_TOP = 3;  

const int PIN_BUTTON_INIT = 4;     
const int PIN_BUTTON_EMERGENCY = 9;
const int PIN_POT = A0;            

// * Outputs
const int PIN_BUZZER = A1;         

const int PIN_LED =  A3;           
const int PIN_LED_EMERGENCY = 8;   
const int PIN_MOTOR_DIR = 11;      
const int PIN_MOTOR_STEP = 10;

// * Mechanics
const int STEPS_PER_REVOLUTION = 200;

const int INPUTS_DIGITAL[] = {
  PIN_BUTTON_LEFT,
  PIN_BUTTON_RIGHT,
  PIN_BUTTON_UP,
  PIN_BUTTON_DOWN,
  PIN_END_STOP_BOTTOM,
  PIN_END_STOP_TOP,
  PIN_BUTTON_INIT,
  PIN_BUTTON_EMERGENCY
};

const int INPUTS_ANALOG[] = {
  PIN_POT
};

const int OUTPUTS[] = {
  PIN_BUZZER,
  PIN_LED,
  PIN_LED_EMERGENCY,
  PIN_MOTOR_DIR,
  PIN_MOTOR_STEP
};

const int NUM_PINS_DIGITAL = sizeof(INPUTS_DIGITAL) / sizeof(INPUTS_DIGITAL[0]);
const int NUM_PINS_ANALOG = sizeof(INPUTS_ANALOG) / sizeof(INPUTS_ANALOG[0]);
const int NUM_PINS_OUTPUT = sizeof(OUTPUTS) / sizeof(OUTPUTS[0]);

// Function names (some functions need to be defined prior to be used in the loop)
void serialSystemVars(int verbosity = FULL);
/*void readInputs();
void serialCheck();
bool inputEvent();
bool pinEvent(int p);
void moveUp();
void moveDown();
void pulseMotor();
void copyInputs();
void serialPrintInputs();*/
