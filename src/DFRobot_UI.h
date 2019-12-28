/*!
 * @file DFRobot_UI.h
 * @brief DFRobot_UI 类的基础结构,可以在屏幕上创建一系列的控件，如按钮,文本框,进度条等
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2019-12-6
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_GDL/src/DFRpbot_UI
 */
 
#ifndef __DFROBOT_UI_H
#define __DFROBOT_UI_H

#include "Arduino.h"
#include "DFRobot_GDL.h"
#if defined (__AVR__)
#define TOUCHPOINTS   1
#else
#define TOUCHPOINTS   5
#endif

#define BLACK_RGB565        0x0000
#define BLUE_RGB565         0x001F
#define RED_RGB565          0xF800
#define GREEN_RGB565        0x07E0
#define CYAN_RGB565         0x07FF
#define MAGENTA_RGB565      0xF81F
#define YELLOW_RGB565       0xFFE0
#define WHITE_RGB565        0xFFFF
#define NAVY_RGB565         0x000F
#define DARKGREEN_RGB565    0x03E0
#define DARKCYAN_RGB565     0x03EF
#define MAROON_RGB565       0x7800
#define PURPLE_RGB565       0x780F
#define OLIVE_RGB565        0x7BE0
#define LIGHTGREY_RGB565    0xC618
#define DARKGREY_RGB565     0x7BEF
#define ORANGE_RGB565       0xFD20
#define GREENYELLOW_RGB565  0xAFE5
#define DCYAN_RGB565        0x03EF


class DFRobot_UI
{
public:
  typedef String scanF() ;
  
  /**
   * @brief 滑条的回调函数，当进度条的进度值发生改变时，会进入此回调函数
   * @param value 进度条的值
   * @n 回调函数里面发生的事件，用户需自定义
   */
  typedef void sliderCallback(uint16_t value);
  
  /**
   * @brief tableview的回调函数
   * @param highLightPage 高亮的页的页数
   * @n 回调函数里面发生的事件，用户需自定义
   */
  typedef void tableViewCallback(uint8_t highLightPage);
  
  /**
   * @brief 开关的回调函数，当开关的状态发生改变时，会进入此回调函数
   * @param state 进度条的值
   * @n 回调函数里面发生的事件，用户需自定义
   */
  typedef void switchCallback(uint8_t state);
  
  /**
   * @brief 按钮的回调函数，当按钮被按下，会进入此回调函数
   * @param text 按钮的名字
   * @n 回调函数里面发生的事件，用户需自定义
   */
  typedef void buttonCallback(char* text);
  
  /**
   * @brief 进度条的回调函数
   * @n 引发进度条发生改变的事件应该写在里面
   */
  typedef void barCallback();

  /*!
    文本框的状态
  */
  typedef enum {
    DRAWBOX,  /**<开始绘制文本框>**/
    DRAWTEXT,/**<绘制字符串.>**/
    ADDCHAR,/**<向文本框添加一个字符.>**/
    NOCHANGE,/**<无改变.>**/
    CLEARACHAR,/**<删除文本框内容的最后一个字符.>**/
  } sTextState_t;
  
  /*!
    触摸点的数据
  */
  typedef struct {
    uint8_t id;/**<触摸点的id>**/
    uint16_t x;/**<触摸点的x坐标>**/
    uint16_t y;/**<触摸点的y坐标>**/
    uint16_t wSize/**<触摸区域的宽度>**/;
    uint16_t hSize;/**<触摸区域的高度>**/
  } sPoint_t;
  
  /*!
    开关控件的参数 sSwitch_t类型
  */
  typedef struct {
    uint16_t posx; /**<开关在x轴的坐标>**/
    uint16_t posy;/**<开关在y轴的坐标>**/
    uint16_t  width ;/**<开关的宽度>**/
    uint16_t  height ;/**<开关的高度>**/
    uint16_t fgColor;/**<开关的前景色>**/
    uint16_t bgColor;/**<开关的背景色>**/
    bool change;/**<开关是否改变的标志>**/
    uint8_t  laststate;/**<开关的上一次的状态>**/
    uint8_t  state;/**<开关的状态(on / off)>**/
    switchCallback *callBack;/**<回调函数的指针>**/
  } sSwitch_t;
  
