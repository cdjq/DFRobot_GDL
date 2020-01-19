/*!
 * @file ChineseFont.ino
 * @brief 演示不同自带中文字库效果 
 * @n 本示例支持的主板有Arduino Uno, Leonardo, Mega2560, ESP32, ESP8266, FireBeetle-M0
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
/*ESP32 and ESP8266*/
#elif defined(ESP32) || defined(ESP8266)
#define TFT_DC  D3
#define TFT_CS  D4
#define TFT_RST D5
/*AVR系列主板*/
#else
#define TFT_DC  2
#define TFT_CS  3
#define TFT_RST 4
#endif

/**
 * @brief Constructor  硬件SPI通信的构造函数
 * @param dc  SPI通信的命令/数据线引脚
 * @param cs  SPI通信的片选引脚
 * @param rst  屏的复位引脚
 */
DFRobot_ST7789_240x240_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
//DFRobot_ST7789_240x320_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
/*M0主板下DMA传输*/
//DFRobot_ST7789_240x240_DMA_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
//DFRobot_ST7789_240x320_DMA_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);

/*
 *可供用户选择的宏定义颜色
 *COLOR_RGB565_BLACK   COLOR_RGB565_NAVY    COLOR_RGB565_DGREEN   COLOR_RGB565_DCYAN 
 *COLOR_RGB565_MAROON  COLOR_RGB565_PURPLE  COLOR_RGB565_OLIVE    COLOR_RGB565_LGRAY     
 *COLOR_RGB565_DGRAY   COLOR_RGB565_BLUE    COLOR_RGB565_GREEN    COLOR_RGB565_CYAN  
 *COLOR_RGB565_RED     COLOR_RGB565_MAGENTA COLOR_RGB565_YELLOW   COLOR_RGB565_ORANGE           
 *COLOR_RGB565_WHITE   
 */


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  screen.begin();
}

void loop() {
  //设置字体字号为4 字号范围1-4
  screen.setTextSize(4);
  /*设置屏幕颜色*/
  screen.fillScreen(COLOR_RGB565_WHITE);
  //设置字体文件
  screen.setFont(&SIMKAIFont12pt);
  
  /*
   *@brief 设置文本位置
   *@param x 文本第一个字横坐标
   *@param y 文本第一个字纵坐标
   */
  screen.setCursor(/*x=*/10,/*y=*/120);
  //设置文本颜色
  //可选颜色列表和fillScreen函数中使用的颜色列表相同
  screen.setTextColor(COLOR_RGB565_WHITE); 
  //设置文本自动换行模式
  //true=文本自动换行，false=不自动换行
  screen.setTextWrap(true);
  // 输出文本  
  screen.print("你好");
  delay(2000);
  
  //使用SIMKAIFont48pt字体
  screen.fillScreen(COLOR_RGB565_WHITE);
  screen.setFont(&SIMKAIFont48pt);
  screen.setCursor(10,120);
  screen.setTextColor(COLOR_RGB565_WHITE);
  screen.setTextWrap(true);
  screen.print("你好");
  delay(2000);
  
  //使用SIMKAIFont18pt字体
  screen.fillScreen(COLOR_RGB565_WHITE);
  screen.setFont(&SIMKAIFont18pt);
  screen.setCursor(10,120);
  screen.setTextColor(COLOR_RGB565_WHITE);
  screen.setTextWrap(true);
  screen.print("你好");
  delay(2000);
  
  //使用SIMKAIFont24pt字体
  screen.fillScreen(COLOR_RGB565_WHITE);
  screen.setFont(&SIMKAIFont24pt);
  screen.setCursor(10,120);
  screen.setTextColor(COLOR_RGB565_WHITE);
  screen.setTextWrap(true);
  screen.print("你好");
  delay(2000);
  
  //使用SIMKAIFont36pt字体
  screen.fillScreen(COLOR_RGB565_WHITE);
  screen.setFont(&SIMKAIFont36pt);
  screen.setCursor(10,120);
  screen.setTextColor(COLOR_RGB565_WHITE);
  screen.setTextWrap(true);
  screen.print("你好");
  delay(2000);
  
  //使用SIMKAIFont72pt字体
  screen.fillScreen(COLOR_RGB565_WHITE);
  screen.setFont(&SIMKAIFont72pt);
  screen.setCursor(10,120);
  screen.setTextColor(COLOR_RGB565_WHITE);
  screen.setTextWrap(true);
  screen.print("你好");
  delay(2000);
}
