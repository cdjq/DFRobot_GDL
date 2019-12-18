#include "DFRobot_GDL.h"
#include "Drivers/DFRobot_SSD1306.h"
#include "Drivers/DFRobot_ILI9488.h"
#define DEFAULT_SPI_FREQ  40000000
#define DFEAULT_IIC_FREQ  400000
//#define pgm_read_byte(addr)  (*(const unsigned char *)(addr))

void DFRobot_GDL::initDisplay(){
  int16_t length = 2, n = 0;
  const uint8_t *addr = _gdl.dev->addr;
  //Serial.print("addr = ");Serial.println(addr[0],HEX);Serial.println(pgm_read_byte(&length), HEX);
  //DBG(*(const unsigned char *)(addr));
  uint8_t flag, cmd, argsNum, val;
  uint16_t time = 0;
 // DBG("Error2!");
  if(addr == NULL){
      DBG("addr error!");
      return;
  }
  while(((flag = pgm_read_byte(addr++)) > 0)) {
       //DBG(flag);
       cmd = pgm_read_byte(addr++);
       //DBG(cmd,HEX);
       //_gdl.dev->talk(&_gdl, GDL_COM_WRITE_CMD, &cmd, 1);
       val = pgm_read_byte(addr++);
       argsNum = val & 0x7F;
       //DBG(*addr,HEX);
       sendCommand(cmd, addr, argsNum);
       addr += argsNum;
       if(val & 0x80) {
           time = pgm_read_byte(addr++)*255 + pgm_read_byte(addr++);
           //DBG("time: ");DBG(time);
           delay(time);
       }
  }
  
}

void DFRobot_GDL::drawPixel(int16_t x, int16_t y, uint16_t color){
  setDisplayArea((uint16_t)x, (uint16_t)y, 1, 1, color);
}
void DFRobot_GDL::fillScreen(uint16_t color){
  setDisplayArea(0, 0, _width, _height, color);
}
void DFRobot_GDL::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color){
  setDisplayArea((uint16_t)x, (uint16_t)y, 1, h, color);
}

void DFRobot_GDL::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color){
  setDisplayArea((uint16_t)x, (uint16_t)y, w, 1, color);
}

void DFRobot_GDL::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color){
  setDisplayArea((uint16_t)x, (uint16_t)y, w, h, color);
}

void DFRobot_GDL::getColorFormat(uint8_t *pBuf, uint8_t &len, uint8_t &pixel, uint16_t color){
  switch(_gdl.cMode){
      case COLOR_MODE_SINGLE:
           if(color)
               pBuf[0] = 1;
           else
               pBuf[0] = 0;
           len = 1;
           pixel = 8;//一个字节代表8个像素点
           break;
      case COLOR_MODE_RGB111://一个字节代表2个像素点
           pBuf[0] =((color & 0x07) << 3) | ((color & 0x07));
           len = 1;
           pixel = 2;//一个字节代表2个像素点
           break;
      case COLOR_MODE_RGB565:
           pBuf[0] = color >> 8;
           pBuf[1] = color;
           len = 2;
           pixel = 1;//两个字节代表1个像素点
           break;
      case COLOR_MODE_RGB666:
           pBuf[0] = (color >> 8)&0xF8;
           pBuf[1] = (color >> 3)&0xFC;
           pBuf[2] = color << 3;
           len = 3;
           pixel = 1;//3个字节代表1个像素点
           break;
      case COLOR_MODE_RGB888:
           pBuf[0] = (color >> 8)&0xF8;
           pBuf[1] = (color >> 3)&0xFC;
           pBuf[2] = color << 3;
           len = 3;
           pixel = 1;//3个字节代表1个像素点
           break;
  }
}

uint8_t DFRobot_GDL::rgb565ToRGB666(uint8_t *rgb666, uint16_t color){
  uint8_t r = color >> 11;
  uint8_t g = (color << 5) >> 10;
  uint8_t b = color & 0x001F;
  r = (r << 1) | (r & 0x01);
  b = (b << 1) | (b & 0x01);
  *(rgb666 + 0) = r << 2;
  *(rgb666 + 1) = g << 2;
  *(rgb666 + 2) = b << 2;/*三个字节的前18位为*/
  return 3;
}
void DFRobot_GDL::rgb565ToRGB888(uint8_t *r, uint8_t *g, uint8_t *b, uint16_t color){
  uint8_t r5 = (color >> 11);
  uint8_t g6 = (color << 5) >> 10;
  uint8_t b5 = color & 0x001F;
  *r = (r5 << 3) | ((r5 & 0x01) << 2) | (((r5 >> 1)&0x01) << 1) | ((r5 >> 2)&0x01);
  *g = (g6 << 2) | ((g6 & 0x01) << 1) | ((g6 >> 1)&0x01);
  *b = (b5 << 3) | ((b5 & 0x01) << 2) | (((b5 >> 1)&0x01) << 1) | ((b5 >> 2)&0x01);
}

