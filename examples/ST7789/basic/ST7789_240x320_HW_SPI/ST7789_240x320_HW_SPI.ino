#include "DFRobot_GDL.h"
#define DC  D4
#define CS  D5
#define RST D6

DFRobot_ST7789_240x320_HW_SPI screen(DC,CS,RST);
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
