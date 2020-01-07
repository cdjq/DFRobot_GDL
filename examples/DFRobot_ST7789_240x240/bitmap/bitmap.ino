//主控需要40000字节的动态内存，ESP8266和ESP32可运行，项目使用了近38万字节
#include "DFRobot_GDL.h"
#include "pgmspace.h"
#include "Bitmap.h"
#include "XBitmap.h"
#include "GrayscaleBitmap.h"
#include "mask.h"
#include "RGBBitmap.h"
//自定义通信引脚
#if defined(ESP8266)||defined(ESP32)
#define DC  D4
#define CS  D5
#define RST D6
#define BL  D7
#else
#define DC  4 
#define CS  5
#define RST 6
#define BL  7
#endif

DFRobot_ST7789_240x240_HW_SPI screen(DC,CS,RST,BL);
void setup() {
  Serial.begin(115200);
  screen.begin();
}
void loop() {
  /**
   * @brief 将屏幕刷成白色
   * @param 0xFFFF 白色参数
   */
  screen.fillScreen(0xFFFF);
  /**
   * @brief 画带背景的单色图
   * @param x      0 设置画图起点是屏幕左上方，靠左
   * @param y      0 靠上
   * @param bitmap gImage_Bitmap 头文件Bitmap中的数组，数组元素是单字节
   * @param w      240 图片宽度
   * @param h      240 图片高度
   * @param color  0xFF00 黑色图片部分设置为黄色
   * @param bg     0x00FF 白色背景部分设置为蓝色
   */
  screen.drawBitmap(0,0,gImage_Bitmap,240,240,0xFF00,0x00FF);
  /**
   * @brief 画无背景的单色图
   * @param x      0 设置画图起点是屏幕左上方，靠左
   * @param y      0 靠上
   * @param bitmap gImage_Bitmap 头文件Bitmap中的数组，数组元素是单字节
   * @param w      240 图片宽度
   * @param h      240 图片高度
   * @param color  0x000F 黑色图片部分设置为深蓝色
   */
  screen.drawBitmap(0,0,gImage_Bitmap,240,240,0x000F);
  screen.fillScreen(0xFFFF);
  /**
   * @brief 画位顺序不同的单色图
   * @param x      0 设置画图起点是屏幕左上方，靠左
   * @param y      0 靠上
   * @param bitmap gImage_XBitmap 头文件XBitmap中的数组，数组元素是单字节
   * @param w      240 图片宽度
   * @param h      240 图片高度
   * @param color  0x0000 黑色图片部分设置为黑色
   */
  screen.drawXBitmap(0,0,gImage_XBitmap,240,240,0x0000);
  screen.fillScreen(0x66FF);
  /**
   * @brief 画彩色图
   * @param x      0 设置画图起点是屏幕左上方，靠左
   * @param y      0 靠上
   * @param bitmap gImage_RGBBitmap 头文件RGBBitmap的数组，数组元素是单字节，这里强制转换为2字节
   * @param w      240 图片宽度
   * @param h      240 图片高度
   */
  screen.drawRGBBitmap(0,0,(const unsigned uint16_t*)gImage_RGBBitmap,240,240);
  /**
   * @brief 用掩码作为单色图，画单色图
   * @param x      0 设置画图起点是屏幕左上方，靠左
   * @param y      0 靠上
   * @param bitmap gImage_mask 头文件mask中的数组，数组元素是单字节
   * @param w      240 图片宽度
   * @param h      240 图片高度
   * @param color  0x0000 黑色图片部分设置为黑色
   */
  screen.drawBitmap(0,0,gImage_mask,240,240,0x0000);
  /**
   * @brief 画彩色图，掩码白色部分不画
   * @param x      0 设置画图起点是屏幕左上方，靠左
   * @param y      0 靠上
   * @param bitmap gImage_RGBBitmap 头文件RGBBitmap的数组，数组元素是单字节，这里强制转换为2字节
   * @param mask   gImage_mask 头文件mask中的数组，数组元素是单字节
   * @param w      240 图片宽度
   * @param h      240 图片高度
   */
  screen.drawRGBBitmap(0,0,(const unsigned uint16_t*)gImage_RGBBitmap,gImage_mask,240,240);
  screen.fillScreen(0x0000);
  /**
   * @brief 循环画无背景的单色图，颜色不断变化
   * @param x      0 设置画图起点是屏幕左上方，靠左
   * @param y      0 靠上
   * @param bitmap gImage_Bitmap 头文件Bitmap中的数组，数组元素是单字节
   * @param w      240 图片宽度
   * @param h      240 图片高度
   * @param color  i 黑色图片部分设置为偏蓝可变色
   */
  for (int16_t i = 0x00ff; ; i+=0x3300) {
    screen.drawBitmap(0,0,gImage_Bitmap,240,240,i);
  }
  screen.drawGrayscaleBitmap(0,0,gImage_GrayscaleBitmap,240,240);//画灰度图，此屏幕不支持
  screen.drawGrayscaleBitmap(0,0,gImage_GrayscaleBitmap,gImage_mask,240,240);//画灰度图,带掩码，此屏幕不支持
}
