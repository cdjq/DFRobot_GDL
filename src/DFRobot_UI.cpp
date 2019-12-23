#include "DFRobot_UI.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>
DFRobot_UI::DFRobot_UI(DFRobot_GDL *gdl, uint16_t width, uint16_t height) {
  lcdWidth = width;
  lcdHeight = height;
  cursorState = true;
  theme = THEME2;
  _gdl = gdl;
}
void DFRobot_UI:: begin() 
{
  bgColor = GREEN_RGB565;
  pressed = 0 ;
  timer = 0 ;
  timer1 = 0 ;
  click = 0 ;
  screenPressed = 0;
  _gdl->fillRect(0, 0, lcdWidth, lcdHeight, bgColor);
}
void DFRobot_UI::setTheme(sTheme_t the) 
{
  theme = the;
}
void DFRobot_UI::creatText(sTextBox_t *tb) 
{
  tb->posx = 5;
  tb->posy = 10;
  tb->width = lcdWidth - 10;
  tb->height = lcdHeight / 4;
  tb->state  = DRAWBOX;
  tb->bgColor = WHITE_RGB565;
  tb->fontSize = lcdHeight / 160 ;
  tb->state == NOCHANGE;
  if (theme == THEME1) {
    _gdl->fillRoundRect(tb->posx - 2, tb->posy - 2, tb->width + 4, tb->height + 4, 12, DARKGREY_RGB565);
    _gdl->fillRoundRect(tb->posx, tb->posy, tb->width, tb->height, 10, tb->bgColor);
  }
  else {
    _gdl->fillRect(tb->posx - 2, tb->posy - 2, tb->width + 4, tb->height + 4, DARKGREY_RGB565);
    _gdl->fillRect(tb->posx, tb->posy, tb->width, tb->height, tb->bgColor);
  }

}
void DFRobot_UI::setText(sTextBox_t *te,char * text){
  memcpy(te->text, text, strlen(text));
  memcpy(te->text + strlen(text), "\0", 1);
  te->state = DRAWTEXT;
}
void DFRobot_UI::textAddChar(sTextBox_t *te,char txt){
  te->cache = txt;
  te->state = ADDCHAR;
}
void DFRobot_UI::refreshTextBox(sTextBox_t *tb) 
{
  uint8_t column = 0;
  uint8_t line = 0 ;
  uint8_t offset_x, offset_y;
  uint8_t singleWord = tb->width / (8 * tb->fontSize) - 1;
  offset_x = 5;
  offset_y = 5 ;
  if (tb->state == DRAWTEXT) {
    if (theme == THEME1 ) {
      _gdl->fillRoundRect(tb->posx, tb->posy, tb->width, tb->height, 10, tb->bgColor);
    }
    else {
      _gdl->fillRect(tb->posx, tb->posy, tb->width, tb->height, tb->bgColor);
    }
    //tb->state = NOCHANGE;
  }
  if (tb->state == DRAWTEXT) {
    for (uint8_t i = 0 ; i < strlen(tb->text); i++) {
      _gdl->drawChar(offset_x + tb->posx + 8 * tb->fontSize * column, offset_y + tb->posy + 8 * tb->fontSize * line, tb->text[i] , tb->fgColor, tb->bgColor, tb->fontSize);
      column++;
      if (column >= tb->width / (8 * tb->fontSize) - 1) {
        column = 0 ;
        line++;
      }
      tb->state = NOCHANGE;
      if (line > tb->height / (8 * tb->fontSize) - 1) return;
      tb->cursorx = column;
      tb->cursory = line;
    }

  }
  else if (tb->state == CLEARACHAR) {
    tb->text[strlen(tb->text) - 1] = '\0';
    tb->cursorx = strlen(tb->text) % singleWord;
    tb->cursory = strlen(tb->text) / singleWord;
    _gdl->fillRect(tb->cursorx * (8 * tb->fontSize) + offset_x + tb->posx, tb->cursory * (8 * tb->fontSize) + offset_y + tb->posy, 8 * tb->fontSize, 8 * tb->fontSize, tb->bgColor);
    tb->state = NOCHANGE;
    if (line > tb->height / (8 * tb->fontSize) - 1) return;

  }
  else if (tb->state == ADDCHAR) {
    tb->text[strlen(tb->text) + 1] = '\0';
    tb->text[strlen(tb->text)] =  tb->cache;
    _gdl->drawChar(tb->cursorx * (8 * tb->fontSize) + offset_x + tb->posx, tb->cursory * (8 * tb->fontSize) + offset_y + tb->posy, tb->cache , tb->fgColor, tb->bgColor, tb->fontSize);
    tb->cursorx = strlen(tb->text) % singleWord;
    tb->cursory = strlen(tb->text) / singleWord;
    tb->state = NOCHANGE;
    if (line > tb->height / (8 * tb->fontSize) - 1) return;


  }
  drawCursor(tb, offset_x, offset_y, 0);
  delay(50);
  drawCursor(tb, offset_x, offset_y, 1);

}

