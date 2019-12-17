#include "DFRobot_UI.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>
DFRobot_UI::DFRobot_UI(DFRobot_GDL *gdl, uint16_t width, uint16_t height) {
  lcd_width = width;
  lcd_height = height;
  cursorState = true;
  theme = THEME2;
  _gdl = gdl;
}
void DFRobot_UI:: begin() 
{
  bg_color = GREEN_RGB565;
  pressed = 0 ;
  _gdl->fillRect(0, 0, lcd_width, lcd_height, bg_color);
}
void DFRobot_UI::setTheme(sTheme_t the) 
{
  theme = the;
}
void DFRobot_UI::creatText(sTextBox_t *tb) 
{
  tb->pos_x = 5;
  tb->pos_y = 10;
  tb->width = lcd_width - 10;
  tb->height = lcd_height / 4;
  tb->state  = DRAWBOX;
  tb->bg_color = WHITE_RGB565;
  tb->fontSize = lcd_height / 160 ;
  tb->state == NOCHANGE;
  if (theme == THEME1) {
    _gdl->fillRoundRect(tb->pos_x - 2, tb->pos_y - 2, tb->width + 4, tb->height + 4, 12, DARKGREY_RGB565);
    _gdl->fillRoundRect(tb->pos_x, tb->pos_y, tb->width, tb->height, 10, tb->bg_color);
  }
  else {
    _gdl->fillRect(tb->pos_x - 2, tb->pos_y - 2, tb->width + 4, tb->height + 4, DARKGREY_RGB565);
    _gdl->fillRect(tb->pos_x, tb->pos_y, tb->width, tb->height, tb->bg_color);
  }

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
      _gdl->fillRoundRect(tb->pos_x, tb->pos_y, tb->width, tb->height, 10, tb->bg_color);
    }
    else {
      _gdl->fillRect(tb->pos_x, tb->pos_y, tb->width, tb->height, tb->bg_color);
    }
    //tb->state = NOCHANGE;
  }
  if (tb->state == DRAWTEXT) {
    for (uint8_t i = 0 ; i < strlen(tb->text); i++) {

      _gdl->drawChar(offset_x + tb->pos_x + 8 * tb->fontSize * column, offset_y + tb->pos_y + 8 * tb->fontSize * line, tb->text[i] , tb->fg_color, tb->bg_color, tb->fontSize);
      column++;
      if (column >= tb->width / (8 * tb->fontSize) - 1) {
        column = 0 ;
        line++;
      }
      tb->state = NOCHANGE;
      if (line > tb->height / (8 * tb->fontSize) - 1) return;
      tb->cursor_x = column;
      tb->cursor_y = line;
    }

  }
  else if (tb->state == CLEARACHAR) {
    tb->text[strlen(tb->text) - 1] = '\0';
    tb->cursor_x = strlen(tb->text) % singleWord;
    tb->cursor_y = strlen(tb->text) / singleWord;
    _gdl->fillRect(tb->cursor_x * (8 * tb->fontSize) + offset_x + tb->pos_x, tb->cursor_y * (8 * tb->fontSize) + offset_y + tb->pos_y, 8 * tb->fontSize, 8 * tb->fontSize, tb->bg_color);
    tb->state = NOCHANGE;
    if (line > tb->height / (8 * tb->fontSize) - 1) return;

  }
  else if (tb->state == ADDCHAR) {
    tb->text[strlen(tb->text) + 1] = '\0';
    tb->text[strlen(tb->text)] =  tb->cache;
    _gdl->drawChar(tb->cursor_x * (8 * tb->fontSize) + offset_x + tb->pos_x, tb->cursor_y * (8 * tb->fontSize) + offset_y + tb->pos_y, tb->cache , tb->fg_color, tb->bg_color, tb->fontSize);
    tb->cursor_x = strlen(tb->text) % singleWord;
    tb->cursor_y = strlen(tb->text) / singleWord;
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
    _gdl->fillRoundRect(bu->pos_x - 1, bu->pos_y - 1, bu->width + 2, bu->height + 2, 11, DCYAN_RGB565);
    _gdl->fillRoundRect(bu->pos_x, bu->pos_y, bu->width, bu->height, 10, bu->bg_color);
  }
  else {
    _gdl->fillRect(bu->pos_x, bu->pos_y, bu->width, bu->height, bu->bg_color);

  }
  // Serial.println(bu->text[0]);
  drawButtonString(bu, CENTER, CENTER, bu->text  );
}
void DFRobot_UI::creatButton(sButton_t *bu) 
{
  bu->width = lcd_width / 5;
  bu->height = lcd_height / 10;
  bu->fg_color = BLACK_RGB565;
  bu->bg_color = LIGHTGREY_RGB565;
  bu->fontSize = (lcd_height * 3) / 480 ;
  bu->click  = 0 ;
  if (theme == THEME1) {
    _gdl->fillRoundRect(bu->pos_x - 1, bu->pos_y - 1, bu->width + 2, bu->height + 2, 11, DARKGREY_RGB565);
    _gdl->fillRoundRect(bu->pos_x, bu->pos_y, bu->width, bu->height, 10, bu->bg_color);
  }
  else {
    _gdl->fillRect(bu->pos_x, bu->pos_y, bu->width, bu->height, bu->bg_color);

  }
  // Serial.println(bu->text[0]);
  drawButtonString(bu, CENTER, CENTER, bu->text);
}
void DFRobot_UI::updateCoordinate()
{ if (position) free(position);
  String str = scan();
  number  = pointNum(str);
  
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
    _gdl->fillRoundRect(bu->pos_x - 1, bu->pos_y - 1, bu->width + 2, bu->height + 2, 11, bu->fg_color);
    //fillRoundRect(bu->pos_x, bu->pos_y, bu->width, bu->height, 10, bu->bg_color);
  }
  else {
    _gdl->fillRect(bu->pos_x, bu->pos_y, bu->width, bu->height, bu->fg_color);
    //fillRect(bu->pos_x, bu->pos_y, bu->width, bu->height, bu->bg_color);
  }
  drawButtonString(bu, CENTER, CENTER, bu->text );
}

