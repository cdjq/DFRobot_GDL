#include "DFRobot_Display_Series.h"
#include "DFRobot_GDL.h"
#include "DFRobot_ST7735S.h"
#include "DFRobot_SSD1306.h"
#include "DFRobot_ILI9488.h"
#include "DFRobot_ST7789.h"


GDL_PB_DEV(gdl_dev_st7789_240x320_hw_spi, (uint8_t *)DFRobot_ST7789_initCmd, GDL_COM_HW_SPI);
GDL_PB_DEV(gdl_dev_st7789_240x240_hw_spi, (uint8_t *)DFRobot_ST7789_initCmd, GDL_COM_HW_SPI);
GDL_PB_DEV(gdl_dev_st7735s_80x160_hw_spi, (uint8_t *)DFRobot_ST7735S_initCmd, GDL_COM_HW_SPI);
GDL_PB_DEV(gdl_dev_ssd1306_128x32_hw_iic, (uint8_t *)DFRobot_SSD1306_initCmd, GDL_COM_HW_IIC);
GDL_PB_DEV(gdl_dev_ssd1306_128x32_8080_p16, (uint8_t *)DFRobot_ILI9488_initCmd, GDL_COM_8080_P16);
GDL_PB_DEV(gdl_dev_ili9488_320x480_hw_spi, (uint8_t *)DFRobot_ILI9488_initCmd, GDL_COM_HW_SPI);
#ifdef ARDUINO_SAM_ZERO
GDL_PB_DEV(gdl_dev_ili9488_320x480_dma_spi, (uint8_t *)DFRobot_ILI9488_initCmd, GDL_COM_DMA_SPI);
#endif
//sGdl_dev_t gdl_dev_ssd1306_128x32_8080_p16 = {(uint8_t *)st7796s_init1, GDL_COM_8080_P16};

//sGdl_dev_t gdl_dev_st7735s_80x160_hw_spi = {DFRobot_ST7735S_initCmd, GDL_COM_HW_SPI};
/////////////////////////////////////////////////////////////////////////////
DFRobot_ST7735S_80x160::DFRobot_ST7735S_80x160(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_dev_st7735s_80x160_hw_spi, 80, 160, dc, cs, rst, bl){

}
void DFRobot_ST7735S_80x160::begin(){
  init_interface();//接口初始化
  initDisplay();//显示屏初始化
}
void DFRobot_ST7735S_80x160::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color){
  Serial.print("w1 = ");Serial.println(w);
  Serial.print("h1 = ");Serial.println(h);
  x += 26;
  y += 1;
  uint16_t x1 = x + w -1;
  uint16_t y1 = y + h -1;
  sendCommand(0x2A);
  sendArgument(x);
  sendArgument(x1);
  sendCommand(0x2B);
  sendArgument(y);
  sendArgument(y1);
  sendCommand(0x2C);
  for(uint16_t i = 0; i < w; i++){
      for(uint16_t j = 0; j < h; j++){
          sendData16(color);
      }
  }
}
//////////////////////////////////////////////////////////////////////
// void setColorMode(uint8_t mode){
  // switch(mode){
      // case COLOR_MODE_RGB444:
           
  // }
// }

// DFRobot_ST7735S_80x160::DFRobot_ST7735S_80x160(uint8_t sck, uint8_t mosi, uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl, uint8_t miso)
  // :DFRobot_GDL(&gdl_dev_st7735s_80x160_hw_spi, 80, 160, sck, mosi, dc, cs, rst, bl, miso){
  
// }
DFRobot_SSD1306_128x32::DFRobot_SSD1306_128x32(uint8_t addr, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_dev_ssd1306_128x32_hw_iic, 128, 32, addr, rst, bl){
  
}
DFRobot_SSD1306_128x32::~DFRobot_SSD1306_128x32(){
  if(_gdl.buffer != NULL){
      free(_gdl.buffer);
      _gdl.buffer = NULL;
  }
}

void DFRobot_SSD1306_128x32::begin(){
  _gdl.buffer = (uint8_t *)malloc(128*64/8);
  memset(_gdl.buffer,0xff,128*64/8);
  init_interface();//接口初始化
  initDisplay();//显示屏初始化
}

void DFRobot_SSD1306_128x32::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color){
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
	  //Serial.print("i = ");Serial.println(i);
	  //Serial.print("sbit = ");Serial.println(sBit);
	  //Serial.print("ebit = ");Serial.println(eBit);
	  //Serial.print("offset = ");Serial.println(offset);
	  //
	  //Serial.print("data = ");Serial.println(data);
	  //Serial.print("color = ");Serial.println(color);
	  sBit = (eBit + 1)%4;
      for(uint16_t j = 0; j < w; j++){//每页传输w个字节，给buf[w]赋值一次性
          uint16_t index = i*128 + j;//计算该数据在buffer中的下标
          if(color){
              _gdl.buffer[index] |= data;
          }else{
              _gdl.buffer[index] &= ~data;
          }
          buf[j] = _gdl.buffer[index];
		  //Serial.print("j = ");Serial.println(j);
		  //Serial.print("buf = ");Serial.println(buf[j], HEX);
      }
      sendCommand(0xB0 + i);
      sendCommand(/*0x00);*/lsbCol);
      sendCommand(/*0x10);*/msbCol);
	  sendData(buf, w);
  }
}

