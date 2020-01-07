/*!
 * @file font.ino
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
  screen.setTextSize(2);
  screen.fillScreen(0);
  screen.setFont(&FreeMono12pt7b);
  screen.setCursor(10,120);
  screen.setTextColor(255);
  screen.setTextWrap(true);
  screen.print("This is");
  delay(500);
  screen.fillScreen(0);
  screen.setFont(&FreeMonoBold12pt7b);
  screen.setCursor(10,120);
  screen.setTextColor(65504);
  screen.setTextWrap(true);
  screen.print("a function");
  delay(500);
  screen.fillScreen(0);
  screen.setFont(&FreeMonoBoldOblique12pt7b);
  screen.setCursor(10,160);
  screen.setTextColor(63488);
  screen.setTextWrap(true);
  screen.print("of every fonts");
  delay(500);
  screen.fillScreen(0);
  screen.setFont(&FreeMonoOblique12pt7b);
  screen.setCursor(80,160);
  screen.setTextColor(127);
  screen.setTextWrap(true);
  screen.print("You");
  delay(500);
  screen.fillScreen(0);
  screen.setFont(&FreeSans12pt7b);
  screen.setCursor(80,120);
  screen.setTextColor(255);
  screen.setTextWrap(true);
  screen.print("can");
  delay(500);
  screen.fillScreen(0);
  screen.setFont(&FreeSansBold12pt7b);
  screen.setCursor(60,120);
  screen.setTextColor(63488);
  screen.setTextWrap(true);
  screen.print("change");
  delay(500);
  screen.fillScreen(0);
  screen.setFont(&FreeSansBoldOblique12pt7b);
  screen.setCursor(80,120);
  screen.setTextColor(127);
  screen.setTextWrap(true);
  screen.print("all");
  delay(500);
  screen.fillScreen(0);
  screen.setFont(&FreeSansOblique12pt7b);
  screen.setCursor(80,120);
  screen.setTextColor(255);
  screen.setTextWrap(true);
  screen.print("the");
  delay(500);
  screen.fillScreen(0);
  screen.setFont(&FreeSerif12pt7b);
  screen.setCursor(80,60);
  screen.setTextColor(65504);
  screen.setTextWrap(true);
  screen.print("fonts");
  delay(500);
  screen.fillScreen(0);
  screen.setFont(&FreeSerifBold12pt7b);
  screen.setCursor(50,60);
  screen.setTextColor(255);
  screen.setTextWrap(true);
  screen.print("just");
  delay(500);
  screen.fillScreen(0);
  screen.setFont(&FreeSerifBoldItalic12pt7b);
  screen.setCursor(20,50);
  screen.setTextColor(255);
  screen.setTextWrap(true);
  screen.print("like");
  delay(500);
  screen.fillScreen(0);
  screen.setFont(&FreeSerifItalic12pt7b);
  screen.setCursor(20,80);
  screen.setTextColor(63488);
  screen.setTextWrap(true);
  screen.print("demo");
  delay(500);
}

void loop() {
}
