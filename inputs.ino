#include <Pushbutton.h>

// Mode selectors
#define YELLOW_MODE_BUTTON_PIN  8
#define RED_MODE_BUTTON_PIN     7
#define GREEN_MODE_BUTTON_PIN   6
#define BLUE_MODE_BUTTON_PIN    5

// Control
#define YELLOW_BUTTON_PIN  A3
#define RED_BUTTON_PIN     A2
#define GREEN_BUTTON_PIN   A1
#define BLUE_BUTTON_PIN    A0

#define OPTIONS_BUTTON_PIN 13

#define JOYSTICK_X_PIN     A6
#define JOYSTICK_Y_PIN     A7
#define JOYSTICK_SW_PIN    4


// Mode selector buttons
Pushbutton yellowModeButton(YELLOW_MODE_BUTTON_PIN);
Pushbutton redModeButton(RED_MODE_BUTTON_PIN);
Pushbutton greenModeButton(GREEN_MODE_BUTTON_PIN);
Pushbutton blueModeButton(BLUE_MODE_BUTTON_PIN);

// Control Buttons
Pushbutton yellowButton(YELLOW_BUTTON_PIN);
Pushbutton redButton(RED_BUTTON_PIN);
Pushbutton greenButton(GREEN_BUTTON_PIN);
Pushbutton blueButton(BLUE_BUTTON_PIN);
//Pushbutton optionsButton(OPTIONS_BUTTON_PIN);
Pushbutton joySWButton(JOYSTICK_SW_PIN);

void readPushButtons() {
    # if defined(DEBUG_MODE) 
      Serial.println("readPushButtons");        
    # endif
    
    bitWrite(controlsState, YELLOW, yellowButton.isPressed());
    bitWrite(controlsState, RED, redButton.isPressed());
    bitWrite(controlsState, GREEN, greenButton.isPressed());
    bitWrite(controlsState, BLUE, blueButton.isPressed());

    # if defined(DEBUG_MODE) 
      Serial.println(controlsState, BIN);        
    # endif
      
    bitWrite(modesState, YELLOW, yellowModeButton.isPressed());
    bitWrite(modesState, RED, redModeButton.isPressed());
    bitWrite(modesState, GREEN, greenModeButton.isPressed());
    bitWrite(modesState, BLUE, blueModeButton.isPressed());
    
    # if defined(DEBUG_MODE) 
      Serial.println(modesState, BIN);        
    # endif    
}

void readJoystick() {
  int x = analogRead(JOYSTICK_X_PIN);
  int y = analogRead(JOYSTICK_Y_PIN);

  if (x < 400) {
    if (y < 400) {
      # if defined(DEBUG_MODE)  
        Serial.println("Joystick -> UP - RIGH");        
      # endif
      setJoystickState(0x1);
      return;
    }
    else if (y > 800){
      # if defined(DEBUG_MODE) 
        Serial.println("Joystick -> DOWN - RIGHT");        
      # endif
      
      setJoystickState(0x3);
      return;
    } else {
      # if defined(DEBUG_MODE)  
        Serial.println("Joystick -> RIGHT");
      # endif
      
      setJoystickState(0x2);
      return;
    }
  } else if ( x > 800) {
    if (y < 400) {
      # if defined(DEBUG_MODE) 
        Serial.println("Joystick -> UP - LEFT");
      # endif
      
      setJoystickState(0x7);
      return;
    }
    else if (y > 800){
      # if defined(DEBUG_MODE) 
        Serial.println("Joystick -> DOWN - LEFT");
      # endif
      
      setJoystickState(0x5);
      return;
    } else {
      # if defined(DEBUG_MODE) 
        Serial.println("Joystick -> LEFT");
      # endif
      
      setJoystickState(0x6);
      return;
    }
  } else if (y < 400) {
      # if defined(DEBUG_MODE) 
        Serial.println("Joystick -> UP");
      # endif
      
      setJoystickState(0x0);
      return;
    }
    else if (y > 800){
      # if defined(DEBUG_MODE) 
        Serial.println("Joystick -> DOWN");
      # endif
      
      setJoystickState(0x4);
      return;
    } else {
        # if defined(DEBUG_MODE) 
          Serial.println("Joystick -> CENTER");
        # endif
        
        setJoystickState(0x8);
      return;
    }
}