void DFRobot_UI::setTouchFunction(scanF* fuc) 
{
  scan = fuc;
}
void DFRobot_UI::drawButton(sButton_t *bu) {
  if (theme == THEME1) {
    _gdl->fillRoundRect(bu->posx - 1, bu->posy - 1, bu->width + 2, bu->height + 2, 11, DCYAN_RGB565);
    _gdl->fillRoundRect(bu->posx, bu->posy, bu->width, bu->height, 10, bu->bgColor);
  }
  else {
    _gdl->fillRect(bu->posx, bu->posy, bu->width, bu->height, bu->bgColor);

  }
  // Serial.println(bu->text[0]);
  drawButtonString(bu, CENTER, CENTER, bu->text  );
}
void DFRobot_UI::creatButton(sButton_t *bu) 
{
  bu->width = lcdWidth / 5;
  bu->height = lcdHeight / 10;
  bu->fgColor = BLACK_RGB565;
  bu->bgColor = LIGHTGREY_RGB565;
  bu->fontSize = (lcdHeight * 3) / 480 ;
  bu->click  = 0 ;
  if (theme == THEME1) {
    _gdl->fillRoundRect(bu->posx - 1, bu->posy - 1, bu->width + 2, bu->height + 2, 11, DARKGREY_RGB565);
    _gdl->fillRoundRect(bu->posx, bu->posy, bu->width, bu->height, 10, bu->bgColor);
  }
  else {
    _gdl->fillRect(bu->posx, bu->posy, bu->width, bu->height, bu->bgColor);

  }
  // Serial.println(bu->text[0]);
  drawButtonString(bu, CENTER, CENTER, bu->text);
}
void DFRobot_UI::updateCoordinate()
{ 
  if (position) free(position);
  String str = scan();
  number  = pointNum(str);
 //Serial.println(number);
  position = (sPoint_t*)malloc(number * sizeof(sPoint_t));

  
  if (position == NULL) {
    while (1);
  }
  stringToPoint(str, position);
}
void DFRobot_UI::refreshButton(sButton_t *bu) {
  if (number == 0) return;
#if defined (__AVR__)
  if (judgePress(bu, position[0].x, position[0].y) == true && bu->click == 0) {
    bu->click = 1;
    drawClickButton(bu);
  }

  if ( judgePress(bu, position[0].x, position[0].y) == false && bu->click == 1) {
    bu->click = 0;
    bu->callBack(bu->text);
    drawButton(bu);
  }
#else

  uint8_t n = 0;
  for (uint8_t i = 0; i < number; i++) {
    if (judgePress(bu, position[i].x, position[i].y) == true && bu->click == 0){
      bu->click = 1;
      drawClickButton(bu);
      break;
    }
  }
  for (uint8_t i = 0; i < number; i++) {

    if (judgePress(bu, position[i].x, position[i].y) == false) {
      n++;
    }
    if (n == number && bu->click == 1) {
      bu->click = 0;
      bu->callBack(bu->text);
      drawButton(bu);
    }
  }
#endif
}

