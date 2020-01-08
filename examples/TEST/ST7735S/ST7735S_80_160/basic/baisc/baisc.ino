#include "DFRobot_GDL.h"
#define CS  D3
#define DC  D2
#define RST D4



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
DFRobot_ST7735S_80x160 screen(DC, CS, RST, D1);
  screen.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
