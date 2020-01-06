/*!
 * @file button.ino
 * @brief 在屏幕上创建一个按钮控件，用户可以自定义按钮的参数
 * @n 示例里面创建了三个按钮A,B,C,按下A,B按钮会在文本框内显示，按下C按钮会删除文本框的一个字符
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
  sButton_t结构体是存储按钮的参数，里面的参数如下
  posx:按钮在x轴的坐标
  posy：按钮在y轴的坐标
  width ：按钮的宽度
  height ：按钮的高度
  fgColor：按钮的前景色
  bgColor：按钮的背景色
  fontSize：按钮字体的大小
  text[10] ：按钮的名字
  click ：按钮是否被点击的标志
  callBack ：按钮的回电函数的函数指针
*/
DFRobot_UI::sButton_t btn1 ;
DFRobot_UI::sButton_t btn2 ;
DFRobot_UI::sButton_t btn3 ;

  /*!
    文本款的参数如下：
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
 * @brief 按钮的回调函数，当按钮被按下，会进入此回调函数
 * @param text 按钮的名字
 * @n 回调函数里面发生的事件，用户需自定义
 */
void buCallback(char * text) {
  switch (*text) {
    case 'A' : {
        /**
         * @brief 在文本框添加一个字符
         * @param te sTextBox_t 类型的结构体
         * @param txt 需要添加的字符
         */
        ui.textAddChar(&tb,'A');
        break;
      }
    case 'B' : {
        ui.textAddChar(&tb,'B');
        break;
      }
    case 'C' : {
        /**
         * @brief 在文本框删除一个字符
         * @param te sTextBox_t 类型的结构体
         */
        ui.textDeleteChar(&tb);; break;
    }
    default  :  break;
  }

}
void setup()
{

  Serial.begin(9600);
  touch.begin();
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
  ui.setTheme(DFRobot_UI::CLASSIC);
  ui.begin();
  /**
   * @brief 初始化按钮控件的参数
   * @param bu sButton_t类型的结构体数据，存储按钮参数的结构体
   * @n 若用户徐自定义按钮的参数，如长度和宽度等可在此函数后自定义这些数据
   */
  ui.initButton(&btn1);
  /**用户自定义按钮参数*/
  btn1.posx = 100;
  btn1.posy = 220;
  btn1.callBack = buCallback;
  memcpy(btn1.text, "B", 1);
  /**
   * @brief 在屏幕上创建一个按钮控件
   * @param bu sButton_t类型的结构体数据，里面包含了按钮的位置，长度和宽度等参数
   * @n 用户可以自定义这些数据
   */
  ui.creatButton(&btn1);
  
  ui.initButton(&btn2);
  btn2.posx = 30;
  btn2.posy = 220;
  btn2.callBack = buCallback;
  memcpy(btn2.text, "A", 1);
  ui.creatButton(&btn2);

  ui.initButton(&btn3);
  btn3.posx = 170;
  btn3.posy = 220;
  btn3.callBack = buCallback;
  memcpy(btn3.text, "C", 1);
  ui.creatButton(&btn3);

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
   * @brief 刷新按钮，根据所发生的事件来刷新按钮
   * @param bu sButton_t类型的结构体数据，里面包含了按钮的位置，长度和宽度等参数
   * @n 用户需要自定义这些数据
   */
  ui.refreshButton(&btn1);
  ui.refreshTextBox(&tb);
  ui.refreshButton(&btn2);
  ui.refreshTextBox(&tb);
  ui.refreshButton(&btn3);
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