void DFRobot_UI::drawClickButton(sButton_t *bu) 
{

  if (theme == THEME1) {
    _gdl->fillRoundRect(bu->posx - 1, bu->posy - 1, bu->width + 2, bu->height + 2, 11, bu->fgColor);
    //fillRoundRect(bu->posx, bu->posy, bu->width, bu->height, 10, bu->bgColor);
  }
  else {
    _gdl->fillRect(bu->posx, bu->posy, bu->width, bu->height, bu->fgColor);
    //fillRect(bu->posx, bu->posy, bu->width, bu->height, bu->bgColor);
  }
  drawButtonString(bu, CENTER, CENTER, bu->text );
}

void  DFRobot_UI::creatTableview(sTableview_t *tv) 
{
  tv->offset = 10 ;
  for (uint8_t i = 0 ; i < tv->numPage; i++) {
    tv->text[i].posx = tv->offset + (lcdWidth / (tv->numPage)) * i;
    tv->text[i].posy = tv->offset;
    tv->text[i].width = lcdWidth / (tv->numPage) - tv->offset;
    tv->text[i].height = lcdHeight / 10;
    tv->text[i].bgColor = CYAN_RGB565;
    tv->text[i].fgColor = BLACK_RGB565;
    tv->highLightPage = 1;
    tv->text[i].fontSize = tv->text[i].width / (64) ;
    tv->text[i].click  = 0 ;
  }

  for (uint8_t i = 0 ; i < tv->numPage; i++) {
    drawButton(&tv->text[i]);
    //Serial.println(i);
  }
  _gdl->fillRect(tv->text[0].posx, tv->text[0].posy + tv->text[0].height + 10, tv->text[0].width , 10, MAROON_RGB565);

}

void DFRobot_UI::refreshTableview(sTableview_t *tv) 
{
  if (number == 0) return;
  if (pressed == 0) {
    for (uint8_t i = 0 ; i < tv->numPage; i++) {
      if (buttonPressed(&tv->text[i], position[0].x, position[0].y) == 1) {
        drawClickButton(&tv->text[i]);
        break;
      }
    }
  }
  if (pressed == 1) {
    for (uint8_t i = 0 ; i < tv->numPage; i++) {

      if (buttonRelease(&tv->text[i], position[0].x, position[0].y) == 1) {
        drawButton(&tv->text[i]);
        if (tv->callback != NULL && tv->highLightPage != (i + 1)) {
          _gdl->fillRect(0, tv->text[i].posy + tv->text[i].height +1 , 320, 400, bgColor);
          _gdl->fillRect(tv->text[i].posx, tv->text[i].posy + tv->text[i].height + 10, tv->text[i].width , 10, MAROON_RGB565);
          tv->highLightPage = i + 1;
          tv->callback(tv->highLightPage);
        }
      }
    }
  }
}

