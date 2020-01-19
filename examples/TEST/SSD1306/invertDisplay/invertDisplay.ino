#include "DFRobot_GDL.h"

DFRobot_SSD1306_128x32_HW_IIC oled;
void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   oled.begin();
   oled.fillScreen(0);
   oled.println("Hello World!");
   oled.update();
}

void loop() {
  // put your main code here, to run repeatedly:
  oled.invertDisplay(true);
  delay(500);
  oled.invertDisplay(false);
  delay(500);
}
