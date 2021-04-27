// Machine architecture
// * Inputs
const int PIN_BUTTON_LEFT = 6;     
const int PIN_BUTTON_RIGHT = 5;    
const int PIN_BUTTON_UP = 7;       
const int PIN_BUTTON_DOWN = 2;     

const int PIN_END_STOP = A2;       
const int PIN_END_STOP_MOTOR = 3;  

const int PIN_BUTTON_INIT = 4;     
const int PIN_BUTTON_EMERGENCY = 9;
const int PIN_POT = A0;            

// * Outputs
const int PIN_BUZZER = A1;         

const int PIN_LED =  A3;           
const int PIN_LED_EMERGENCY = 8;   
const int PIN_MOTOR_DIR = 11;      
const int PIN_MOTOR_STEP = 10;

const int INPUTS_DIGITAL[] = {
  PIN_BUTTON_LEFT,
  PIN_BUTTON_RIGHT,
  PIN_BUTTON_UP,
  PIN_BUTTON_DOWN,
  PIN_END_STOP,
  PIN_END_STOP_MOTOR,
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
