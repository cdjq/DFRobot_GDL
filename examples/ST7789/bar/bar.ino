#include "DFRobot_UI.h"
#include "Arduino.h"
#include "DFRobot_GDL.h"
#include "DFRobot_Touch.h"



#define SPI_CS 3
#define SPI_DC 4

DFRobot_Touch_XPTxxx gt911(2); //tcs,tclk,tdout,tdin,tirq
DFRobot_ST7789_240x320_HW_SPI screen(SPI_DC,SPI_CS);
DFRobot_UI ui(&screen, 240, 320);
DFRobot_UI::sBar_t bar;
String scan() {

  return gt911.scan();
}

void barCallback(){

    bar.value += 1;
   
}
void setup()
{

  Serial.begin(9600);
  gt911.begin();
  screen.begin();
  ui.setTouchFunction(scan);
  ui.setTheme(DFRobot_UI::THEME2);
  ui.begin();

  ui.drawString(10,100,"Page of loading",0xffff,DARKGREY_RGB565,2,0);
  ui.initBar(&bar);
  bar.posx = 50;
  bar.posy = 160;
  bar.callBack = barCallback;
  ui.creatBar(&bar);
}


void loop()
{
  ui.updateCoordinate();
  ui.refreshBar(&bar);
}