DFRobot_ILI9488_480x320::DFRobot_ILI9488_480x320(uint8_t cs, uint8_t dc, uint8_t wr, uint8_t rd, \
   uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, \
   uint8_t d7, uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11, uint8_t d12, uint8_t d13, \
   uint8_t d14, uint8_t d15, uint8_t rst, uint8_t bl, bool isParal6800)
  :DFRobot_GDL(&gdl_dev_ssd1306_128x32_8080_p16, 320, 480, cs,dc,wr,rd,d0,d1,d2,d3,d4,d5,d6,\
d7,d8,d9,d10,d11,d12,d13,d14,d15,rst,bl,isParal6800){
  // DBG();Serial.println(gdl_dev_ssd1306_128x32_8080_p16.addr[0],HEX);
  // Serial.println(gdl_dev_ssd1306_128x32_8080_p16.addr[1],HEX);
  // DBG((uint32_t)&gdl_dev_ssd1306_128x32_8080_p16.addr[0],HEX);
  // DBG((uint32_t)&st7796s_init1[0],HEX);
  // DBG(st7796s_init1[0]);
}

DFRobot_ILI9488_480x320::DFRobot_ILI9488_480x320(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_dev_ili9488_320x480_hw_spi, 320, 480, dc, cs, rst, bl){}
#ifdef ARDUINO_SAM_ZERO
DFRobot_ILI9488_480x320::DFRobot_ILI9488_480x320(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl, uint8_t dma)
  :DFRobot_GDL(&gdl_dev_ili9488_320x480_dma_spi, 320, 480, dc, cs, rst, bl){}
#endif
void DFRobot_ILI9488_480x320::begin(){
  init_interface();//接口初始化
  initDisplay();//显示屏初始化
  setColorMode(COLOR_MODE_RGB565);
}
void DFRobot_ILI9488_480x320::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color){
  uint8_t buf[3], len = 0, pixel = 0;
  getColorFormat(buf, len, pixel, color);
  uint16_t x1 = x + w -1;
  uint16_t y1 = y + h -1;
  sendCommand(0x2A);
  sendArgument(x);
  sendArgument(x1);
  sendCommand(0x2B);
  sendArgument(y);
  sendArgument(y1);
  sendCommand(0x2C);

  for(uint16_t i = 0; i < w; i++){
      for(uint16_t j = 0; j < h; j++){
          sendData(buf, len);
      }
  }
  delay(5);
}

void DFRobot_ILI9488_480x320::setColorMode(uint8_t mode){
  sendCommand(0x3A);
  switch(mode){
	  case COLOR_MODE_RGB111://暂不支持，找不到规律，调不通
	       sendArgument8(0x11);
		   _gdl.cMode = COLOR_MODE_RGB111;
		   break;
	  case COLOR_MODE_RGB565:
	       sendArgument8(0x55);
		   _gdl.cMode = COLOR_MODE_RGB565;
		   break;
	  case COLOR_MODE_RGB666:
	       sendArgument8(0x66);
		   _gdl.cMode = COLOR_MODE_RGB666;
		   break;
	  case COLOR_MODE_RGB888:
	       sendArgument8(0x77);
		   _gdl.cMode = COLOR_MODE_RGB888;
		   break;
  }
}

DFRobot_ILI9488_320x480_HW_SPI::DFRobot_ILI9488_320x480_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_ILI9488_480x320(dc, cs, rst, bl){}
void DFRobot_ILI9488_320x480_HW_SPI::begin(uint32_t freq, uint8_t cMode){
  DFRobot_ILI9488_480x320::begin();
  setColorMode(COLOR_MODE_RGB666);
}
#ifdef ARDUINO_SAM_ZERO
DFRobot_ILI9488_320x480_DMA_SPI::DFRobot_ILI9488_320x480_DMA_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_ILI9488_480x320(dc, cs, rst, bl, 1){}
/*void DFRobot_ILI9488_320x480_DMA_SPI::begin(uint8_t cMode){
  DFRobot_ILI9488_480x320::begin();
  //setColorMode(cMode);
}*/
#endif

DFRobot_ST7789_240x240_HW_SPI::DFRobot_ST7789_240x240_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_dev_st7789_240x240_hw_spi, 240, 240, dc, cs, rst, bl){}
DFRobot_ST7789_240x240_HW_SPI::~DFRobot_ST7789_240x240_HW_SPI(){}
void DFRobot_ST7789_240x240_HW_SPI::begin(){
  init_interface();//接口初始化
  initDisplay();//显示屏初始化
}
void DFRobot_ST7789_240x240_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
  uint8_t buf[3], len = 0, pixel = 0;
  //getColorFormat(buf, len, pixel, color);
  uint16_t x1 = x + w -1;
  uint16_t y1 = y + h -1;
  sendCommand(0x2A);
  sendArgument(x);
  sendArgument(x1);
  sendCommand(0x2B);
  sendArgument(y);
  sendArgument(y1);
  sendCommand(0x2C);

  for(uint16_t i = 0; i < w; i++){
      for(uint16_t j = 0; j < h; j++){
          sendData16(color);
      }
  }
}

DFRobot_ST7789_240x320_HW_SPI::DFRobot_ST7789_240x320_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_dev_st7789_240x320_hw_spi, 240, 320, dc, cs, rst, bl){}
DFRobot_ST7789_240x320_HW_SPI::~DFRobot_ST7789_240x320_HW_SPI(){}
void DFRobot_ST7789_240x320_HW_SPI::begin(){
  init_interface();//接口初始化
  initDisplay();//显示屏初始化
}
void DFRobot_ST7789_240x320_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
  sendCommand(0x2A);
  sendArgument(x);
  sendArgument(x + w -1);
  sendCommand(0x2B);
  sendArgument(y);
  sendArgument(y + h -1);
  sendCommand(0x2C);
  writeColor(color, uint32_t(w*h));
}