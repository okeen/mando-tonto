#include <SoftwareSerial.h>

#define RADIO_RX_PIN       2   
#define RADIO_TX_PIN       3

SoftwareSerial radioSerial(RADIO_RX_PIN, RADIO_TX_PIN);

void setupRadio() {
  radioSerial.begin(9600);
  # if defined(DEBUG_MODE)  
    Serial.println("Radio INIT done");
  # endif  
  
}

void sendStateByRadio() {
  
  if ((radioSerial.available() >= 0)) {
    
    # if defined(DEBUG_MODE)
      Serial.print(modesState , BIN);
      Serial.print('-');
      Serial.print(controlsState , BIN);
      Serial.print('-');
      Serial.println(joystickState , BIN); 
      Serial.println("SENDING");   
    # endif  
    
    radioSerial.write(0xAF);
    radioSerial.write(modesState);
    radioSerial.write(controlsState);
    radioSerial.write(joystickState);
    radioSerial.write(0xFA);    
    
    lastModesState = modesState;
    lastControlsState = controlsState;
    lastJoystickState = joystickState;
  }    
}
