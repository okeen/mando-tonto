#include <arduino-timer.h>

#define YELLOW  0
#define RED     1
#define GREEN   2
#define BLUE    3

#define RESCUE  4
#define SIREN   5
#define PARTY   6
#define LIGHTS  7

//#define DEBUG_MODE 1   
#define DEBUG_DELAY 0   

#define MODE_BUTTONS_COUNT  4   

// *state* byte to describe the full controller s2tate
// Bits: 0 - 2: Joystick orientation from 0 degrees to 315 degrees in scale of 45 degrees each
// Bits: 3 - 7: Push button's state: Yellow - Red - Green - Blue - Options
byte modesState = 0x0;
byte controlsState = 0x0;
byte joystickState = 0x0;

byte lastModesState;
byte lastControlsState;
byte lastJoystickState;

auto timer = timer_create_default();

void setup() {
  # if defined(DEBUG_MODE)  
    Serial.begin(9600);
  # endif  
  
  # if defined(DEBUG_MODE)  
    Serial.println("Leds INIT done");
  # endif  
  initLeds();
  setupRadio();
  initDisplay();
  delay(1000); // power-up safety delay  
  
  timer.every(100, updateTimerMethods);
}

void loop() {
    readPushButtons();
    readJoystick();

    if ((lastModesState != modesState) || (lastControlsState != controlsState) || (lastJoystickState != joystickState)) {
      setMode();
      sendStateByRadio();
    }
    
    timer.tick();
    delay(0);
}

void setMode() {
  # if defined(DEBUG_MODE)  
    Serial.println("Set Mode");
  # endif  
        
//  if (modesState != 0x0 || controlsState != 0x0 ) {
    bool pressed;
    
    for (byte i = YELLOW; i <= LIGHTS;i++) {
      if (i < RESCUE) {
        pressed = bitRead(modesState, i);
      } else {
        pressed = bitRead(controlsState, i - RESCUE);
      }
      
      if (pressed) {
        setDisplayMode(i);
        setLedsMode(i);
      }      
    }   
//  }      
}

void setJoystickState(uint8_t value) {
  joystickState = value;
}

void updateTimerMethods() {
  updateDisplay();
  updateLeds(false);
}
