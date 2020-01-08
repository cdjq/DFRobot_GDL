
#include "DFRobot_Touch.h"
DFRobot_Touch_XPTxxx  touch(/*cs =*/10);

uint8_t stringToPoint(String str, uint16_t *point) 
{
  char pin[4];
  uint8_t nowi = 0;
  uint8_t n = 0;
  uint8_t b = 0;
  //Serial.println(str.length());
  for (uint8_t i = 0; i < str.length(); i++) {

    if (str[i] == ',' || str[i] == ' ')
    {
      n = 0;

      if (nowi == 1) point[0] = atoi(pin);
      if (nowi == 2) point[1] = atoi(pin);
      if (nowi == 4) {
        b++;
      }
      nowi++;
      if (nowi == 5)nowi = 0;
      memset(pin, '\0', 4);
      continue;
    }
    pin[n] = str[i];
    n++;
  }

}


void setup()
{

  Serial.begin(9600);
  touch.begin();

}


void loop()
{
 uint16_t point[2];
 String str = touch.scan();
 stringToPoint(str,point);
 Serial.print("(");
 Serial.print(int(point[0]));
 Serial.print(",");
  Serial.print(int(point[1]));
   Serial.println(")");
 delay(1000);
}
