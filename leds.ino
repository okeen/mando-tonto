#define YELLOW_LED  12
#define RED_LED     11
#define GREEN_LED   10
#define BLUE_LED    9

const byte leds[MODE_BUTTONS_COUNT] =  {YELLOW_LED,RED_LED,GREEN_LED,BLUE_LED};      // the number of the LED pin

byte ledMode = PARTY;

void initLeds() {
  for (byte i=0; i < MODE_BUTTONS_COUNT; i ++) {
      pinMode(leds[i], OUTPUT);
  }
  
}
void updateLeds(bool shouldRestartIndex) {
  static byte frameIndex = 0;

  if (shouldRestartIndex) {
    frameIndex = 0;
  }

  switch(ledMode) {
    case RESCUE:
      for (byte i=0;i< 4; i++) {
          digitalWrite(leds[i], bitRead(controlsState, 0));
      }
      break;
    case PARTY:
      digitalWrite(leds[GREEN_LED],  frameIndex % 2 == 0);
      digitalWrite(leds[BLUE_LED],   frameIndex % 2 == 1);
      digitalWrite(leds[RED_LED],    frameIndex % 2 == 0);
      digitalWrite(leds[YELLOW_LED], frameIndex % 2 == 1);      
      break;  
    case SIREN:      
      for (byte i=0;i< 4; i++) {
        digitalWrite(leds[i], frameIndex % 4 == i);
      }
      break;    
    case LIGHTS:      
      digitalWrite(leds[GREEN_LED],  false);
      digitalWrite(leds[BLUE_LED],   true);
      digitalWrite(leds[RED_LED],    true);
      digitalWrite(leds[YELLOW_LED], true);      
      break;    
    default:
      for (byte i=0;i< 4; i++) {
        digitalWrite(leds[i], i == ledMode);
      } 
  }
  
  if (++frameIndex == 64) {
    frameIndex = 0;
  }

}

void setLedsMode(byte mode) {
  ledMode = mode;
  updateLeds(true);
}

void lightLedInNormalMode(byte led) {
  for (byte i=0;i< 4; i++) {
    digitalWrite(leds[i], i == led );
   }

}
