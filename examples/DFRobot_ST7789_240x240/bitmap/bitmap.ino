/*!
 * @file bitmap.ino
 * @brief 根据位图软件生成的图像数组画单色图、彩色图和灰度图，主控需要40000字节的动态内存，ESP8266和ESP32可运行，项目使用了近38万字节
 * @n 本示例支持的主板有ESP32, ESP8266, FireBeetle-M0
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [YeHangYu](hangyu.ye@dfrobot.com)
 * @version  V0.1
 * @date  2020-01-07
 * @url https://github.com/DFRobot/DFRobot_GDL
 */
 
#include "DFRobot_GDL.h"
#include "pgmspace.h"
#include "Bitmap.h"
#include "XBitmap.h"
#include "GrayscaleBitmap.h"
#include "mask.h"
#include "RGBBitmap.h"
//自定义通信引脚
/*M0*/
#if defined ARDUINO_SAM_ZERO
#define TFT_DC  7
#define TFT_CS  5
#define TFT_RST 6
#define TFT_BL  9
/*ESP32 and ESP8266*/
#elif defined(ESP32) || defined(ESP8266)
#define TFT_DC  D3
#define TFT_CS  D4
#define TFT_RST D5
#define TFT_BL  D6
/*AVR系列主板*/
#else
#define TFT_DC  2
#define TFT_CS  3
#define TFT_RST 4
#define TFT_BL  5
#endif

/**
 * @brief Constructor  硬件SPI通信的构造函数
 * @param dc  SPI通信的命令/数据线引脚
 * @param cs  SPI通信的片选引脚
 * @param rst  屏的复位引脚
 * @param bl  屏幕的背光引脚
 */
DFRobot_ST7789_240x240_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST,/*bl=*/TFT_BL);
/*M0主板下DMA传输*/
//DFRobot_ST7789_240x240_DMA_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST,/*bl=*/TFT_BL);

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
  screen.drawBitmap(/*x=*/0,/*y=*/0,/*bitmap gImage_Bitmap=*/gImage_Bitmap,/*w=*/240,/*h=*/240,/*color=*/0xFF00,/*bg=*/0x00FF);
  /**
   * @brief 画无背景的单色图
   * @param x      0 设置画图起点是屏幕左上方，靠左
   * @param y      0 靠上
   * @param bitmap gImage_Bitmap 头文件Bitmap中的数组，数组元素是单字节
   * @param w      240 图片宽度
   * @param h      240 图片高度
   * @param color  0x000F 黑色图片部分设置为深蓝色
   */
  screen.drawBitmap(/*x=*/0,/*y=*/0,/*bitmap gImage_Bitmap=*/gImage_Bitmap,/*w=*/240,/*h=*/240,/*color=*/0x000F);
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
  screen.drawXBitmap(/*x=*/0,/*y=*/0,/*bitmap gImage_Bitmap=*/gImage_XBitmap,/*w=*/240,/*h=*/240,/*color=*/0x0000);
  screen.fillScreen(0x66FF);
  /**
   * @brief 画彩色图
   * @param x      0 设置画图起点是屏幕左上方，靠左
   * @param y      0 靠上
   * @param bitmap gImage_RGBBitmap 头文件RGBBitmap的数组，数组元素是单字节，这里强制转换为2字节
   * @param w      240 图片宽度
   * @param h      240 图片高度
   */
  screen.drawRGBBitmap(/*x=*/0,/*y=*/0,/*bitmap gImage_Bitmap=*/(const unsigned uint16_t*)gImage_RGBBitmap,/*w=*/240,/*h=*/240);
  /**
   * @brief 用掩码作为单色图，画单色图
   * @param x      0 设置画图起点是屏幕左上方，靠左
   * @param y      0 靠上
   * @param bitmap gImage_mask 头文件mask中的数组，数组元素是单字节
   * @param w      240 图片宽度
   * @param h      240 图片高度
   * @param color  0x0000 黑色图片部分设置为黑色
   */
  screen.drawBitmap(/*x=*/0,/*y=*/0/*dc=*/,/*bitmap gImage_Bitmap=*/gImage_mask,/*w=*/240,/*h=*/240,/*color=*/0x0000);
  /**
   * @brief 画彩色图，掩码白色部分不画
   * @param x      0 设置画图起点是屏幕左上方，靠左
   * @param y      0 靠上
   * @param bitmap gImage_RGBBitmap 头文件RGBBitmap的数组，数组元素是单字节，这里强制转换为2字节
   * @param mask   gImage_mask 头文件mask中的数组，数组元素是单字节
   * @param w      240 图片宽度
   * @param h      240 图片高度
   */
  screen.drawRGBBitmap(/*x=*/0,/*y=*/0,/*bitmap gImage_Bitmap=*/(const unsigned uint16_t*)gImage_RGBBitmap,/*mask=*/gImage_mask,/*w=*/240,/*h=*/240);
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
    screen.drawBitmap(/*x=*/0,/*y=*/0,/*bitmap gImage_Bitmap=*/gImage_Bitmap,/*w=*/240,/*h=*/240,/*color=*/i);
  }
  //screen.drawGrayscaleBitmap(0,0,gImage_GrayscaleBitmap,240,240);//画灰度图，此屏幕不支持
  //screen.drawGrayscaleBitmap(0,0,gImage_GrayscaleBitmap,gImage_mask,240,240);//画灰度图,带掩码，此屏幕不支持
}