void DFRobot_UI::creatBar(sBar_t *bar){
  uint8_t edgeWidth = lcdWidth / 160;
  bar->width = lcdWidth-50;
  bar->height = lcdHeight/40;
  bar->fgColor = DARKGREY_RGB565;
  bar->bgColor = 0xffff;
  bar->lastValue = 0;
  bar->value = 0;
  bar->sliderPos = (bar->width * bar->value) / 100 + bar->posx ;
  _gdl->fillRoundRect(bar->posx - edgeWidth, bar->posy - edgeWidth, bar->width + 2 * edgeWidth, bar->height + 2 * edgeWidth, bar->height / 2, DARKGREY_RGB565);
  _gdl->fillRoundRect(bar->posx, bar->posy, bar->width , bar->height, bar->height / 2, bar->bgColor);
  _gdl->setCursor((bar->posx+bar->width)/2,bar->posy+bar->height+5);
  _gdl->setTextColor(bar->fgColor, bgColor);
  _gdl->setTextSize(2);
  _gdl->print(bar->value);
  _gdl->print("%");
}
void DFRobot_UI::refreshBar(sBar_t *bar){
  bar->sliderPos = (bar->width * bar->value) / 100 + bar->posx ;
  if(bar->callBack) bar->callBack();
  if(bar->value >= 100)  bar->value = 100 ;

  for(uint8_t i = bar->lastValue; i < bar->value+1;i++){
  _gdl->fillRoundRect(bar->posx, bar->posy, i*(bar->width)/100, bar->height, bar->height / 2, bar->fgColor);
   bar->lastValue = bar->value;
  _gdl->setCursor((bar->posx+bar->width)/2,bar->posy+bar->height+5);
  _gdl->setTextColor(bar->fgColor, bgColor);
  _gdl->setTextSize(2);
  _gdl->print(bar->value);
  _gdl->print("%");
  }

}
void  DFRobot_UI::creatSlider(sSlider_t *slider) 
{

  uint8_t edgeWidth = lcdWidth / 160;
  slider->height = lcdHeight/100;
  slider->width = lcdWidth-20;
  slider->sliderWidth = lcdWidth / 16;
  slider->sliderHeight = lcdHeight / 24;
  slider->bgColor = 0x00;
  slider->fgColor = 0xff0;
  slider->value = 10 ;
  slider->range = 100 ;
  slider->change = false;
  slider->sliderPos = (slider->width * slider->value) / slider->range + slider->posx ;
  //fillRect(0,0,lcdWidth,lcdHeight,bgColor);
  slider->sliderPos = (slider->width * slider->value) / slider->range + slider->posx ;
  _gdl->fillRoundRect(slider->posx - edgeWidth, slider->posy - edgeWidth, slider->width + 2 * edgeWidth, slider->height + 2 * edgeWidth, slider->height / 2, DARKGREY_RGB565);
  _gdl->fillRoundRect(slider->posx, slider->posy, slider->width , slider->height, slider->height / 2, slider->bgColor);
  // fillRoundRect(slider->posx,slider->posy,slider->range,10,5,slider->bgColor);
  _gdl->fillRoundRect(slider->posx, slider->posy, slider->sliderPos, slider->height, slider->height / 2, slider->fgColor);
  _gdl->fillRoundRect(slider->posx + slider->sliderPos - slider->sliderWidth / 2 - edgeWidth, slider->posy - (slider->sliderHeight - slider->height) / 2 - edgeWidth, slider->sliderWidth + 2 * edgeWidth, slider->sliderHeight + 2 * edgeWidth, slider->sliderWidth / 10, DARKGREY_RGB565);
  _gdl->fillRoundRect(slider->posx + slider->sliderPos - slider->sliderWidth / 2, slider->posy - (slider->sliderHeight - slider->height) / 2, slider->sliderWidth, slider->sliderHeight, slider->sliderWidth / 10, LIGHTGREY_RGB565);
}
void DFRobot_UI::refreshSliser(sSlider_t *slider) 
{
  if (number == 0) return;
  uint8_t edgeWidth = lcdWidth / 160;
  char str[10];
  slider->sliderPos = (slider->width * slider->value) / slider->range + slider->posx ;
  uint16_t slider_x = slider->posx + slider->sliderPos - slider->sliderWidth / 2;
  uint16_t slider_y = slider->posy + slider->height / 2 - slider->sliderHeight / 2 ;

  if (slider->change == 0) {
    if (position[0].x > slider_x && (position[0].x < slider_x + slider->sliderWidth) && ((position[0].y > slider_y) && (position[0].y < slider_y + slider->sliderHeight))) {
      slider->change = 1;

    }
  }
  if (slider->change == 1) {

    if (position[0].x < slider->posx || (position[0].x > slider->posx + slider->width) || ((position[0].y < slider_y) || (position[0].y > slider_y + slider->sliderHeight))) {
      slider->change = 0;
      if (slider->callBack )  {
        slider->callBack(slider->value);
      }

    }
  }
  slider->sliderPos = position[0].x - slider->posx;
  if (slider->change == 1) {
    slider->value = ((position[0].x - slider->posx) * (slider->range)) / slider->width ;
    _gdl->fillRoundRect(slider->posx + slider->lastsliderPos - slider->sliderWidth / 2 - edgeWidth, slider->posy - (slider->sliderHeight - slider->height) / 2 - edgeWidth, slider->sliderWidth + 2 * edgeWidth, slider->sliderHeight + 2 * edgeWidth, slider->sliderWidth / 10, GREEN_RGB565);
    _gdl->fillRect(slider->posx - slider->height / 2, slider->posy - (slider->sliderHeight - slider->height) / 2 - 2 * edgeWidth, slider->width + slider->height + 4 * edgeWidth, slider->sliderHeight + 4 * edgeWidth, bgColor);
    _gdl->fillRoundRect(slider->posx - edgeWidth, slider->posy - edgeWidth, slider->width + 2 * edgeWidth, slider->height + 2 * edgeWidth, slider->height / 2, DARKGREY_RGB565);
    _gdl->fillRoundRect(slider->posx, slider->posy, slider->width , slider->height, slider->height / 2, slider->bgColor);
    _gdl->fillRoundRect(slider->posx, slider->posy, slider->sliderPos, slider->height, slider->height / 2, slider->fgColor);
    _gdl->fillRoundRect(slider->posx + slider->sliderPos - slider->sliderWidth / 2 - edgeWidth, slider->posy - (slider->sliderHeight - slider->height) / 2 - edgeWidth, slider->sliderWidth + 2 * edgeWidth, slider->sliderHeight + 2 * edgeWidth, slider->sliderWidth / 10, DARKGREY_RGB565);
    _gdl->fillRoundRect(slider->posx + slider->sliderPos  - slider->sliderWidth / 2, slider->posy - (slider->sliderHeight - slider->height) / 2, slider->sliderWidth, slider->sliderHeight, slider->sliderWidth / 10, LIGHTGREY_RGB565);
    //_gdl->fillRect(slider->posx + slider->width / 2, slider->posy + 40 , 20, 20, bgColor);
    itoa(slider->value, str, 10);
    _gdl->setTextColor(DARKCYAN_RGB565, bgColor);
    _gdl->setTextSize(2);
    _gdl->setCursor(slider->posx + slider->width / 2,slider->posy + 40);
    _gdl->print(slider->value);
  }
     slider->lastsliderPos = slider->sliderPos;
  //scan(&touch_x, &touch_y);
  /*if (touch_x > slider->posx && (touch_x < slider->posx + slider->width) && ((touch_y > slider->posy) && (touch_y < slider->posy +slider->height))){
       slider->value = ((touch_x - slider->posx)*(slider->range))/slider->width ;
       slider->sliderPos = touch_x - slider->posx;
       slider->change = true;
    }

    if(slider->change == true && slider->sliderPos != touch_x - slider->posx){
    slider->change = false;
    fillRect(slider->posx-slider->height/2,slider->posy-(slider->sliderHeight-slider->height)/2-2*edgeWidth,slider->width+slider->height+4 * edgeWidth,slider->sliderHeight + 4* edgeWidth,bgColor);
    fillRoundRect(slider->posx-edgeWidth,slider->posy-edgeWidth,slider->width + 2 * edgeWidth,slider->height +2 * edgeWidth,slider->height/2,DARKGREY_RGB565);
    fillRoundRect(slider->posx,slider->posy,slider->width ,slider->height,slider->height/2,slider->bgColor);
    fillRoundRect(slider->posx,slider->posy,slider->sliderPos,slider->height,slider->height/2,slider->fgColor);
    fillRoundRect(slider->posx+slider->sliderPos -slider->sliderWidth/2-edgeWidth,slider->posy-(slider->sliderHeight-slider->height)/2-edgeWidth,slider->sliderWidth+2 * edgeWidth,slider->sliderHeight+2 * edgeWidth,slider->sliderWidth/10,DARKGREY_RGB565);
    fillRoundRect(slider->posx+slider->sliderPos  -slider->sliderWidth/2,slider->posy-(slider->sliderHeight-slider->height)/2,slider->sliderWidth,slider->sliderHeight,slider->sliderWidth/10,LIGHTGREY_RGB565);
    fillRect(slider->posx + slider->width/2, slider->posy + 40 ,40,40,bgColor);
    itoa(slider->value,str,10);
    drawString(slider->posx + slider->width/2, slider->posy + 40, str, DARKCYAN_RGB565, bgColor, 2,1);
    if(slider->callBack)  {slider->callBack(slider->value);}
    }
  */

}


