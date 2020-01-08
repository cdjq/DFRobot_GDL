/*!
 * @file UI_keypad.ino
 * @brief 在屏幕上创建一个数字键盘控件
 * @n 用户可以点击键盘上面的数字然后会看到输出的结果显示在上面的文本框里面，在输入时需要点击
 * @n 文本框确保文本框被选中
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
  posx：数字键盘在x轴的坐标
  posy：数字键盘在y轴的坐标
  width：数字键盘的宽度
  height：数字键盘的高度
  mode;：文数字键盘的模式0.带有文本框,1.不带文本框，数字输出的位置由自己指定
  btn[12]：数字键盘里面的按钮数据
  callBack：数字键盘的回调函数
  textBox：数字键盘的文本框数据
*/
DFRobot_UI::sKeyPad_t kb;

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
  //mode = 0 代表数字键盘自带了文本框
  kb.mode = 0;
  
  /**
   * @brief 创建一个数字键盘控件
   * @param te sKeyPad_t 类型的结构体
   */
   ui.creatKeyBoard(&kb);
}

void loop()
{
  /**
   * @brief 更新触摸点的数据
   */
  ui.updateCoordinate();
  
  /**
   * @brief 刷新数字键盘
   * @param te sKeyPad_t，里面包含了数字键盘的位置，长度和宽度等参数
   */
  ui.refreshKeyBoard(&kb);

}