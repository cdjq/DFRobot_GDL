#include "DFRobot_Touch.h"
#define TOUCH_CS 3

//DFRobot_Touch_GTXXXX touch;
DFRobot_Touch_XPT2046 touch1(TOUCH_CS);
void setup() {
  Serial.begin(115200); 
  //touch.begin();
  touch1.begin();
}

void loop() {
  //Serial.println(touch.scan());
  //touch1.scan();
 Serial.println(touch1.scan());
 delay(1000);
  
}