  /*!
    sSlider_t类型的结构体 ,用来存储开关控件的参数
  */
  typedef struct {
    uint16_t posx;/**<滑条在x轴的坐标>**/
    uint16_t posy;/**<滑条在y轴的坐标>**/
    uint16_t sliderHeight;/**<滑块的高度>**/
    uint16_t sliderWidth;/**<滑块的宽度>**/
    uint16_t fgColor;/**<前景颜色>**/
    uint16_t bgColor;/**<背景颜色>**/
    uint16_t  width;/**<宽度>**/
    uint16_t  height ;/**<高度>**/
    uint16_t range;/**<范围>**/
    uint16_t  lastsliderPos;/**<滑块上一次的位置(y坐标)>**/
    uint16_t  sliderPos;/**<滑块的位置>**/
    int8_t value;/**<滑块的值>**/
    bool change;/**<滑块值是否发生改变的标志>**/
    sliderCallback *callBack;/**<滑块回调函数的指针>**/
  } sSlider_t;
  
  /*!
    结构体，用来存储进度条控件的参数
  */
  typedef struct{
    uint16_t posx;/**<进度条在x轴的坐标>**/
    uint16_t posy;/**<进度条在y轴的坐标>**/
    uint16_t width;/**<进度条的宽度>**/
    uint16_t height;/**<进度条的高度>**/
    uint16_t fgColor;/**<进度条前景颜色>**/
    uint16_t bgColor;/**<进度条背景颜色>**/
    uint16_t sliderPos;/**<进度条的进度的x坐标>**/
    barCallback *callBack;/**<进度条回调函数的函数指针>**/
    uint8_t lastValue;/**<进度条上一次的进度>**/
    uint8_t value;/**<进度条的进度(0~99)>**/
  } sBar_t ;
  
  /*!
    结构体类型，用来存储按钮控件的参数
  */
  typedef struct {
    uint16_t posx;/**<按钮在x轴的坐标>**/
    uint16_t posy;/**<按钮在y轴的坐标>**/
    uint16_t  width ;/**<按钮的宽度>**/
    uint16_t  height ;/**<按钮的高度>**/
    uint16_t fgColor;/**<按钮的前景色>**/
    uint16_t bgColor;/**<按钮的背景色>**/
    uint8_t fontSize;/**<按钮字体的大小>**/
    char  text[10] ;/**<按钮的名字>**/
    bool click;/**<按钮是否被点击的标志>**/
    buttonCallback  *callBack ;/**<按钮的回调函数的函数指针>**/
  } sButton_t ;
  
  /*!
    枚举类型，用来定义不同的主题效果
  */
  typedef enum {
    THEME1,/**<主题1>**/
    THEME2,/**<主题2>**/
  } sTheme_t;

  /*!
    结构体类型，用来存储文本框控件的参数
  */
  typedef struct {
    uint16_t posx;/**<文本框在x轴的坐标>**/
    uint16_t posy;/**<文本框在y轴的坐标>**/
    uint16_t  width;/**<文本框的宽度>**/
    uint16_t  height;/**<文本框的高度>**/
    uint16_t fgColor;/**<文本框内字体的前景的颜色>**/
    uint16_t bgColor;/**<文本框内字体的背景颜色>**/
    uint8_t fontSize;/**<文本框内字体的大小>**/
    sTextState_t state;/**<文本框的状态>**/
    char cache ;/**<文本框添加一个字符的缓存>**/
    char  text[100] ;/**<文本框内容>**/
    uint16_t cursorx;/**<文本框光标在x轴的坐标>**/
    uint16_t cursory;/**<文本框光标在y轴的坐标>**/
  } sTextBox_t;
  
  /*!
    结构体类型，用来存储tableview控件的参数
  */
  typedef struct {
    uint16_t offset;/**<table间的间距>**/
    sButton_t text[4];/**<每个table相当与一个按钮>**/
    uint8_t  numPage;/**<table的个数>**/
    uint8_t highLightPage;/**<高亮的table>**/
    tableViewCallback *callback;/**<tableview的回调函数>**/
  } sTableview_t;
  