void  DFRobot_UI::creatSwitch(sSwitch_t *sw) 
{

  sw->fgColor = LIGHTGREY_RGB565;
  sw->bgColor = bgColor;
  sw->width = lcdWidth / 5;
  sw->height = lcdHeight / 20;
  sw->state = 0;
  sw->laststate = 0; //fillRoundRect(100,100,100,100,20,10);
  _gdl->fillRoundRect(sw->posx - 1, sw->posy - 1, sw->width + 2, sw->height + 2, sw->height / 2, DARKGREY_RGB565);
  _gdl->fillRoundRect(sw->posx, sw->posy, sw->width, sw->height, sw->height / 2, sw->fgColor);
  _gdl->fillCircle(sw->posx, sw->posy + sw->height / 2, sw->height / (1.2) + 1,  DARKGREY_RGB565);
  _gdl->fillCircle(sw->posx, sw->posy + sw->height / 2, sw->height / (1.2),  sw->fgColor);
}
void DFRobot_UI::refreshSwitch(sSwitch_t *sw) {
  if (number == 0) return;
#if defined (__AVR__)
  if (sw->change == false ) {
    if (((position[0].x > sw->posx) && (position[0].x < sw->posx + sw->width)) && ((position[0].y > sw->posy) && (position[0].y < sw->posy + sw->height))) {
      sw->change = true;
      sw->state = 1 - sw->state ;
    }
  }
  if (sw->change == true && (((position[0].x < sw->posx) || (position[0].x > sw->posx + sw->width)) || ((position[0].y < sw->posy) || (position[0].y > sw->posy + sw->height)))) {
    sw->change = false;
    _gdl->fillRect(sw->posx - sw->height / (1.2) - 1 , sw->posy - sw->height / (1.2), sw->width + sw->height * 2, (sw->height / (1.2)) * 3 , bgColor);
    if (sw->state == 1 ) {
      _gdl->fillRoundRect(sw->posx - 1, sw->posy - 1, sw->width + 2, sw->height + 2, sw->height / 2, DARKGREY_RGB565);
      _gdl->fillRoundRect(sw->posx, sw->posy, sw->width, sw->height, sw->height / 2, BLUE_RGB565);
      _gdl->fillCircle(sw->posx + sw->width , sw->posy + sw->height / 2, sw->height / (1.2) + 1,  DARKGREY_RGB565);
      _gdl->fillCircle(sw->posx + sw->width, sw->posy + sw->height / 2, sw->height / (1.2),  NAVY_RGB565);

    }
    if (sw->state == 0) {
      _gdl->fillRoundRect(sw->posx - 1, sw->posy - 1, sw->width + 2, sw->height + 2, sw->height / 2, DARKGREY_RGB565);
      _gdl->fillRoundRect(sw->posx, sw->posy, sw->width, sw->height, sw->height / 2, sw->fgColor);
      _gdl->fillCircle(sw->posx, sw->posy + sw->height / 2, sw->height / (1.2) + 1,  DARKGREY_RGB565);
      _gdl->fillCircle(sw->posx, sw->posy + sw->height / 2, sw->height / (1.2),  sw->fgColor);
    }
    if (sw ->callBack) sw ->callBack(sw->state);
  }
#else
  if (sw->change == false ) {
    for (uint8_t i = 0 ; i < number ; i++) {
      if (((position[i].x > sw->posx) && (position[i].x < sw->posx + sw->width)) && ((position[i].y > sw->posy) && (position[i].y < sw->posy + sw->height))) {
        sw->change = true;
        sw->state = 1 - sw->state ;
        break;
      }
    }
  }
  uint8_t n = 0;
  if (sw->change == true) {
    for (uint8_t i = 0 ; i < number ; i++) {
      if ((((position[i].x < sw->posx) || (position[i].x > sw->posx + sw->width)) || ((position[i].y < sw->posy) || (position[i].y > sw->posy + sw->height)))) {
        n++;
      }
      if (n == number) {
        sw->change = false;
        _gdl->fillRect(sw->posx - sw->height / (1.2) - 1 , sw->posy - sw->height / (1.2), sw->width + sw->height * 2, (sw->height / (1.2)) * 3 , bgColor);
        if (sw->state == 1 ) {
          _gdl->fillRoundRect(sw->posx - 1, sw->posy - 1, sw->width + 2, sw->height + 2, sw->height / 2, DARKGREY_RGB565);
          _gdl->fillRoundRect(sw->posx, sw->posy, sw->width, sw->height, sw->height / 2, BLUE_RGB565);
          _gdl->fillCircle(sw->posx + sw->width , sw->posy + sw->height / 2, sw->height / (1.2) + 1,  DARKGREY_RGB565);
          _gdl->fillCircle(sw->posx + sw->width, sw->posy + sw->height / 2, sw->height / (1.2),  NAVY_RGB565);

        }
        if (sw->state == 0) {
          _gdl->fillRoundRect(sw->posx - 1, sw->posy - 1, sw->width + 2, sw->height + 2, sw->height / 2, DARKGREY_RGB565);
          _gdl->fillRoundRect(sw->posx, sw->posy, sw->width, sw->height, sw->height / 2, sw->fgColor);
          _gdl->fillCircle(sw->posx, sw->posy + sw->height / 2, sw->height / (1.2) + 1,  DARKGREY_RGB565);
          _gdl->fillCircle(sw->posx, sw->posy + sw->height / 2, sw->height / (1.2),  sw->fgColor);
        }
        if (sw ->callBack) sw ->callBack(sw->state);
      }
    }
  }
#endif


}
void DFRobot_UI::drawCursor(sTextBox_t *text, uint8_t offset_x, uint8_t offset_y, bool state) 
{
  uint16_t  x = text->posx + offset_x + ((text->fontSize) * 8) * (text->cursorx) + 2;



  uint16_t  y = text->posy + offset_y + (text->fontSize) * 8 * (text->cursory);
  uint16_t color ;
  if (state == 1 ) {
    color = text->bgColor;
  }
  else {
    color = text->fgColor;
  }

  _gdl->fillRect(x, y, 2, text->fontSize * 8, color);

}

