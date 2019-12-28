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
  gt911.begin(320,480);
  screen.begin();
  ui.setTouchFunction(scan);
  ui.setTheme(DFRobot_UI::THEME1);
  ui.begin();
    pinMode(SPI_RST,OUTPUT);
  digitalWrite(SPI_RST, HIGH);
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