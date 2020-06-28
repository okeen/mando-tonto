#include <Pushbutton.h>
#include <SoftwareSerial.h>


#define YELLOW_BUTTON_PIN  4
#define RED_BUTTON_PIN     5
#define GREEN_BUTTON_PIN   6
#define BLUE_BUTTON_PIN    7

#define OPTIONS_BUTTON_PIN A6

#define JOYSTICK_X_PIN     A5
#define JOYSTICK_Y_PIN     A4
#define JOYSTICK_SW_PIN     A3

#define RADIO_RX_PIN       2   
#define RADIO_TX_PIN       3   

Pushbutton yellowButton(YELLOW_BUTTON_PIN);
Pushbutton redButton(RED_BUTTON_PIN);
Pushbutton greenButton(GREEN_BUTTON_PIN);
Pushbutton blueButton(BLUE_BUTTON_PIN);
Pushbutton optionsButton(OPTIONS_BUTTON_PIN);

// *state* byte to describe the full controller state
// Bits: 0 - 2: Joystick orientation from 0 degrees to 315 degrees in scale of 45 degrees each
// Bits: 3 - 7: Push button's state: Yellow - Red - Green - Blue - Options
byte inputsState = 0b00000000;

SoftwareSerial radioSerial(RADIO_RX_PIN, RADIO_TX_PIN);
int last_idx = 0;

void setup() {
    Serial.begin(9600);
    delay(1000); // power-up safety delay

    radioSerial.begin(9600);
    
}

void loop() {
    readPushButtons();
    readJoystick();
    sendStateByRadio();
    delay(1000);
}

void readPushButtons() {
    bitWrite(inputsState, 3, yellowButton.isPressed());
    bitWrite(inputsState, 4, redButton.isPressed());
    bitWrite(inputsState, 5, greenButton.isPressed());
    bitWrite(inputsState, 6, blueButton.isPressed());
    bitWrite(inputsState, 7, optionsButton.isPressed());
}

void readJoystick() {
  int x = analogRead(JOYSTICK_X_PIN);
  int y = analogRead(JOYSTICK_Y_PIN);

  Serial.print("Joystick x: ");
  Serial.println(x);
  Serial.print("Joystick Y: ");
  Serial.println(y);
  
  if (x < 400) {
    if (y < 400) {
      Serial.println("Joystick -> UP - RIGHT");
      setJoystickState(0, 0, 1);
      return;
    }
    else if (y > 800){
      Serial.println("Joystick -> DOWN - RIGHT");
      setJoystickState(0, 1, 1);
      return;
    } else {
      Serial.println("Joystick -> RIGHT");
      setJoystickState(0, 1, 0);
      return;
    }
  } else if ( x > 800) {
    if (y < 400) {
      Serial.println("Joystick -> UP - LEFT");
      setJoystickState(1, 1, 1);
      return;
    }
    else if (y > 800){
      Serial.println("Joystick -> DOWN - LEFT");
      setJoystickState(1, 0, 1);
      return;
    } else {
      Serial.println("Joystick -> LEFT");
      setJoystickState(1, 1, 0);
      return;
    }
  } else if (y < 400) {
      Serial.println("Joystick -> UP");
      setJoystickState(0, 0, 0);
      return;
    }
    else if (y > 800){
      Serial.println("Joystick -> DOWN");
      setJoystickState(1, 0, 0);
      return;
    } else {
        Serial.println("Joystick -> CENTER");
      return;
    }
}

void sendStateByRadio() {
  if(radioSerial.available() >= 0) {
    Serial.println(inputsState , BIN);
    
    radioSerial.println(inputsState , BIN);
  }    
}

void setJoystickState(bool bit3, bool bit2, bool bit1) {
  bitWrite(inputsState, 0, bit1);
  bitWrite(inputsState, 1, bit2);
  bitWrite(inputsState, 2, bit3);
}