  typedef enum {
    CENTER,
    RIGHT,
    LEFT,
  } sLocation;
  
  /*!
    该枚举定义了不同的手势
  */
  typedef enum {
    UPGLIDE ,/**<向上滑动>**/
    DOWNGLIDE,/**<向下滑动>**/
    LEFTGLIDE,/**<向左滑动>**/
    RIGHTGLIDE,/**<向右滑动>**/
    LONGPRESSDE,/**<长按屏幕>**/
    SINGLECLICK,/**<单击屏幕>**/
    DOUBLECLICK,/**<双击屏幕>**/
    NONE,/**<没有识别到有效手势>**/
  } sGestures_t;
  
protected:
  scanF * scan;
public:

  /**
   * @brief 构造函数
   * @param gdl 
   * @param width 屏幕的宽度.
   * @param height 屏幕的高度.
   */
  DFRobot_UI(DFRobot_GDL *gdl, uint16_t width, uint16_t height);
  
  /**
   * @brief 初始化函数,初始化UI使用到的一些参数
   */
  void begin();
  
  /**
   * @brief 初始化按钮控件的参数
   * @param bu sButton_t类型的结构体数据，存储按钮参数的结构体
   * @n 若用户徐自定义按钮的参数，如长度和宽度等可在此函数后自定义这些数据
   */
  void initButton(sButton_t *bu);

  /**
   * @brief 在屏幕上创建一个按钮控件
   * @param bu sButton_t类型的结构体数据，里面包含了按钮的位置，长度和宽度等参数
   * @n 用户可以自定义这些数据
   */
  void creatButton(sButton_t *bu);
  
  /**
   * @brief 刷新按钮，根据所发生的事件来刷新按钮
   * @param bu sButton_t类型的结构体数据，里面包含了按钮的位置，长度和宽度等参数
   * @n 用户需要自定义这些数据
   */
  void refreshButton(sButton_t *bu);
  
  /**
   * @brief 设置UI的主题
   * @param the sTheme_t类型数据，包含了了两种主题，主要是颜色和按钮验收的不同
   * @n   the 的参数 ：THEME1,
                     ：THEME2,
   */
  void setTheme(sTheme_t the);
  
  /**
   * @brief 注册一个触摸函数
   * @param fuc 用户自定义的一个函数的指针，类型须于scanF保持一致
   */
  void setTouchFunction(scanF* fuc);
  
  /**
   * @brief 绘制字符串
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
  void drawString(int16_t x, int16_t y, char  *c, uint16_t color, uint16_t bg, uint8_t size, boolean mode);
  
  /**
   * @brief 刷新滑条
   * @param slider sSlider_t，里面包含了滑条的位置，长度和宽度等参数
   */
  void refreshSliser(sSlider_t *slider);
  
  /**
   * @brief 初始化滑条控件
   * @param slider 用户创建的存储滑条参数的结构体变量
   * @n 用户如果需要可以自定义这些参数
   */
  void initSlider(sSlider_t *slider);
  
  /**
   * @brief 在屏幕上创建一个滑条
   * @param slider sSlider_t类型的数据
   * @n 用户可以自定义结构体里面的数据或者使用经初始化的参数
   */
  void creatSlider(sSlider_t *slider);
  
  /**
   * @brief 初始化进度条控件
   * @param bar sSlider_t类型的变量，用户创建的存储进度条参数的结构体变量
   * @n 用户如果需要可以自定义这些参数
   */
  void initBar(sBar_t *bar);
  
  /**
   * @brief 在屏幕上创建一个进度条
   * @param bar sBar_t类型的数据
   * @n 用户可以自定义结构体里面的数据或者使用经初始化的参数
   */
  void creatBar(sBar_t *bar);
  
  /**
   * @brief 刷新进度条
   * @param bar sBar_t，里面包含了进度条的位置，长度和宽度等参数
   */
  void refreshBar(sBar_t *bar);
  
