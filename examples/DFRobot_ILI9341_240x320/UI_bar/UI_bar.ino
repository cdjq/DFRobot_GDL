/*!
 * @file UI_bar.ino
 * @brief 在屏幕上创建一个进度条控件，用户可以自定义进度条的参数，也可以使用默认的参数
 * @n 用户可以通过进度条的回调函数控制进度条的值
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
#define TOUCH_CS 2
/*ESP32 and ESP8266*/
#elif defined(ESP32) || defined(ESP8266)
#define TFT_DC  D3
#define TFT_CS  D4
#define TFT_RST D5
#define TOUCH_CS D6
/*AVR系列主板*/
#else
#define TFT_DC  2
#define TFT_CS  3
#define TFT_RST 4
#define TOUCH_CS 5
#endif
/**
 * @brief Constructor  当触摸采用XPT2046芯片时，可以调用此构造函数
 * @param cs  SPI片选信号
 * @param rst  复位信号
 * @param irq  中断信号
 */
DFRobot_Touch_XPT2046 touch(/*cs=*/TOUCH_CS);
 
/**
 * @brief Constructor  当屏采用硬件SPI通信，驱动IC是st7789，屏幕分辨率是240x320时，可以调用此构造函数
 * @param dc  SPI通信的命令/数据线引脚
 * @param cs  SPI通信的片选引脚
 * @param rst  屏的复位引脚
 */
//DFRobot_ILI9341_240x320_HW_SPI screen(TFT_DC,TFT_CS,TFT_RST);
DFRobot_ST7789_240x320_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
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
DFRobot_UI ui(&screen, &touch,/*width=*/240,/*height=*/320);

uint8_t value1 = 0;
uint8_t value2 = 0;
uint8_t value3 = 0;
//进度条bar1的回调函数
void barCallback1(void *obj){
	DFRobot_UI::sObject_t *bar1 = (DFRobot_UI::sObject_t *)obj;
    //自动让进度条值每次+1;
   delay(50);
    ui.setBarValue(bar1,value1);
	if(value1 < 100) value1++;
}
//进度条bar2的回调函数
void barCallback2(void *obj){
	DFRobot_UI::sObject_t *bar2 = (DFRobot_UI::sObject_t *)obj;
    //自动让进度条值每次+1;
    delay(50);
    ui.setBarValue(bar2,value2);
	if(value2 < 100) value2++;
	
}
//进度条bar3的回调函数
void barCallback3(void *obj){
    DFRobot_UI::sObject_t *bar3 = (DFRobot_UI::sObject_t *)obj;
    //自动让进度条值每次+1;
    delay(50);
    ui.setBarValue(bar3,value3);
	if(value3 < 100) value3++;
}
void setup()
{
  
  Serial.begin(9600);
  //ui初始化
  ui.begin();
  ui.setTheme(DFRobot_UI::MODERN);

  //在屏幕上显示字符串
  ui.drawString(/*x=*/10,/*y=*/200,"Page of loading",COLOR_RGB565_WHITE,ui.bgColor,/*fontsize =*/2,/*Invert=*/0);
  //创建一个进度条控件
  DFRobot_UI::sObject_t *bar1 = ui.creatBar();
  /**用户自定义进度条参数*/
  ui.setBarStyle(bar1,0);
  bar1->setCallBack(bar1,barCallback1);
  ui.draw(bar1,10,160);
  
  DFRobot_UI::sObject_t *bar2 = ui.creatBar();
  /**用户自定义进度条参数*/
  ui.setBarStyle(bar2,1);
  bar2->setCallBack(bar2,barCallback2);
  ui.draw(bar2,100,100);

  DFRobot_UI::sObject_t *bar3 = ui.creatBar();
  /**用户自定义进度条参数*/
  ui.setBarStyle(bar3,2);
  bar3->setCallBack(bar3,barCallback3);
  ui.draw(bar3,20,10);
}


void loop()
{
  //刷新所有控件
  ui.refresh();
}