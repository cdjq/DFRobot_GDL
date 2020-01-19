#include "DFRobot_GDL.h"

#if defined(ESP8266)||defined(ESP32)
#define DC  D4
#define CS  D5
#define RST D6
#define BL  D7
#else
#define DC  2 
#define CS  3
#define RST 5
#define BL  6
#endif

DFRobot_ILI9341_240x320_HW_SPI screen(DC,CS,RST,BL);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  screen.begin();
}

void loop() {
uint32_t t = millis();
screen.fillScreen(COLOR_RGB565_RED);
#if defined(ARDUINO_SAM_ZERO)
SerialUSB.println(millis()- t);
#else
Serial.println(millis()- t);
#endif
t = millis();
screen.fillScreen(COLOR_RGB565_GREEN);
#if defined(ARDUINO_SAM_ZERO)
SerialUSB.println(millis()- t);
#else
Serial.println(millis()- t);
#endif
t = millis();
screen.fillScreen(COLOR_RGB565_BLUE);
#if defined(ARDUINO_SAM_ZERO)
SerialUSB.println(millis()- t);
#else
Serial.println(millis()- t);
#endif
}