void  DFRobot_UI::creatTableview(sTableview_t *tv) 
{
  tv->offset = 10 ;
  for (uint8_t i = 0 ; i < tv->numPage; i++) {
    tv->text[i].pos_x = tv->offset + (lcd_width / (tv->numPage)) * i;
    tv->text[i].pos_y = tv->offset;
    tv->text[i].width = lcd_width / (tv->numPage) - tv->offset;
    tv->text[i].height = lcd_height / 10;
    tv->text[i].bg_color = CYAN_RGB565;
    tv->text[i].fg_color = BLACK_RGB565;
    tv->highLightPage = 1;
    tv->text[i].fontSize = tv->text[i].width / (64) ;
    tv->text[i].click  = 0 ;
  }

  for (uint8_t i = 0 ; i < tv->numPage; i++) {
    drawButton(&tv->text[i]);
    //Serial.println(i);
  }
  _gdl->fillRect(tv->text[0].pos_x, tv->text[0].pos_y + tv->text[0].height + 10, tv->text[0].width , 10, MAROON_RGB565);

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
  Serial.println(pressed);
  if (pressed == 1) {
    for (uint8_t i = 0 ; i < tv->numPage; i++) {

      if (buttonRelease(&tv->text[i], position[0].x, position[0].y) == 1) {
        drawButton(&tv->text[i]);
        if (tv->callback != NULL && tv->highLightPage != (i + 1)) {
          _gdl->fillRect(0, 0, 320, 480, bg_color);
          for (uint8_t i = 0 ; i < tv->numPage; i++) {
            drawButton(&tv->text[i]);
          }
          _gdl->fillRect(tv->text[i].pos_x, tv->text[i].pos_y + tv->text[i].height + 10, tv->text[i].width , 10, MAROON_RGB565);
          tv->highLightPage = i + 1;
          tv->callback(tv->highLightPage);
        }
      }
    }
  }
}