bool DFRobot_UI::buttonPressed(sButton_t *bu , uint16_t touch_x, uint16_t touch_y)
{


  if (judgePress(bu, touch_x, touch_y) == true) {

    if (bu->click == 0 ) {
      pressed = 1;
      bu->click = 1;
      return 1;
    }

  }
  return 0;
}

bool DFRobot_UI::buttonRelease(sButton_t *bu , uint16_t touch_x, uint16_t touch_y) 
{

  if (judgePress(bu, touch_x, touch_y) == false) {

    if (bu->click == 1) {
      pressed = 0;
      bu->click = 0;
      return 1;
    }
  }
  return 0;
}

bool DFRobot_UI::judgePress(sButton_t *bu, uint16_t x, uint16_t y) {

  if ((x > bu->posx && x < ( bu->posx + bu->width)) && (y > bu->posy && y < ( bu->posy + bu->height)))
  {
    return true;
  }
  else
  {
    return false;
  }


}

void DFRobot_UI::drawButtonString(sButton_t *bu , sLocation x, sLocation y, char * c) 
{

  int16_t po_x, po_y;

  char b ;
  
  if (x == CENTER && y == CENTER) {
    po_x =  bu->posx + bu->width / 2 - (4 * bu->fontSize) / 2 ;
    po_y =  bu->posy + bu->height / 2 - (8 * bu->fontSize) / 2;
    po_x = po_x - bu->fontSize * 8 * (strlen(c) - 1) * (0.5);
  }
  else if (x == LEFT && y == CENTER) {
    po_x =  bu->posx ;
    po_y =  bu->posy + bu->height / 2 - (8 * bu->fontSize) / 2 ;
  }
  uint8_t length = (bu->width)/(8 * bu->fontSize);
  if(length >= strlen(c)) length = strlen(c);
  for (uint16_t i = 0 ; i < length ; i++) {
    b = c[i];
    if (bu->click == 0) {
      _gdl->drawChar(po_x + i * 8 * bu->fontSize, po_y, b, bu->fgColor, bu->bgColor, bu->fontSize);
    }
    else {
      _gdl->drawChar(po_x + i * 8 * bu->fontSize, po_y, b, bu->bgColor, bu->fgColor, bu->fontSize);
    }
  }
}

