/*!
 * @file DFRobot_UI.h
 * @brief DFRobot_UI 基础方法的实现
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2019-12-6
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_GDL/src/DFRpbot_UI
 */
#include "DFRobot_UI.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>


void DFRobot_UI::buttonEvent(void *obj)
{
 // Serial.println("按钮处理函数");
  sObject_t * ob = (sObject_t *)obj;
  sButton_t *btn = (sButton_t *)ob->privateData;
  //Serial.println(ob->posx);
  //Serial.println(ob->posy);
  if(_touch == NULL){
    return;
  }
  if (judgePress(ob, position[0].x, position[0].y) == true && btn->click == 0) {
    btn->click = 1;
    drawClickButton(ob,btn->text,btn->click);
  }
  if ( judgePress(ob, position[0].x, position[0].y) == false && btn->click == 1) {
    btn->click = 0;
    if(btn->callBack)btn->callBack(btn->text);
    drawButton(ob);
  }
}
DFRobot_UI::DFRobot_UI(DFRobot_GDL *gdl,DFRobot_Touch *touch, uint16_t width, uint16_t height) 
{
  lcdWidth = width;
  lcdHeight = height;
  cursorState = true;
  theme = MODERN;
  _gdl = gdl;
  _touch = touch;
}

void DFRobot_UI:: begin()
{
  bgColor = 2312;
  pressed = 0 ;
  timer = 0 ;
  timer1 = 0 ;
  click = 0 ;
  _gdl->begin();
  if(_touch != NULL){
    _touch->begin();
  }
  screenPressed = 0;
  head.posx = 0;
  head.posy = 0;
  head.width = 0;
  head.height = 0;
  head.fgColor = 0;
  head.bgColor = 0;
  head.privateData = NULL;
  head.next = NULL;
  head.event =NULL;
  _gdl->fillRect(0, 0, lcdWidth, lcdHeight, bgColor);
}

void DFRobot_UI::setButtonText(sObject_t* obj,char * c){
  sObject_t * ob = (sObject_t *)obj;
  sButton_t *btn = (sButton_t *)ob->privateData;
  memcpy(btn->text, c, strlen(c));
}
void setButtonCallback(void *obj,DFRobot_UI::buttonCallback *callBack){
  DFRobot_UI::sObject_t * ob = ( DFRobot_UI::sObject_t *)obj;
  DFRobot_UI::sButton_t *btn = (DFRobot_UI::sButton_t *)ob->privateData;
  btn->callBack = callBack;
}
void setBarCallback(void *obj,DFRobot_UI::barCallback *callBack){

  DFRobot_UI::sObject_t * ob = ( DFRobot_UI::sObject_t *)obj;
  DFRobot_UI::sBar_t *bar = (DFRobot_UI::sBar_t *)ob->privateData;
  bar->callBack = callBack;
}
void setSliserCallback(void *obj,DFRobot_UI::sliderCallback *callBack){

  DFRobot_UI::sObject_t * ob = ( DFRobot_UI::sObject_t *)obj;
  DFRobot_UI::sSlider_t *slider = (DFRobot_UI::sSlider_t *)ob->privateData;
  slider->callBack = callBack;
}
void setSwitchCallback(void *obj,DFRobot_UI::switchCallback *callBack){
  DFRobot_UI::sObject_t * ob = ( DFRobot_UI::sObject_t *)obj;
  DFRobot_UI::sSwitch_t *sw = (DFRobot_UI::sSwitch_t *)ob->privateData;
  sw->callBack = callBack;
}

void setTableviewCallback(void *obj,DFRobot_UI::tableViewCallback *callBack){
  DFRobot_UI::sObject_t * ob = ( DFRobot_UI::sObject_t *)obj;
  DFRobot_UI::sTableview_t *tb = (DFRobot_UI::sTableview_t *)ob->privateData;
  tb->callback = callBack;
}
void setKPCallback(void *obj,DFRobot_UI::keyPadCallback *callBack){
  DFRobot_UI::sObject_t * ob = ( DFRobot_UI::sObject_t *)obj;
  DFRobot_UI::sKeyPad_t *kp = (DFRobot_UI::sKeyPad_t *)ob->privateData;
  kp->callBack = callBack;
}
DFRobot_UI::sObject_t *DFRobot_UI::creatButton(){
  sObject_t* btn= (sObject_t*)malloc(sizeof(sObject_t));
  sButton_t *buttonData = (sButton_t *)malloc(sizeof(sButton_t));
  buttonData->fontSize = (lcdHeight * 3) / 480 ;
  memset(buttonData->text, '\0', sizeof(buttonData->text));
  buttonData->click  = 0 ;
  buttonData->callBack = NULL ;
  btn->privateData = NULL;
  btn->next = NULL;
  btn->event = &DFRobot_UI::buttonEvent;
  btn->privateData = buttonData;
  btn->draw = &DFRobot_UI::drawButton;
  btn->setCallBack = setButtonCallback;
  btn->posx = 0;
  btn->posy = 0;
  btn->width = lcdWidth / 4;
  btn->height = lcdHeight / 8;
  btn->fgColor = BLACK_RGB565;
  btn->bgColor = LIGHTGREY_RGB565;
  btn->fontSize = 3;
  sObject_t* obj= &head;

  if(btn == NULL) while(1);

  while(obj->next != NULL){
    obj = obj->next;
  }
  obj->next =  btn;
  return btn;
}

