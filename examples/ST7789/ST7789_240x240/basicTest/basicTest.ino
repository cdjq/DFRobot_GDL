/*!
 * @file basicTest.ino
 * @brief 演示不同自带英文字库效果 
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [LuoYufeng](yufeng.luo@dfrobot.com)
 * @version  V0.1
 * @date  2020-01-07
 * @url https://github.com/DFRobot/DFRobot_GDL
 */
 
#include "DFRobot_GDL.h"
#include "Fonts/Fonts/SIMKAIFont18pt.h"

#define DC  D2
#define CS  D3
#define RST D4
#define BL  D5
DFRobot_ST7789_240x240_HW_SPI screen(DC,CS,RST,BL);

void setup() {
  Serial.begin(115200);
  screen.begin();//生成了screen对象
}

void loop(){
    testdrawpixel();
    //testline();
    //testfastlines(COLOR_RGB565_PURPLE,COLOR_RGB565_YELLOW);       
    //testrects(COLOR_RGB565_BLACK,COLOR_RGB565_WHITE);
    //testroundrects();
    //testcircles(24,COLOR_RGB565_BLUE);
    //testtriangles(COLOR_RGB565_YELLOW);
    //testprint();

}
/*测试画像素点*/
void testdrawpixel() {
  /*
   *@brief 清屏
   *@param c 屏幕颜色
   */
  screen.fillScreen(0x0000);
  int x = 0;
  int y = 240;
  for(int i = 0; i <= 120; i += 10){
    for (x = 239 - i; x >= i; x-=10 ){
      /*
       *@brief 画像素点
       *@param x 横坐标
       *       y 纵坐标
       *       c 像素点颜色
       */
      screen.drawPixel(x, y, COLOR_RGB565_ORANGE);
      delay(10);
    }
    for (y = 239 - i; y >= i; y-=10){
      screen.drawPixel(x, y, COLOR_RGB565_ORANGE);
      delay(10);
    }
    for (x = i; x <= 239 - i; x+=10 ){
      screen.drawPixel(x, y, COLOR_RGB565_ORANGE);
      delay(10);
    }
    for (y = i; y <= 239 - i; y+=10){
      screen.drawPixel(x, y, COLOR_RGB565_ORANGE);
      delay(10);
    }
  }
}
/*测试画线*/
void testline(){
  uint16_t color = 0x00FF;
  screen.fillScreen(0x0000);
  for (int16_t x=0; x < screen.width(); x+=6) {
    /*
     *@brief 画线段
     *@param x0 第一个顶点横坐标
     *       y0 第一个顶点纵坐标
     *       x1 第二个顶点横坐标
     *       y1 第二个顶点纵坐标
     *       c 线段颜色
     */
    screen.drawLine(screen.width()/*屏幕宽度*//2, screen.height()/*屏幕高度*//2, x, 0, color+=0x0700);
  }
  for (int16_t y=0; y < screen.height(); y+=6) {
    screen.drawLine(screen.width()/2, screen.height()/2, screen.width(), y, color+=0x0700);
  }
 
  for (int16_t x = screen.width(); x >= 0; x-=6) {
    screen.drawLine(screen.width()/2, screen.height()/2, x,screen.height(), color+=0x0700);
  }
  for (int16_t y = screen.height(); y >= 0; y-=6) {
    screen.drawLine(screen.width()/2, screen.height()/2, 0, y, color+=0x0700);
  }
}
/*测试快速画线(需设置延时)，只有横线和纵线*/
void testfastlines(uint16_t color1, uint16_t color2) {
  for (int16_t y=0; y < screen.height(); y+=4) {
    /*
     *@brief 画线段
     *@param x 第一个顶点横坐标
     *       y 第一个顶点纵坐标
     *       w 线段的长度
     *       c 线段颜色
     */
    screen.drawFastHLine(0, y, screen.width(), color2);
    delay(10);
  }
  for(int16_t x=0; x < screen.width(); x+=4) {
    /*
     *@brief 画线段
     *@param x 第一个顶点横坐标
     *       y 第一个顶点纵坐标
     *       h 线段的长度
     *       c 线段颜色
     */
    screen.drawFastVLine(x, 0, screen.height(), color1);
    delay(10);
  }
}
/*测试画矩形*/
void testrects(uint16_t color1, uint16_t color2) {
  /*
   *@brief 画填充矩形
   *@param x 顶点横坐标
   *@param y 顶点纵坐标
   *@param w 横向边长
   *@param h 纵向边长
   *@param color 填充颜色，565结构的RGB色
   */
  screen.fillRect(6,6, screen.width()-12, screen.width()-12, color1);
    int16_t x=screen.width()-12;
    for (; x > 100; x-=12) {
      /*
       *@brief 画空心矩形
       *@param x 顶点横坐标
       *@param y 顶点纵坐标
       *@param w 横向边长
       *@param h 纵向边长
       *@param color 填充颜色，565结构的RGB色
       */
      screen.drawRect(screen.width()/2 -x/2, screen.height()/2 -x/2 , x, x, color2+=0x0F00);
      delay(100);
    }
    screen.fillRect(screen.width()/2 -x/2, screen.height()/2 -x/2 , x, x, color2);
    delay(100);
    for(; x > 6; x-=6){
      screen.drawRect(screen.width()/2 -x/2, screen.height()/2 -x/2 , x, x, color1);
      delay(100);
    }
}
/*测试画圆角矩形*/
void testroundrects() {
  screen.fillScreen(COLOR_RGB565_BLACK);
  int color = 0xF00F;
  int i;
  int x = 0;
  int y = 0;
  int w = screen.width()-3;
  int h = screen.height()-3;
  for(i = 0 ; i <= 16; i+=2) {
    /*
     *@brief 画空心圆角矩形
     *@param x0 起始顶点横坐标
     *@param y0 起始顶点纵坐标
     *@param w 横向边长
     *@param h 纵向边长
     *@param radius 圆角半径
     *@param color 边框颜色，565结构的RGB色
     */
    screen.drawRoundRect(x, y, w, h, 20, color);
    x+=5;
    y+=5;
    w-=10;
    h-=10;
    color+=0x0100;
    delay(50);
  }
  for(i = 0 ; i <= 16; i+=2) {
    /*
     *@brief 画填充圆角矩形
     *@param x0 起始顶点横坐标
     *@param y0 起始顶点纵坐标
     *@param w 横向边长
     *@param h 纵向边长
     *@param radius 圆角半径
     *@param color 填充颜色，565结构的RGB色
     */
    screen.fillRoundRect(x, y, w, h, 10, color);
    x+=5;
    y+=5;
    w-=10;
    h-=10;
    color+=0x0500;
    delay(50);
  }
}
/*测试画圆*/
void testcircles(uint8_t radius, uint16_t color) {
  screen.fillScreen(COLOR_RGB565_BLACK);
  for (int16_t x=radius; x <=screen.width()-radius; x+=radius*2) {
    for (int16_t y=radius; y <=screen.height()-radius; y+=radius*2) {
      /*
       *@brief 画空心圆
       *@param x0 圆心横坐标
       *@param y0 圆心纵坐标
       *@param r 半径
       *@param color 圆周颜色，565结构的RGB色
       */
      screen.drawCircle(x, y, radius, color);
        if(x == y ||x == -y)
          /*
           *@brief 画填充圆
           *@param x0 圆心横坐标
           *@param y0 圆心纵坐标
           *@param r 半径
           *@param color 填充颜色，565结构的RGB色
           */
          screen.fillCircle(x, y, radius, color);
       color += 800;
       delay(100);
    }
  }
}
/*测试画三角形*/
void testtriangles(uint16_t color){
  screen.fillScreen(COLOR_RGB565_BLACK);
  for (int16_t i=0; i <=screen.width(); i+=24)
    /*
     *@brief 画空心三角形
     *@param x0 起始顶点横坐标
     *@param y0 起始顶点纵坐标
     *@param x1 第二个顶点横坐标
     *@param y1 第二个顶点纵坐标
     *@param x2 第三个顶点横坐标
     *@param y2 第三个顶点纵坐标
     *@param color 边框颜色，565结构的RGB色
     */
    screen.drawTriangle(i,0,0,239-i,239-i,239, color);
  for (int16_t i=0; i <screen.width(); i+=24)
    screen.drawTriangle(239,i,0,239-i,i,0, color);
  for (int16_t i=0; i <screen.width(); i+=24)
    screen.drawTriangle(239,i,i,0,239-i,239, color);
  color = COLOR_RGB565_RED;
  for (int16_t i=0; i <=screen.width(); i+=24)
    /*
     *@brief 画填充三角形
     *@param x0 起始顶点横坐标
     *@param y0 起始顶点纵坐标
     *@param x1 第二个顶点横坐标
     *@param y1 第二个顶点纵坐标
     *@param x2 第三个顶点横坐标
     *@param y2 第三个顶点纵坐标
     *@param color 填充颜色，565结构的RGB色
     */
    screen.fillTriangle(i,0,0,239-i,239-i,239, color+=100);
  for (int16_t i=0; i <screen.width(); i+=24)
    screen.fillTriangle(239,i,0,239-i,i,0, color+=100);
  for (int16_t i=0; i <screen.width(); i+=24)
    screen.fillTriangle(239,i,i,0,239-i,239, color+=100);
}

