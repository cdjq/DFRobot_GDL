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
  gt911.begin(320,480);
  screen.begin();
  ui.setTouchFunction(scan);
  ui.setTheme(DFRobot_UI::THEME1);
  ui.begin();
    pinMode(SPI_RST,OUTPUT);
  digitalWrite(SPI_RST, HIGH);
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