#ifndef __DFROBOT_TYPE_H
#define __DFROBOT_TYPE_H
#include "Arduino.h"
#include "DFRobot_Type.h"
#include "DFRobot_GDL.h"
#include "Interface/DFRobot_IF.h"
#include "Drivers/DFRobot_LCDType.h"

GDL_IF_PB_DEV(gdl_Dev_ST7789_R240x240_HW_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7789_initCmd, IF_COM_HW_SPI);
GDL_IF_PB_DEV(gdl_Dev_ST7789_R240x320_HW_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7789_initCmd, IF_COM_HW_SPI);
GDL_IF_PB_DEV(gdl_Dev_ST7735S_R80x160_HW_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7735S_initCmd, IF_COM_HW_SPI);
GDL_IF_PB_DEV(gdl_Dev_ILI9488_R480x320_HW_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ILI9488_initCmd, IF_COM_HW_SPI);
GDL_IF_PB_DEV(gdl_Dev_SSD1306_R128x32_HW_IIC, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_SSD1306_initCmd, IF_COM_HW_IIC);

DFRobot_ST7789_240x240_HW_SPI::DFRobot_ST7789_240x240_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ST7789_R240x240_HW_SPI, 240, 240, dc, cs, rst, bl){}
DFRobot_ST7789_240x240_HW_SPI::~DFRobot_ST7789_240x240_HW_SPI(){}
void DFRobot_ST7789_240x240_HW_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  /*复位*/
  CLR_PIN_LOW(_if.pinList[IF_PIN_RST]);
  delay(1000);
  SET_PIN_HIGH(_if.pinList[IF_PIN_RST]);
  delay(1000);
  initDisplay();
}
void DFRobot_ST7789_240x240_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
  sendCommand(0x2A);
  sendData16(x);
  sendData16(x + w -1);
  sendCommand(0x2B);
  sendData16(y);
  sendData16(y + h -1);
  sendCommand(0x2C);
  sendColor(color, (uint32_t)w*h);
}

DFRobot_ST7789_240x320_HW_SPI::DFRobot_ST7789_240x320_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ST7789_R240x320_HW_SPI, 240, 320, dc, cs, rst, bl){}
DFRobot_ST7789_240x320_HW_SPI::~DFRobot_ST7789_240x320_HW_SPI(){}
void DFRobot_ST7789_240x320_HW_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  /*复位*/
  CLR_PIN_LOW(_if.pinList[IF_PIN_RST]);
  delay(1000);
  SET_PIN_HIGH(_if.pinList[IF_PIN_RST]);
  delay(1000);
  initDisplay();
}
void DFRobot_ST7789_240x320_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
  sendCommand(0x2A);
  sendData16(x);
  sendData16(x + w -1);
  sendCommand(0x2B);
  sendData16(y);
  sendData16(y + h -1);
  sendCommand(0x2C);
  sendColor(color, (uint32_t)w*h);
}

DFRobot_ST7735S_80x160_HW_SPI::DFRobot_ST7735S_80x160_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ST7735S_R80x160_HW_SPI, 80, 160, dc, cs, rst, bl){}
DFRobot_ST7735S_80x160_HW_SPI::~DFRobot_ST7735S_80x160_HW_SPI(){}
void DFRobot_ST7735S_80x160_HW_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  /*复位*/
  CLR_PIN_LOW(_if.pinList[IF_PIN_RST]);
  delay(1000);
  SET_PIN_HIGH(_if.pinList[IF_PIN_RST]);
  delay(1000);
  initDisplay();
}
void DFRobot_ST7735S_80x160_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
  sendCommand(0x2A);
  sendData16(x);
  sendData16(x + w -1);
  sendCommand(0x2B);
  sendData16(y);
  sendData16(y + h -1);
  sendCommand(0x2C);
  sendColor(color, (uint32_t)w*h);
}

DFRobot_ILI9488_480x320_HW_SPI::DFRobot_ILI9488_480x320_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ILI9488_R480x320_HW_SPI, 480, 320, dc, cs, rst, bl){}
DFRobot_ILI9488_480x320_HW_SPI::~DFRobot_ILI9488_480x320_HW_SPI(){}
void DFRobot_ILI9488_480x320_HW_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  /*复位*/
  CLR_PIN_LOW(_if.pinList[IF_PIN_RST]);
  delay(1000);
  SET_PIN_HIGH(_if.pinList[IF_PIN_RST]);
  delay(1000);
  initDisplay();
}
void DFRobot_ILI9488_480x320_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
  sendCommand(0x2A);
  sendData16(x);
  sendData16(x + w -1);
  sendCommand(0x2B);
  sendData16(y);
  sendData16(y + h -1);
  sendCommand(0x2C);
  sendColor(color, (uint32_t)w*h);
}

