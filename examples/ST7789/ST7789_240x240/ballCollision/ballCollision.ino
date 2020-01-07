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
//#define DC  D3
//#define CS  D4
//#define RST D5
//#define BL  D6
#if defined(__AVR__)
#define DC  2
#define CS  3
#define RST 4
#define BL  5
#elif defined(ESP8266)
#define DC  D2
#define CS  D3
#define RST D4
#define BL  D5
#elif defined(NRF5) || defined(ESP_PLATFORM)
#define DC  D2
#define CS  D3
#define RST D4
#define BL  D5
#endif
DFRobot_ST7789_240x240_HW_SPI screen(DC,CS,RST,BL);

int16_t xx0 = 40;int16_t yy0 = 100;int16_t xx1 = 200;int16_t yy1 = 30;int16_t xx2 = 100;int16_t yy2 = 60;
int16_t xx3 = 5;int16_t yy3 = 5;int16_t xx4 = 5;int16_t yy4 = 5;int16_t xx5 = 5;int16_t yy5 = 5;
uint16_t color1 = 65504;
uint16_t color2 = 63488;
uint16_t color3 = 127;
int16_t r1;
int16_t r2;
int16_t r3;
//int16_t xx3 = 129;int16_t yy3 = 100;int16_t xx4 = 111;int16_t yy4 = 87;int16_t xx5 = 133;int16_t yy5 = 87;
/*
int16_t xx0 = 35;int16_t yy0 = 100;int16_t xx1 = 56;int16_t yy1 = 85;int16_t xx2 = 56;int16_t yy2 = 34;
int16_t xx3 = 77;int16_t yy3 = 100;int16_t xx4 = 22;int16_t yy4 = 60;int16_t xx5 = 90;int16_t yy5 = 60;
*/
void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    screen.begin();
    /*
     *初始化
     */
    screen.fillScreen(65535);
    screen.fillCircle(xx0,yy0,10,color1);
    screen.fillCircle(xx1,yy1,10,color2);
    screen.fillCircle(xx2,yy2,10,color3);
}

void loop() {
    screen.fillCircle(xx0,yy0,10,65535);
    screen.fillCircle(xx1,yy1,10,65535);
    screen.fillCircle(xx2,yy2,10,65535);
    if(yy0<11)
        yy3 = 5;
    else if(yy0>229)
        yy3 = -5;
    if(xx0<11)
        xx3 = 5;
    else if(xx0>229)
        xx3 = -5;
    if(yy1<11)
        yy4 = 5;
    else if(yy1>229)
        yy4 = -5;
    if(xx1<11)
        xx4 = 5;
    else if(xx1>229)
        xx4 = -5;
    if(yy2<11)
        yy5 = 5;
    else if(yy2>229)
        yy5 = -5;
    if(xx2<11)
        xx5 = 5;
    else if(xx2>229)
        xx5 = -5;
    r1 = (yy0-yy1)*(yy0-yy1) + (xx0-xx1)*(xx0-xx1);
    r2 = (yy0-yy2)*(yy0-yy2) + (xx0-xx2)*(xx0-xx2);
    r3 = (yy2-yy1)*(yy2-yy1) + (xx2-xx1)*(xx2-xx1);
    if(r1 <= 400){
        int dx,dy;
        dy = yy3;dx = xx3;
        yy3 = yy4;xx3 = xx4;
        yy4 = dy;xx4 = dx; 
    }
    if(r2 <= 400){
        int dx,dy;
        dy = yy3;dx = xx3;
        yy3 = yy5;xx3 = xx5;
        yy5 = dy;xx5 = dx; 
    }
    if(r3 <= 400){
        int dx,dy;
        dy = yy4;dx = xx4;
        yy4 = yy5;xx4 = xx5;
        yy5 = dy;xx5 = dx; 
    }
    yy0 += yy3;xx0 += xx3;
    yy1 += yy4;xx1 += xx4;
    yy2 += yy5;xx2 += xx5;
    screen.fillCircle(xx0,yy0,10,color1);
    screen.fillCircle(xx1,yy1,10,color2);
    screen.fillCircle(xx2,yy2,10,color3);
    delay(100);
}