//draw a char
void DFRobot_UI::drawString(int16_t x, int16_t y, char * c, uint16_t color, uint16_t bg, uint8_t size, boolean mode) 
{
  char b ;
   _gdl->setTextColor(color, bg);
   _gdl->setTextSize(size);
  for (uint16_t i = 0 ; i < strlen(c); i++) {
    b = c[i];
    _gdl->setCursor(x + i * 6 * size,y);
    _gdl->print(b);
  }

}

uint8_t DFRobot_UI::pointNum(String str)
{

  uint8_t num = 0;
  for (uint8_t i = 0; i < str.length(); i++) {
    if (str[i] == ' ') num++;
  }
  return num;

}
uint8_t DFRobot_UI::stringToPoint(String str, sPoint_t *point) 
{
  char pin[4];
  uint8_t nowi = 0;
  uint8_t n = 0;
  uint8_t b = 0;
  //Serial.println(str.length());
  for (uint8_t i = 0; i < str.length(); i++) {

    if (str[i] == ',' || str[i] == ' ')
    {
      n = 0;
      if (nowi == 0) point[b].id = atoi(pin);
      if (nowi == 1) point[b].x = atoi(pin);
      if (nowi == 2) point[b].y = atoi(pin);
      if (nowi == 3) point[b].wSize = atoi(pin);
      if (nowi == 4) {
        point[b].hSize = atoi(pin);
        b++;
      }
      nowi++;
      if (nowi == 5)nowi = 0;
      memset(pin, '\0', 4);
      continue;
    }
    pin[n] = str[i];
    n++;
  }

}
bool DFRobot_UI::focus(uint16_t x,uint16_t y){
  if(((x > 1) && (x < lcdWidth)) && ( (y > 1) && (y < lcdHeight) )){
     return true;
  }
  else{
     return false;
  }
}
bool DFRobot_UI::press(uint16_t x,uint16_t y)
{

   if(focus(x,y) == true){

        if(screenPressed == 0 ){
           screenPressed = 1;
            return true;
        }
   }
  return false;
}