void  DFRobot_UI::creatSlider(sSlider_t *slider) 
{

  uint8_t edgeWidth = lcd_width / 160;
  slider->slider_pos = (slider->width * slider->value) / slider->range + slider->pos_x ;
  //fillRect(0,0,lcd_width,lcd_height,bg_color);
  slider->slider_pos = (slider->width * slider->value) / slider->range + slider->pos_x ;
  _gdl->fillRoundRect(slider->pos_x - edgeWidth, slider->pos_y - edgeWidth, slider->width + 2 * edgeWidth, slider->height + 2 * edgeWidth, slider->height / 2, DARKGREY_RGB565);
  _gdl->fillRoundRect(slider->pos_x, slider->pos_y, slider->width , slider->height, slider->height / 2, slider->bg_color);
  // fillRoundRect(slider->pos_x,slider->pos_y,slider->range,10,5,slider->bg_color);
  _gdl->fillRoundRect(slider->pos_x, slider->pos_y, slider->slider_pos, slider->height, slider->height / 2, slider->fg_color);
  _gdl->fillRoundRect(slider->pos_x + slider->slider_pos - slider->slider_width / 2 - edgeWidth, slider->pos_y - (slider->slider_height - slider->height) / 2 - edgeWidth, slider->slider_width + 2 * edgeWidth, slider->slider_height + 2 * edgeWidth, slider->slider_width / 10, DARKGREY_RGB565);
  _gdl->fillRoundRect(slider->pos_x + slider->slider_pos - slider->slider_width / 2, slider->pos_y - (slider->slider_height - slider->height) / 2, slider->slider_width, slider->slider_height, slider->slider_width / 10, LIGHTGREY_RGB565);
}
void DFRobot_UI::refreshSliser(sSlider_t *slider) 
{
  if (number == 0) return;
  uint8_t edgeWidth = lcd_width / 160;
  char str[10];
  slider->slider_pos = (slider->width * slider->value) / slider->range + slider->pos_x ;
  uint16_t slider_x = slider->pos_x + slider->slider_pos - slider->slider_width / 2;
  uint16_t slider_y = slider->pos_y + slider->height / 2 - slider->slider_height / 2 ;

  if (slider->change == 0) {
    if (position[0].x > slider_x && (position[0].x < slider_x + slider->slider_width) && ((position[0].y > slider_y) && (position[0].y < slider_y + slider->slider_height))) {
      slider->change = 1;

    }
  }
  if (slider->change == 1) {

    if (position[0].x < slider->pos_x || (position[0].x > slider->pos_x + slider->width) || ((position[0].y < slider_y) || (position[0].y > slider_y + slider->slider_height))) {
      slider->change = 0;
      if (slider->callBack )  {
        slider->callBack(slider->value);
      }

    }
  }
  slider->slider_pos = position[0].x - slider->pos_x;
  if (slider->change == 1) {
    slider->value = ((position[0].x - slider->pos_x) * (slider->range)) / slider->width ;

    _gdl->fillRect(slider->pos_x - slider->height / 2, slider->pos_y - (slider->slider_height - slider->height) / 2 - 2 * edgeWidth, slider->width + slider->height + 4 * edgeWidth, slider->slider_height + 4 * edgeWidth, bg_color);
    _gdl->fillRoundRect(slider->pos_x - edgeWidth, slider->pos_y - edgeWidth, slider->width + 2 * edgeWidth, slider->height + 2 * edgeWidth, slider->height / 2, DARKGREY_RGB565);
    _gdl->fillRoundRect(slider->pos_x, slider->pos_y, slider->width , slider->height, slider->height / 2, slider->bg_color);
    _gdl->fillRoundRect(slider->pos_x, slider->pos_y, slider->slider_pos, slider->height, slider->height / 2, slider->fg_color);
    _gdl->fillRoundRect(slider->pos_x + slider->slider_pos - slider->slider_width / 2 - edgeWidth, slider->pos_y - (slider->slider_height - slider->height) / 2 - edgeWidth, slider->slider_width + 2 * edgeWidth, slider->slider_height + 2 * edgeWidth, slider->slider_width / 10, DARKGREY_RGB565);
    _gdl->fillRoundRect(slider->pos_x + slider->slider_pos  - slider->slider_width / 2, slider->pos_y - (slider->slider_height - slider->height) / 2, slider->slider_width, slider->slider_height, slider->slider_width / 10, LIGHTGREY_RGB565);
    _gdl->fillRect(slider->pos_x + slider->width / 2, slider->pos_y + 40 , 40, 40, bg_color);
    itoa(slider->value, str, 10);
    drawString(slider->pos_x + slider->width / 2, slider->pos_y + 40, str, DARKCYAN_RGB565, bg_color, 2, 1);
  }

  //scan(&touch_x, &touch_y);
  /*if (touch_x > slider->pos_x && (touch_x < slider->pos_x + slider->width) && ((touch_y > slider->pos_y) && (touch_y < slider->pos_y +slider->height))){
       slider->value = ((touch_x - slider->pos_x)*(slider->range))/slider->width ;
       slider->slider_pos = touch_x - slider->pos_x;
       slider->change = true;
    }

    if(slider->change == true && slider->slider_pos != touch_x - slider->pos_x){
    slider->change = false;
    fillRect(slider->pos_x-slider->height/2,slider->pos_y-(slider->slider_height-slider->height)/2-2*edgeWidth,slider->width+slider->height+4 * edgeWidth,slider->slider_height + 4* edgeWidth,bg_color);
    fillRoundRect(slider->pos_x-edgeWidth,slider->pos_y-edgeWidth,slider->width + 2 * edgeWidth,slider->height +2 * edgeWidth,slider->height/2,DARKGREY_RGB565);
    fillRoundRect(slider->pos_x,slider->pos_y,slider->width ,slider->height,slider->height/2,slider->bg_color);
    fillRoundRect(slider->pos_x,slider->pos_y,slider->slider_pos,slider->height,slider->height/2,slider->fg_color);
    fillRoundRect(slider->pos_x+slider->slider_pos -slider->slider_width/2-edgeWidth,slider->pos_y-(slider->slider_height-slider->height)/2-edgeWidth,slider->slider_width+2 * edgeWidth,slider->slider_height+2 * edgeWidth,slider->slider_width/10,DARKGREY_RGB565);
    fillRoundRect(slider->pos_x+slider->slider_pos  -slider->slider_width/2,slider->pos_y-(slider->slider_height-slider->height)/2,slider->slider_width,slider->slider_height,slider->slider_width/10,LIGHTGREY_RGB565);
    fillRect(slider->pos_x + slider->width/2, slider->pos_y + 40 ,40,40,bg_color);
    itoa(slider->value,str,10);
    drawString(slider->pos_x + slider->width/2, slider->pos_y + 40, str, DARKCYAN_RGB565, bg_color, 2,1);
    if(slider->callBack)  {slider->callBack(slider->value);}
    }
  */

}


