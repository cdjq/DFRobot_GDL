/*!
 * @file UI_bar.ino
 * @brief 在屏幕上创建一个进度条控件，用户可以自定义进度条的参数，也可以使用默认的参数
 * @n 用户可以通过进度条的回调函数控制进度条的值
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
 * @brief Constructor  当屏采用硬件SPI通信，驱动IC是st7789，屏幕分辨率是240x320时，可以调用此构造函数
 * @param dc  SPI通信的命令/数据线引脚
 * @param cs  SPI通信的片选引脚
 * @param rst  屏的复位引脚
 */
DFRobot_ST7789_240x240_HW_SPI screen(TFT_DC,TFT_CS,TFT_RST,TFT_BL);
/*M0主板下DMA传输*/
//DFRobot_ST7789_240x240_DMA_SPI screen(TFT_DC,TFT_CS,TFT_RST,TFT_BL);

/**
 * @brief 构造函数
 * @param gdl 屏幕对象
 * @param width 屏幕的宽度.
 * @param height 屏幕的高度.
 */
DFRobot_UI ui(&screen, /*width=*/240,/*height=*/240);

  /*!
    sBar_t结构体里面的参数如下
    posx:进度条在x轴的坐标
    posy：进度条在y轴的坐标
    width：进度条的宽度
    height：进度条的高度
    fgColor ：进度条前景颜色
    bgColor：进度条背景颜色
    sliderPos：进度条的进度的x坐标
    callBack ：进度条回调函数的函数指针
    lastValue ：进度条上一次的进度
    value ：进度条的进度(0~99)
  */
DFRobot_UI::sBar_t bar1,bar2,bar3;

/**
 * @brief 进度条的回调函数
 * @n 引发进度条发生改变的事件应该写在里面
 */
void barCallback1(){
    //自动让进度条值每次+1;
    delay(50);
    bar1.value += 1;

}
void barCallback2(){
    //自动让进度条值每次+1;
    delay(50);
    bar2.value += 1;

}
void barCallback3(){
    //自动让进度条值每次+1;
    delay(50);
    bar3.value += 1;

}

void setup()
{
  
  Serial.begin(9600);
  //初始化显示屏幕
  screen.begin();
  /**
   * @brief 设置UI的主题
   * @param the eTheme_t类型数据，包含了了两种主题，主要是颜色和按钮验收的不同
   * @n   the 的参数 ：CLASSIC,
                     ：MODERN,
   */
  ui.setTheme(DFRobot_UI::MODERN);
  ui.begin();

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
  ui.drawString(10,200,"Page of loading",WHITE_RGB565,DARKGREY_RGB565,2,0);

  /**
   * @brief 在屏幕上创建一个进度条
   * @param bar sBar_t类型的数据
   * @n 用户可以自定义结构体里面的数据或者使用经初始化的参数
   */
  ui.initBar(&bar1);
  /**用户自定义进度条参数*/
  bar1.posx = 10;
  bar1.posy = 40;
  bar1.mode =0;
  bar1.callBack = barCallback1;

  /**
   * @brief 在屏幕上创建一个进度条
   * @param bar sBar_t类型的数据
   * @n 用户可以自定义结构体里面的数据或者使用经初始化的参数
   */
  ui.creatBar(&bar1);

  ui.initBar(&bar2);
  /**用户自定义进度条参数*/
  bar2.posx = 50;
  bar2.posy = 100;
  bar2.mode =1;
  bar2.callBack = barCallback2;

  /**
   * @brief 在屏幕上创建一个进度条
   * @param bar sBar_t类型的数据
   * @n 用户可以自定义结构体里面的数据或者使用经初始化的参数
   */
  ui.creatBar(&bar2);

  ui.initBar(&bar3);
  /**用户自定义进度条参数*/
  bar3.posx = 10;
  bar3.posy = 160;
  bar3.mode =2;
  bar3.callBack = barCallback3;

  /**
   * @brief 在屏幕上创建一个进度条
   * @param bar sBar_t类型的数据
   * @n 用户可以自定义结构体里面的数据或者使用经初始化的参数
   */
  ui.creatBar(&bar3);
}


void loop()
{
  /**
   * @brief 刷新进度条
   * @param bar sBar_t，里面包含了进度条的位置，长度和宽度等参数
   */
  ui.refreshBar(&bar1);
  ui.refreshBar(&bar2);
  ui.refreshBar(&bar3);
}