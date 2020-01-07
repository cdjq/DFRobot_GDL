/*!
 * @file ChineseFont.ino
 * @brief 演示不同自带英文字库效果 
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [LuoYufeng](yufeng.luo@dfrobot.com)
 * @version  V0.1
 * @date  2020-01-07
 * @url https://github.com/DFRobot/DFRobot_GDL
 */
 
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
  screen.setTextSize(4);
  screen.fillScreen(65535);
  screen.setFonts(&SIMKAIFont48pt);
  screen.setCursor(10,120);
  screen.setTextColor(65535);
  screen.setTextWrap(true);
  screen.print("你好");
  delay(2000);
  screen.fillScreen(65535);
  screen.setFonts(&SIMKAIFont24pt);
  screen.setCursor(10,120);
  screen.setTextColor(65535);
  screen.setTextWrap(true);
  screen.print("你好");
  delay(2000);
  screen.fillScreen(65535);
  screen.setFonts(&SIMKAIFont36pt);
  screen.setCursor(10,120);
  screen.setTextColor(65535);
  screen.setTextWrap(true);
  screen.print("你好");
  delay(2000);
  screen.fillScreen(65535);
  screen.setFonts(&SIMKAIFont72pt);
  screen.setCursor(10,120);
  screen.setTextColor(65535);
  screen.setTextWrap(true);
  screen.print("你好");
  delay(2000);
}

void loop() {
}
