#include "DFRobot_UI.h"
#include "Arduino.h"
#include "DFRobot_GDL.h"
#include "DFRobot_Touch.h"

#define SPI_CS 3
#define SPI_DC 4
DFRobot_Touch_XPTxxx gt911(2); //tcs,tclk,tdout,tdin,tirq
DFRobot_ST7789_240x320_HW_SPI screen(SPI_DC,SPI_CS);
DFRobot_UI ui(&screen, 240, 320);
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