DFRobot_UI::sObject_t *DFRobot_UI::creatText(){
  sObject_t* text= (sObject_t*)malloc(sizeof(sObject_t));
  sTextBox_t *textData = (sTextBox_t *)malloc(sizeof(sTextBox_t));
  textData->state  = DRAWBOX;

  textData->state = NOCHANGE;
  textData->selected = 0 ;
  textData->text[0] = '\0';
  textData->cursorx = 0;
  textData->cursory = 0;
  text->next = NULL;
  text->event = &DFRobot_UI::refreshTextBox;
  text->privateData = textData;
  text->draw = &DFRobot_UI::drawText;
  text->posx = 10;
  text->posy = 10;
  text->width = lcdWidth -20;
  text->height = lcdHeight / 5;
  text->fgColor = BLACK_RGB565;
  text->bgColor = LIGHTGREY_RGB565;
  text->fontSize = lcdHeight / 160;
  sObject_t* obj= &head;

  if(text == NULL) while(1);

  while(obj->next != NULL){
    obj = obj->next;
  }
  obj->next =  text;
  return text;
}
DFRobot_UI::sObject_t *DFRobot_UI::creatKeyPad(){
  sObject_t* kb= (sObject_t*)malloc(sizeof(sObject_t));
  sKeyPad_t *kbData = (sKeyPad_t *)malloc(sizeof(sKeyPad_t));
  kbData->mode = 0;
  kbData->text = 0;
  kbData->callBack = NULL;
  kb->posx =0;
  kb->posy = 0;
  kb->width=100;
  kb->height= 100;
  kb->next = NULL;
  kb->event = &DFRobot_UI::KeyBoardEvent;
  kb->privateData = kbData;
  kb->draw = &DFRobot_UI::drawKeyBoard;
  kb->setCallBack = setKPCallback;
  sObject_t* obj= &head;

  if(kb == NULL) while(1);

  while(obj->next != NULL){
    obj = obj->next;
  }
  obj->next =  kb;
  return kb;
}
DFRobot_UI::sObject_t *DFRobot_UI::creatSwitch()
{
  sObject_t* sw= (sObject_t*)malloc(sizeof(sObject_t));
  sSwitch_t *swData = (sSwitch_t *)malloc(sizeof(sSwitch_t));

  swData->callBack = NULL;
  swData->state = 0;
  swData->laststate = 0;
  sw->posx =0;
  sw->posy = 0;
  sw->width=30;
  sw->height= 10;
  sw->next = NULL;
  sw->fgColor = LIGHTGREY_RGB565;
  sw->bgColor = bgColor;
  sw->event = &DFRobot_UI::switchEvent;
  sw->privateData = swData;
  sw->draw = &DFRobot_UI::drawSwitch;
  sw->setCallBack = setSwitchCallback;
  sObject_t* obj= &head;

  if(sw == NULL) while(1);

  while(obj->next != NULL){
    obj = obj->next;
  }
  obj->next =  sw;
  return sw;
}
void DFRobot_UI::setTableviewName(sObject_t *obj,uint16_t pageNum,char * c1 ,char * c2 ,char * c3,char * c4)
{
  sObject_t * ob = (sObject_t *)obj;
  sTableview_t *tb = (sTableview_t *)ob->privateData;
  strcpy(tb->text[0].text,c1);
  strcpy(tb->text[1].text,c2);
  strcpy(tb->text[2].text,c3);
  strcpy(tb->text[3].text,c4);
  tb->numPage = pageNum;
}
DFRobot_UI::sObject_t *DFRobot_UI::creatTableview(){
  sObject_t* tb= (sObject_t*)malloc(sizeof(sObject_t));
  sTableview_t *tbData = (sTableview_t *)malloc(sizeof(sTableview_t));

  tbData->callback = NULL;
  tbData->offset = 10;
  tbData->highLightPage =0;
  tbData->numPage =4;
  tb->posx =0;
  tb->posy = 0;
  tb->width=100;
  tb->height= 100;
  tb->next = NULL;
  tb->fgColor = LIGHTGREY_RGB565;
  tb->bgColor = bgColor;
  tb->event = &DFRobot_UI::tableviewEvent;
  tb->privateData = tbData;
  tb->draw = &DFRobot_UI::drawTableview;
  tb->setCallBack = setTableviewCallback;
  sObject_t* obj= &head;

  if(tb == NULL) while(1);

  while(obj->next != NULL){
    obj = obj->next;
  }
  obj->next =  tb;
  return tb;
}
DFRobot_UI::sObject_t *DFRobot_UI::creatBar(){
  sObject_t* bar= (sObject_t*)malloc(sizeof(sObject_t));
  sBar_t *barData = (sBar_t *)malloc(sizeof(sBar_t));
  bar->posx = 30;
  bar->posy = lcdHeight - 60;
  barData->callBack = NULL;
  bar->width = lcdWidth - 50;
  bar->height = lcdHeight / 40;
  bar->fgColor = LIGHTGREY_RGB565;
  bar->bgColor = 0xffff;
  barData->lastValue = 0;
  barData->value = 0;
  barData->mode=1;
  barData->color = WHITE_RGB565;
  barData->sliderPos = (bar->width * barData->value) / 100 + bar->posx ;
  
  bar->next = NULL;
  bar->event = &DFRobot_UI::barEvent;
  bar->privateData = barData;
  bar->draw = &DFRobot_UI::drawBar;
  bar->setCallBack = setBarCallback;
  sObject_t* obj= &head;
  if(bar == NULL) while(1);

  while(obj->next != NULL){
    obj = obj->next;
  }
  obj->next =  bar;
  return bar;
}
void DFRobot_UI::draw(sObject_t* obj,uint16_t posx,uint16_t posy,uint16_t width,uint16_t height){
  if(posx != 0){
    obj->posx =posx;
  }
  if(posy != 0){
    obj->posy = posy;
  }
  if(width != 0){
    obj->width = width;
  }
  if(height != 0){
  obj->height = height;
  }
  obj->fontSize = 2;
  (this->*obj->draw)(obj);
}

DFRobot_UI::sObject_t *DFRobot_UI::creatSlider()
{
  sObject_t* slider= (sObject_t*)malloc(sizeof(sObject_t));
  sSlider_t *sliderData = (sSlider_t *)malloc(sizeof(sSlider_t));
  sliderData->sliderWidth = lcdWidth / 10;
  sliderData->sliderHeight = lcdHeight / 12;
  sliderData->value = 10 ;
  sliderData->range = 100 ;
  sliderData->change = false;
  sliderData->sliderPos = (slider->width * sliderData->value) / sliderData->range + slider->posx ;
  sliderData->callBack = NULL;
  
  slider->privateData = NULL;
  slider->next = NULL;
  slider->event = &DFRobot_UI::refreshSliser;
  slider->draw = &DFRobot_UI::drawSlider;
  slider->privateData = sliderData;
  slider->setCallBack = setSliserCallback;
  slider->posx = 10;
  slider->posy = lcdHeight - 100;
  slider->height = lcdHeight / 100;
  slider->width = lcdWidth - 100;
  slider->fgColor = BLACK_RGB565;
  slider->bgColor = LIGHTGREY_RGB565;
  slider->fontSize = 3;
  sObject_t* obj= &head;

  if(slider == NULL) while(1);

  while(obj->next != NULL){
    obj = obj->next;
  }
  obj->next =  slider;
  return slider;
}


void DFRobot_UI::refresh()
{
  struct object* obj= &head;
  updateCoordinate();
  while(obj->next != NULL){
    obj = obj->next;
   (this->*obj->event)(obj);
   
  }
}
void DFRobot_UI::setTheme(eTheme_t the)
{
  theme = the;
}

void DFRobot_UI::drawText(void *obj)
{
  sObject_t * ob = (sObject_t *)obj;
  sTextBox_t *tb = (sTextBox_t *)ob->privateData;
  uint8_t column = 0;
  uint8_t line = 0 ;
  uint8_t totalWord;
  uint8_t offset_x = 5;
  uint8_t offset_y = 5;
  uint8_t singleWord = ob->width / (8 * ob->fontSize)-1 ;
  totalWord = singleWord *(ob->height/(8* ob->fontSize)-1)-1;
  if (theme == CLASSIC) {
    _gdl->fillRoundRect(ob->posx - 2, ob->posy - 2, ob->width + 4, ob->height + 4, 12, DARKGREY_RGB565);
    _gdl->fillRoundRect(ob->posx, ob->posy, ob->width, ob->height, 10, ob->bgColor);
  }
  else {
    _gdl->fillRect(ob->posx - 2, ob->posy - 2, ob->width + 4, ob->height + 4, DARKGREY_RGB565);
    _gdl->fillRect(ob->posx, ob->posy, ob->width, ob->height, ob->bgColor);
  }
  if (strlen(tb->text) < totalWord){
     totalWord = strlen(tb->text);
  }
  for (uint8_t i = 0 ; i < totalWord; i++) {
    _gdl->drawChar(offset_x + ob->posx + 8 * ob->fontSize * column, offset_y + ob->posy + 8 * ob->fontSize * line +5, tb->text[i] , LIGHTGREY_RGB565, ob->bgColor, ob->fontSize);
    column++;
    if (column >= ob->width / (8 * ob->fontSize) - 1) {
      column = 0 ;
      line++;
    }
    if (line > ob->height / (8 * ob->fontSize) - 1) return;
    tb->cursorx = column;
    tb->cursory = line;
  }
}

