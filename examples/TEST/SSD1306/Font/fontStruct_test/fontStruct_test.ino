#include "DFRobot_GDL.h"

DFRobot_SSD1306_128x32_HW_IIC  screen;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  screen.begin();
  screen.fillScreen(COLOR_RGB565_BLACK);
  screen.setFont(&FreeMono12pt7b);
  screen.print("efag");
  screen.setFont(&SIMKAIFont12pt);
  screen.setTextColor(COLOR_RGB565_RED);
  screen.print("你好，世界！");
  screen.update();
}

void loop() {
  // put your main code here, to run repeatedly:

}