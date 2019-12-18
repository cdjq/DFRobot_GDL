#include "DFRobot_Touch.h"
//#include "DFRobot_GDL.h"
#include <DFRobot_Type.h>
#include "Interface/DFRobot_Interface.h"
#include "Wire.h"
#define ADDR 0x5D

uint8_t IF_addr[] = {0};
sGdlIFDev_t gt9xxx_dev = {NULL, GDL_COM_HW_IIC};

DFRobot_Touch::DFRobot_Touch(sGdlIFDev_t *dev, uint8_t addr, uint8_t rst, uint8_t irq)
  :DFRobot_IF(dev, addr, rst, irq){}

DFRobot_Touch::~DFRobot_Touch(){
  
}
void DFRobot_Touch::initTouch(){
  _points = "";
  _pNum = 0;
  memset(&_size, 0, sizeof(_size));
  memset(&_point, 0, sizeof(sPoints_t));
  init();
}

void DFRobot_Touch::touchConfig(uint8_t *addr){
  uint8_t regByte = pgm_read_byte(addr++);
  uint8_t regValByte = pgm_read_byte(addr++);
  uint8_t regBuf[regValByte];
  uint32_t reg = 0;
  for(uint8_t i = 0; i < regByte; i++){
      regBuf[i] = pgm_read_byte(addr++);
  }
  for(uint8_t j = 0; j < regByte; j++){
      reg |= (uint32_t)(regBuf[regByte -1 -j] << 8*j);
  }
  uint16_t length =  pgm_read_byte(addr++)<<8|pgm_read_byte(addr++);
  int8_t flag = regByte - 1;
  uint8_t buf[regByte+1+regValByte];
  buf[0] = regByte;
  
  for(uint8_t i = 0; i < length; i++){
      memcpy(buf+1, regBuf, regByte);
      for(uint8_t j = 0; j < regValByte; j++){
          buf[regByte+1+j] = pgm_read_byte(addr++);
      }
      //Serial.println(buf[regByte+1]);
      _if.dev->talk(&_if, GDL_COM_WRITE_BUFFER, buf, regValByte);
      reg += 1;
      for(uint8_t i = 0; i < regByte; i++){
          regBuf[regByte - 1- i] = (uint8_t)(reg >> 8*i);
      }
  }
}


DFRobot_Touch_GTxxx::DFRobot_Touch_GTxxx(uint8_t addr, uint8_t rst, uint8_t irq)
  :DFRobot_Touch(&gt9xxx_dev, addr, rst, irq){
  id = "";
  memset(_p, 0, sizeof(_p));
}
DFRobot_Touch_GTxxx::~DFRobot_Touch_GTxxx(){
  
}
void DFRobot_Touch_GTxxx::begin(){
  initTouch();
  char temp[4]={0};//获取芯片id
  uint16_t sizeReg = 0;
  readBuf(0x8140,temp,4);
  id = temp;
  //Serial.println(id);
  //while(1);
  if(id == "5688"){
      _if.dev->addr = (uint8_t *)touchGt5688ConfigTable;
      sizeReg = 0x8051;
  }else if(id == "911"){
      _if.dev->addr = (uint8_t *)touchGT911ConfigTable;
      sizeReg = 0x8048;
  }
  uint8_t *addr = _if.dev->addr;
  touchConfig(addr);
  readBuf(sizeReg,temp,4);

  _size.xw = ((uint8_t)temp[1] << 8) | (uint8_t)temp[0];
  _size.yh = ((uint8_t)temp[3] << 8) | (uint8_t)temp[2];
}
String DFRobot_Touch_GTxxx::scan(){
  uint8_t flag = 0;
  uint8_t val = 0x00;
  String s = "";
  memset(_p, 0, sizeof(_p));
  readBuf(0x814E, &flag, 1);
  //Serial.print("flag = ");Serial.println(flag,HEX);
  if((flag & 0x80) ||((flag&0x0F)<6)){
      writeBuf(0x814E, &val, 1);
  }
  if((flag & 0x80) &&((flag&0x0F)<6)){
      readBuf(0x814F, &_p, sizeof(_p));
      _pNum = flag&0x0F;
      for(uint8_t i = 0; i < _pNum; i++){
          _point.id = _p[i].id;
          if(id == "5688")
              _point.id &= 0x0F;
          _point.x =  _p[i].xl + (_p[i].xh << 8);
          _point.y =  _p[i].yl + (_p[i].yh << 8);
          _point.wSize = _p[i].wSize;
          _point.hSize = _p[i].hSize;
          if((_point.x <= _size.xw) && (_point.y <= _size.yh)){
              s += String(_point.id) + "," + String(_point.x) + "," + String(_point.y) + "," + String(_point.wSize) + ","+ String(_point.hSize) + " ";
          }
      }
  }
  if(s.length() == 0){
     s = "255,0,0,0,0 ";
  }
    // Serial.println(s);
   delay(10);
  _points = s;
  return s;
}