void DFRobot_UI::setText(void *te, char *text) {

  sObject_t * ob = (sObject_t *)te;
  sTextBox_t *tb = (sTextBox_t *)ob->privateData;
  memcpy(tb->text, text, strlen(text));
  memcpy(tb->text + strlen(text), "\0", 1);
  tb->state = DRAWTEXT;
}

void DFRobot_UI::textAddChar(void *te, char txt) {
  if(te == NULL) return;
  sObject_t * ob = (sObject_t *)te;
  sTextBox_t *tb = (sTextBox_t *)ob->privateData;
  if(&tb->cache== NULL) return;
  tb->cache = txt;
  tb->state = ADDCHAR;
}

void DFRobot_UI::textDeleteChar(void *te) {
  sObject_t * ob = (sObject_t *)te;
  sTextBox_t *tb = (sTextBox_t *)ob->privateData;
  tb->state = CLEARACHAR;
}
void DFRobot_UI::endInput()
{
     cursorPosx = 0;
     cursorPosy = 0;
}
bool DFRobot_UI::getTextState(sObject_t* te1)
{  
  sObject_t * obj = (sObject_t *)te1;
   sTextBox_t*te = (sTextBox_t*)obj->privateData;
   return te->selected ;

}
void DFRobot_UI::refreshTextBox(void *obj)
{

  sObject_t * ob = (sObject_t *)obj;
  sTextBox_t *tb = (sTextBox_t *)ob->privateData;
  uint8_t column = 0;
  uint8_t line = 0 ;
  uint8_t offset_x, offset_y;
  uint8_t totalWord;
  if(_touch == NULL){
    return;
  }
  uint8_t singleWord = ob->width / (8 * ob->fontSize) -1;
  if (ob->height/(8* ob->fontSize)<2){
      totalWord = singleWord-2;
  }
  else{
       totalWord = singleWord *(ob->height/(8* ob->fontSize)-1)-2;
  }
  offset_x = 5;
  offset_y = 5 ;

  if(position[0].x > ob->posx && position[0].x < ob->posx +ob->width && position[0].y > ob->posy && position[0].y < ob->posy + ob->height){
     tb->cursorx=strlen(tb->text) % singleWord;
     tb->cursory = strlen(tb->text) / singleWord;
     cursorPosx = ob->posx + offset_x + ((ob->fontSize) * 8) * (tb->cursorx) ;
     cursorPosy = ob->posy + offset_y + (ob->fontSize) * 8 * (tb->cursory);
  }
 if(cursorPosx >= ob->posx && cursorPosx <= ob->posx +ob->width && cursorPosy >= ob->posy && cursorPosy <= ob->posy + ob->height){
    tb->selected = true;
  }
  else{
     tb->selected = false;
  }
  if(tb->selected == false) return;
  if (tb->state == DRAWTEXT) {
    if (theme == CLASSIC ) {
      _gdl->fillRoundRect(ob->posx, ob->posy, ob->width, ob->height, 10, ob->bgColor);
    }
    else {
      _gdl->fillRect(ob->posx, ob->posy, ob->width, ob->height, ob->bgColor);
    }
  }
  if (tb->state == DRAWTEXT) {
    tb->state = NOCHANGE;
    if (strlen(tb->text) < totalWord){
       totalWord = strlen(tb->text);
    }
    for (uint8_t i = 0 ; i < totalWord; i++) {
      _gdl->drawChar(offset_x + ob->posx + 8 * ob->fontSize * column, offset_y + ob->posy + 8 * ob->fontSize * line, tb->text[i] , ob->fgColor, ob->bgColor, ob->fontSize);
      column++;
      if (column >= ob->width / (8 * ob->fontSize) - 1) {
        column = 0 ;
        line++;
      }
      if (line > ob->height / (8 * ob->fontSize) - 1) return;
      tb->cursorx = column;
      tb->cursory = line;
    }
  }
  else if (tb->state == CLEARACHAR) {
    tb->text[strlen(tb->text) - 1] = '\0';
    tb->cursorx = strlen(tb->text) % singleWord;
    tb->cursory = strlen(tb->text) / singleWord;
    _gdl->fillRect(tb->cursorx * (8 * ob->fontSize) + offset_x + ob->posx, tb->cursory * (8 * ob->fontSize) + offset_y + ob->posy, 8 * ob->fontSize, 8 * ob->fontSize, ob->bgColor);
    tb->state = NOCHANGE;
    if (line > ob->height / (8 * ob->fontSize) - 1) return;

  }
  else if (tb->state == ADDCHAR) {
    tb->state = NOCHANGE;
    if (strlen(tb->text) > totalWord) return;
    tb->text[strlen(tb->text) + 1] = '\0';
    tb->text[strlen(tb->text)] =  tb->cache;
    _gdl->drawChar(tb->cursorx * (8 * ob->fontSize) + offset_x + ob->posx, tb->cursory * (8 * ob->fontSize) + offset_y + ob->posy, tb->cache , ob->fgColor, ob->bgColor, ob->fontSize);
    tb->cursorx = strlen(tb->text) % singleWord;
    tb->cursory = strlen(tb->text) / singleWord;

    if (line > ob->height / (8 * ob->fontSize) - 1) return;
  }
  if(tb->selected == true){
    drawCursor(ob, offset_x, offset_y, 0);
    delay(50);
    drawCursor(ob, offset_x, offset_y, 1);
  }

}

