/*!
 * @file basicTest.ino
 * @brief 演示各种图形绘画效果 
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
//DFRobot_ST7789_240x240_DMA_SPI screen(TFT_DC,TFT_CS,TFT_RST,TFT_BL);
/*
 *COLOR_RGB565_BLACK     0x0000   //  黑色    
 *COLOR_RGB565_NAVY      0x000F   //  深蓝色  
 *COLOR_RGB565_DGREEN    0x03E0   //  深绿色  
 *COLOR_RGB565_DCYAN     0x03EF   //  深青色  
 *COLOR_RGB565_MAROON    0x7800   //  深红色      
 *COLOR_RGB565_PURPLE    0x780F   //  紫色  
 *COLOR_RGB565_OLIVE     0x7BE0   //  橄榄绿      
 *COLOR_RGB565_LGRAY     0xC618   //  灰白色
 *COLOR_RGB565_DGRAY     0x7BEF   //  深灰色      
 *COLOR_RGB565_BLUE      0x001F   //  蓝色    
 *COLOR_RGB565_GREEN     0x07E0   //  绿色          
 *COLOR_RGB565_CYAN      0x07FF   //  青色  
 *COLOR_RGB565_RED       0xF800   //  红色       
 *COLOR_RGB565_MAGENTA   0xF81F   //  品红    
 *COLOR_RGB565_YELLOW    0xFFE0   //  黄色
 *COLOR_RGB565_ORANGE    0xFD20   //  橙色        
 *COLOR_RGB565_WHITE     0xFFFF   //  白色
 */
void setup() {
  Serial.begin(115200);
  screen.begin();//生成了screen对象
}

void loop(){
    testdrawpixel();
    testline();
    testfastlines(COLOR_RGB565_PURPLE,COLOR_RGB565_YELLOW);       
    testrects(COLOR_RGB565_BLACK,COLOR_RGB565_WHITE);
    testroundrects();
    testcircles(24,COLOR_RGB565_BLUE);
    testtriangles(COLOR_RGB565_YELLOW);
    testprint();

}
/*测试画像素点*/
void testdrawpixel() {
  /*
   *@brief 清屏
   *@param c 屏幕颜色
   */
  screen.fillScreen(0x0000);
  int x = 0;
  int y = 320;
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
    for (y = 319 - i; y >= i; y-=10){
      screen.drawPixel(x, y, COLOR_RGB565_ORANGE);
      delay(10);
    }
    for (x = i; x <= 239 - i + 1; x+=10 ){
      screen.drawPixel(x, y, COLOR_RGB565_ORANGE);
      delay(10);
    }
    for (y = i; y <= 319 - i + 1; y+=10){
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
  for(int16_t x=0; x < screen.width(); x+=3) {
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
  screen.fillScreen(COLOR_RGB565_BLACK);
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
      screen.drawRect(screen.width()/2 -x/2, screen.height()/2 -x*3/4 , x, x*4/3, color2+=0x0F00);
      delay(100);
    }
    screen.fillRect(screen.width()/2 -x/2, screen.height()/2 -x*3/4 , x, x*4/3, color2);
    delay(100);
    for(; x > 6; x-=6){
      screen.drawRect(screen.width()/2 -x/2, screen.height()/2 -x*3/4 , x, x*4/3, color1);
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
        if(x == y ||x == -y ||x == y + 2*radius)
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
    screen.drawTriangle(i,0,0,319-i,239-i,319, color);
  for (int16_t i=0; i <screen.width(); i+=24)
    screen.drawTriangle(239,i*4/3,0,319-i*4/3,i,0, color);
  for (int16_t i=0; i <screen.width(); i+=24)
    screen.drawTriangle(239,i*4/3,i,0,239-i,319, color);
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
    screen.fillTriangle(i,0,0,319-i,239-i,319, color+=100);
  for (int16_t i=0; i <screen.width(); i+=24)
    screen.fillTriangle(239,i*4/3,0,319-i*4/3,i,0, color+=100);
  for (int16_t i=0; i <screen.width(); i+=24)
    screen.fillTriangle(239,i*4/3,i,0,239-i,319, color+=100);
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
