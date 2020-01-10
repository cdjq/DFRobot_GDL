/*!
 * @file UI_tableview.ino
 * @brief 在屏幕上创建一个table控件，用户可以自定义进度条的参数
 * @n 用户可以选择不同的页来显示不同的内容
 * @n 本示例支持的主板有arduino uno，esp8266，esp32，leonardo，M0，mega2560.
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
DFRobot_ST7789_240x320_HW_SPI screen(TFT_DC,TFT_CS,TFT_RST,TFT_BL);
/*M0主板下DMA传输*/
//DFRobot_ST7789_240x320_DMA_SPI screen(TFT_DC,TFT_CS,TFT_RST,TFT_BL);

/**
 * @brief 构造函数
 * @param gdl 屏幕对象
 * @param width 屏幕的宽度.
 * @param height 屏幕的高度.
 */
DFRobot_UI ui(&screen, /*width=*/240,/*height=*/320);
/*!
  offset : table间的间距
  text[4] ：每个table相当与一个按钮
  numPage ：table的个数
  highLightPage ：高亮的table
  callback ：tableview的回调函数
*/
//创建 sTableview_t类型的结构体变量，用来定义tableview的参数.
DFRobot_UI::sTableview_t tv;

//触摸扫描函数，扫描出触摸点的信息
String scan() {
  return touch.scan();
}
// tableview的回调函数
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
    ui.drawString(10, 200, "this is tab1", WHITE_RGB565, ui.bgColor, 3, 0);
  }
  if (highLightPage == 2) {
    ui.drawString(10, 200, "this is tab2", WHITE_RGB565, ui.bgColor, 3, 0);
  }
  if (highLightPage == 3) {
    ui.drawString(10, 200, "this is tab3", WHITE_RGB565, ui.bgColor, 3, 0);
  }
}

void setup()
{
  Serial.begin(9600);
  touch.begin();
  screen.begin();
  // 注册一个触摸扫描函数
  ui.setTouchFunction(scan);
  
  // 设置UI的主题，有两种主题可供选择 1.CLASSIC ，2.MODERN。
  ui.setTheme(DFRobot_UI::MODERN);
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
  /**
   * @brief 更新触摸点的数据
   */
  ui.updateCoordinate();
  //刷新tableview
  ui.refreshTableview(&tv);
}