void DFRobot_UI::drawKeyBoard(void *obj){
  sObject_t * ob = (sObject_t *)obj;
  sKeyPad_t *kp = (sKeyPad_t *)ob->privateData;
  char keyPad[12] = {'1','2','3','4','5','6','7','8','9','*','0','x'};
  uint8_t b = 0;
  if(kp->mode == 0){
     te1= creatText();
     draw(te1,10,10,220,100);
	 kp->textBox = te1;
	 kp->text = 1;
    b = 2;
  } else {
    b = 3;
  }
  ob->posx = 0;
  ob->posy = lcdHeight-lcdHeight/b-1;
  uint8_t button = 0;
 
  for(uint8_t i = 0 ; i < 4 ; i++){
     for(uint8_t j = 0 ; j < 3 ; j++){
       kp->btn[button].fontSize = (lcdHeight * 3) / 480 ;
       kp->btn[button].width = (lcdWidth-2)/3-1;
       kp->btn[button].height = (lcdHeight/b - 3)/4-1;
       kp->btn[button].posx =  ob->posx + j*((lcdWidth-2)/3);
       kp->btn[button].posy =  ob->posy + i*((lcdHeight/b - 3)/4);
       memcpy(kp->btn[button].text,&keyPad[button],1);
	   kp->btn[button].text[1] = '\0';
	   //memcpy(&kp->btn[button].text[1],'\0',1);
       kp->btn[button].fgColor = BLACK_RGB565;
       kp->btn[button].bgColor = LIGHTGREY_RGB565;
       kp->btn[button].click  = 0;
       kp->btn[button].callBack = NULL;
       if (theme == MODERN) {
         _gdl->fillRoundRect(kp->btn[button].posx - 1, kp->btn[button].posy - 1, kp->btn[button].width + 2, kp->btn[button].height + 2, 11, DCYAN_RGB565);
         _gdl->fillRoundRect(kp->btn[button].posx, kp->btn[button].posy, kp->btn[button].width, kp->btn[button].height, 10, kp->btn[button].bgColor);
       }
       else {
         _gdl->fillRect(kp->btn[button].posx, kp->btn[button].posy, kp->btn[button].width, kp->btn[button].height, kp->btn[button].bgColor);

        }
       drawkpString(&kp->btn[button],CENTER,CENTER,kp->btn[button].text);
       button++;
    }
  }
}
void DFRobot_UI::setKeyPadMode(sObject_t * obj,uint8_t mode){
	sKeyPad_t *kp = (sKeyPad_t*)obj->privateData;
	kp->mode = mode;
}
void DFRobot_UI::KeyBoardEvent(void *obj){
  sObject_t * ob = (sObject_t *)obj;
  sKeyPad_t *kb = (sKeyPad_t *)ob->privateData;
  if(_touch == NULL){
    return;
  }
  if(kb->callBack) kb->callBack(ob);
  
  for(uint8_t i=0 ;i<12;i++){
  if (judgeKpPress(&kb->btn[i], position[0].x, position[0].y) == true && kb->btn[i].click == 0) {
    kb->btn[i].click = 1;
     if (theme == MODERN) {
       _gdl->fillRoundRect(kb->btn[i].posx - 1, kb->btn[i].posy - 1, kb->btn[i].width + 2, kb->btn[i].height + 2, 11, kb->btn[i].fgColor);
     }
     else {
       _gdl->fillRect(kb->btn[i].posx, kb->btn[i].posy, kb->btn[i].width, kb->btn[i].height, kb->btn[i].fgColor);
     }
    drawkpString(&kb->btn[i],CENTER,CENTER,&kb->btn[i].text[0]);
   }
  if ( judgeKpPress(&kb->btn[i], position[0].x, position[0].y) == false && kb->btn[i].click == 1) {
    kb->btn[i].click = 0;
    if (theme == MODERN) {
      _gdl->fillRoundRect(kb->btn[i].posx - 1, kb->btn[i].posy - 1, kb->btn[i].width + 2, kb->btn[i].height + 2, 11, DCYAN_RGB565);
      _gdl->fillRoundRect(kb->btn[i].posx, kb->btn[i].posy, kb->btn[i].width, kb->btn[i].height, 10, kb->btn[i].bgColor);
    }
    else {
      _gdl->fillRect(kb->btn[i].posx, kb->btn[i].posy, kb->btn[i].width, kb->btn[i].height, kb->btn[i].bgColor);
    
     }
    drawkpString(&kb->btn[i],CENTER,CENTER,&kb->btn[i].text[0]);
    if(kb->text == 0) continue;
    if(kb->btn[i].text[0] == 'x'){
      textDeleteChar(kb->textBox);
    }
    else{
      textAddChar(kb->textBox,kb->btn[i].text[0]);
    } 

   }
  }
}
void DFRobot_UI::setKeyPadText(sObject_t * kp,sObject_t * text)
{
    sKeyPad_t * kpp= (sKeyPad_t *)kp->privateData;
    kpp->textBox = text;
    sTextBox_t * te= (sTextBox_t *)text->privateData;
    te->selected = 1;
    kpp->text = 1;
    //cursorPosx = text->posx + 5 ;
    //cursorPosy = text->posy + 5 ;
}

/*
void DFRobot_UI::initButton(sButton_t *bu) {

  bu->posx = 0;
  bu->posy = 0;
  bu->width = lcdWidth / 4;
  bu->height = lcdHeight / 8;
  bu->fgColor = BLACK_RGB565;
  bu->bgColor = LIGHTGREY_RGB565;
  bu->fontSize = (lcdHeight * 3) / 480 ;
  memset(bu->text, '\0', sizeof(bu->text));
  bu->click  = 0 ;
  bu->callBack = NULL ;
}
*/
void DFRobot_UI::drawButton(void *obj) {
  sObject_t * ob = (sObject_t *)obj;
  sButton_t *btn = (sButton_t *)ob->privateData;
  if (theme == MODERN) {
    _gdl->fillRoundRect(ob->posx - 1, ob->posy - 1, ob->width + 2, ob->height + 2, 11, DCYAN_RGB565);
    _gdl->fillRoundRect(ob->posx, ob->posy, ob->width, ob->height, 10, ob->bgColor);
  }
  else {
    _gdl->fillRect(ob->posx, ob->posy, ob->width, ob->height, ob->bgColor);

  }
  // Serial.println(bu->text[0]);
  drawButtonString(ob, CENTER, CENTER, btn->text,btn->click);
}
/*
void DFRobot_UI::creatButton(sButton_t *bu)
{
  if (theme == MODERN) {
    _gdl->fillRoundRect(bu->posx - 1, bu->posy - 1, bu->width + 2, bu->height + 2, 11, DARKGREY_RGB565);
    _gdl->fillRoundRect(bu->posx, bu->posy, bu->width, bu->height, 10, bu->bgColor);
  }
  else {
    _gdl->fillRect(bu->posx, bu->posy, bu->width, bu->height, bu->bgColor);

  }
  // Serial.println(bu->text[0]);
  drawButtonString(bu, CENTER, CENTER, bu->text);
}
*/
void DFRobot_UI::updateCoordinate()
{
  if (position) free(position);
  if(_touch == NULL) return;
  String str = _touch->scan();
  number  = pointNum(str);
  //delay(300);
  //Serial.println(str);
  position = (sPoint_t*)malloc(number * sizeof(sPoint_t));


  if (position == NULL) {
    while (1);
  }
  stringToPoint(str, position);
}
/*
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
    if (judgePress(bu, position[i].x, position[i].y) == true && bu->click == 0) {
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
*/
void DFRobot_UI::drawClickButton(sObject_t *obj,char *text , bool click)
{
    if (theme == MODERN) {
         _gdl->fillRoundRect(obj->posx - 1, obj->posy - 1, obj->width + 2, obj->height + 2, 11, DCYAN_RGB565);
         _gdl->fillRoundRect(obj->posx, obj->posy, obj->width, obj->height, 10, obj->fgColor);
     }
     else {
        _gdl->fillRect(obj->posx, obj->posy, obj->width, obj->height, obj->fgColor);

        }

  drawButtonString(obj, CENTER, CENTER, text,click);
}

void  DFRobot_UI::drawTableview(void *obj)
{
  sObject_t * ob = (sObject_t *)obj;
  sTableview_t *tb = (sTableview_t *)ob->privateData;
  tb->offset = 10 ;
  for (uint8_t i = 0 ; i < tb->numPage; i++) {
    tb->text[i].posx = tb->offset + (lcdWidth / (tb->numPage)) * i;
    tb->text[i].posy = tb->offset;
    tb->text[i].width = lcdWidth / (tb->numPage) - tb->offset;
    tb->text[i].height = lcdHeight / 10;
    tb->text[i].bgColor = CYAN_RGB565;
    tb->text[i].fgColor = BLACK_RGB565;
    tb->highLightPage = 0;
    tb->text[i].fontSize = tb->text[i].width / (50) ;
    tb->text[i].click  = 0 ;
  }

  for (uint8_t i = 0 ; i < tb->numPage; i++) {
    if (theme == MODERN) {
         _gdl->fillRoundRect(tb->text[i].posx - 1, tb->text[i].posy - 1, tb->text[i].width + 2, tb->text[i].height + 2, 11, DCYAN_RGB565);
         _gdl->fillRoundRect(tb->text[i].posx, tb->text[i].posy, tb->text[i].width, tb->text[i].height, 10, tb->text[i].bgColor);
     }
     else {
        _gdl->fillRect(tb->text[i].posx, tb->text[i].posy, tb->text[i].width, tb->text[i].height, tb->text[i].bgColor);

        }
       drawkpString(&tb->text[i],CENTER,CENTER,&tb->text[i].text[0]);
	   Serial.println(tb->text[i].text[0]);
  }
  //_gdl->fillRect(tb->text[0].posx, tb->text[0].posy + tb->text[0].height + 10, tb->text[0].width , 10, COLOR_RGB565_PINK);

}

