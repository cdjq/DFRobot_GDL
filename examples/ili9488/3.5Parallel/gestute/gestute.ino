#include "DFRobot_UI.h"
#include "Arduino.h"
#include "DFRobot_GDL.h"
#include "DFRobot_Touch.h"

#define RST 42
#define WR 41
#define RD 40
#define CS 38
#define RS 39

#define d0 22
#define d1 23
#define d2 24
#define d3 25
#define d4 26
#define d5 27
#define d6 28
#define d7 29
#define d8 37
#define d9 36
#define d10 35
#define d11 34
#define d12 33
#define d13 32
#define d14 31
#define d15 30

DFRobot_ILI9488_480x320 screen(CS, RS, WR, RD, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15/*,BL,RST*/);
DFRobot_UI ui(&screen, 320, 480);
DFRobot_Touch_GTxxx gt911;

DFRobot_UI::sTextBox_t tb;
String scan() {

  return gt911.scan();
}

void setup()
{

  Serial.begin(9600);
  gt911.begin();
  screen.begin();
  
  ui.begin();
  ui.setTouchFunction(scan);
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