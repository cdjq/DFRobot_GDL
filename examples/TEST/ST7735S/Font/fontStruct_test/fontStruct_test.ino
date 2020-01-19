#include "DFRobot_GDL.h"
#if defined(ESP8266)||defined(ESP32)
#define DC  D3
#define CS  D4
#define RST D5
#define BL  D6
#else
#define DC  2 
#define CS  3
#define RST 5
#define BL  6
#endif

DFRobot_ST7735S_80x160_HW_SPI screen(DC,CS,RST,BL);
uint16_t unicodeArray[0];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  screen.begin();
  screen.fillScreen(COLOR_RGB565_BLACK);
  screen.setFont(&SIMKAIFont18pt);
  screen.setTextColor(COLOR_RGB565_RED);
  screen.print("你好，世界！");
  #ifdef ARDUINO_SAM_ZERO
  SerialUSB.print("位图数据(字节): ");
  SerialUSB.println(sizeof(SIMKAIFont48ptBitmaps));
  SerialUSB.print("字形数据(字节): ");
  SerialUSB.println(sizeof(SIMKAIFont48ptGlyphs));
  SerialUSB.print("SIMKAIFont48pt结构体变量占用的字节为:  ");
  SerialUSB.println(sizeof(SIMKAIFont48pt));
  SerialUSB.print("unicode:  ");
  SerialUSB.println(sizeof(unicodeArray));
  #else
  Serial.print("位图数据(字节): ");
  Serial.println(sizeof(SIMKAIFont48ptBitmaps));
  Serial.print("字形数据(字节): ");
  Serial.println(sizeof(SIMKAIFont48ptGlyphs));
  Serial.print("SIMKAIFont48pt结构体变量占用的字节为:  ");
  Serial.println(sizeof(SIMKAIFont48pt));
  Serial.print("unicode:  ");
  Serial.println(sizeof(unicodeArray));
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:

}