void DFRobot_UI::tableviewEvent(void *obj)
{
  sObject_t * ob = (sObject_t *)obj;
  sTableview_t *tb = (sTableview_t *)ob->privateData;
  if(_touch == NULL){
    return;
  }
  if (number == 0) return;
  
    for (uint8_t i = 0 ; i < tb->numPage; i++) {
      if (judgeKpPress(&tb->text[i], position[0].x, position[0].y) == 1 && tb->text[i].click == 0) {
       tb->text[i].click = 1;
          //Serial.println(i);
     if (theme == MODERN) {
       _gdl->fillRoundRect(tb->text[i].posx - 1, tb->text[i].posy - 1, tb->text[i].width + 2, tb->text[i].height + 2, 11, tb->text[i].fgColor);
     }
     else {
       _gdl->fillRect(tb->text[i].posx, tb->text[i].posy, tb->text[i].width, tb->text[i].height, tb->text[i].fgColor);
     }
    drawkpString(&tb->text[i],CENTER,CENTER,&tb->text[i].text[0]);
    break;
     }
  //_gdl->fillRect(tb->text[0].posx, tb->text[0].posy + tb->text[0].height + 10, tb->text[0].width , 10, MAROON_RGB565);
      }
    

    for (uint8_t i = 0 ; i < tb->numPage; i++) {

      if (judgeKpPress(&tb->text[i], position[0].x, position[0].y) == 1 && tb->text[i].click == 1) {
      tb->text[i].click = 0;
      if (theme == MODERN) {
         _gdl->fillRoundRect(tb->text[i].posx - 1, tb->text[i].posy - 1, tb->text[i].width + 2, tb->text[i].height + 2, 11, DCYAN_RGB565);
         _gdl->fillRoundRect(tb->text[i].posx, tb->text[i].posy, tb->text[i].width, tb->text[i].height, 10, tb->text[i].bgColor);
       }
      else {
        _gdl->fillRect(tb->text[i].posx, tb->text[i].posy, tb->text[i].width, tb->text[i].height, tb->text[i].bgColor);

        }
       drawkpString(&tb->text[i],CENTER,CENTER,&tb->text[i].text[0]);
       
        if (tb->highLightPage != (i + 1)) {
          _gdl->fillRect(0, tb->text[i].posy + tb->text[i].height + 1 , 320, 400, bgColor);
          _gdl->fillRect(tb->text[i].posx, tb->text[i].posy + tb->text[i].height + 10, tb->text[i].width , 10, COLOR_RGB565_PINK);
             Serial.println(i);
          tb->highLightPage = i + 1;
          if(tb->callback) tb->callback(&tb->highLightPage);
        }
    }
  }
}

void DFRobot_UI::changeTableview(sObject_t* obj,uint8_t page)
{    
     sTableview_t *tv = (sTableview_t *)obj->privateData;
     if (theme == MODERN) {
       _gdl->fillRoundRect(tv->text[page-1].posx - 1, tv->text[page-1].posy - 1, tv->text[page-1].width + 2, tv->text[page-1].height + 2, 11, tv->text[page-1].fgColor);
     }
     else {
       _gdl->fillRect(tv->text[page-1].posx, tv->text[page-1].posy, tv->text[page-1].width, tv->text[page-1].height, tv->text[page-1].fgColor);
     }
    drawkpString(&tv->text[page-1],CENTER,CENTER,&tv->text[page-1].text[0]);
 美女呢                          
        _gdl->fillRect(tv->text[page-1].posx, tv->text[page-1].posy, tv->text[page-1].width, tv->text[page-1].height, tv->text[page-1].bgColor);
        }
       drawkpString(&tv->text[page-1],CENTER,CENTER,&tv->text[page-1].text[0]);
	
     //drawButton(&tv->text[page-1]);
     _gdl->fillRect(0, tv->text[page-1].posy + tv->text[page-1].height + 1 , 320, 400, bgColor);
     _gdl->fillRect(tv->text[page-1].posx, tv->text[page-1].posy + tv->text[page-1].height + 10, tv->text[page-1].width , 10, COLOR_RGB565_PINK);
     tv->highLightPage = page;
    if(tv->callback) tv->callback(&tv->highLightPage);
}

