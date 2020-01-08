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
DFRobot_UI::sButton_t bu1 ;
DFRobot_UI::sButton_t bu2 ;
DFRobot_UI::sButton_t bu3 ;
DFRobot_UI::sTextBox_t tb;
String scan() {

  return gt911.scan();
}

void buCallback(char * text) {
  switch (*text) {
    case 'A' : {
        ui.textAddChar(&tb,'A');
        break;
      }
    case 'B' : {
        ui.textAddChar(&tb,'B');
        break;
      }
    case 'C' :         ui.textAddChar(&tb,'C');; break;
    default  :  break;
  }

}
void setup()
{

  Serial.begin(9600);
  gt911.begin();
  screen.begin();
  ui.setTouchFunction(scan);
  ui.setTheme(DFRobot_UI::THEME1);
  ui.begin();

  bu1.posx = 100;
  bu1.posy = 220;
  bu1.callBack = buCallback;
  memcpy(bu1.text, "B", 1);
  ui.creatButton(&bu1);

  bu2.posx = 30;
  bu2.posy = 220;
  bu2.callBack = buCallback;
  memcpy(bu2.text, "A", 1);
  ui.creatButton(&bu2);

  bu3.posx = 170;
  bu3.posy = 220;
  bu3.callBack = buCallback;
  memcpy(bu3.text, "C", 1);
  ui.creatButton(&bu3);

  ui.creatText(&tb);
}


void loop()
{
  // 修改为其它方式传入点坐标
  ui.updateCoordinate();
  ui.refreshButton(&bu1);
  ui.refreshTextBox(&tb);
  ui.refreshButton(&bu2);
  ui.refreshTextBox(&tb);
  ui.refreshButton(&bu3);
  ui.refreshTextBox(&tb);
}