#include "DFRobot_UI.h"
#include "Arduino.h"
#include "DFRobot_GDL.h"
#include "DFRobot_Touch.h"

#include <LCDWIKI_TOUCH.h> //touch screen library
LCDWIKI_TOUCH gt911(2,3,4,5,6); //tcs,tclk,tdout,tdin,tirq

#define SPI_RST 8
#define SPI_CS 7
#define SPI_DC 6

DFRobot_ILI9488_320x480_HW_SPI screen(SPI_DC,SPI_CS);
DFRobot_UI ui(&screen, 320, 480);


DFRobot_UI::sTextBox_t tb;
String scan() {

  return gt911.scan();
}

void setup()
{

  Serial.begin(9600);
  gt911.begin(320,480);
  screen.begin();
  ui.setTouchFunction(scan);
  ui.setTheme(DFRobot_UI::THEME1);
  ui.begin();
    pinMode(SPI_RST,OUTPUT);
  digitalWrite(SPI_RST, HIGH);
  ui.creatText(&tb);
   ui.drawString(10, 240,"Gesture recognition area",0xffff, ui.bgColor, 2, 0);
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