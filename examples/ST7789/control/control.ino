#include "DFRobot_UI.h"
#include "Arduino.h"
#include "DFRobot_GDL.h"
#include "DFRobot_Touch.h"



#define SPI_CS 3
#define SPI_DC 4
DFRobot_Touch_XPTxxx gt911(2); //tcs,tclk,tdout,tdin,tirq
DFRobot_ST7789_240x320_HW_SPI screen(SPI_DC,SPI_CS);
DFRobot_UI ui(&screen, 240,320);

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
  slider.posy = 200;

  slider.callBack = changeColor;

  ui.creatSlider(&slider);

  sw.posx = 45;
  sw.posy = 160;
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