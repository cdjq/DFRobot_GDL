#include "DFRobot_UI.h"
#include "Arduino.h"
#include "DFRobot_GDL.h"
#include "DFRobot_Touch.h"




#define SPI_CS 3
#define SPI_DC 4
DFRobot_Touch_XPTxxx gt911(2); //tcs,tclk,tdout,tdin,tirq
DFRobot_ST7789_240x320_HW_SPI screen(SPI_DC,SPI_CS);
DFRobot_UI ui(&screen, 240, 320);


DFRobot_UI::sTextBox_t tb;
String scan() {

  return gt911.scan();
}

void setup()
{

  Serial.begin(9600);
  gt911.begin();
  screen.begin();
  ui.setTouchFunction(scan);
  ui.setTheme(DFRobot_UI::THEME1);
  ui.begin();
  ui.creatText(&tb);
  ui.setGestureArea(40,100,150,150);
   //ui.drawString(10, 240,"Gesture recognition areasadasdasdasdasdasd",0xffff, ui.bgColor, 2, 0);
}


void loop()
{
    //DFRobot_UI::sGestures_t ge;
    ui.updateCoordinate();
    switch(ui.getGestures()){
      case ui.UPGLIDE : ui.setText(&tb,"upwards slide"); break;
      case ui.DOWNGLIDE : ui.setText(&tb,"down slide"); break;
      case ui.LEFTGLIDE : ui.setText(&tb,"left slide"); break;
      case ui.RIGHTGLIDE : ui.setText(&tb,"right slide"); break;
      case ui.LONGPRESSDE : ui.setText(&tb,"long press"); break;
      case ui.SINGLECLICK : ui.setText(&tb,"click"); break;
      case ui.DOUBLECLICK : ui.setText(&tb,"double click"); break;
      default  :  break;
      }
   ui.refreshTextBox(&tb);


   
}