void  DFRobot_UI::creatSwitch(sSwitch_t *sw) 
{

  sw->fg_color = LIGHTGREY_RGB565;
  sw->bg_color = bg_color;
  sw->width = lcd_width / 5;
  sw->height = lcd_height / 20;
  sw->state = 0;
  sw->laststate = 0; //fillRoundRect(100,100,100,100,20,10);
  _gdl->fillRoundRect(sw->pos_x - 1, sw->pos_y - 1, sw->width + 2, sw->height + 2, sw->height / 2, DARKGREY_RGB565);
  _gdl->fillRoundRect(sw->pos_x, sw->pos_y, sw->width, sw->height, sw->height / 2, sw->fg_color);
  _gdl->fillCircle(sw->pos_x, sw->pos_y + sw->height / 2, sw->height / (1.2) + 1,  DARKGREY_RGB565);
  _gdl->fillCircle(sw->pos_x, sw->pos_y + sw->height / 2, sw->height / (1.2),  sw->fg_color);
}
void DFRobot_UI::refreshSwitch(sSwitch_t *sw) {
  if (number == 0) return;
#if defined (__AVR__)
  if (sw->change == false ) {
    if (((position[0].x > sw->pos_x) && (position[0].x < sw->pos_x + sw->width)) && ((position[0].y > sw->pos_y) && (position[0].y < sw->pos_y + sw->height))) {
      sw->change = true;
      sw->state = 1 - sw->state ;
    }
  }
  if (sw->change == true && (((position[0].x < sw->pos_x) || (position[0].x > sw->pos_x + sw->width)) || ((position[0].y < sw->pos_y) || (position[0].y > sw->pos_y + sw->height)))) {
    sw->change = false;
    _gdl->fillRect(sw->pos_x - sw->height / (1.2) - 1 , sw->pos_y - sw->height / (1.2), sw->width + sw->height * 2, (sw->height / (1.2)) * 3 , bg_color);
    if (sw->state == 1 ) {
      _gdl->fillRoundRect(sw->pos_x - 1, sw->pos_y - 1, sw->width + 2, sw->height + 2, sw->height / 2, DARKGREY_RGB565);
      _gdl->fillRoundRect(sw->pos_x, sw->pos_y, sw->width, sw->height, sw->height / 2, BLUE_RGB565);
      _gdl->fillCircle(sw->pos_x + sw->width , sw->pos_y + sw->height / 2, sw->height / (1.2) + 1,  DARKGREY_RGB565);
      _gdl->fillCircle(sw->pos_x + sw->width, sw->pos_y + sw->height / 2, sw->height / (1.2),  NAVY_RGB565);

    }
    if (sw->state == 0) {
      _gdl->fillRoundRect(sw->pos_x - 1, sw->pos_y - 1, sw->width + 2, sw->height + 2, sw->height / 2, DARKGREY_RGB565);
      _gdl->fillRoundRect(sw->pos_x, sw->pos_y, sw->width, sw->height, sw->height / 2, sw->fg_color);
      _gdl->fillCircle(sw->pos_x, sw->pos_y + sw->height / 2, sw->height / (1.2) + 1,  DARKGREY_RGB565);
      _gdl->fillCircle(sw->pos_x, sw->pos_y + sw->height / 2, sw->height / (1.2),  sw->fg_color);
    }
    if (sw ->callBack) sw ->callBack(sw->state);
  }
#else
  if (sw->change == false ) {
    for (uint8_t i = 0 ; i < number ; i++) {
      if (((position[i].x > sw->pos_x) && (position[i].x < sw->pos_x + sw->width)) && ((position[i].y > sw->pos_y) && (position[i].y < sw->pos_y + sw->height))) {
        sw->change = true;
        sw->state = 1 - sw->state ;
        break;
      }
    }
  }
  uint8_t n = 0;
  if (sw->change == true) {
    for (uint8_t i = 0 ; i < number ; i++) {
      if ((((position[i].x < sw->pos_x) || (position[i].x > sw->pos_x + sw->width)) || ((position[i].y < sw->pos_y) || (position[i].y > sw->pos_y + sw->height)))) {
        n++;
      }
      if (n == number) {
        sw->change = false;
        _gdl->fillRect(sw->pos_x - sw->height / (1.2) - 1 , sw->pos_y - sw->height / (1.2), sw->width + sw->height * 2, (sw->height / (1.2)) * 3 , bg_color);
        if (sw->state == 1 ) {
          _gdl->fillRoundRect(sw->pos_x - 1, sw->pos_y - 1, sw->width + 2, sw->height + 2, sw->height / 2, DARKGREY_RGB565);
          _gdl->fillRoundRect(sw->pos_x, sw->pos_y, sw->width, sw->height, sw->height / 2, BLUE_RGB565);
          _gdl->fillCircle(sw->pos_x + sw->width , sw->pos_y + sw->height / 2, sw->height / (1.2) + 1,  DARKGREY_RGB565);
          _gdl->fillCircle(sw->pos_x + sw->width, sw->pos_y + sw->height / 2, sw->height / (1.2),  NAVY_RGB565);

        }
        if (sw->state == 0) {
          _gdl->fillRoundRect(sw->pos_x - 1, sw->pos_y - 1, sw->width + 2, sw->height + 2, sw->height / 2, DARKGREY_RGB565);
          _gdl->fillRoundRect(sw->pos_x, sw->pos_y, sw->width, sw->height, sw->height / 2, sw->fg_color);
          _gdl->fillCircle(sw->pos_x, sw->pos_y + sw->height / 2, sw->height / (1.2) + 1,  DARKGREY_RGB565);
          _gdl->fillCircle(sw->pos_x, sw->pos_y + sw->height / 2, sw->height / (1.2),  sw->fg_color);
        }
        if (sw ->callBack) sw ->callBack(sw->state);
      }
    }
  }
#endif


}
void DFRobot_UI::drawCursor(sTextBox_t *text, uint8_t offset_x, uint8_t offset_y, bool state) 
{
  uint16_t  x = text->pos_x + offset_x + ((text->fontSize) * 8) * (text->cursor_x) + 2;



  uint16_t  y = text->pos_y + offset_y + (text->fontSize) * 8 * (text->cursor_y);
  uint16_t color ;
  if (state == 1 ) {
    color = text->bg_color;
  }
  else {
    color = text->fg_color;
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

  if ((x > bu->pos_x && x < ( bu->pos_x + bu->width)) && (y > bu->pos_y && y < ( bu->pos_y + bu->height)))
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
    po_x =  bu->pos_x + bu->width / 2 - (4 * bu->fontSize) / 2 ;
    po_y =  bu->pos_y + bu->height / 2 - (8 * bu->fontSize) / 2;
    po_x = po_x - bu->fontSize * 8 * (strlen(c) - 1) * (0.5);
  }
  else if (x == LEFT && y == CENTER) {
    po_x =  bu->pos_x ;
    po_y =  bu->pos_y + bu->height / 2 - (8 * bu->fontSize) / 2 ;
  }

  for (uint16_t i = 0 ; i < strlen(c) ; i++) {
    b = c[i];
    if (bu->click == 0) {
      _gdl->drawChar(po_x + i * 8 * bu->fontSize, po_y, b, bu->fg_color, bu->bg_color, bu->fontSize);
    }
    else {
      _gdl->drawChar(po_x + i * 8 * bu->fontSize, po_y, b, bu->bg_color, bu->fg_color, bu->fontSize);
    }
  }
}

//draw a char
void DFRobot_UI::drawString(int16_t x, int16_t y, char * c, uint16_t color, uint16_t bg, uint8_t size, boolean mode) 
{
  char b ;
  //Serial.print("c :");
  //Serial.println(sizeof(c));
  for (uint16_t i = 0 ; i < strlen(c); i++) {
    b = c[i];
    _gdl->drawChar(x + i * 6 * size, y, b, color, bg, size);
  }
}


String DFRobot_UI::pointToString(uint16_t *point)
{

  String str = "";
  uint8_t num;
  for (uint8_t i = 0; i < 10;) {
    str += "1";
    str += ",";
    str += point[i];
    str += ",";
    str += point[i + 1];
    str += ",";
    str += "10";
    str += ",";
    str += "10";
    str += " ";
    i += 2;
  }
  return str;
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



