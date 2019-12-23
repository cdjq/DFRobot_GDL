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
  typedef void sliderCallback(uint16_t value);
  typedef void tableViewCallback(uint8_t highLightPage);
  typedef void switchCallback(uint8_t state);
  typedef void buttonCallback(char* text);
  typedef void barCallback();
  typedef enum {
    DRAWBOX,
    DRAWTEXT,
    ADDCHAR,
    DRAWRESULTS,
    NOCHANGE,
    CLEARACHAR,
  } sTextState_t;
  typedef struct {
    uint8_t id;
    uint16_t x;
    uint16_t y;
    uint16_t wSize;
    uint16_t hSize;
  } sPoint_t;
  typedef struct {
    uint16_t posx;
    uint16_t posy;
    uint16_t  width ;
    uint16_t  height ;
    uint16_t fgColor;
    uint16_t bgColor;
    bool change;
    uint8_t  laststate;
    uint8_t  state;
    switchCallback *callBack;
  
  } sSwitch_t;
  typedef struct {
    uint16_t posx;
    uint16_t posy;
    int16_t maxValue;
    int16_t minValue;
    uint16_t sliderHeight;
    uint16_t sliderWidth;
    uint16_t fgColor;
    uint16_t bgColor;
    uint16_t  width;
    uint16_t  height ;
    uint16_t range;
    uint16_t  lastsliderPos;
    uint16_t  sliderPos;
    uint16_t value;
    bool change;
    sliderCallback *callBack;
  
  } sSlider_t;
  typedef struct{
    uint16_t posx;
    uint16_t posy;
    uint16_t width;
    uint16_t height;
    uint16_t fgColor;
    uint16_t bgColor;
    uint16_t sliderPos;
    barCallback *callBack;
    uint8_t lastValue;
    uint8_t value;
  } sBar_t ;
  typedef struct {
    uint16_t posx;
    uint16_t posy;
    uint16_t  width ;
    uint16_t  height ;
    uint16_t fgColor;
    uint16_t bgColor;
    uint8_t fontSize;
    char  text[10] ;
    bool click;
    buttonCallback  *callBack ;
  } sButton_t ;
  typedef enum {
    THEME1,
    THEME2,
  } sTheme_t;
  
  typedef struct {
    uint16_t posx;
    uint16_t posy;
    uint16_t  width;
    uint16_t  height;
    uint16_t fgColor;
    uint16_t bgColor;
    uint8_t fontSize;
    sTextState_t state;
    char cache ;
    char  text[40] ;
    uint16_t cursorx;
    uint16_t cursory;
  } sTextBox_t;

  typedef struct {
    uint16_t offset;
    //uint16_t
    sButton_t text[4];
  
    uint8_t  numPage;
    uint8_t highLightPage;
    tableViewCallback *callback;
  } sTableview_t;
  typedef enum {
    CENTER,
    RIGHT,
    LEFT,
  } sLocation;
typedef enum {
  UPGLIDE ,
  DOWNGLIDE,
  LEFTGLIDE,
  RIGHTGLIDE,
  LONGPRESSDE,
  SINGLECLICK,
  DOUBLECLICK,
  NONE,
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
   * @brief 在屏幕上创建一个按钮控件
   * @param bu sButton_t类型的结构体数据，里面包含了按钮的位置，长度和宽度等参数
   * @n 用户需要自定义这些数据
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

  void creatSlider(sSlider_t *slider);
  void creatBar(sBar_t *bar);
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
  void creatSwitch(sSwitch_t *sw);
  void refreshSwitch(sSwitch_t *sw);
  void creatText(sTextBox_t *tb);
  void refreshTextBox(sTextBox_t *te);
  void setText(sTextBox_t *te,char * text);
  void textAddChar(sTextBox_t *te,char txt);
  uint8_t pointNum(String str);
  uint8_t stringToPoint(String str, sPoint_t *point);
  /**
   * @brief 更新触摸点的数据
   */
  void updateCoordinate();
  sGestures_t getGestures();
  uint16_t bgColor;
private:
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

  uint16_t lcdWidth;
  uint16_t lcdHeight;
  uint8_t pressed;
  uint8_t screenPressed; 
  sGestures_t lastGestute;
  uint16_t bx1,by1,bx2,by2;
  uint8_t click;
};
#endif