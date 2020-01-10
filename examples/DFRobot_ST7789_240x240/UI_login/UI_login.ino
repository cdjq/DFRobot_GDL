/*!
 * @file UI_login.ino
 * @brief 一个登录的界面
 * @n 本示例支持的主板有arduino uno，esp8266，esp32，leonardo，M0，mega2560.
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
DFRobot_ST7789_240x240_HW_SPI screen(TFT_DC,TFT_CS,TFT_RST,TFT_BL);
/*M0主板下DMA传输*/
//DFRobot_ST7789_240x240_DMA_SPI screen(TFT_DC,TFT_CS,TFT_RST,TFT_BL);

/**
   @brief 构造函数
   @param gdl 屏幕对象
   @param width 屏幕的宽度.
   @param height 屏幕的高度.
*/
DFRobot_UI ui(&screen, /*width=*/240,/*height=*/240);

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
DFRobot_UI::sTextBox_t tb1, tb2;
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
DFRobot_UI::sButton_t btn1, btn2 ;

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

void keyboard() {
  
  //判断是哪一个文本框被选中
  if (tb1.selected == true) {
    //指定键盘输出信息的位置
    kb.textBox = &tb1;  } 
  else if (tb2.selected == true ) {
    kb.textBox = &tb2;
  }
}

void setup()
{

  Serial.begin(9600);
  //初始化显示屏幕
  screen.begin();

  // 设置UI的主题，有两种主题可供选择 1.CLASSIC ，2.MODERN。
  ui.setTheme(DFRobot_UI::CLASSIC);
  ui.begin();
  //初始化文本框，会对文本框的参数进行初始化
  ui.initText(&tb1);
    /**用户自定义文本框的参数*/
  tb1.posx = 20;
  tb1.posy = 30;
  tb1.width = 180;
  tb1.height = 30;
  tb1.selected = 0;
  tb1.fontSize = 3;
  //在屏幕上创建一个文本框，根据自定义或初始化的参数绘制文本框
  ui.creatText(&tb1);
  ui.initText(&tb2);

  tb2.posx = 20;
  tb2.posy = 80;
  tb2.width = 180;
  tb2.height = 30;
  tb2.selected = 1;
  tb2.fontSize = 3;
  ui.creatText(&tb2);
  
  //初始化按钮，会对按钮的参数进行初始化
  ui.initButton(&btn1);
  /**用户自定义按钮参数*/
  btn1.posx = 20;
  btn1.posy = 120;
  btn1.width = 180;
  btn1.height = 30;
  btn1.fontSize = 2;
  btn1.fgColor = RED_RGB565;
  btn1.bgColor = CYAN_RGB565;
  memcpy(btn1.text, "login", 5);

  //在屏幕上创建一个按钮，根据自定义或初始化的参数绘制按钮
  ui.creatButton(&btn1);
  kb.mode = 1;
  kb.callBack = keyboard;
  ui.creatKeyBoard(&kb);
  ui.drawString(20, 10, "login interface", CYAN_RGB565, ui.bgColor, 2, 0);
}


void loop()
{
  //刷新文本框
  ui.refreshTextBox(&tb1);
  ui.refreshTextBox(&tb2);
  //刷新数字键盘
  ui.refreshKeyBoard(&kb);
}