#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


byte displayMode = PARTY;

void initDisplay() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    # if defined(DEBUG_MODE)  
      Serial.println(F("SSD1306 allocation failed"));
    # endif  
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.drawBitmap(23, 4, logoBMP, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  # if defined(DEBUG_MODE)  
    Serial.println("Display INIT done");
  # endif    
}

void updateDisplay() {
  static byte frameIndex = 0;

//  if (frameIndex % 10 == 0) {
//    display.startscrollleft(0x00, 0x0F);  
//  }
//  
//  if (frameIndex % 10 == 5) {
//    display.startscrollright(0x00, 0x0F);  
//  }

  switch (displayMode) {
    case PARTY:
      display.fillCircle(63, 30, 19,  frameIndex % 2 == 0);
      
      break;
    case RESCUE:
      display.fillCircle(50, 30, 8, SSD1306_WHITE);
      display.fillTriangle(50, 30, 74, 15, 74, 45, SSD1306_WHITE);

      byte color = bitRead(controlsState, 0) ? SSD1306_WHITE : SSD1306_BLACK;
      display.drawLine(80, 12, 90, 9, color);
      display.drawLine(80, 25, 90, 22, color);
      display.drawLine(80, 35, 90, 38, color);
      display.drawLine(80, 48, 90, 51, color);        
      break;  
    
  }
  display.display();
  
  if (++frameIndex == 64) {
    frameIndex = 0;
   }
   
}

void setDisplayMode(byte mode) {
  displayMode = mode;
  
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);

  switch (mode) {
    case BLUE:
      display.drawBitmap(0, 4, chaseBMP, DISPLAY_MODE_BITMAPS_WIDTH, DISPLAY_MODE_BITMAPS_HEIGHT, 1);    
      display.setCursor(65, 28);
      display.println(F("CHASE"));
      break;    
    case GREEN:
      display.drawBitmap(0, 4, rockyBMP, DISPLAY_MODE_BITMAPS_WIDTH, DISPLAY_MODE_BITMAPS_HEIGHT, 1);    
      display.setCursor(65, 28);
      display.println(F("ROCKY"));  
      break;    
    case YELLOW:
      display.drawBitmap(0, 4, rubbleBMP, DISPLAY_MODE_BITMAPS_WIDTH, DISPLAY_MODE_BITMAPS_HEIGHT, 1);    
      display.setCursor(56, 40);
      display.println(F("RUBBLE"));  
      break;    
    case RED:
      display.drawBitmap(0, 4, marshalBMP, DISPLAY_MODE_BITMAPS_WIDTH, DISPLAY_MODE_BITMAPS_HEIGHT, 1);    
      display.setCursor(68, 40);
      display.setTextSize(1); // Draw 2X-scale text
      display.println(F("MARSHAL")); 
      break;
    case SIREN:
      display.drawBitmap(20, 4, logoBMP, LOGO_WIDTH, LOGO_HEIGHT, 1);          
      break;
    case LIGHTS:
      display.fillRoundRect(40, 70, 60, 60, 2, SSD1306_INVERSE);
      break;
    case RESCUE:
      break;
    case PARTY:
      display.fillRect(0, 100, 60, 120,1);
      display.fillRect(43, 30, 40, 90,1);
      display.drawCircle(63, 30, 20, SSD1306_INVERSE);
    
                      
  }
  display.display();
}
