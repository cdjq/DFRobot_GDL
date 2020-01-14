#include "DFRobot_GDL.h"
#if defined(ESP8266)||defined(ESP32)
#define DC  D3
#define CS  D4
#define RST D5
#define BL  D6
#else
#define DC  2 
#define CS  3
#define RST 5
#define BL  6
#endif

DFRobot_ST7789_240x240_HW_SPI tft(DC,CS,RST,BL);
void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   Serial.println("++++++++++++++++");
   tft.begin();
   tft.fillScreen(COLOR_RGB565_BLACK);
   tft.println("Hello World!");
   tft.setCursor(0, 30);
   tft.setTextColor(COLOR_RGB565_RED);
   tft.setTextSize(1);
   tft.println("Hello World!");
   tft.setTextColor(COLOR_RGB565_YELLOW);
   tft.setTextSize(2);
   tft.println("Hello World!");
   tft.setTextColor(COLOR_RGB565_GREEN);
   tft.setTextSize(3);
   tft.println("Hello World!");
   tft.setTextColor(COLOR_RGB565_BLUE);
   tft.setTextSize(4);
   tft.print(1234.567);
}

void loop() {
  // put your main code here, to run repeatedly:
  tft.invertDisplay(true);
  delay(500);
  tft.invertDisplay(false);
  delay(500);
}
