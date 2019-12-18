#ifndef __DFROBOT_GDL_H
#define __DFROBOT_GDL_H

#include <Arduino.h>
#include "Print.h"
#include <SPI.h>
#include <Wire.h>
#include "Frame/Adafruit_GFX.h"
#include <DFRobot_Type.h>
#include "Drivers/DFRobot_ST7735S.h"
#include "Fonts/gdlFontDef.h"
#include "DFRobot_3WireSPI.h"
//#include "Drivers/DFRobot_Display_Series.h"
//#include "Fonts/SIMKAIFont12pt.h"

#if 1
#ifdef ARDUINO_SAM_ZERO//M0板子的串口与其他串口使用方式有区别
#define DBG(...) {SerialUSB.print("["); SerialUSB.print(__FUNCTION__); SerialUSB.print("(): "); SerialUSB.print(__LINE__); SerialUSB.print(" ] "); SerialUSB.println(__VA_ARGS__);}
#else
#define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#endif
#else
#define DBG(...)
#endif

#define COLOR_MODE_SINGLE  0
#define COLOR_MODE_RGB111  1
#define COLOR_MODE_RGB565  2
#define COLOR_MODE_RGB666  3
#define COLOR_MODE_RGB888  4

/*color*/
#define DF_GDL_RED         0xF800
#define DF_GDL_ORANGE      0xFD20
#define DF_GDL_YELLOW      0xFFE0
#define DF_GDL_GREEN       0x07E0
#define DF_GDL_CYAN        0x07FF
#define DF_GDL_BLUE        0x001F
#define DF_GDL_PURPLE      0x780F
#define DF_GDL_BLACK       0x0000
#define DF_GDL_WHITE       0xFFFF

class DFRobot_GDL : public Adafruit_GFX{

public:
  uint8_t _type; //0:DF_GDL_HW_SPI, 1:DF_GDL_SF_SPI, 2:DF_GDL_HW_IIC, 3:DF_GDL_SF_IIC
  sGdlDev_t _gdl;
  DFRobot_GDL(int16_t w, int16_t h):Adafruit_GFX(w,h){};
  DFRobot_GDL(sGdl_dev_t *dev, int16_t w, int16_t h, uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl);//hardware SPI
  //DFRobot_GDL(sGdl_dev_t *dev, int16_t w, int16_t h, uint8_t sck, uint8_t mosi, uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl, uint8_t miso);
  DFRobot_GDL(sGdl_dev_t *dev, int16_t w, int16_t h, uint8_t addr, uint8_t rst, uint8_t bl);
  DFRobot_GDL(sGdl_dev_t *dev, int16_t w, int16_t h, uint8_t cs, uint8_t dc/*rs*/, uint8_t wr, uint8_t rd, \
                   uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, \
                   uint8_t d5, uint8_t d6, uint8_t d7, uint8_t d8, uint8_t d9, \
                   uint8_t d10, uint8_t d11, uint8_t d12, uint8_t d13, uint8_t d14, \
                   uint8_t d15, uint8_t rst, uint8_t bl, bool isParal6800);
  //DFRobot_GDL(uint8_t addr, int16_t w, int16_t h);//hardware IIC
  ~DFRobot_GDL();
  void init_gdl();
  void init_interface();
  void init_hw_spi(sGdl_dev_t *dev, uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl);
  void init_hw_iic(sGdl_dev_t *dev, uint8_t addr, uint8_t rst, uint8_t bl);
  void init_paral_8080(sGdl_dev_t *dev, uint8_t dc, uint8_t cs, uint8_t wr, uint8_t rd, uint8_t rst, uint8_t bl, uint8_t *pins, uint8_t bits);
  void init_paral_6800(sGdl_dev_t *dev, uint8_t dc, uint8_t cs, uint8_t wr, uint8_t en, uint8_t rst, uint8_t bl, uint8_t *pins, uint8_t bits);
  
  void initDisplay();
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void fillScreen(uint16_t color);
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  void getColorFormat(uint8_t *pBuf, uint8_t &len, uint8_t &pixel, uint16_t color);
  virtual void setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) = 0;

  uint8_t rgb565ToRGB666(uint8_t *rgb666, uint16_t color);
  void rgb565ToRGB888(uint8_t *r, uint8_t *g, uint8_t *b, uint16_t color);
  uint16_t rgb888ToRGB565(uint8_t r, uint8_t g, uint8_t b);
  
  void setFonts(const gdl_Font_t *font);
  virtual size_t write(const uint8_t *buffer, size_t size);
  uint32_t utf8ToUnicode(uint8_t num, uint8_t *buf);
  uint8_t getUtf_8Bytes(uint8_t b);
  void drawCharBitmaps(uint16_t x, uint16_t y, gdl_Font_t *gdlFont, uint16_t fg, uint16_t bg);
  void sendCommand(uint8_t cmd, uint8_t *args = NULL, uint8_t len = 0);
  void sendCommand(uint8_t cmd, const uint8_t *args, uint8_t len);
  void sendArgument8(uint8_t args, bool isCmd = false);
  void sendArgument(uint16_t args, bool isCmd = false);
  void sendData(uint8_t dat);
  void sendData(uint8_t *pBuf, uint16_t len);
  void sendData16(uint16_t data);