bool DFRobot_UI::release(uint16_t x,uint16_t y){
   if(focus(x,y) != true){
        if(screenPressed == 1){
           screenPressed = 0;

           return true;
        }

  }
  return false;
}
DFRobot_UI::sGestures_t DFRobot_UI::getGestures()
{

    uint16_t x,y;
    int interval = 0;

     if(lastGestute != LONGPRESSDE || millis() - timer1 > 2000){
     if(millis() - timer1 >=500){
            if(interval >=500 || click == 1){
             click = 0;
             lastGestute = SINGLECLICK;
             return SINGLECLICK;
          }
            else if(click == 2){
             click = 0;
            lastGestute = DOUBLECLICK;
            return  DOUBLECLICK;
            }
         }
     }
    if (press(position[0].x,position[0].y) == true){
        
        bx1 = position[0].x;
        by1 = position[0].y;
        timer = millis();
    }

    if(release(position[0].x,position[0].y) == true){
        x = bx2;
        y = by2;
        //timer = millis();
        if (x >= 50 +bx1) return RIGHTGLIDE;
        else if (bx1  >= 50 +x) return LEFTGLIDE;
        else if(y  >= 50 + by1)  return DOWNGLIDE;
        else if(by1 >= 50 + y) return UPGLIDE;
        else if((x < 50 +bx1 && y < 50 + by1 && x > bx1 -50 && y > by1 -50 )&&(click == 0)) {
                   click = 1;
        if(lastGestute == LONGPRESSDE) {
                click = 0;   
           lastGestute = NONE;
               }
                   timer1 = millis();
                   return NONE;
         }
        else if((x < 50 +bx1 && y < 50 + by1 && x > bx1 -50 && y > by1 -50 )&&(click == 1)){
                  click = 2 ;
                  interval = millis() - timer1 ;
                   return NONE;
          }

 
}
 
 
    if((millis() - timer >=2000) && screenPressed == 1){
        if(position[0].x < bx1 + 10 && position[0].x > bx1 - 10 && position[0].y < by1 + 10 && position[0].y > by1 - 10){
            screenPressed = 0;
            lastGestute = LONGPRESSDE;
            return LONGPRESSDE;
     }
      }
    bx2 = position[0].x;
    by2 = position[0].y;
    return NONE;

}

