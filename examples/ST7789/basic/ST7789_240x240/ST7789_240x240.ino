#include "DFRobot_GDL.h"
//#define DC  D3
//#define CS  D4
//#define RST D5
//#define BL  D6

#define DC  D2
#define CS  D3
#define RST D4
#define BL  D5
DFRobot_ST7789_240x240_HW_SPI screen(DC,CS,RST,BL);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  screen.begin();
}

void loop() {
screen.fillScreen(0xF800);
screen.fillScreen(0x07E0);
screen.fillScreen(0x001F);
}
