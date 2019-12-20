#include "DFRobot_GDL.h"
#include "DFRobot_Interface.h"

DFRobot_GDL::DFRobot_GDL(sGdl_dev_t *dev, int16_t w, int16_t h, uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :Adafruit_GFX(w, h){
  init_hw_spi(dev, dc, cs, rst, bl);
}
// DFRobot_GDL::DFRobot_GDL(sGdl_dev_t *dev, int16_t w, int16_t h, uint8_t sck, uint8_t mosi, uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl, uint8_t miso)
  // ::Adafruit_GFX(w, h){
  
// }
DFRobot_GDL::DFRobot_GDL(sGdl_dev_t *dev, int16_t w, int16_t h, uint8_t addr, uint8_t rst, uint8_t bl)
  :Adafruit_GFX(w, h){
  init_hw_iic(dev, addr, rst, bl);
}

DFRobot_GDL::DFRobot_GDL(sGdl_dev_t *dev, int16_t w, int16_t h, uint8_t cs, uint8_t dc/*rs*/, uint8_t wr, uint8_t rd, \
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, \
    uint8_t d5, uint8_t d6, uint8_t d7, uint8_t d8, uint8_t d9, \
    uint8_t d10, uint8_t d11, uint8_t d12, uint8_t d13, uint8_t d14, \
    uint8_t d15, uint8_t rst, uint8_t bl, bool isParal6800)
  :Adafruit_GFX(w, h){
  uint8_t temp[] = {d0,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15};//
  if(isParal6800) 
      init_paral_6800(dev, dc, cs, wr, rd, rst, bl, temp, sizeof(temp));
  else
      init_paral_8080(dev, dc, cs, wr, rd, rst, bl, temp, sizeof(temp));
}

DFRobot_GDL::~DFRobot_GDL(){
  if(_gdl.pinList != NULL){
      free(_gdl.pinList);
  }
  _gdl.pinList = NULL;
}

void DFRobot_GDL::init_gdl(){
  for(uint8_t i = 0; i < _gdl.interface; i++){
      _gdl.pinList[i] = GDL_PIN_NONE;
  }
  _gdl.buffer = NULL;
  _gdl.rotation = 0;
  _gdlFont = NULL;
}
void DFRobot_GDL::init_interface(){
  _gdl.dev->talk(&_gdl, GDL_COM_INTERFACE_INIT, NULL, 0);
}

void DFRobot_GDL::init_hw_spi(sGdl_dev_t *dev, uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl){
  _gdl.interface = DF_GDL_HW_SPI;
  _gdl.dev = dev;
  if((_gdl.pinList =(uint8_t *)malloc(_gdl.interface)) == NULL){
      return;
  }
  init_gdl();
  _gdl.pinList[GDL_PIN_DC] = dc;
  _gdl.pinList[GDL_PIN_CS] = cs;
  _gdl.pinList[GDL_PIN_RST] = rst;
  _gdl.pinList[GDL_PIN_BL] = bl;
  pinMode(_gdl.pinList[GDL_PIN_DC], OUTPUT);
  GDL_DC_HIGH(_gdl.pinList[GDL_PIN_DC]);
  if(_gdl.pinList[GDL_PIN_CS] != GDL_PIN_NONE){
      pinMode(_gdl.pinList[GDL_PIN_CS], OUTPUT);
      GDL_CS_HIGH(_gdl.pinList[GDL_PIN_CS]);
  }
  if(_gdl.pinList[GDL_PIN_RST] != GDL_PIN_NONE){
      pinMode(_gdl.pinList[GDL_PIN_RST], OUTPUT);
      GDL_RST_HIGH(_gdl.pinList[GDL_PIN_RST]);
  }
 // Serial.println(_gdl.pinList[GDL_PIN_BL]);
  if(_gdl.pinList[GDL_PIN_BL] != GDL_PIN_NONE){
      pinMode(_gdl.pinList[GDL_PIN_BL], OUTPUT);
      GDL_BL_HIGH(_gdl.pinList[GDL_PIN_BL]);
  }
}

void DFRobot_GDL::init_hw_iic(sGdl_dev_t *dev, uint8_t addr, uint8_t rst, uint8_t bl){
  _gdl.interface = DF_GDL_HW_IIC;
  _gdl.dev = dev;
  if((_gdl.pinList =(uint8_t *)malloc(_gdl.interface)) == NULL){
      return;
  }
  init_gdl();
  _gdl.pinList[GDL_PIN_ADDR] = addr;
  _gdl.pinList[GDL_PIN_RST] = rst;
  _gdl.pinList[GDL_PIN_BL] = bl;
  if(_gdl.pinList[GDL_PIN_RST] != GDL_PIN_NONE){
      pinMode(_gdl.pinList[GDL_PIN_RST], OUTPUT);
      GDL_RST_HIGH(_gdl.pinList[GDL_PIN_RST]);
  }
 // Serial.println(_gdl.pinList[GDL_PIN_BL]);
  if(_gdl.pinList[GDL_PIN_BL] != GDL_PIN_NONE){
      pinMode(_gdl.pinList[GDL_PIN_BL], OUTPUT);
      GDL_BL_HIGH(_gdl.pinList[GDL_PIN_BL]);
  }
}
void DFRobot_GDL::init_paral_8080(sGdl_dev_t *dev, uint8_t dc, uint8_t cs, uint8_t wr, uint8_t rd, uint8_t rst, uint8_t bl, uint8_t *pins, uint8_t bits){
  _gdl.interface = DF_GDL_PARAL_8080 + bits;
  _gdl.dev = dev;
  //Serial.print("dev[0] = ");Serial.println(dev->addr[0]);
  if((_gdl.pinList =(uint8_t *)malloc(_gdl.interface)) == NULL){
      return;
  }
  init_gdl();
  _gdl.pinList[GDL_PIN_RST] = rst;
  _gdl.pinList[GDL_PIN_BL] = bl;
  _gdl.pinList[GDL_PIN_DC] = dc;
  _gdl.pinList[GDL_PIN_CS] = cs;
  _gdl.pinList[GDL_PIN_WR] = wr;
  _gdl.pinList[GDL_PIN_RD] = rd;
  for(int i = 0; i < bits; i++){
      _gdl.pinList[i + GDL_PIN_D0] = pins[i];
  }
  pinMode(_gdl.pinList[GDL_PIN_DC], OUTPUT);
  pinMode(_gdl.pinList[GDL_PIN_CS], OUTPUT);
  // for(uint8_t i = 0; i < DF_GDL_PARAL_8080; i++){
    // GDL_PIN_OUT(_gdl.pinList[i]);
	// GDL_DC_HIGH(_gdl.pinList[i]);
  // }
}
void DFRobot_GDL::init_paral_6800(sGdl_dev_t *dev, uint8_t dc, uint8_t cs, uint8_t wr, uint8_t en, uint8_t rst, uint8_t bl, uint8_t *pins, uint8_t bits){
  _gdl.interface = DF_GDL_PARAL_8080 + bits;
  _gdl.dev = dev;
  if((_gdl.pinList =(uint8_t *)malloc(_gdl.interface)) == NULL){
      return;
  }
  init_gdl();
  _gdl.pinList[GDL_PIN_RST] = rst;
  _gdl.pinList[GDL_PIN_BL] = bl;
  _gdl.pinList[GDL_PIN_DC] = dc;
  _gdl.pinList[GDL_PIN_CS] = cs;
  _gdl.pinList[GDL_PIN_WR] = wr;
  _gdl.pinList[GDL_PIN_RD] = en;
  for(int i = 0; i < bits; i++){
     _gdl.pinList[i + GDL_PIN_D0] = pins[i];
  }
}

void DFRobot_GDL::sendCommand(uint8_t cmd, const uint8_t *args, uint8_t len){
  _gdl.dev->talk(&_gdl, GDL_COM_WRITE_CMD, &cmd, 1);
  for(uint8_t i = 0; i < len; i++){
    _gdl.dev->talk(&_gdl, GDL_COM_DISPLAY_INIT, (uint8_t *)args+i, 1);
  }
}
void DFRobot_GDL::sendCommand(uint8_t cmd, uint8_t *args, uint8_t len){
  _gdl.dev->talk(&_gdl, GDL_COM_WRITE_CMD, &cmd, 1);
  for(uint8_t i = 0; i < len; i++){
    _gdl.dev->talk(&_gdl, GDL_COM_WRITE_CMD, args+i, 1);
  }
}
void DFRobot_GDL::sendArgument8(uint8_t args, bool isCmd){
  if(isCmd)
	  _gdl.dev->talk(&_gdl, GDL_COM_WRITE_CMD, &args, 1);
  else
	  _gdl.dev->talk(&_gdl, GDL_COM_WRITE_DATA, &args, 1);
}

void DFRobot_GDL::sendArgument(uint16_t args, bool isCmd){
  uint8_t temp[2] = {(args >> 8), args};
  sendArgument8(temp[0], isCmd);
  sendArgument8(temp[1], isCmd);
}

void DFRobot_GDL::sendData(uint8_t dat){
  _gdl.dev->talk(&_gdl, GDL_COM_WRITE_DATA, &dat, 1);
}

void DFRobot_GDL::sendData(uint8_t *pBuf, uint16_t len){
  _gdl.dev->talk(&_gdl, GDL_COM_WRITE_DATA, pBuf, len);
}
void DFRobot_GDL::sendData16(uint16_t data){
  uint8_t temp[2];
  temp[0] = data >> 8;
  temp[1] = data;
  _gdl.dev->talk(&_gdl, GDL_COM_WRITE_DATA, temp, 2);
}
void DFRobot_GDL::writeColor(uint16_t color, uint32_t len){
  uint8_t buf[2 + 1];
  buf[0] = 2;
  buf[1] = color >> 8;
  buf[2] = color;
  _gdl.dev->talk(&_gdl, IF_COM_WRITE_COLOR, buf, len);
}
void DFRobot_GDL::writeColor(uint8_t *colorBuf, uint8_t pixelBytes, uint32_t len)
{
  uint8_t buf[pixelBytes + 1];
  buf[0] = pixelBytes;
  for(uint8_t i = 0; i < pixelBytes; i++){
	  buf[1+i] = colorBuf[i];
  }
  _gdl.dev->talk(&_gdl, IF_COM_WRITE_COLOR, buf, len);
}
