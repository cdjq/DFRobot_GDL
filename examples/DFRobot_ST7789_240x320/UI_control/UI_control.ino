/*!
 * @file UI_contal.ino
 * @brief 在屏幕上创建一个开关，文本框和滑条控件，用户可以这些控件的参数，也可以使用默认的参数
 * @n 当用户使用控件时，会在文本框显示你当前的操作
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
  滑块的参数如下：
  posx:滑条在x轴的坐标
  posy：滑条在y轴的坐标
  sliderHeight:滑块的高度
  sliderWidth：滑块的宽度
  fgColor：前景颜色
  bgColor：背景颜色
  width：宽度
  height ：高度
  range：范围
  lastsliderPos ：滑块上一次的位置(y坐标)
  sliderPos：滑块的位置
  value：滑块的值
  change：滑块值是否发生改变的标志
  callBack:滑块回调函数的指针
*/
DFRobot_UI::sSlider_t slider ;

/*!
  开关控件的参数 sSwitch_t类型，参数如下
  posx ：开关在x轴的坐标
  posy ：开关在y轴的坐标
  width ：开关的宽度
  height ：开关的高度
  fgColor ：开关的前景色
  bgColor ： 开关的背景色
  change ：开关是否改变的标准
  laststate：开关的上一次的状态
  state ：开关的状态(on / off)
  callBack : 回调函数的指针
*/
DFRobot_UI::sSwitch_t sw;

/*!
  文本框参数如下：
  posx :文本框在x轴的坐标
  posy ：文本框在y轴的坐标
  width ：文本框的宽度
  height：文本框的高度
  fgColor ：文本框内字体的前景的颜色
  bgColor：文本框内字体的背景颜色
  fontSize:文本框内字体的大小
  state：文本框的状态
  cache ：文本框添加一个字符的缓存
  text[40] ：文本框内容
  cursorx ：文本框光标在x轴的坐标
  cursory ：文本框光标在y轴的坐标
*/
DFRobot_UI::sTextBox_t tb;

//触摸扫描函数
String scan() {
  return touch.scan();
}

//滑条控件的回调函数
void changeColor(uint16_t value) {
  char str[3];
  itoa((int)value, str, 10);
  memcpy(tb.text, "slider's value is ", 19);
  memcpy(tb.text + 19, "\0", 1);
  memcpy(tb.text + 18, str, 3);
  ui.setText(&tb,tb.text);
}

//开关控件的回调函数
void swCallBack(uint8_t state) {
  if (state == 0) {
    memcpy(tb.text, "you have turn off the Switch!", 29);
    //使文本框显示特定的字符串
    ui.setText(&tb,tb.text);
  }
  else if (state == 1) {
    memcpy(tb.text, "you have turn on the Switch!", 28);
    ui.setText(&tb,tb.text);
  }
}
void setup()
{

  Serial.begin(9600);
  //初始化触摸屏幕
  touch.begin();
  //初始化显示屏幕
  screen.begin();

  //注册一个触摸扫描函数
  ui.setTouchFunction(scan);

  // 设置UI的主题，有两种主题可供选择 1.CLASSIC ，2.MODERN。
  ui.setTheme(DFRobot_UI::MODERN);
  ui.begin();

  //初始化滑条控件，对滑条的参数进行初始化赋值
  ui.initSlider(&slider);
  //自定义滑条参数
  slider.posx = 10;
  slider.posy = 200;
  slider.callBack = changeColor;
  
  //在屏幕上创建一个滑条控件，根据自定义或初始化的参数绘制滑条
  ui.creatSlider(&slider);
  
  //初始化开关控件，对开关的参数进行初始化赋值
  ui.initSwitch(&sw);
  sw.posx = 45;
  sw.posy = 160;
  sw.callBack = swCallBack;
 
  //在屏幕上创建一个开关控件，根据自定义或初始化的参数绘制开关
  ui.creatSwitch(&sw);
  //初始化文本框控件，对文本框的参数进行初始化赋值
  ui.initText(&tb);
  memcpy(tb.text, "please enter text", 17);
  //在屏幕上创建一个文本框控件，根据自定义或初始化的参数绘制文本框
  ui.creatText(&tb);
}


void loop()
{
  /**
   * @brief 更新触摸点的数据
   */
  ui.updateCoordinate();
  
  //刷新滑条
  ui.refreshSliser(&slider);
  //刷新开关
  ui.refreshSwitch(&sw );

  //刷新文本框
  ui.refreshTextBox(&tb);
}