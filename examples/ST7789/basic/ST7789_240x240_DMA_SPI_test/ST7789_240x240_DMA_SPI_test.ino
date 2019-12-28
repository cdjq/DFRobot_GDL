#include "DFRobot_GDL.h"

#if defined(ESP8266)||defined(ESP32)
#define DC  D4
#define CS  D5
#define RST D6
#define BL  D7
#else
#define DC  4 
#define CS  5
#define RST 6
#define BL  7
#endif

DFRobot_ST7789_240x240_DMA_SPI screen(DC,CS,RST,BL);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  screen.begin();
}

void loop() {
uint32_t t = millis();
screen.fillScreen(0xF800);
SerialUSB.println(millis()- t);
t = millis();
screen.fillScreen(0x07E0);
SerialUSB.println(millis()- t);
t = millis();
screen.fillScreen(0x001F);
SerialUSB.println(millis()- t);
}
