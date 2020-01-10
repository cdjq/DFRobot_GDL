/*!
 * @file ChineseFont.ino
 * @brief 演示不同自带中文字库效果 
 * @      支持Arduino Uno, Leonardo, Mega2560, ESP32, ESP8266, M0
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [LuoYufeng](yufeng.luo@dfrobot.com)
 * @version  V0.1
 * @date  2020-01-07
 * @url https://github.com/DFRobot/DFRobot_GDL
 */
 
#include "DFRobot_GDL.h"
/*M0*/
#if defined ARDUINO_SAM_ZERO
#define TFT_DC  7
#define TFT_CS  5
#define TFT_RST 6
#define TFT_BL  9
/*ESP32 and ESP8266*/
#elif defined(ESP32) || defined(ESP8266)
#define TFT_DC  D3
#define TFT_CS  D4
#define TFT_RST D5
#define TFT_BL  D6
/*AVR系列主板*/
#else
#define TFT_DC  2
#define TFT_CS  3
#define TFT_RST 4
#define TFT_BL  5
#endif
DFRobot_ST7789_240x320_HW_SPI screen(TFT_DC,TFT_CS,TFT_RST,TFT_BL);
/*M0主板下DMA传输*/
//DFRobot_ST7789_240x320_DMA_SPI screen(TFT_DC,TFT_CS,TFT_RST,TFT_BL);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  screen.begin();
}

void loop() {
  /*
   *@brief 设置字体大小
   *@param s 字体字号
   */
  screen.setTextSize(4);
  /*
   *@brief 清屏
   *@param c 屏幕颜色
   */
  screen.fillScreen(COLOR_RGB565_WHITE);
  /*
   *@brief 设置字体
   *@param *f 自制字体文件
   */
  screen.setFonts(&SIMKAIFont12pt);
  /*
   *@brief 设置文本位置
   *@param x 文本第一个字横坐标
   *@param y 文本第一个字纵坐标
   */
  screen.setCursor(10,120);
  /*
   *@brief 设置文本颜色
   *@param c 文本颜色
   */
  screen.setTextColor(COLOR_RGB565_WHITE);
  /*
   *@brief 文本换行
   *@param true=文本换行，false=不换行
   */
  screen.setTextWrap(true);
  /*
   *@brief 输出文本
   */
  screen.print("你好");
  delay(2000);
  screen.fillScreen(COLOR_RGB565_WHITE);
  screen.setFonts(&SIMKAIFont48pt);
  screen.setCursor(10,120);
  screen.setTextColor(COLOR_RGB565_WHITE);
  screen.setTextWrap(true);
  screen.print("你好");
  delay(2000);
  screen.fillScreen(COLOR_RGB565_WHITE);
  screen.setFonts(&SIMKAIFont18pt);
  screen.setCursor(10,120);
  screen.setTextColor(COLOR_RGB565_WHITE);
  screen.setTextWrap(true);
  screen.print("你好");
  delay(2000);
  screen.fillScreen(COLOR_RGB565_WHITE);
  screen.setFonts(&SIMKAIFont24pt);
  screen.setCursor(10,120);
  screen.setTextColor(COLOR_RGB565_WHITE);
  screen.setTextWrap(true);
  screen.print("你好");
  delay(2000);
  screen.fillScreen(COLOR_RGB565_WHITE);
  screen.setFonts(&SIMKAIFont36pt);
  screen.setCursor(10,120);
  screen.setTextColor(COLOR_RGB565_WHITE);
  screen.setTextWrap(true);
  screen.print("你好");
  delay(2000);
  screen.fillScreen(COLOR_RGB565_WHITE);
  screen.setFonts(&SIMKAIFont72pt);
  screen.setCursor(10,120);
  screen.setTextColor(COLOR_RGB565_WHITE);
  screen.setTextWrap(true);
  screen.print("你好");
  delay(2000);
}
