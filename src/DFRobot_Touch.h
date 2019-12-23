#ifndef __DFROBOT_TOUCH_H
#define __DFROBOT_TOUCH_H
#include "Arduino.h"
#include "Wire.h"
#include "TouchDrivers/DFRobot_GT911.h"
#include "TouchDrivers/DFRobot_GT5688.h"
#include <DFRobot_Type.h>
#include "DFRobot_IF.h"
#define XFAC      920 //663
#define XOFFSET   (-20) //(-13)
#define YFAC      1300 //894
#define YOFFSET   (-30) 
class DFRobot_Touch: public DFRobot_IF{
public:
  typedef struct{
      uint8_t id;
      uint16_t x;
      uint16_t y;
      uint8_t wSize;
      uint8_t hSize;
  }sPoints_t;
  typedef struct{
      uint16_t xw;
	  uint16_t yh;
  }sResolution_t;
  
  sResolution_t _size;
  String _points;
  sPoints_t _point;
  uint8_t _pNum;
  DFRobot_Touch(sGdlIFDev_t *dev, uint8_t addr, uint8_t rst, uint8_t irq);
  DFRobot_Touch(sGdlIFDev_t *dev, uint8_t dc, uint8_t cs, uint8_t rst, uint8_t irq);
  ~DFRobot_Touch();
  void initTouch();
  void touchConfig(uint8_t *addr);
  virtual String scan() = 0;
};


class DFRobot_Touch_GTxxx: public DFRobot_Touch{
public:
  DFRobot_Touch_GTxxx(uint8_t addr = 0x5D, uint8_t rst = 255, uint8_t irq = 255);
  ~DFRobot_Touch_GTxxx();
  void begin();
  String scan();
private:
  typedef struct{
      uint8_t id;
      uint8_t xl;
      uint8_t xh;
      uint8_t yl;
      uint8_t yh;
      uint8_t wSize;
      uint8_t hSize;
      uint8_t reserve;
  }sGtPoints_t;
  sGtPoints_t _p[5];
  String id;//GT911和GT5688都有id
};

class DFRobot_Touch_XPTxxx:DFRobot_Touch{
public:
  DFRobot_Touch_XPTxxx(uint8_t cs, uint8_t dc = 255,uint8_t rst = 255, uint8_t irq = 255);
  ~DFRobot_Touch_XPTxxx();
  void begin();
  String scan();
  uint16_t readxy(uint8_t cmd);
private:
  uint8_t _cs;
  String id;//GT911和GT5688都有id
};
#endif