  /**
   * @brief 在屏幕上创建一个tableview控件
   * @param tv sTableview_t，里面包含了tableview的页数，内容等参数
   * @n 用户需要自定义这些数据
   */
  void creatTableview(sTableview_t *tv);
  
  /**
   * @brief 刷新tableview
   * @param sTableview_t sSlider_t，里面包含了滑条的位置，长度和宽度等参数
   */
  void refreshTableview(sTableview_t *tv);
  
  /**
   * @brief 初始化开关控件,对开关的某些参数进行初始化
   * @param sw sSwitch_t 类型的结构体
   * @n 里面的参数配置都是默认的，如果用户需要自定义可以直接修改结构体里面的参数
   */
  void initSwitch(sSwitch_t *sw);
  
  /**
   * @brief 创建一个开关控件
   * @param sw sSwitch_t 类型的结构体
   */
  void creatSwitch(sSwitch_t *sw);
  
  /**
   * @brief 刷新开关控件
   * @param sw sSwitch_t，里面包含了开关的位置，长度和宽度等参数
   * @n 当某事件产生，会进入开关的回调函数
   */
  void refreshSwitch(sSwitch_t *sw);
  
  /**
   * @brief 创建一个文本框，
   * @param tb sTextBox_t 类型的结构体，
   */
  void creatText(sTextBox_t *tb);
  
  /**
   * @brief 刷新文本框
   * @param te sTextBox_t，里面包含了开关的位置，长度和宽度等参数
   * @n 可以对文本框的操作有：
     @n                    1.让文本框显示字符串
     @n                    2.在文本框添加一个字符
     @n                    2.在文本框删除一个字符
   */
  void refreshTextBox(sTextBox_t *te);
  
  /**
   * @brief 让文本框显示字符串，
   * @param tb sTextBox_t 类型的结构体
   * @param text 需要让文本框显示的字符
   */
  void setText(sTextBox_t *te,char * text);
  
  /**
   * @brief 在文本框删除一个字符
   * @param te sTextBox_t 类型的结构体
   */
  void textDeleteChar(sTextBox_t *te);
  
  /**
   * @brief 在文本框添加一个字符
   * @param te sTextBox_t 类型的结构体
   * @param txt 需要添加的字符
   */
  void textAddChar(sTextBox_t *te,char txt);

  /**
   * @brief 更新触摸点的数据
   */
  void updateCoordinate();
  
  /**
   * @brief 设置触摸的手势识别区域
   * @param x 识别区域的开始位置的x坐标
   * @param y 识别区域的开始位置的y坐标
   * @param width 识别区域的宽度
   * @param height 识别区域的高度
   */
  void setGestureArea(uint16_t x,uint16_t y,uint16_t width,uint16_t height);
  
  /**
   * @brief 获取手势
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
  sGestures_t getGestures();
  uint16_t bgColor;
private:
  uint8_t pointNum(String str);
  uint8_t stringToPoint(String str, sPoint_t *point);
  void drawClickButton(sButton_t *bu);
  void drawButtonString(sButton_t *bu , sLocation x, sLocation y, char * c);
  void drawButton(sButton_t *bu);
  void drawCursor(sTextBox_t *text, uint8_t offset_x, uint8_t offset_y, bool state);
  bool judgePress(sButton_t *bu, uint16_t x, uint16_t y);
  bool buttonPressed(sButton_t *bu , uint16_t touch_x, uint16_t touch_y);
  bool buttonRelease(sButton_t *bu, uint16_t touch_x, uint16_t touch_y);
  bool release(uint16_t x,uint16_t y);
  bool press(uint16_t x,uint16_t y);
  bool focus(uint16_t x,uint16_t y);
  sPoint_t * position;
  DFRobot_GDL *_gdl;
  uint8_t number;
  long long timer;
  long long timer1;
  sTheme_t theme;
  bool cursorState;
  uint16_t color;
  uint16_t lcdWidth;
  uint16_t lcdHeight;
  uint8_t pressed;
  uint8_t screenPressed; 
  sGestures_t lastGestute;
  uint16_t bx1,by1,bx2,by2;
  uint16_t gesturex,gesturey,gestureWidth,gestureHeight;
  uint8_t click;
};
#endif