uint16_t DFRobot_GDL::rgb888ToRGB565(uint8_t r, uint8_t g, uint8_t b){
  uint16_t color = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
  return color;
}








#ifdef ARDUINO_AVR_UNO
DFRobot_LT768_320x480_3W_SPI::DFRobot_LT768_320x480_3W_SPI(uint8_t cs)
  :DFRobot_GDL(800,480),_cs(cs){
  
}
void DFRobot_LT768_320x480_3W_SPI::begin(){
  sw3WireSPI.begin();
  WriteCommand(0x05);
  WriteData(202);
  WriteCommand(0x07);
  WriteData(138);
  WriteCommand(0x09);
  WriteData(138);
  WriteCommand(0x06);
  WriteData(70);
  WriteCommand(0x80);
  WriteData(100);
  WriteCommand(0x0A);
  WriteData(100);
  WriteCommand(0x00);
  delayMicroseconds(1);
  WriteData(0x80);
  delay(1);
  WriteCommand(0xe0);
  WriteData(0x41);
  WriteCommand(0xe1);
  WriteData(3);
  WriteCommand(0xe2);
  WriteData(11);
  WriteCommand(0xe3);
  WriteData(3);
  WriteCommand(0xe4);
  WriteData(1);
  WriteCommand(0x01);
  WriteData(0xD1);

  WriteCommand(0x02);
  WriteData(0x40);

  WriteCommand(0x03);
  WriteData(0x00);
   
  WriteCommand(0x12);
  WriteData(0x80);
  WriteCommand(0x13);
   WriteData(0x03);

  WriteCommand(0x14);
  WriteData(99);
  WriteCommand(0x15);
  WriteData(0);
  WriteCommand(0x1A);
  WriteData(223);
  WriteCommand(0x1B);
  WriteData(1);
  WriteCommand(0x16);
  WriteData(16);
  WriteCommand(0x17);
  WriteData(4);
  WriteCommand(0x18);
  WriteData(19);
  WriteCommand(0x19);
  WriteData(1);
  WriteCommand(0x1C);
  WriteData(19);
  WriteCommand(0x1D);
  WriteData(19);
  WriteCommand(0x1E);
  WriteData(11);
  WriteCommand(0x1F);
  WriteData(2);
  WriteCommand(0x5E);
  WriteData(0x01);
  WriteCommand(0xB7);
  WriteData(0x41);

  WriteCommand(0x85);
  WriteData(0x0A);
  WriteCommand(0x84);
  WriteData(199);
  WriteCommand(0x8A);
  WriteData(100);
  WriteCommand(0x8B);
  WriteData(0);
  WriteCommand(0x86);
   WriteData(0x3A);
  WriteCommand(0x84);
  WriteData(199);
  WriteCommand(0x8E);
  WriteData(100);
  WriteCommand(0x8F);
  WriteData(0);
  WriteCommand(0x8C);
  WriteData(50);
  WriteCommand(0x8D);
  WriteData(0);
  WriteCommand(0x12);
  WriteData(0xC0);
  WriteCommand(0x10);
  WriteData(4);
  WriteCommand(0x20);
  WriteData(0);
  WriteCommand(0x21);
  WriteData(0);
  WriteCommand(0x22);
  WriteData(0);
  WriteCommand(0x23);
  WriteData(0);
  WriteCommand(0x24);
  WriteData(800&0x00FF);//w
  WriteCommand(0x25);
  WriteData(800>>8);//w
  WriteCommand(0x26);
  WriteData(0);
  WriteCommand(0x27);
  WriteData(0);
  WriteCommand(0x28);
  WriteData(0);
  WriteCommand(0x29);
  WriteData(0);

  WriteCommand(0x50);
  WriteData(0);
  WriteCommand(0x51);
  WriteData(0);
  WriteCommand(0x52);
  WriteData(0);
  WriteCommand(0x53);
  WriteData(0);
  WriteCommand(0x54);
  WriteData(800&0x00FF);
  WriteCommand(0x51);
  WriteData(800>>8);
  WriteCommand(0x56);
  WriteData(0);
  WriteCommand(0x57);
  WriteData(0);
  WriteCommand(0x58);
  WriteData(0);
  WriteCommand(0x59);
  WriteData(0);
  WriteCommand(0x5A);
  WriteData(800&0xff);
  WriteCommand(0x5B);
  WriteData(800>>8);
  WriteCommand(0x5C);
  WriteData(480&0xFF);
  WriteCommand(0x57);
  WriteData(480>>8);
}

