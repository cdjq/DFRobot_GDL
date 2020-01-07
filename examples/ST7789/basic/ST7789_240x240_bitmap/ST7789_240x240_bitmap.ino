#include "DFRobot_GDL.h"
#include "kirino.h"
//#define DC  D3
//#define CS  D4
//#define RST D5
//#define BL  D6

#define DC  2
#define CS  3
#define RST 4
#define BL  5

DFRobot_ST7789_240x240_HW_SPI screen(DC,CS,RST,BL);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  screen.begin();
  screen.fillScreen(65535);
  screen.drawRGBBitmap(0,0,(uint16_t*)gImage_kirino,239,240);
  
}

void loop() {
}
