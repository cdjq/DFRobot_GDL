#ifndef __DFROBOT_PARALLEL_H
#define __DFROBOT_PARALLEL_H

#include "Arduino.h"
//#include "DFRobot_GDL.h"
#if 0
#define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define SET_PIN_IN(pin)  if(pin != PARAL_PIN_NONE){pinMode(pin, INPUT);}
#define SET_PIN_OUT(pin)  if(pin != PARAL_PIN_NONE){pinMode(pin, OUTPUT);}

#ifdef ARDUINO_ARCH_AVR
#define SET_PIN_HIGH(pin)  {*portOutputRegister(digitalPinToPort(pin)) |= digitalPinToBitMask(pin);}
#define SET_PIN_LOW(pin)   {*portOutputRegister(digitalPinToPort(pin)) &= ~digitalPinToBitMask(pin);}
#define GET_PIN_LEVEL(pin)  if(pin != PARAL_PIN_NONE){digitalRead(pin, LOW);}
#define SET_PIN_LEVEL(pin,value)  {(value)?SET_PIN_HIGH(pin):SET_PIN_LOW(pin);}
#else
#define SET_PIN_HIGH(pin)  {digitalWrite(pin, HIGH);}
#define SET_PIN_LOW(pin)   digitalWrite(pin, LOW)
#define GET_PIN_LEVEL(pin)  if(pin != PARAL_PIN_NONE){digitalRead(pin, LOW);}
#define SET_PIN_LEVEL(pin,value)  if(pin != PARAL_PIN_NONE){digitalWrite(pin, value);}
#endif
/*并口模式选择 8080/6800*/
#define PARAL_MODE_8080  1
#define PARAL_MODE_6800  2

#define PARAL_BUS_WIDTH8   8
#define PARAL_BUS_WIDTH16  16

/*字节顺序*/
#define PARAL_MSBFIRST  0
#define PARAL_LSBFIRST  1

#define PARAL_PIN_NONE   255

#define PARAL_PIN_D0   0
#define PARAL_PIN_D1   1
#define PARAL_PIN_D2   2
#define PARAL_PIN_D3   3
#define PARAL_PIN_D4   4
#define PARAL_PIN_D5   5
#define PARAL_PIN_D6   6
#define PARAL_PIN_D7   7
#define PARAL_PIN_D8   8
#define PARAL_PIN_D9   9
#define PARAL_PIN_D10  10
#define PARAL_PIN_D11  11
#define PARAL_PIN_D12  12
#define PARAL_PIN_D13  13
#define PARAL_PIN_D14  14
#define PARAL_PIN_D15  15

#define PARAL_PIN_MAX  16

/*数据位数选择*/


/*默认为8080模式*/


/*如果_rd*/
class DFRobot_Parallel{
public:
  DFRobot_Parallel(uint8_t wr, uint8_t rd_en, uint8_t mode = PARAL_MODE_8080);//6800
  DFRobot_Parallel();
  ~DFRobot_Parallel();
  void config(uint8_t wr, uint8_t rd_en, uint8_t mode = PARAL_MODE_8080);
  void setPins(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5, uint8_t pin6, uint8_t pin7);
  void setPins(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5, uint8_t pin6, uint8_t pin7, \
      uint8_t pin8, uint8_t pin9, uint8_t pin10, uint8_t pin11, uint8_t pin12, uint8_t pin13, uint8_t pin14, uint8_t pin15);
  void setPins(void *pins, uint8_t len);
  void begin();
  
  
  void write(uint8_t *pBuf, uint8_t len);
  void write(uint8_t value, uint8_t bits = 8);
  void write16(uint16_t value, uint8_t bits = 16);
  void writeBits(uint32_t value, uint8_t bits = 32);
  
  void transfer(uint8_t value);
  void transfer16(uint16_t value);

protected:
  void setPin(uint8_t pin, uint8_t value);
  void set_pin_in();
  void set_pin_out();
  void contrl_8080_w();
  void contrl_8080_r();
  void contrl_6800_w();
  void contrl_6800_r();
private:
  void sendData();
private:
  uint8_t _cs;
  uint8_t _dc;
  uint8_t _wr;
  uint8_t _rd;//如果_rd = PARAL_PIN_NONE,则为6800模式，否则为8080
  uint8_t _pinList[16];
  bool _isBegin;
  uint8_t _mode;
  uint8_t _bus_w;//数据总线宽度
  uint8_t _index;//在第几条数据总线上
  uint8_t _bitOrder;
  uint8_t _dir; //0:outPut, 1:input, 2未配置
};

extern DFRobot_Parallel PARAL;


#endif