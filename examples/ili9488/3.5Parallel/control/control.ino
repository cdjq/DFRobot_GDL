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
DFRobot_UI::sSlider_t slider ;
DFRobot_UI::sSwitch_t sw;
DFRobot_UI::sTextBox_t tb;
String scan() {

  return gt911.scan();
}
void changeColor(uint16_t value) {
  char str[3];
  itoa((int)value, str, 10);

  memcpy(tb.text, "slider's value is ", 19);
  memcpy(tb.text + 19, "\0", 1);
  memcpy(tb.text + 18, str, 3);
  ui.setText(&tb,tb.text);
}
void swCallBack(uint8_t state) {
  if (state == 0) {
    memcpy(tb.text, "you have turn off the Switch!", 29);
    ui.setText(&tb,tb.text);
  }
  else if (state == 1) {
    memcpy(tb.text, "you have turn on the Switch!", 28);
    ui.setText(&tb,tb.text);
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
  slider.posx = 10;
  slider.posy = 300;
  slider.height = 10;
  slider.width = 300;
  slider.sliderWidth = 40;
  slider.sliderHeight = 40;
  slider.bgColor = 0xC618;
  slider.fgColor = 0xff0;
  slider.value = 50 ;
  slider.range = 100 ;
  slider.callBack = changeColor;
  slider.change = false;
  ui.creatSlider(&slider);

  sw.posx = 45;
  sw.posy = 200;
  sw.callBack = swCallBack;
  ui.creatSwitch(&sw);

  ui.creatText(&tb);
}


void loop()
{
  ui.updateCoordinate();
  ui.refreshSliser(&slider);
  ui.refreshSwitch(&sw );
  ui.refreshTextBox(&tb);
}