/*!
 * @file bar.ino
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

//自定义通信引脚CS,DC
#define SPI_CS 3
#define SPI_DC 4

DFRobot_Touch_XPT2046 touch(/*cs=*/2); 

DFRobot_ST7789_240x320_HW_SPI screen(SPI_DC,SPI_CS);
/**
 * @brief 构造函数
 * @param gdl 屏幕对象
 * @param width 屏幕的宽度.
 * @param height 屏幕的高度.
 */
DFRobot_UI ui(&screen, /*width=*/240,/*height=*/320);

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
DFRobot_UI::sBar_t bar;

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
 * @brief 进度条的回调函数
 * @n 引发进度条发生改变的事件应该写在里面
 */
void barCallback(){
    //自动让进度条值每次+1;
    bar.value += 1;
   
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
   * drawString：绘制字符串
   * @param x 所需绘制字符串在屏幕上的x坐标
   * @param y 所需绘制字符串在屏幕上的x坐标
   * @param c 字符数组的指针
   * @param color 字体的颜色
   * @param bg 字体背景的颜色
   * @param size 字体的大小
   * @param mode 字体显示模式
   * @n mode  0 ： 正常显示
   *          1 ： 颜色反转
   */
  ui.drawString(10,100,"Page of loading",0xffff,DARKGREY_RGB565,2,0);

  /**
   * @brief 在屏幕上创建一个进度条
   * @param bar sBar_t类型的数据
   * @n 用户可以自定义结构体里面的数据或者使用经初始化的参数
   */
  ui.initBar(&bar);
  /**用户自定义进度条参数*/
  bar.posx = 50;
  bar.posy = 160;
  bar.callBack = barCallback;

  /**
   * @brief 在屏幕上创建一个进度条
   * @param bar sBar_t类型的数据
   * @n 用户可以自定义结构体里面的数据或者使用经初始化的参数
   */
  ui.creatBar(&bar);
}


void loop()
{
  /**
   * @brief 更新触摸点的数据
   */
  ui.updateCoordinate();

  /**
   * @brief 刷新进度条
   * @param bar sBar_t，里面包含了进度条的位置，长度和宽度等参数
   */
  ui.refreshBar(&bar);
}