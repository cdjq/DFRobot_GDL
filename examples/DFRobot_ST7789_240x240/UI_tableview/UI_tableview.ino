/*!
 * @file UI_tableview.ino
 * @brief 在屏幕上创建一个table控件，用户可以自定义进度条的参数
 * @n 用户可以选择不同的页来显示不同的内容
 * @n 本示例支持的主板有Arduino Uno, Leonardo, Mega2560, ESP32, ESP8266, FireBeetle-M0
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
#define TFT_BL  9
#define TOUCH_CS 2
/*ESP32 and ESP8266*/
#elif defined(ESP32) || defined(ESP8266)
#define TFT_DC  D2
#define TFT_CS  D3
#define TFT_RST D4
#define TFT_BL  D5
#define TOUCH_CS D6
/*AVR系列主板*/
#else
#define TFT_DC  2
#define TFT_CS  3
#define TFT_RST 4
#define TFT_BL  5
#define TOUCH_CS 6
#endif

/**
 * @brief Constructor  硬件SPI通信的构造函数
 * @param dc  SPI通信的命令/数据线引脚
 * @param cs  SPI通信的片选引脚
 * @param rst  屏的复位引脚
 * @param bl  屏幕的背光引脚
 */
DFRobot_ST7789_240x240_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST,/*bl=*/TFT_BL);
/*M0主板下DMA传输*/
//DFRobot_ST7789_240x240_DMA_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST,/*bl=*/TFT_BL);

/**
 * @brief 构造函数
 * @param gdl 屏幕对象
 * @param width 屏幕的宽度.
 * @param height 屏幕的高度.
 */
DFRobot_UI ui(&screen, /*width=*/240,/*height=*/240);

//创建 sTableview_t类型的结构体对象tv
DFRobot_UI::sTableview_t tv;

/**
 * @brief tableview的回调函数
 * @param highLightPage 被选中的页
 */
void tvCallback(uint8_t highLightPage) {
  
  if (highLightPage == 1) {
  /**
   * drawString：绘制字符串
   * @param x 所需绘制字符串在屏幕上的x坐标
   * @param y 所需绘制字符串在屏幕上的x坐标
   * @param c 字符数组的指针
   * @param color 字体的颜色(RGB565)
   * @param bg 字体背景的颜色(RGB565)
   * @param size 字体的大小
   * @param mode 字体显示模式
   * @n mode  0 ： 正常显示
   *          1 ： 颜色反转
   */
    ui.drawString(/*x=*/10, /*y=*/180, /*c=*/"this is tab1",/*color=*/WHITE_RGB565, /*bg=*/ui.bgColor, /*size=*/3, /*mode=*/0);
  }
  
  //设置tab2
  if (highLightPage == 2) {
    ui.drawString(10, 180, "this is tab2", WHITE_RGB565, ui.bgColor, 3, 0);
  }
  
  //设置tab3
  if (highLightPage == 3) {
    ui.drawString(10, 180, "this is tab3", WHITE_RGB565, ui.bgColor, 3, 0);
  }
}

void setup()
{
  Serial.begin(115200);

  screen.begin();
  
   // 设置UI的主题，有两种主题可供选择 1.CLASSIC ，2.MODERN。
  ui.setTheme(DFRobot_UI::MODERN);
  
  //初始化函数,初始化UI使用到的一些参数 
  ui.begin();
  
  //自定义tableview的页数为三，最大为四
  tv.numPage = 3;
  //定义tableview的回调函数
  tv.callback = tvCallback;
  //设置tableview的内容
  memcpy(tv.text[0].text, "Tab 1", 5);
  memcpy(tv.text[1].text, "Tab 2", 5);
  memcpy(tv.text[2].text, "Tab 3", 5);
  
  //在屏幕上创建一个tableview，根据自定义或初始化的参数绘制tableview
  ui.creatTableview(&tv);
}

void loop()
{
  for(uint8_t i=1 ; i<4 ;i++ ){
  //刷新tableview
  ui.refreshTableview(&tv);
  delay(500);
  ui.changeTableview(&tv,i);
  }
}