#include "DFRobot_IF.h"
/*typedef struct{
  uint8_t interface;//通信接口，保存的是通信接口的引脚数，及pinList的长度
  uin8_t freq;//通信频率
  uProtocol_t pro;//通信协议：IIC，并口，SPI，DMA等等
  uint8_t *pinList;//保存通信接口的引脚数据，它的长度由某种通信接口的最大引脚数决定
}sIF_t __attribute__ ((packed));*/

DFRobot_IF::DFRobot_IF(sGdlIFDev_t *dev, uint8_t addr, uint8_t rst, uint8_t irq/*bl*/){
  initHWIIC(dev, addr, rst, irq);
}
DFRobot_IF::~DFRobot_IF(){
  if(_if.pinList != NULL){
      free(_if.pinList);
  }
  _if.pinList = NULL;
}

void DFRobot_IF::init(){
  _if.dev->talk(&_if, GDL_COM_INTERFACE_INIT, NULL, 0);
}
void DFRobot_IF::initIF(){
  for(uint8_t i = 0; i < _if.interface; i++){
      _if.pinList[i] = GDL_PIN_NONE;
  }
  _if.length = 0xFFFF;
}
void DFRobot_IF::initHWIIC(sGdlIFDev_t *dev, uint8_t addr, uint8_t rst, uint8_t bl/*irq*/){
  _if.interface = DF_GDL_HW_IIC;
  _if.freq = 0;
  if((_if.pinList =(uint8_t *)malloc(_if.interface)) == NULL){
      return;
  }
  initIF();
  _if.pinList[GDL_PIN_ADDR] = addr;
  _if.pinList[GDL_PIN_RST] = rst;
  _if.pinList[GDL_PIN_BL] = bl;
  if(_if.pinList[GDL_PIN_RST] != GDL_PIN_NONE){
      pinMode(_if.pinList[GDL_PIN_RST], OUTPUT);
      GDL_RST_HIGH(_if.pinList[GDL_PIN_RST]);
  }
  if(_if.pinList[GDL_PIN_BL] != GDL_PIN_NONE){
      pinMode(_if.pinList[GDL_PIN_BL], OUTPUT);
      GDL_BL_HIGH(_if.pinList[GDL_PIN_BL]);
  }
  _if.length = I2C_BUFFER_LENGTH;
  _if.dev = dev;
}

void DFRobot_IF::writeBuf(uint16_t reg, void *pBuf, uint16_t len, bool flag)
{
  if(pBuf == NULL){
      return;
  }
  uint8_t *_pBuf = (uint8_t *)pBuf;
  uint8_t bufPre[3] = {0};
  uint16_t left = len;
  len = 0;
  while(left){
      len = (flag ? len/2 : len);
      reg += len;
      bufPre[0] = 2;
      bufPre[1] = reg >> 8;
      bufPre[2] = reg & 0xFF;
      len = (left > _if.length ? _if.length : left);
      uint8_t buf[3+len];
      memset(buf, 0, sizeof(buf));
      memcpy(buf, bufPre, 3);
      memcpy(buf+3, _pBuf, len);
      _if.dev->talk(&_if, GDL_COM_WRITE_BUFFER, buf, len);
      left -= len;
      _pBuf += len;
  }

}
void DFRobot_IF::readBuf(uint16_t reg, void *pBuf, uint16_t len, bool flag)
{
  if(pBuf == NULL)
    return; 
  uint8_t *_pBuf = (uint8_t *)pBuf;
  uint8_t bufPre[3] = {0};
  uint16_t left = len;
  len = 0;
  //_if.length = 2;
  while(left){
      len = (flag ? len/2 : len);
      reg += len;
      bufPre[0] = 2;
      bufPre[1] = reg >> 8;
      bufPre[2] = reg & 0xFF;
      len = (left > _if.length ? _if.length : left);
            uint8_t buf[3+len];
      memset(buf, 0, sizeof(buf));
      memcpy(buf, bufPre, 3);
      _if.dev->talk(&_if, GDL_COM_READ_BUFFER, buf, len);
      memcpy(_pBuf, buf, len);
      left -= len;
      _pBuf += len;
  }
}