/*
void DFRobot_UI::initBar(sBar_t *bar) {
  bar->posx = 30;
  bar->posy = lcdHeight - 60;
  bar->callBack = NULL;
  bar->width = lcdWidth - 50;
  bar->height = lcdHeight / 40;
  bar->fgColor = LIGHTGREY_RGB565;
  bar->bgColor = 0xffff;
  bar->lastValue = 0;
  bar->value = 0;
  bar->color = WHITE_RGB565;
  bar->sliderPos = (bar->width * bar->value) / 100 + bar->posx ;
}
*/
void DFRobot_UI::setBarStyle(sObject_t *obj,uint8_t mode){
  sBar_t *bar = (sBar_t *)obj->privateData;
  bar->mode = mode;
	
	
}
void DFRobot_UI::drawBar(void *obj){

  sObject_t * ob = (sObject_t *)obj;
  sBar_t *bar = (sBar_t *)ob->privateData;
  
  uint8_t edgeWidth = lcdWidth / 160;
  if (bar->mode == 0) {
    _gdl->fillRoundRect(ob->posx - edgeWidth, ob->posy - edgeWidth, ob->width + 2 * edgeWidth, ob->height + 2 * edgeWidth, ob->height / 2, DARKGREY_RGB565);
    _gdl->fillRoundRect(ob->posx, ob->posy, ob->width , ob->height, ob->height / 2, ob->bgColor);
    _gdl->setCursor((ob->posx + ob->width) / 2, ob->posy + ob->height + 5);
    _gdl->setTextColor(ob->fgColor, bgColor);
    _gdl->setTextSize(2);
    _gdl->print(bar->value);
    _gdl->print("%");
  }
  else if(bar->mode == 1){
    _gdl->fillCircle(ob->posx, ob->posy, 32, LIGHTGREY_RGB565);
    _gdl->fillCircle(ob->posx, ob->posy, 30, 0xffff);
    _gdl->fillCircle(ob->posx, ob->posy, 26, LIGHTGREY_RGB565);
    _gdl->fillCircle(ob->posx, ob->posy, 24, bgColor);
    _gdl->fillCircle(ob->posx + (0), ob->posy - (28), 3, WHITE_RGB565);
    _gdl->setCursor(ob->posx-8, ob->posy - 8);
    _gdl->setTextColor(ob->fgColor, bgColor);
    _gdl->setTextSize(2);
    _gdl->print(bar->value);
  }
  else {
    for(uint8_t i = 0 ; i < 25 ;i++){
        _gdl->fillRect(ob->posx+i*(ob->width/25),ob->posy,(ob->width/25-2),ob->height*2,65535);
     }
    _gdl->setCursor((ob->posx + ob->width) / 2-10, ob->posy + ob->height*2 + 5);
    _gdl->setTextColor(ob->fgColor, bgColor);
    _gdl->setTextSize(2);
    _gdl->print(bar->value);
    _gdl->print("%");
  }
}
void DFRobot_UI::setBarValue(sObject_t * obj,uint8_t value){

  sBar_t *bar = (sBar_t*)obj->privateData; 
  bar->value = value;
}
void DFRobot_UI::barEvent(void *obj) {
  sObject_t * ob = (sObject_t *)obj;
  sBar_t *bar = (sBar_t *)ob->privateData;
  //Serial.println(position[0].x);
  double pi = 3.1415926;
  double rad1, rad2, cosa, sina, x, y;
  bar->sliderPos = (ob->width * bar->value) / 100 + ob->posx ;
  if (bar->callBack) bar->callBack(ob);

  if (bar->value > 100){
    bar->value = 100;
    return;
  }
  if (bar->mode == 0) {
    if(bar->lastValue == bar->value) return;
    _gdl->fillRect((ob->posx + ob->width) / 2,ob->posy + ob->height + 5, 2*8*3 , 2*8, bgColor);
    for (uint8_t i = bar->lastValue; i < bar->value + 1; i++) {
      
      bar->lastValue = bar->value;
      if(bar->value>96) continue;
      _gdl->fillRoundRect(i * (ob->width) / 100+ob->posx, ob->posy, ob->height, ob->height, ob->height/2  , YELLOW_RGB565);
    }
    _gdl->setCursor((ob->posx + ob->width) / 2, ob->posy + ob->height + 5);
    _gdl->setTextColor(ob->fgColor, bgColor);
    _gdl->setTextSize(2);
    _gdl->print(bar->value);
    _gdl->print("%");
  }
  
  else if(bar->mode == 1){
    if(bar->lastValue == bar->value) return;
    _gdl->fillRect(ob->posx -14,ob->posy-8 , 4*8 , 2*8, bgColor);
    for (double i = (bar->lastValue); i < bar->value ;) {
      rad1 = i * (3.6) * pi / 180;
      cosa = cos(rad1);
      sina = sin(rad1);
      x = 0 - sina * 28 - 0.5;
      y = 28 * cosa;
      _gdl->fillCircle(ob->posx - (x), ob->posy - (y), 3, bar->color);
      i += 1;
      if ((bar->color & 0x1f) > 1) {
      bar->color -= 1;
      }
      else if (((bar->color >> 5) & 0x3f) != 0) {
        bar->color >>= 5;
        bar->color -= 1;
        bar->color <<= 5;
      }
      bar->lastValue = bar->value;
    }
    if(bar->value <10){
      _gdl->setCursor(ob->posx -5, ob->posy - 8);
    }
    else if(bar->value >=10  && bar->value <100){
      _gdl->setCursor(ob->posx -12, ob->posy - 8);
	}
	else{
     _gdl->setCursor(ob->posx -17, ob->posy - 8);
	}
    _gdl->setTextSize(2);
    _gdl->print(bar->value);
  }
  else{
    for(uint8_t i = bar->lastValue/4 ; i < bar->value/4 ;i++){
        _gdl->fillRect(ob->posx+i*(ob->width/25),ob->posy,(ob->width/25-2),ob->height*2,ob->fgColor);
     }
       _gdl->setCursor((ob->posx + ob->width) / 2-10, ob->posy + ob->height*2 + 5);
       _gdl->setTextColor(ob->fgColor, bgColor);
       _gdl->setTextSize(2);
       _gdl->print(bar->value);
       _gdl->print("%");
        bar->lastValue = bar->value;
  }
}



void DFRobot_UI::drawSlider(void *obj)
{
  sObject_t * ob = (sObject_t *)obj;
  sSlider_t *slider = (sSlider_t *)ob->privateData;
  uint8_t edgeWidth = lcdWidth / 160;
  slider->sliderPos = (ob->width * slider->value) / slider->range + ob->posx ;
  _gdl->fillRoundRect(ob->posx - edgeWidth, ob->posy - edgeWidth, ob->width + 2 * edgeWidth, ob->height + 2 * edgeWidth, ob->height / 2, DARKGREY_RGB565);
  _gdl->fillRoundRect(ob->posx, ob->posy, ob->width , ob->height, ob->height / 2, ob->bgColor);
  _gdl->fillRoundRect(ob->posx, ob->posy, slider->sliderPos, ob->height, ob->height / 2, ob->fgColor);
  _gdl->fillRoundRect(ob->posx + slider->sliderPos - slider->sliderWidth / 2 - edgeWidth, ob->posy - (slider->sliderHeight - ob->height) / 2 - edgeWidth, slider->sliderWidth + 2 * edgeWidth, slider->sliderHeight + 2 * edgeWidth, slider->sliderWidth / 10, DARKGREY_RGB565);
  _gdl->fillRoundRect(ob->posx + slider->sliderPos - slider->sliderWidth / 2, ob->posy - (slider->sliderHeight - ob->height) / 2, slider->sliderWidth, slider->sliderHeight, slider->sliderWidth / 10, LIGHTGREY_RGB565);
}

