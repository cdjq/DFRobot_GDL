/*!
 * @file UI_login.ino
 * @brief 一个登录的界面
 * @n 本示例支持的主板有Arduino Uno, Leonardo, Mega2560, ESP32, ESP8266, FireBeetle-M0
 *
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2019-12-6
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_GDL/src/DFRpbot_UI
*/

#include "DFRobot_UI.h"
#include "Arduino.h"
#include "DFRobot_GDL.h"
#include "DFRobot_Touch.h"
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
 * @param bl  屏幕的背光引脚
 */
DFRobot_ST7789_240x240_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
//DFRobot_ST7789_240x320_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
/*M0主板下DMA传输*/
//DFRobot_ST7789_240x240_DMA_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
//DFRobot_ST7789_240x320_DMA_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);

/**
 * @brief 构造函数
 * @param gdl 屏幕对象
 * @param touch 触摸对象
 * @param width 屏幕的宽度.
 * @param height 屏幕的高度.
 */
DFRobot_UI ui(&screen, NULL,/*width=*/240,/*height=*/240);

//声明文本框对象tb1,tb2.
DFRobot_UI::sObject_t* tb1, *tb2;
void setup()
{

  Serial.begin(115200);
  
  ui.begin();
  // 设置UI的主题，有两种主题可供选择 1.CLASSIC ，2.MODERN。
  ui.setTheme(DFRobot_UI::MODERN);
 

  //创建一个文本框控件
  tb1 = ui.creatText();
  ui.draw(tb1,/**x=*/30,/**y=*/30,/*width*/180,/*height=*/30);
  
  
  //创建一个文本框控件
  tb2 = ui.creatText();
  ui.draw(tb2,/**x=*/30,/**y=*/80,/*width*/180,/*height=*/30);

  
  //在屏幕上创建一个按钮控件
  DFRobot_UI::sObject_t * btn1 = ui.creatButton();
  //设置按钮的名字
  ui.setButtonText(btn1,"login");
  ui.draw(btn1,/**x=*/30,/**y=*/120,/*width*/180,/*height*/30);
  //创建数字键盘控件
  DFRobot_UI::sObject_t * kp = ui.creatKeyPad();
  //设置数值键盘模式 0：自带文本框,1:需要外部定义文本框
  ui.setKeyPadMode(kp,1);
  ui.draw(kp);
  
  ui.drawString(30, 10, "login interface", COLOR_RGB565_CYAN, ui.bgColor, 2, 0);
}


void loop()
{
  //刷新
  ui.refresh();

}