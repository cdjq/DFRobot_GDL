/*!
 * @file ballCollision.ino
 * @brief 演示小球在屏幕中运动碰撞的动画效果 
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [LuoYufeng](yufeng.luo@dfrobot.com)
 * @version  V0.1
 * @date  2020-01-07
 * @url https://github.com/DFRobot/DFRobot_GDL
 */

#include "DFRobot_GDL.h"
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
DFRobot_ST7789_240x320_HW_SPI screen(TFT_DC,TFT_CS,TFT_RST,TFT_BL);
/*M0主板下DMA传输*/
//DFRobot_ST7789_240x320_DMA_SPI screen(TFT_DC,TFT_CS,TFT_RST,TFT_BL);


int xx0 = 39;int yy0 = 99;int xx1 = 199;int yy1 = 29;int xx2 = 99;int yy2 = 59;
int xx3 = 5;int yy3 = 5;int xx4 = 5;int yy4 = 5;int xx5 = 5;int yy5 = 5;
uint16_t color1 = COLOR_RGB565_YELLOW;
uint16_t color2 = COLOR_RGB565_RED;
uint16_t color3 = COLOR_RGB565_BLUE;
void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    screen.begin();
  /*
   *@brief 清屏
   *@param c 屏幕颜色
   */
    screen.fillScreen(COLOR_RGB565_BLACK);
    screen.fillCircle(xx0,yy0,10,color1);
    screen.fillCircle(xx1,yy1,10,color2);
    screen.fillCircle(xx2,yy2,10,color3);
}

void loop() {
    screen.fillCircle(xx0,yy0,10,COLOR_RGB565_BLACK);
    screen.fillCircle(xx1,yy1,10,COLOR_RGB565_BLACK);
    screen.fillCircle(xx2,yy2,10,COLOR_RGB565_BLACK);
    int r1 = (yy0-yy1)*(yy0-yy1) + (xx0-xx1)*(xx0-xx1);
    int r2 = (yy0-yy2)*(yy0-yy2) + (xx0-xx2)*(xx0-xx2);
    int r3 = (yy2-yy1)*(yy2-yy1) + (xx2-xx1)*(xx2-xx1);
    if(r1 <= 400){
        int t = 0;
        if(fabs(yy0-yy1)<fabs(xx0-xx1)){
            t = xx3;xx3 = xx4;xx4 =t;
        }
        else if(fabs(yy0-yy1)>fabs(xx0-xx1)){
            t = yy3;yy3 = yy4;yy4 =t;
        }
        else{
            t = yy3;yy3 = yy4;yy4 =t;
            t = xx3;xx3 = xx4;xx4 =t;
        }
    }
    if(r2 <= 400){
        int t;
        if(fabs(yy0-yy2)<fabs(xx0-xx2)){
            t = xx3;xx3 = xx5;xx5 =t;
        }
        else if(fabs(yy0-yy2)>fabs(xx0-xx2)){
            t = yy3;yy3 = yy5;yy5 =t;
        }
        else{
            t = yy3;yy3 = yy5;yy5 =t;
            t = xx3;xx3 = xx5;xx5 =t;
        }
    }
    if(r3 <= 400){
        int t;
        if(fabs(yy2-yy1)<fabs(xx2-xx1)){
            t = xx5;xx5 = xx4;xx4 =t;
        }
        else if(fabs(yy2-yy1)>fabs(xx2-xx1)){
            t = yy5;yy5 = yy4;yy4 =t;
        }
        else{
            t = yy5;yy5 = yy4;yy4 =t;
            t = xx5;xx5 = xx4;xx4 =t;
        }
    }
    if(yy0<=9)
        yy3 = 5;
    else if(yy0>=309)
        yy3 = -5;
    if(xx0<=9)
        xx3 = 5;
    else if(xx0>=229)
        xx3 = -5;
    if(yy1<=9)
        yy4 = 5;
    else if(yy1>=309)
        yy4 = -5;
    if(xx1<=9)
        xx4 = 5;
    else if(xx1>=229)
        xx4 = -5;
    if(yy2<=9)
        yy5 = 5;
    else if(yy2>=309)
        yy5 = -5;
    if(xx2<=9)
        xx5 = 5;
    else if(xx2>=229)
        xx5 = -5;
    yy0 += yy3;xx0 += xx3;
    yy1 += yy4;xx1 += xx4;
    yy2 += yy5;xx2 += xx5;
    
    screen.fillCircle(xx0,yy0,10,color1);
    screen.fillCircle(xx1,yy1,10,color2);
    screen.fillCircle(xx2,yy2,10,color3);
    delay(100);
}
