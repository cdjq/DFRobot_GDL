#include "Arduino.h"
#include "DFRobot_GDL.h"

#define SPI_RST 4
#define SPI_CS 3
#define SPI_DC 5

DFRobot_ILI9488_320x480_HW_SPI screen(SPI_DC,SPI_CS);
void setup() {
  // put your setup code here, to run once:
  pinMode(SPI_RST,OUTPUT);
  digitalWrite(SPI_RST, HIGH);
  Serial.begin(115200);
  screen.begin();
  
  
  
  //screen.fillScreen(0x001F);
  //screen.setColorMode(COLOR_MODE_RGB111);
  screen.fillScreen(0x0001);
  //screen.fillScreen(0x0001);
  
  //screen.fillScreen(0x0001);
  //screen.fillScreen(0x0002);
  //screen.fillScreen(0x0004);
  //screen.setTextSize(4);
  //screen.setTextColor(0xF800, 0x001F);
  screen.println("hello, world!");
   
   screen.setCursor(300,24);
   screen.setTextColor(0x001F,0x0000);
//  
//
  //screen.setFonts(&SIMKAIFont12pt);
  //screen.println("你好世界！");
  //screen.println("你好世界！");
  screen.drawFastHLine(46, 50,100,0x001F);
   screen.setFont(&FreeMonoBold12pt7b);
  screen.println("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz!asdfg");
//   screen.setFont(&FreeMonoBoldOblique12pt7b);
//   screen.println("hello, world!");
//   screen.setFont(&FreeMonoOblique12pt7b);
//   screen.println("hello, world!");

//   screen.setFont(&FreeSans12pt7b);
//   screen.println("hello, world!");
//   screen.setFont(&FreeSansBold12pt7b);
//   screen.println("hello, world!");
//  screen.setFont(&FreeSansBoldOblique12pt7b);
//   screen.println("hello, world!");
//   screen.setFont(&FreeSansOblique12pt7b);
//   screen.println("hello, world!");

//    screen.setFont(&FreeSerif12pt7b);
//   screen.println("hello, world!");
//   screen.setFont(&FreeSerifBold12pt7b);
//   screen.println("hello, world!");
//   screen.setFont(&FreeSerifBoldItalic12pt7b);
//   screen.println("hello, world!");
//   screen.setFont(&FreeSerifItalic12pt7b);
//   screen.println("hello, world!");
//  screen.setFont(&FreeSerifBoldItalic12pt7b);
//   screen.println("hello, world!");
  //screen.println("你好！");
}

void loop() {
  // put your main code here, to run repeatedly:
screen.drawFastHLine(46, 50,100,0x001F);
screen.drawPixel(100, 100,0x001F);
delay(1000);
}
