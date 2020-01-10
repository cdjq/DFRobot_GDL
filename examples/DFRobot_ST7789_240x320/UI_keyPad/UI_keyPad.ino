/*!
 * @file UI_keypad.ino
 * @brief 在屏幕上创建一个数字键盘控件
 * @n 用户可以点击键盘上面的数字然后会看到输出的结果显示在上面的文本框里面，在输入时需要点击
 * @n 文本框确保文本框被选中
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

//触摸扫描函数
String scan() {

  return touch.scan();
}

void setup()
{

  Serial.begin(9600);
  touch.begin();
  screen.begin();

  // 注册一个触摸扫描函数
  ui.setTouchFunction(scan);

  // 设置UI的主题，有两种主题可供选择 1.CLASSIC ，2.MODERN。
  ui.setTheme(DFRobot_UI::CLASSIC);
  ui.begin();
  //mode = 0 代表数字键盘自带了文本框
  kb.mode = 0;
  

   //创建一个数字键盘
   ui.creatKeyBoard(&kb);
}

void loop()
{
  /**
   * @brief 更新触摸点的数据
   */
  ui.updateCoordinate();
  
  // 刷新数字键盘
  ui.refreshKeyBoard(&kb);

}