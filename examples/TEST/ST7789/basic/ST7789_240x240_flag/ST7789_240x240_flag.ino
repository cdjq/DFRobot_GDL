#include "DFRobot_GDL.h"
//#define DC  D3
//#define CS  D4
//#define RST D5
//#define BL  D6
#if defined(__AVR__)
#define DC  2
#define CS  3
#define RST 4
#define BL  5
#elif defined(ESP8266)
#define DC  D2
#define CS  D3
#define RST D4
#define BL  D5
#elif defined(NRF5) || defined(ESP_PLATFORM)
#define DC  D2
#define CS  D3
#define RST D4
#define BL  D5
#endif
DFRobot_ST7789_240x240_HW_SPI screen(DC,CS,RST,BL);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  screen.begin();
  screen.fillScreen(63488);
  screen.fillTriangle(35,100,56,85,56,34,65504);
  screen.fillTriangle(77,100,56,85,56,34,65504);
  screen.fillTriangle(22,60,56,85,90,60,65504);
  screen.fillTriangle(115,100,122,95,122,78,65504);
  screen.fillTriangle(129,100,122,95,122,78,65504);
  screen.fillTriangle(111,87,122,95,133,87,65504);
  screen.fillTriangle(115,60,122,55,122,38,65504);
  screen.fillTriangle(129,60,122,55,122,38,65504);
  screen.fillTriangle(111,47,122,55,133,47,65504);
  screen.fillTriangle(85,30,92,25,92,8,65504);
  screen.fillTriangle(99,30,92,25,92,8,65504);
  screen.fillTriangle(81,17,92,25,103,17,65504);
  screen.fillTriangle(85,130,92,125,92,108,65504);
  screen.fillTriangle(99,130,92,125,92,108,65504);
  screen.fillTriangle(81,117,92,125,103,117,65504);
}

void loop() {
}