DFRobot_SSD1306_128x32_HW_IIC::DFRobot_SSD1306_128x32_HW_IIC(uint8_t addr, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_SSD1306_R128x32_HW_IIC, 128, 32, addr, rst, bl){
  
}

DFRobot_SSD1306_128x32_HW_IIC::~DFRobot_SSD1306_128x32_HW_IIC(){

}

void DFRobot_SSD1306_128x32_HW_IIC::begin(uint32_t freq){
  gdlInit(freq);
  _lcd.buffer = (uint8_t *)malloc(128*64/8);
  memset(_lcd.buffer,0xff,128*64/8);
  CLR_PIN_LOW(_if.pinList[IF_PIN_RST]);
  delay(1000);
  SET_PIN_HIGH(_if.pinList[IF_PIN_RST]);
  delay(1000);
  initDisplay();//显示屏初始化
}

void DFRobot_SSD1306_128x32_HW_IIC::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color){
  uint8_t buf[w];//定义大小为w的数组，该数组存放一次性发送的数据
  memset(buf, 0x00, w);
  uint8_t pageS = y/4;//起始页
  uint8_t pageE = (y + h - 1)/4;//结束页
  uint8_t n = 0;//每页每列能操控的像素点的个数
  uint8_t data = 0x00;//数据
  uint8_t sBit = y%4;//sBit*2为第y行在8bits的第几位
  uint8_t eBit = 0;
  uint8_t lsbCol = x & 0x0F;
  uint8_t msbCol = (x >> 4) | 0x10;
  uint8_t offset = 0;
  for(uint8_t i = pageS; i < pageE + 1; i++){//该区域有多少页，一页一页的写数据
      if((i + 1) == (pageE + 1)){
          eBit = (y + h - 1)%4;
      }else{
          eBit = (i*4 + 3)%4;
      }
      n = eBit - sBit;
      offset = sBit*2;
      switch(n){
          case 0:
               data = 0x03 << offset;
               break;
          case 1:
               data = 0x0F << offset;
               break;
          case 2:
               data = 0x3F << offset;
               break;
          default:
               data = 0xff << offset;
               break;
      }
      sBit = (eBit + 1)%4;
      for(uint16_t j = 0; j < w; j++){//每页传输w个字节，给buf[w]赋值一次性
          uint16_t index = i*128 + j;//计算该数据在buffer中的下标
          if(color){
              _lcd.buffer[index] |= data;
          }else{
              _lcd.buffer[index] &= ~data;
          }
          buf[j] = _lcd.buffer[index];
      }
      sendCommand(0xB0 + i);
      sendCommand(lsbCol);
      sendCommand(msbCol);
      sendBuf(buf, w);
  }
}


#ifdef ARDUINO_SAM_ZERO
GDL_IF_PB_DEV(gdl_Dev_ST7789_R240x240_DMA_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7789_initCmd, IF_COM_DMA_SPI);
GDL_IF_PB_DEV(gdl_Dev_ST7735S_R80x160_DMA_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7735S_initCmd, IF_COM_DMA_SPI);

DFRobot_ST7789_240x240_DMA_SPI::DFRobot_ST7789_240x240_DMA_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ST7789_R240x240_DMA_SPI, 240, 240, dc, cs, rst, bl){}
DFRobot_ST7789_240x240_DMA_SPI::~DFRobot_ST7789_240x240_DMA_SPI(){}
void DFRobot_ST7789_240x240_DMA_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  /*复位*/
  CLR_PIN_LOW(_if.pinList[IF_PIN_RST]);
  delay(1000);
  SET_PIN_HIGH(_if.pinList[IF_PIN_RST]);
  delay(1000);
  initDisplay();
}
void DFRobot_ST7789_240x240_DMA_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
  sendCommand(0x2A);
  sendData16(x);
  sendData16(x + w -1);
  sendCommand(0x2B);
  sendData16(y);
  sendData16(y + h -1);
  sendCommand(0x2C);
  sendColor(color, (uint32_t)w*h);
}

DFRobot_ST7735S_80x160_DMA_SPI::DFRobot_ST7735S_80x160_DMA_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ST7735S_R80x160_DMA_SPI, 80, 160, dc, cs, rst, bl){}
DFRobot_ST7735S_80x160_DMA_SPI::~DFRobot_ST7735S_80x160_DMA_SPI(){}
void DFRobot_ST7735S_80x160_DMA_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  /*复位*/
  CLR_PIN_LOW(_if.pinList[IF_PIN_RST]);
  delay(1000);
  SET_PIN_HIGH(_if.pinList[IF_PIN_RST]);
  delay(1000);
  initDisplay();
}
void DFRobot_ST7735S_80x160_DMA_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
  sendCommand(0x2A);
  sendData16(x);
  sendData16(x + w -1);
  sendCommand(0x2B);
  sendData16(y);
  sendData16(y + h -1);
  sendCommand(0x2C);
  sendColor(color, (uint32_t)w*h);
}

#endif//end M0


#endif
