/*!
 * @file contal.ino
 * @brief 在屏幕上创建一个开关，文本框和滑条控件，用户可以这些控件的参数，也可以使用默认的参数
 * @n 当用户使用控件时，会在文本框显示你当前的操作
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
DFRobot_ST7789_240x240_HW_SPI screen(TFT_DC,TFT_CS,TFT_RST,TFT_BL);

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

/**
 * @brief 触摸扫描函数，扫描出触摸点的信息
 * @return 返回包含点坐标信息的字符串
 * @n 字符串的信息格式"id,x1,y1,width,height "
 * @n id:点的id
 * @n x1：第一个点的x坐标
 * @n y1：第一个点的y坐标
 * @n width ：触摸到的范围的宽度
 * @n height ：触摸的范围的高度
 */
String scan() {
  return touch.scan();
}

/**
 * @brief 滑条的回调函数，当进度条的进度值发生改变时，会进入此回调函数
 * @param value 进度条的值
 * @n 回调函数里面发生的事件，用户需自定义
 */
void changeColor(uint16_t value) {
  char str[3];
  itoa((int)value, str, 10);

  memcpy(tb.text, "slider's value is ", 19);
  memcpy(tb.text + 19, "\0", 1);
  memcpy(tb.text + 18, str, 3);
  ui.setText(&tb,tb.text);
}

/**
 * @brief 开关的回调函数，当开关的状态发生改变时，会进入此回调函数
 * @param state 进度条的值
 * @n 回调函数里面发生的事件，用户需自定义
 */
void swCallBack(uint8_t state) {
  if (state == 0) {
    memcpy(tb.text, "you have turn off the Switch!", 29);
    /**
     * @brief 让文本框显示字符串，
     * @param tb sTextBox_t 类型的结构体
     * @param text 需要让文本框显示的字符
     */
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

  /**
   * @brief 注册一个触摸函数
   * @param fuc 用户自定义的一个函数的指针，类型须于scanF保持一致
   */
  ui.setTouchFunction(scan);

  /**
   * @brief 设置UI的主题
   * @param the eTheme_t类型数据，包含了了两种主题，主要是颜色和按钮验收的不同
   * @n   the 的参数 ：CLASSIC,
                     ：MODERN,
   */
  ui.setTheme(DFRobot_UI::MODERN);
  ui.begin();

  /**
   * @brief 初始化滑条控件
   * @param slider 用户创建的存储滑条参数的结构体变量
   * @n 用户如果需要可以自定义这些参数
   */
  ui.initSlider(&slider);
  //自定义滑条参数
  slider.posx = 10;
  slider.posy = 200;
  slider.callBack = changeColor;
  
  /**
   * @brief 在屏幕上创建一个滑条
   * @param slider sSlider_t类型的数据
   * @n 用户可以自定义结构体里面的数据或者使用经初始化的参数
   */
  ui.creatSlider(&slider);
  
  /**
   * @brief 初始化开关控件,对开关的某些参数进行初始化
   * @param sw sSwitch_t 类型的结构体
   * @n 里面的参数配置都是默认的，如果用户需要自定义可以直接修改结构体里面的参数
   */
  ui.initSwitch(&sw);
  sw.posx = 45;
  sw.posy = 160;
  sw.callBack = swCallBack;
 
  /**
   * @brief 创建一个开关控件
   * @param sw sSwitch_t 类型的结构体
   */
  ui.creatSwitch(&sw);
  /**
   * @brief 初始化文本框控件,对文本框的某些参数进行初始化
   * @param tb sTextBox_t 类型的结构体
   * @n 里面的参数配置都是默认的，如果用户需要自定义可以直接修改结构体里面的参数
   */
  ui.initText(&tb);
  memcpy(tb.text, "please enter text", 17);
  /**
   * @brief 创建一个文本框，
   * @param tb sTextBox_t 类型的结构体，
   */
  ui.creatText(&tb);
}


void loop()
{
  /**
   * @brief 更新触摸点的数据
   */
  ui.updateCoordinate();
  
  /**
   * @brief 刷新滑条
   * @param slider sSlider_t，里面包含了滑条的位置，长度和宽度等参数
   */
  ui.refreshSliser(&slider);
  /**
   * @brief 刷新开关控件
   * @param sw sSwitch_t，里面包含了开关的位置，长度和宽度等参数
   * @n 当某事件产生，会进入开关的回调函数
   */
  ui.refreshSwitch(&sw );

  /**
   * @brief 刷新文本框
   * @param te sTextBox_t，里面包含了开关的位置，长度和宽度等参数
   * @n 可以对文本框的操作有：
     @n                    1.让文本框显示字符串
     @n                    2.在文本框添加一个字符
     @n                    2.在文本框删除一个字符
   */
  ui.refreshTextBox(&tb);
}