void DFRobot_LT768_320x480_3W_SPI::WriteCommand(uint8_t cmd) {
  digitalWrite(_cs, LOW);
  sw3WireSPI.spiSendByte(0x00);
  sw3WireSPI.spiSendByte(cmd);
  digitalWrite(_cs, HIGH);
}
void DFRobot_LT768_320x480_3W_SPI::WriteData(uint8_t dat) {
  digitalWrite(_cs, LOW);
  sw3WireSPI.spiSendByte(0x80);
  sw3WireSPI.spiSendByte(dat);
  digitalWrite(_cs, HIGH);
}

void DFRobot_LT768_320x480_3W_SPI::WriteData16(uint16_t dat) {
  uint8_t buf[2] = {dat >> 8, dat};
  digitalWrite(_cs, LOW);
  sw3WireSPI.spiSendByte(0x80);
  sw3WireSPI.spiSendByte(buf[1]);
  digitalWrite(_cs, HIGH);
  digitalWrite(_cs, LOW);
  sw3WireSPI.spiSendByte(0x80);
  sw3WireSPI.spiSendByte(buf[0]);
  digitalWrite(_cs, HIGH);
}
uint16_t DFRobot_LT768_320x480_3W_SPI::SPI_DataRead(void)
{
  uint8_t temp = 0;
  digitalWrite(_cs, LOW);
  sw3WireSPI.spiSendByte(0xC0);
  temp =sw3WireSPI.spiReadByte();
  digitalWrite(_cs, HIGH);
  return (uint16_t)temp;
}

