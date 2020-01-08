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
  ui.setTheme(DFRobot_UI::CLASSIC);
  ui.begin();
  /**
   * @brief 初始化按钮控件的参数
   * @param bu sButton_t类型的结构体数据，存储按钮参数的结构体
   * @n 若用户徐自定义按钮的参数，如长度和宽度等可在此函数后自定义这些数据
   */
  ui.initButton(&btn1);
  /**用户自定义按钮参数*/
  btn1.posx = 80;
  btn1.posy = 150;
  btn1.callBack = buCallback;
  memcpy(btn1.text, "B", 1);
  /**
   * @brief 在屏幕上创建一个按钮控件
   * @param bu sButton_t类型的结构体数据，里面包含了按钮的位置，长度和宽度等参数
   * @n 用户可以自定义这些数据
   */
  ui.creatButton(&btn1);
  
  ui.initButton(&btn2);
  btn2.posx = 10;
  btn2.posy = 150;
  btn2.callBack = buCallback;
  memcpy(btn2.text, "A", 1);
  ui.creatButton(&btn2);

  ui.initButton(&btn3);
  btn3.posx = 150;
  btn3.posy = 150;
  btn3.callBack = buCallback;
  memcpy(btn3.text, "C", 1);

  ui.creatButton(&btn3);
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