void DFRobot_UI::refreshSliser(void *obj)
{
  sObject_t * ob = (sObject_t *)obj;
  sSlider_t *slider = (sSlider_t *)ob->privateData;
  if(_touch == NULL){
    return;
  }
  if (number == 0) return;
  uint8_t edgeWidth = lcdWidth / 160;
  uint16_t slider_x = ob->posx + slider->sliderPos - slider->sliderWidth / 2;
  uint16_t slider_y = ob->posy + ob->height / 2 - slider->sliderHeight / 2 ;
  if (slider->change == 0) {
    if (position[0].x > slider_x && (position[0].x < slider_x + slider->sliderWidth) && ((position[0].y > slider_y) && (position[0].y < slider_y + slider->sliderHeight))) {
      slider->change = 1;

    }
  }

  if (slider->change == 1) {

    if (position[0].x < ob->posx || (position[0].x > ob->posx + ob->width) || ((position[0].y < slider_y) || (position[0].y > slider_y + slider->sliderHeight))) {
      slider->change = 0;
      if (slider->value >= 100) return;
      if (slider->callBack )  {
        slider->callBack(&slider->value);
      }
      _gdl->setTextColor(DARKCYAN_RGB565, bgColor);
      _gdl->setTextSize(2);
      _gdl->setCursor(ob->posx + ob->width / 2, ob->posy + 40);
      _gdl->print(slider->value);

    }
  }

  
  if (slider->change == 1) {
    slider->sliderPos = position[0].x - ob->posx;
    slider->value = ((position[0].x - ob->posx) * (slider->range)) / ob->width ;
    if (slider->value >= 100) slider->value = 99;
    if (slider->value < 98 && slider->value > 3) {
      _gdl->fillRoundRect(ob->posx + slider->lastsliderPos - slider->sliderWidth / 2 - edgeWidth, ob->posy - (slider->sliderHeight - ob->height) / 2 - edgeWidth, slider->sliderWidth + 2 * edgeWidth, slider->sliderHeight + 2 * edgeWidth, slider->sliderWidth / 10, bgColor);
      _gdl->fillRect(ob->posx - ob->height / 2, ob->posy - (slider->sliderHeight - ob->height) / 2 - 2 * edgeWidth, ob->width + ob->height + 4 * edgeWidth, slider->sliderHeight + 4 * edgeWidth, bgColor);
      _gdl->fillRoundRect(ob->posx - edgeWidth, ob->posy - edgeWidth, ob->width + 2 * edgeWidth, ob->height + 2 * edgeWidth, ob->height / 2, DARKGREY_RGB565);
      _gdl->fillRoundRect(ob->posx, ob->posy, ob->width , ob->height, ob->height / 2, ob->bgColor);
      _gdl->fillRoundRect(ob->posx, ob->posy, slider->sliderPos, ob->height, ob->height / 2, ob->fgColor);
      _gdl->fillRoundRect(ob->posx + slider->sliderPos - slider->sliderWidth / 2 - edgeWidth, ob->posy - (slider->sliderHeight - ob->height) / 2 - edgeWidth, slider->sliderWidth + 2 * edgeWidth, slider->sliderHeight + 2 * edgeWidth, slider->sliderWidth / 10, DARKGREY_RGB565);
      _gdl->fillRoundRect(ob->posx + slider->sliderPos  - slider->sliderWidth / 2, ob->posy - (slider->sliderHeight - ob->height) / 2, slider->sliderWidth, slider->sliderHeight, slider->sliderWidth / 10, LIGHTGREY_RGB565);
      _gdl->fillRect(ob->posx + ob->width / 2, ob->posy + 40 , 2 * 8 * 3, 2 * 8, bgColor);
    }
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

void DFRobot_UI::drawSwitch(void *obj)
{
  sObject_t * ob = (sObject_t *)obj;
  sSwitch_t *sw = (sSwitch_t *)ob->privateData;
  _gdl->fillRoundRect(ob->posx - 1, ob->posy - 1, ob->width + 2, ob->height + 2, ob->height / 2, DARKGREY_RGB565);
  _gdl->fillRoundRect(ob->posx, ob->posy, ob->width, ob->height, ob->height / 2, ob->fgColor);
  _gdl->fillCircle(ob->posx + ob->height / (1.2),ob->posy + ob->height / 2, ob->height / (1.2) + 1,  DARKGREY_RGB565);
  _gdl->fillCircle(ob->posx + ob->height / (1.2), ob->posy + ob->height / 2, ob->height / (1.2),  ob->fgColor);
}
void DFRobot_UI::switchEvent(void *obj){

  sObject_t * ob = (sObject_t *)obj;
  sSwitch_t *sw = (sSwitch_t *)ob->privateData;
  if(_touch == NULL){
    return;
  }
  if (number == 0) return;
#if defined (__AVR__)
  if (sw->change == false ) {
    if (((position[0].x > ob->posx) && (position[0].x < ob->posx + ob->width)) && ((position[0].y > ob->posy) && (position[0].y < ob->posy + ob->height))) {
      sw->change = true;
      sw->state = 1 - sw->state ;
    }
  }
  if (sw->change == true && (((position[0].x < ob->posx) || (position[0].x > ob->posx + ob->width)) || ((position[0].y < ob->posy) || (position[0].y > ob->posy + ob->height)))) {
    sw->change = false;
    _gdl->fillRect(ob->posx - ob->height / (1.2) - 1 , ob->posy - ob->height / (1.2), ob->width + ob->height * 2, (ob->height / (1.2)) * 3 , bgColor);
    if (sw->state == 1 ) {
      _gdl->fillRoundRect(ob->posx - 1, ob->posy - 1, ob->width + 2, ob->height + 2, ob->height / 2, DARKGREY_RGB565);
      _gdl->fillRoundRect(ob->posx, ob->posy, ob->width, ob->height, ob->height / 2, BLUE_RGB565);
      _gdl->fillCircle(ob->posx + ob->width - ob->height / (1.2), ob->posy + ob->height / 2, ob->height / (1.2) + 1,  DARKGREY_RGB565);
      _gdl->fillCircle(ob->posx + ob->width - ob->height / (1.2), ob->posy + ob->height / 2, ob->height / (1.2),  NAVY_RGB565);

    }
    if (sw->state == 0) {
      _gdl->fillRoundRect(ob->posx - 1, ob->posy - 1, ob->width + 2, ob->height + 2, ob->height / 2, DARKGREY_RGB565);
      _gdl->fillRoundRect(ob->posx, ob->posy, ob->width, ob->height, ob->height / 2, ob->fgColor);
      _gdl->fillCircle(ob->posx + ob->height / (1.2), ob->posy + ob->height / 2, ob->height / (1.2) + 1,  DARKGREY_RGB565);
      _gdl->fillCircle(ob->posx + ob->height / (1.2), ob->posy + ob->height / 2, ob->height / (1.2),  ob->fgColor);
    }
    if (sw ->callBack) sw->callBack(&sw->state);
  }
#else
  if (sw->change == false ) {
    for (uint8_t i = 0 ; i < number ; i++) {
      if (((position[i].x > ob->posx) && (position[i].x < ob->posx + ob->width)) && ((position[i].y > ob->posy) && (position[i].y < ob->posy + ob->height))) {
        sw->change = true;
        sw->state = 1 - sw->state ;
        break;
      }
    }
  }
  uint8_t n = 0;
  if (sw->change == true) {
    for (uint8_t i = 0 ; i < number ; i++) {
      if ((((position[i].x < ob->posx) || (position[i].x > ob->posx + ob->width)) || ((position[i].y < ob->posy) || (position[i].y > ob->posy + ob->height)))) {
        n++;
      }
      if (n == number) {
        sw->change = false;
        _gdl->fillRect(ob->posx - ob->height / (1.2) - 1 , ob->posy - ob->height / (1.2), ob->width + ob->height * 2, (ob->height / (1.2)) * 3 , bgColor);
        if (sw->state == 1 ) {
          _gdl->fillRoundRect(ob->posx - 1, ob->posy - 1, ob->width + 2, ob->height + 2, ob->height / 2, DARKGREY_RGB565);
          _gdl->fillRoundRect(ob->posx, ob->posy, ob->width, ob->height, ob->height / 2, BLUE_RGB565);
          _gdl->fillCircle(ob->posx + ob->width - ob->height / (1.2), ob->posy + ob->height / 2, ob->height / (1.2) + 1,  DARKGREY_RGB565);
          _gdl->fillCircle(ob->posx + ob->width - ob->height / (1.2), ob->posy + ob->height / 2, ob->height / (1.2),  NAVY_RGB565);

        }
        if (sw->state == 0) {
          _gdl->fillRoundRect(ob->posx - 1, ob->posy - 1, ob->width + 2, ob->height + 2, ob->height / 2, DARKGREY_RGB565);
          _gdl->fillRoundRect(ob->posx, ob->posy, ob->width, ob->height, ob->height / 2, ob->fgColor);
          _gdl->fillCircle(ob->posx + ob->height / (1.2), ob->posy + ob->height / 2, ob->height / (1.2) + 1,  DARKGREY_RGB565);
          _gdl->fillCircle(ob->posx + ob->height / (1.2), ob->posy + ob->height / 2, ob->height / (1.2),  ob->fgColor);
        }
        if (sw ->callBack) sw ->callBack(&sw->state);
      }
    }
  }
#endif
}

void DFRobot_UI::drawCursor(sObject_t* obj, uint8_t offset_x, uint8_t offset_y, bool state)
{
  sTextBox_t *textData = (sTextBox_t *)obj->privateData;
  uint16_t  x = obj->posx + offset_x + ((obj->fontSize) * 8) * (textData->cursorx) + 2;
  uint16_t  y = obj->posy + offset_y + (obj->fontSize) * 8 * (textData->cursory);
  uint16_t color ;
  if (state == 1 ) {
    color = obj->bgColor;
  }
  else {
    color = obj->fgColor;
  }

  _gdl->fillRect(x, y, 2, obj->fontSize * 8, color);

}
/*
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
*/
bool DFRobot_UI::judgePress(sObject_t *obj, uint16_t x, uint16_t y) {

  if ((x > obj->posx && x < ( obj->posx + obj->width)) && (y > obj->posy && y < ( obj->posy + obj->height)))
  {
    return true;
  }
  else
  {
    return false;
  }


}
bool DFRobot_UI::judgeKpPress(sButton_t*obj, uint16_t x, uint16_t y)
{

  if ((x > obj->posx && x < ( obj->posx + obj->width)) && (y > obj->posy && y < ( obj->posy + obj->height)))
  {
    return true;
  }
  else
  {
    return false;
  }




}
void DFRobot_UI::drawButtonString(sObject_t *obj, eLocation_t x, eLocation_t y, char * c,bool click)
{

  int16_t po_x, po_y;

  char b ;
  if (x == CENTER && y == CENTER) {
    po_x =  obj->posx + obj->width / 2 - (4 * obj->fontSize) / 2 ;
    po_y =  obj->posy + obj->height / 2 - (8 * obj->fontSize) / 2;
    po_x = po_x - obj->fontSize * 8 * (strlen(c) - 1) * (0.5);
  }
  else if (x == LEFT && y == CENTER) {
    po_x =  obj->posx ;
    po_y =  obj->posy + obj->height / 2 - (8 * obj->fontSize) / 2 ;
  }
  uint8_t length = (obj->width) / (8 * obj->fontSize);
  if (length >= strlen(c)) length = strlen(c);
  for (uint16_t i = 0 ; i < length ; i++) {
    b = c[i];
    if (click == 0) {
      _gdl->drawChar(po_x + i * 8 * obj->fontSize, po_y, b, obj->fgColor, obj->bgColor, obj->fontSize);
    }
    else {
      _gdl->drawChar(po_x + i * 8 * obj->fontSize, po_y, b, obj->bgColor, obj->fgColor, obj->fontSize);
    }
  }
}
void DFRobot_UI::drawkpString(sButton_t *btn, eLocation_t x, eLocation_t y, char * c){
int16_t po_x, po_y;
  //sButton_t* btn = kp->btn[num];
  char b ;
  if (x == CENTER && y == CENTER) {
    po_x =  btn->posx + btn->width / 2 - (4 * btn->fontSize) / 2 ;
    po_y =  btn->posy + btn->height / 2 - (8 * btn->fontSize) / 2;
    po_x = po_x - btn->fontSize * 8 * (strlen(c) - 1) * (0.5);
  }
  else if (x == LEFT && y == CENTER) {
    po_x =  btn->posx ;
    po_y =  btn->posy + btn->height / 2 - (8 * btn->fontSize) / 2 ;
  }
  uint8_t length = (btn->width) / (8 * btn->fontSize);
  if (length >= strlen(c)) length = strlen(c);
  
  for (uint16_t i = 0 ; i < length ; i++) {
    b = c[i];
    if (btn->click == 0) {
      _gdl->drawChar(po_x + i * 8 * btn->fontSize, po_y, b, btn->fgColor, btn->bgColor, btn->fontSize);
    }
    else {
      _gdl->drawChar(po_x + i * 8 * btn->fontSize, po_y, b, btn->bgColor, btn->fgColor, btn->fontSize);
    }
  }



}

void DFRobot_UI::drawString(int16_t x, int16_t y, char * c, uint16_t color, uint16_t bg, uint8_t size, boolean mode)
{
  char b ;
  _gdl->setTextColor(color, bg);
  _gdl->setTextSize(size);
  for (uint16_t i = 0 ; i < strlen(c); i++) {
    b = c[i];
    _gdl->setCursor(x + i * 6 * size, y);
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

bool DFRobot_UI::focus(uint16_t x, uint16_t y) {
  if ((x > gesturex) && x < (gesturex + gestureWidth) && (y > gesturey) && y < (gesturey + gestureHeight) ) {
    return true;
  }
  else {
    return false;
  }
}

bool DFRobot_UI::press(uint16_t x, uint16_t y)
{

  if (focus(x, y) == true) {

    if (screenPressed == 0 ) {
      screenPressed = 1;
      return true;
    }
  }
  return false;
}

bool DFRobot_UI::release(uint16_t x, uint16_t y) {
  if (focus(x, y) != true) {
    if (screenPressed == 1) {
      screenPressed = 0;

      return true;
    }

  }
  return false;
}
void DFRobot_UI::setGestureArea(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
  gesturex = x;
  gesturey = y;
  gestureWidth = width;
  gestureHeight = height;
  _gdl->fillRoundRect(x, y, width, height, height / 4, LIGHTGREY_RGB565);
  drawString(x + 5, y + height / 2, "Gesture area", DARKGREY_RGB565, LIGHTGREY_RGB565, 2, 0);
}

DFRobot_UI::eGestures_t DFRobot_UI::getGestures()
{
  uint16_t x, y;
  int interval = 0;

  if (lastGestute != LONGPRESSDE || millis() - timer1 > 2000) {
    if (millis() - timer1 >= 500) {
      if (interval >= 500 || click == 1) {
        click = 0;
        lastGestute = SINGLECLICK;
        return SINGLECLICK;
      }
      else if (click == 2) {
        click = 0;
        lastGestute = DOUBLECLICK;
        return  DOUBLECLICK;
      }
    }
  }
  if (press(position[0].x, position[0].y) == true) {

    bx1 = position[0].x;
    by1 = position[0].y;
    timer = millis();
  }
  if (release(position[0].x, position[0].y) == true) {
    x = bx2;
    y = by2;
    //timer = millis();
    if (x >= 30 + bx1) return RIGHTGLIDE;
    else if (bx1  >= 30 + x) return LEFTGLIDE;
    else if (y  >= 30 + by1)  return DOWNGLIDE;
    else if (by1 >= 30 + y) return UPGLIDE;
    else if ((x < 30 + bx1 && y < 30 + by1 && x > bx1 - 30 && y > by1 - 30 ) && (click == 0)) {
      click = 1;
      if (lastGestute == LONGPRESSDE) {
        click = 0;
        lastGestute = NONE;
      }
      timer1 = millis();
      return NONE;
    }
    else if ((x < 30 + bx1 && y < 30 + by1 && x > bx1 - 30 && y > by1 - 30 ) && (click == 1)) {
      click = 2 ;
      interval = millis() - timer1 ;
      return NONE;
    }
  }
  if ((millis() - timer >= 2000) && screenPressed == 1) {
    if (position[0].x < bx1 + 20 && position[0].x > bx1 - 20 && position[0].y < by1 + 20 && position[0].y > by1 - 20) {
      screenPressed = 0;
      lastGestute = LONGPRESSDE;
      return LONGPRESSDE;
    }
  }
  bx2 = position[0].x;
  by2 = position[0].y;
  return NONE;
}