uint8_t DFRobot_LT768_320x480_3W_SPI::SPI_StatusRead(void)
{
  uint8_t temp = 0;
  digitalWrite(_cs, LOW);
  sw3WireSPI.spiSendByte(0x40);
  temp = sw3WireSPI.spiReadByte();
  digitalWrite(_cs, HIGH);
  return temp;
}
uint8_t DFRobot_LT768_320x480_3W_SPI::LCD_StatusRead(void)
{
  uint8_t temp = 0;
  temp = SPI_StatusRead();
  return temp;
}
uint16_t DFRobot_LT768_320x480_3W_SPI::LCD_DataRead(void)
{
  uint16_t temp = 0; 
  temp = SPI_DataRead(); 
  return temp;
}
void DFRobot_LT768_320x480_3W_SPI::LCD_RegisterWrite(uint8_t cmd,uint8_t data){
  WriteCommand(cmd);
  WriteData(data);
}
void DFRobot_LT768_320x480_3W_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color){
  uint16_t x1 = x + w;
  uint16_t y1 = y + h;
  uint8_t temp;
	/*WriteCommand(0x10);
	temp = LCD_DataRead();
	Serial.print("temp 0x10= ");Serial.print(temp,HEX);
    temp &= 0xF7;
    temp |= 0x04;
	Serial.print("___");Serial.println(temp, HEX);
	WriteCommand(temp);
	LCD_RegisterWrite(0x20,0);
	LCD_RegisterWrite(0x21,0);
	LCD_RegisterWrite(0x22,0);
	LCD_RegisterWrite(0x23,0);
	LCD_RegisterWrite(0x24,0x20);//0x320 = 800
	LCD_RegisterWrite(0x25,3);
	LCD_RegisterWrite(0x26,0);
	LCD_RegisterWrite(0x27,0);
	LCD_RegisterWrite(0x28,0);
	LCD_RegisterWrite(0x29,0);
	LCD_RegisterWrite(0x50,0);
	LCD_RegisterWrite(0x51,0);
	LCD_RegisterWrite(0x52,0);
	LCD_RegisterWrite(0x53,0);
	LCD_RegisterWrite(0x54,0x20);
	LCD_RegisterWrite(0x55,3);
	LCD_RegisterWrite(0x56,x);
	LCD_RegisterWrite(0x57,x>>8);
	LCD_RegisterWrite(0x58,y);
	LCD_RegisterWrite(0x59,y>>8);
	LCD_RegisterWrite(0x5A,w);
	LCD_RegisterWrite(0x5B,w>>8);
 	LCD_RegisterWrite(0x5C,y);
	LCD_RegisterWrite(0x5D,y>>8);
	
	WriteData(0x03);
	temp = LCD_DataRead();
	Serial.print("temp 0x03= ");Serial.print(temp,HEX);
    temp &= 0xfb;
	Serial.print("___");Serial.println(temp, HEX);
	WriteData(temp);
	
	WriteData(0x5E);
	temp = LCD_DataRead();
	Serial.print("temp 0x5E= ");Serial.print(temp,HEX);
	temp |= 0x02;
	temp |= 0x01;
	Serial.print("___");Serial.println(temp, HEX);
	WriteData(temp);
	WriteCommand(0x40);
	uint8_t n = 0,buf[2] = {color, color >> 8};
	for(uint16_t i=0;i < h;i++)
  { 
      for(uint16_t j=0;j < w;j++)
      {
        do{
        }while( LCD_StatusRead()&0x80 );
        WriteData(buf[n++]);
		if(n == 2){
			n = 0;
		}
      }
   }
    do{
	}while( (LCD_StatusRead()&0x40) == 0x00 );*/
 // uint32_t color = 0x00ff0000;
  WriteCommand(0xD2);
  WriteData(color>>8);
  WriteCommand(0xD3);
  WriteData(color>>3);
  WriteCommand(0xD4);
  WriteData(color<<3);
  
  WriteCommand(0x68);
  WriteData(x);
  WriteCommand(0x69);
  WriteData(x>>8);
  WriteCommand(0x6A);
  WriteData(y);
  WriteCommand(0x6B);
  WriteData(y>>8);
  
  WriteCommand(0x6C);
  WriteData(x1);
  WriteCommand(0x6D);
  WriteData(x1>>8);
  WriteCommand(0x6E);
  WriteData(y1);
  WriteCommand(0x6F);
  WriteData(y1>>8);
  
  WriteCommand(0x76);
  WriteData(0xA0);
  do
  {
      temp=LCD_StatusRead();
  }while(temp&0x08);
  
  
  WriteCommand(0x03);
  temp = LCD_DataRead();
  temp &= 0xfb;
  WriteCommand(temp);
  
  WriteCommand(0x56);
  WriteData(x);
  WriteCommand(0x57);
  WriteData(x>>8);
  WriteCommand(0x58);
  WriteData(y);
  WriteCommand(0x59);
  WriteData(y>>8);
  WriteCommand(0x5A);
  WriteData(w);
  WriteCommand(0x5B);
  WriteData(w>>8);
  WriteCommand(0x5C);
  WriteData(h);
  WriteCommand(0x5D);
  WriteData(h>>8);
  
  WriteCommand(0x5F);
  WriteData(x);
  WriteCommand(0x60);
  WriteData(x>>8);
  WriteCommand(0x61);
  WriteData(y);
  WriteCommand(0x62);
  WriteData(y>>8);
  WriteCommand(0x04);
  uint8_t buf[2] = {color, color>>8};
  uint8_t n = 0;
  for(uint16_t i=0;i< 480;i++)
  { 
	  //Serial.print("i = ");Serial.println(i);
	  for(uint16_t j=0;j< 800;j++)
      {
        do{
        }while( LCD_StatusRead()&0x80 );
        WriteData(buf[0]);
		do{
        }while( LCD_StatusRead()&0x80 );
        WriteData(buf[1]);
      }
   }
    do{
	}while( (LCD_StatusRead()&0x40) == 0x00 );
  
/*
  WriteCommand(0x01);
  temp = LCD_DataRead();
  Serial.print("temp 0x01= ");Serial.println(temp);
  temp |= 0x02;
  WriteData(temp);
  
  WriteCommand(0xB7);
  temp = LCD_DataRead();
  Serial.print("temp 0xB7= ");Serial.println(temp);
  temp |= 0x80;
  WriteData(temp);
  WriteCommand(0xB7);
  temp = LCD_DataRead();
  Serial.print("temp 0xB7= ");Serial.println(temp);
  temp |= 0x40;
  WriteData(temp);
  WriteCommand(0xBB);
  WriteData(0x00);
  
  WriteCommand(0x5F);
  WriteData(x);
  WriteCommand(0x60);
  WriteData(x>>8);
  WriteCommand(0x61);
  WriteData(y);
  WriteCommand(0x62);
  WriteData(y>>8);
  WriteCommand(0xC0);
  WriteData(x);
  WriteCommand(0xC1);
  WriteData(x>>8);
  WriteCommand(0xC2);
  WriteData(y);
  WriteCommand(0xC3);
  WriteData(y>>8);
  
  WriteCommand(0xC6);
  WriteData(x);
  WriteCommand(0xC7);
  WriteData(x>>8);
  
  WriteCommand(0xC8);
  WriteData(y);
  WriteCommand(0xC9);
  WriteData(y>>8);
  
  WriteCommand(0xCA);
  WriteData(x);
  WriteCommand(0xCB);
  WriteData(x>>8);
  WriteCommand(0xC0);
  WriteData(0);
  WriteCommand(0xC1);
  WriteData(0);
  WriteCommand(0xC2);
  WriteData(0);
  WriteCommand(0xC3);
  WriteData(0);
  
  WriteCommand(0xB6);
  temp = LCD_DataRead();
  temp |= 0x01;
  WriteData(temp);
  WriteCommand(0xB6);
    do{       
    }while((LCD_DataRead()&0x01)==0x01);

  //uint32_t color = 0x00ff0000;
 */ 
}
#endif