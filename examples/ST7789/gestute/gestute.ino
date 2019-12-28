/*!
 * @file bar.ino
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
   * @param the sTheme_t类型数据，包含了了两种主题，主要是颜色和按钮验收的不同
   * @n   the 的参数 ：THEME1,
                     ：THEME2,
   */
  ui.setTheme(DFRobot_UI::THEME2);
  ui.begin();
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
     * @n      NONE ：没有手势
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