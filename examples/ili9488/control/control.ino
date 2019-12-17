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
DFRobot_UI ui(320, 480);
DFRobot_Touch_GT911 gt911;
sSlider_t slider ;
sSwitch_t sw;
sButton_t bu1 ;
sButton_t bu2 ;
sButton_t bu3 ;
sTextBox_t tb;
void scan(uint16_t * pos) {
  gt911.getPoint1(&pos[0], &pos[1]);
  gt911.getPoint2(&pos[2], &pos[3]);
  gt911.getPoint3(&pos[4], &pos[5]);
  gt911.getPoint4(&pos[6], &pos[7]);
  gt911.getPoint5(&pos[8], &pos[9]);
}
void fillRect(uint16_t x1, uint16_t y1, uint16_t width , uint16_t height, uint16_t color) {
  screen.fillRect(x1, y1, width, height, color);
}

void changeColor(uint16_t value){
   char str[3];
   itoa((int)value, str, 10);
   
   memcpy(tb.text,"slider's value is ", 19);
   memcpy(tb.text+19,"\0", 1);
   memcpy(tb.text + 18, str, 3);
   tb.state = DRAWTEXT;
}

void buCallback(char * text){
    switch(*text){
        case 'A' :{
          tb.cache = 'A';
          tb.state = ADDCHAR; 
          break;
          }
        case 'B' :{
          tb.cache = 'B';
          tb.state = ADDCHAR; 
          break;
          }
        case 'C' :tb.state = CLEARACHAR;break;
        default  :tb.state = NOCHANGE;break;
        }

}
void swCallBack(uint8_t state){
  if(state == 0){
        memcpy(tb.text, "you have turn off the Switch!", 29);
        tb.state = DRAWTEXT;
  }
  else if (state == 1){
            memcpy(tb.text, "you have turn on the Switch!", 28);
        tb.state = DRAWTEXT; 
  }
  }
void setup()
{

  Serial.begin(9600);
  gt911.begin();
  screen.begin();
  ui.setDrawFunction(fillRect);
  ui.setTouchFunction(scan);
  ui.setTheme(THEME1);
  ui.begin();
  
  slider.pos_x =10;
  slider.pos_y =300;
  slider.height =10;
  slider.width = 300;
  slider.slider_width =40;
  slider.slider_height =40;
  slider.bg_color = 0xC618;
  slider.fg_color = 0xff0;
  slider.value = 50 ;
  slider.range = 100 ;
  slider.callBack = changeColor;
  slider.change = false; 
  ui.creatSlider(&slider);
  
  sw.pos_x =45;
  sw.pos_y = 160;
  sw.callBack = swCallBack;
  ui.creatSwitch(&sw);

  bu1.pos_x =100;
  bu1.pos_y = 220;
  bu1.callBack =buCallback;
  memcpy(bu1.text, "B", 1);
  ui.creatButton(&bu1);

  bu2.pos_x =30;
  bu2.pos_y = 220;
  bu2.callBack =buCallback;
  memcpy(bu2.text, "A", 1);
  ui.creatButton(&bu2);
 
  bu3.pos_x =170;
  bu3.pos_y = 220;
  bu3.callBack =buCallback;
  memcpy(bu3.text, "C", 1);
  ui.creatButton(&bu3);
  
  ui.creatText(&tb);
}


void loop()
{
   uint16_t pos[10];
   scan(pos);
  //Serial.println(pos_x);
   ui.refreshSliser(&slider, pos);
   ui.refreshSwitch(&sw , pos);
   ui.refreshButton(&bu1, pos);
      ui.refreshTextBox(&tb, pos);
   ui.refreshButton(&bu2, pos);
      ui.refreshTextBox(&tb, pos);
   ui.refreshButton(&bu3, pos);
      ui.refreshTextBox(&tb, pos);


}