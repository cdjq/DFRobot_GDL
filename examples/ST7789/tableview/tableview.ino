#include "DFRobot_UI.h"
#include "Arduino.h"
#include "DFRobot_GDL.h"
#include "DFRobot_Touch.h"



#define SPI_CS 3
#define SPI_DC 4
DFRobot_Touch_XPTxxx gt911(2); //tcs
DFRobot_ST7789_240x320_HW_SPI screen(SPI_DC,SPI_CS);

/**
 * @brief 构造函数
 * @param gdl 屏幕对象
 * @param width 屏幕的宽度.
 * @param height 屏幕的高度.
 */
DFRobot_UI ui(&screen, 240, 320);
//定义 sTableview_t类型的结构体变量，用来定义tableview的参数.
DFRobot_UI::sTableview_t tv;

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
  return gt911.scan();
}
/**
 * @brief tableview的回调函数
 * @param highLightPage 被选中的页
 */
void tvCallback(uint8_t highLightPage) {

  if (highLightPage == 1) {
    ui.drawString(10, 200, "this is tab1", 0x0, ui.bgColor, 4, 0);
  }
  if (highLightPage == 2) {
    ui.drawString(10, 200, "this is tab2", 0x00, ui.bgColor, 4, 0);
  }
  if (highLightPage == 3) {
    ui.drawString(10, 200, "this is tab3", 0x00, ui.bgColor, 4, 0);
  }
}

void setup()
{
  Serial.begin(9600);
  gt911.begin();
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
  ui.setTheme(DFRobot_UI::THEME1);
  /**
   * @brief 初始化函数,初始化UI使用到的一些参数
   */
  ui.begin();
  //自定义tableview的页数为三，最大为四
  tv.numPage = 3;
  //定义tableview的回调函数
  tv.callback = tvCallback;
  //设置tableview的内容
  memcpy(tv.text[0].text, "Tab 1", 5);
  memcpy(tv.text[1].text, "Tab 2", 5);
  memcpy(tv.text[2].text, "Tab 3", 5);
  /**
   * @brief 在屏幕上创建一个tableview控件
   * @param tv sTableview_t，里面包含了tableview的页数，内容等参数
   * @n 用户需要自定义这些数据
   */
  ui.creatTableview(&tv);
}

void loop()
{
  /**
   * @brief 更新触摸点的数据
   */
  ui.updateCoordinate();
  /**
   * @brief 刷新tableview
   * @param sTableview_t sSlider_t，里面包含了滑条的位置，长度和宽度等参数
   */
  ui.refreshTableview(&tv);
}