protected:
  void writeColor(uint16_t color, uint32_t len);
  void writeColor(uint8_t *colorBuf, uint8_t pixelBytes, uint32_t len);

private:
  gdl_Font_t *_gdlFont;
};

class DFRobot_ST7735S_80x160: public DFRobot_GDL{
public:
  DFRobot_ST7735S_80x160(uint8_t dc, uint8_t cs = GDL_PIN_NONE, uint8_t rst = GDL_PIN_NONE, uint8_t bl = GDL_PIN_NONE);
  ~DFRobot_ST7735S_80x160(){}
  void begin();
  void setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
 // void setColorMode(uint8_t mode);
};



class DFRobot_SSD1306_128x32: public DFRobot_GDL{
public:
  DFRobot_SSD1306_128x32(uint8_t addr = 0x3C, uint8_t rst = GDL_PIN_NONE, uint8_t bl = GDL_PIN_NONE);
  //DFRobot_SSD1306_128x32(uint8_t sda, uint8_t scl,  uint8_t addr = 0x3C, uint8_t rst = GDL_PIN_NONE, uint8_t bl = GDL_PIN_NONE);
  ~DFRobot_SSD1306_128x32();
  void begin();
  void setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
 // void setColorMode(uint8_t mode);
};

class DFRobot_ILI9488_480x320: public DFRobot_GDL{
public:
  DFRobot_ILI9488_480x320(uint8_t cs, uint8_t dc, uint8_t wr, uint8_t rd, uint8_t d0, uint8_t d1, \
    uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, \
    uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11, uint8_t d12, uint8_t d13, uint8_t d14, \
    uint8_t d15, uint8_t rst = GDL_PIN_NONE, uint8_t bl = GDL_PIN_NONE, bool isParal6800 = false);
  //DFRobot_SSD1306_128x32(uint8_t sda, uint8_t scl,  uint8_t addr = 0x3C, uint8_t rst = GDL_PIN_NONE, uint8_t bl = GDL_PIN_NONE);
  DFRobot_ILI9488_480x320(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl);
#ifdef ARDUINO_SAM_ZERO
  DFRobot_ILI9488_480x320(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl, uint8_t dma);
#endif
  ~DFRobot_ILI9488_480x320(){};
  void begin();
  void setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
  void setColorMode(uint8_t mode);
};

class DFRobot_ILI9488_320x480_HW_SPI: public DFRobot_ILI9488_480x320{
public:
  DFRobot_ILI9488_320x480_HW_SPI(uint8_t dc, uint8_t cs = GDL_PIN_NONE, uint8_t rst = GDL_PIN_NONE, uint8_t bl = GDL_PIN_NONE);
  /*ili9488驱动的4线SPI接口只支持RGB66和RGB111两种颜色格式，默认配置为RGB666*/
  void begin(uint32_t freq = 0, uint8_t cMode = COLOR_MODE_RGB666);//支持2种颜色格式：RGB666和RGB111
};
#ifdef ARDUINO_SAM_ZERO
class DFRobot_ILI9488_320x480_DMA_SPI: public DFRobot_ILI9488_480x320{
public:
  DFRobot_ILI9488_320x480_DMA_SPI(uint8_t dc, uint8_t cs = GDL_PIN_NONE, uint8_t rst = GDL_PIN_NONE, uint8_t bl = GDL_PIN_NONE);
  /*ili9488驱动的4线SPI接口只支持RGB66和RGB111两种颜色格式，默认配置为RGB666*/
 // void begin(uint8_t cMode = COLOR_MODE_RGB666);//支持2种颜色格式：RGB666和RGB111
};
#endif
#ifdef ARDUINO_AVR_UNO
class DFRobot_LT768_320x480_3W_SPI: public DFRobot_GDL{
public:
  DFRobot_LT768_320x480_3W_SPI(uint8_t cs);
  void begin();
  void setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color1);
protected:
  void LCD_RegisterWrite(uint8_t cmd,uint8_t data);
  //void Foreground_color_65k(uint16_t temp);
  void WriteCommand(uint8_t cmd);
  void WriteData(uint8_t dat);
  void WriteData16(uint16_t dat);
  uint8_t SPI_StatusRead(void);
  uint16_t SPI_DataRead(void);
  uint8_t LCD_StatusRead(void);
  uint16_t LCD_DataRead(void);
private:
  uint8_t _cs;
};
#endif

class DFRobot_ST7789_240x240_HW_SPI: public DFRobot_GDL{
public:
  DFRobot_ST7789_240x240_HW_SPI(uint8_t dc, uint8_t cs = GDL_PIN_NONE, uint8_t rst = GDL_PIN_NONE, uint8_t bl = GDL_PIN_NONE);
  ~DFRobot_ST7789_240x240_HW_SPI();
  void begin();
  void setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
};
class DFRobot_ST7789_240x320_HW_SPI: public DFRobot_GDL{
public:
  DFRobot_ST7789_240x320_HW_SPI(uint8_t dc, uint8_t cs = GDL_PIN_NONE, uint8_t rst = GDL_PIN_NONE, uint8_t bl = GDL_PIN_NONE);
  ~DFRobot_ST7789_240x320_HW_SPI();
  void begin();
  void setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
};

#endif