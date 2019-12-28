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
DFRobot_UI::sTableview_t tv;
String scan() {
  return gt911.scan();
}

void tvCallback(uint8_t highLightPage) {

  if (highLightPage == 1) {
    ui.drawString(10, 200, "this is tab1", 0x0, ui.bgColor, 4, 0);
  }
  if (highLightPage == 2) {
    ui.drawString(10, 200, "this is tab2", 0x00, ui.bgColor, 4, 0);
  }
  if (highLightPage == 3) {
    ui.drawString(10, 200, "this is tab3", 0x00, ui.bgColor, 4, 0);
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
  tv.numPage = 3;
  tv.callback = tvCallback;
  memcpy(tv.text[0].text, "Tab 1", 5);
  memcpy(tv.text[1].text, "Tab 2", 5);
  memcpy(tv.text[2].text, "Tab 3", 5);
  ui.creatTableview(&tv);
}

void loop()
{
  ui.updateCoordinate();
  ui.refreshTableview(&tv);
}