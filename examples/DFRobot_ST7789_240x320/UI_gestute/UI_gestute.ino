/*!
 * @file UI_gestute.ino
 * @brief 在屏幕指定区域可以识别到用户所使用的手势，手势的名称会显示到文本框内
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
   * @brief 初始化文本框控件,对文本框的某些参数进行初始化
   * @param tb sTextBox_t 类型的结构体
   * @n 里面的参数配置都是默认的，如果用户需要自定义可以直接修改结构体里面的参数
   */
  ui.initText(&tb);
  /**
   * @brief 在屏幕上创建一个进度条
   * @param bar sBar_t类型的数据
   * @n 用户可以自定义结构体里面的数据或者使用经初始化的参数
   */
  ui.creatText(&tb);
  /**
   * @brief 设置触摸的手势识别区域
   * @param x 识别区域的开始位置的x坐标
   * @param y 识别区域的开始位置的y坐标
   * @param width 识别区域的宽度
   * @param height 识别区域的高度
   */
  ui.setGestureArea(40,100,150,150);
   //ui.drawString(10, 240,"Gesture recognition areasadasdasdasdasdasd",0xffff, ui.bgColor, 2, 0);
}


void loop()
{
    /**
     * @brief 更新触摸点的数据
     */
    ui.updateCoordinate();
    /**
     * getGestures()： 获取手势
     * @return sGestures_t类型的数据，代表着不同的手势
     * @n      UPGLIDE ：向上滑动
     * @n      DOWNGLIDE ：向下滑动
     * @n      LEFTGLIDE ：向左滑动
     * @n      RIGHTGLIDE ：向右滑动
     * @n      LONGPRESSDE ：长按屏幕
     * @n      SINGLECLICK ：单击屏幕
     * @n      DOUBLECLICK ：双击屏幕
     * @n      NONE ：没有手势或无法识别
      */
    switch(ui.getGestures()){
        /**
         * setText ：让文本框显示字符串，
         * @param tb sTextBox_t 类型的结构体
         * @param text 需要让文本框显示的字符
         */
      case ui.UPGLIDE : ui.setText(&tb,"upwards slide"); break;
      case ui.DOWNGLIDE : ui.setText(&tb,"down slide"); break;
      case ui.LEFTGLIDE : ui.setText(&tb,"left slide"); break;
      case ui.RIGHTGLIDE : ui.setText(&tb,"right slide"); break;
      case ui.LONGPRESSDE : ui.setText(&tb,"long press"); break;
      case ui.SINGLECLICK : ui.setText(&tb,"click"); break;
      case ui.DOUBLECLICK : ui.setText(&tb,"double click"); break;
      default  :  break;
      }
  /**
   * refreshTextBox ： 刷新进度条
   * @param bar sBar_t，里面包含了进度条的位置，长度和宽度等参数
   */
   ui.refreshTextBox(&tb);


   
}