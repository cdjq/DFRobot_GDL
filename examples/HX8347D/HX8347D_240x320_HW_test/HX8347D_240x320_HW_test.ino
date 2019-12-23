#include "DFRobot_GDL.h"
#if defined(ESP32)||defined(ESP8266)
#define DC  D4
#define CS  D5
#define RST D6
#else
#define DC  4
#define CS  5
#define RST 6
#endif

DFRobot_HX8347D_240x320_HW_SPI screen(DC,CS,RST);
void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  Serial.begin(115200);
  screen.begin();
}

void loop() {
screen.fillScreen(0xF800);
screen.fillScreen(0x07E0);
screen.fillScreen(0x001F);
}