void testprint() {
  int16_t color = 0x00FF;
  screen.setTextWrap(false);
  screen.fillScreen(COLOR_RGB565_BLACK);
  screen.setCursor(0, 50);
  screen.setTextColor(color+=0x3000);
  screen.setTextSize(0);
  screen.println("Hello World!");
  screen.setTextColor(color+=0x3000);
  screen.setTextSize(1);
  screen.println("Hello World!");
  screen.setTextColor(color+=0x3000);
  screen.setTextSize(2);
  screen.println("Hello World!");
  screen.setTextColor(color+=0x3000);
  screen.setTextSize(3);
  screen.println("Hello World!");
  screen.setTextColor(color+=0x3000);
  screen.setTextSize(4);
  screen.println("Hello!");
  screen.setTextSize(5);
  screen.print("Hello!");
  delay(2000);
  screen.setCursor(0, 0);
  screen.fillScreen(COLOR_RGB565_BLACK);
  screen.setTextSize(2);
  screen.setTextColor(color+=0x3000);
  screen.print("a = ");
  screen.setTextColor(color+=0x3000);
  int a = 1234;
  screen.println(a, 1);
  screen.setTextColor(color+=0x3000);
  screen.print(8675309, HEX);
  screen.println("this is HEX!");
  screen.println("");
  screen.setTextColor(color+=0x0F00);
  screen.println("running for: ");
  screen.setTextColor(color+=0x0F00);
  screen.print(millis());
  screen.setTextColor(color+=0x0F00);
  screen.println("/1000 seconds.");
  char *text = "Hi DFRobot!";
  screen.setTextColor(color+=0x0F00);
  screen.setTextWrap(true);
  screen.setTextSize(3);
  screen.println(text);
  //screen.setFonts((const gdl_Font_t *)SIMKAIFont18ptBitmaps);
  screen.println(text);
  delay(2000);
}