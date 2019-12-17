#ifndef __DFROBOT_IF_H
#define __DFROBOT_IF_H
#include "DFRobot_Type.h"
#include "Interface/DFRobot_Interface.h"
/*硬件IIC一次能传输的最大字节数*/
#ifndef I2C_BUFFER_LENGTH//ESP32(fireBeetle系列定义了I2C_BUFFER_LENGTH)
#ifdef ARDUINO_ARCH_AVR  //AVR系列单片机一次最多传32字节数据
#define I2C_BUFFER_LENGTH  32
#endif
#endif

class DFRobot_IF{
public:
  sGdlIF_t _if;/*interface*/
  DFRobot_IF(sGdlIFDev_t *dev, uint8_t addr, uint8_t rst, uint8_t irq/*bl*/);
  ~DFRobot_IF();
  void init();
protected:
  void initIF();
  void initHWIIC(sGdlIFDev_t *dev, uint8_t addr, uint8_t rst, uint8_t bl/*irq*/);
  
  void writeBuf(uint16_t reg, void *pBuf = NULL, uint16_t len = 0, bool flag = false);//flag代表数据和寄存器是否匹配
  void readBuf(uint16_t reg, void *pBuf, uint16_t len, bool flag = false);
};

#endif