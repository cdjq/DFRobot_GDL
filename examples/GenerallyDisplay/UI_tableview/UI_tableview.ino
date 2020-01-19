/*!
 * @file UI_tableview.ino
 * @brief 在屏幕上创建一个tableview控件，用户可以自定义在屏幕上创建一个tableview控件的参数
 * @n 用户可以选择不同的页来显示不同的内容
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
 * @brief Constructor  当屏采用硬件SPI通信，驱动IC是st7789，屏幕分辨率是240x320时，可以调用此构造函数
 * @param dc  SPI通信的命令/数据线引脚
 * @param cs  SPI通信的片选引脚
 * @param rst  屏的复位引脚
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
DFRobot_UI::sObject_t * tv;
void tbCallback(void * highLightPage){
  uint8_t * hl = (uint8_t *)highLightPage;
  if (*hl == 1) {
    //在屏幕上显示字符串
    ui.drawString(10, 200, "this is tab1", COLOR_RGB565_YELLOW, ui.bgColor, 3, 0);
  }
  if (*hl == 2) {
    ui.drawString(10, 200, "this is tab2", COLOR_RGB565_YELLOW, ui.bgColor, 3, 0);
  }
  if (*hl == 3) {
    ui.drawString(10, 200, "this is tab3", COLOR_RGB565_YELLOW, ui.bgColor, 3, 0);
  }
  if (*hl == 4) {
    ui.drawString(10, 200, "this is tab4", COLOR_RGB565_YELLOW, ui.bgColor, 3, 0);
  }
}
void setup()
{
  
 Serial.begin(9600);

 ui.begin();
  // 设置UI的主题，有两种主题可供选择 1.CLASSIC ，2.MODERN。
 ui.setTheme(DFRobot_UI::MODERN);
 //创建一个tableview控件
 tv = ui.creatTableview();
 //设置tableview的个数 和名字 最大页数为4
 ui.setTableviewName(tv,/*page=*/4,/*page1 name=*/"tab1",/*page2 name=*/"tab2",/*page3 name=*/"tab3",/*page4 name=*/"tab4");
 //设置回调函数
 tv->setCallBack(tv,tbCallback);
 ui.draw(tv);
}
void loop()
{
  for(uint8_t i=1 ; i<5 ;i++ ){
  //刷新
  ui.refresh();
  delay(500);
  ui.changeTableview(tv,i);
  }
}