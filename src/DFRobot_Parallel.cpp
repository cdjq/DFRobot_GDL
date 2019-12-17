#include "DFRobot_Parallel.h"

DFRobot_Parallel PARAL;
DFRobot_Parallel::DFRobot_Parallel(/*uint8_t cs, uint8_t dc, */uint8_t wr, uint8_t rd_en, uint8_t mode){
  /*_cs = cs;
  _dc = dc;*/
  _wr = wr;
  _rd = rd_en;
  _mode = mode;
  _index = 0;
  _bus_w = PARAL_BUS_WIDTH8;
  _bitOrder = PARAL_MSBFIRST;
  _dir = 2;
  /*SET_PIN_OUT(_cs);
  SET_PIN_OUT(_dc);*/
  //set_pin_out();
}//6800

DFRobot_Parallel::DFRobot_Parallel(){
  _wr = PARAL_PIN_NONE;
  _rd = PARAL_PIN_NONE;
  _mode = PARAL_MODE_8080;
  _index = 0;
  _bus_w = PARAL_BUS_WIDTH8;
  _bitOrder = PARAL_MSBFIRST;
}
DFRobot_Parallel::~DFRobot_Parallel(){
  
}

void DFRobot_Parallel::config(uint8_t wr, uint8_t rd_en, uint8_t mode){
  _wr = wr;
  _rd = rd_en;
  _mode = mode;
}

void DFRobot_Parallel::setPins(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5, uint8_t pin6, uint8_t pin7){
  uint8_t pin[] = {pin0,pin1,pin2,pin3,pin4,pin5,pin6,pin7};
  for(int i = 0; i < sizeof(pin); i++){
      setPin(i, pin[i]);
  }
  _bus_w = PARAL_BUS_WIDTH8;
}
void DFRobot_Parallel::setPins(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5, uint8_t pin6, uint8_t pin7, \
    uint8_t pin8, uint8_t pin9, uint8_t pin10, uint8_t pin11, uint8_t pin12, uint8_t pin13, uint8_t pin14, uint8_t pin15){
  uint8_t pin[] = {pin0,pin1,pin2,pin3,pin4,pin5,pin6,pin7,pin8,pin9,pin10,pin11,pin12,pin13,pin14,pin15};
  for(int i = 0; i < sizeof(pin); i++){
      setPin(i, pin[i]);
  }
  _bus_w = PARAL_BUS_WIDTH16;
}

void DFRobot_Parallel::setPins(void *pins, uint8_t len){
  uint8_t *buf = (uint8_t *)pins;
  for(uint8_t i = 0; i < len; i++){
      setPin(i, buf[i]);
  }
  _bus_w = len;
}

void DFRobot_Parallel::setPin(uint8_t pin, uint8_t value){
  if(pin > PARAL_PIN_MAX) return;
  _pinList[pin] = value;
}

void DFRobot_Parallel::begin(){
  if(_mode && _bus_w) _isBegin = true;
  else _isBegin = false;
  Serial.print("_bus_w");Serial.println(_bus_w);
  for(uint8_t i = 0; i < _bus_w; i++){
      SET_PIN_OUT(_pinList[i]);
  //Serial.print("pin[");Serial.print(i);Serial.print("]: ");
  //Serial.println(_pinList[i]);
  }
  SET_PIN_OUT(_wr);
  SET_PIN_OUT(_rd);
  SET_PIN_HIGH(_wr);
  SET_PIN_HIGH(_rd);
}
void DFRobot_Parallel::write(uint8_t *pBuf, uint8_t len){
  if(pBuf == NULL) return;
  //DBG(pBuf[0],HEX);
  //DBG(len);
  uint8_t count = len*8/32;
  uint32_t buf[count];
  for(uint8_t i = 0; i < count; i++){
    buf[i] = (pBuf[i*4 + 0] << 24) + (pBuf[i*4 + 1] << 16) + (pBuf[i*4 + 2] << 8) + (pBuf[i*4 + 3]);
    writeBits(buf[i], 32);
  }
  if(len*8%32){
      uint32_t value = 0;
      uint8_t n = (len*8%32)/8;
      //DBG(n);
      for(uint8_t i = 0; i < n; i++){
          value |= pBuf[4*count + i] << ((n - i - 1)*8);
      }
      writeBits(value, len*8%32);
  }
}

void DFRobot_Parallel::write(uint8_t value, uint8_t bits){
  if(bits > 8) return;
  //DBG(value,HEX);
  writeBits((uint32_t)value, bits);
}
void DFRobot_Parallel::write16(uint16_t value, uint8_t bits){
  if(bits > 16) return;
  writeBits((uint32_t)value, bits);
}

void DFRobot_Parallel::writeBits(uint32_t value, uint8_t bits){
  if(bits > 32) return;
  uint8_t count = bits/_bus_w + ((bits%_bus_w) ? 1 : 0);//数据分几次搬运，默认先搬高位字节

#ifdef ARDUINO_AVR_MEGA2560
  uint8_t n = bits/8 +  ((bits%8) ? 1 : 0);
  if(n == count){
	  uint8_t i = 0;
	  while(n--){
		  *((volatile uint8_t *)((uint16_t) &PORTA)) = (uint8_t)(value>>8*i++);
		  sendData();
	  }
  }else{
	  uint8_t i = 0;
	  while(count--){
		*((volatile uint8_t *)((uint16_t) &PORTA)) = (uint8_t)(value>>8*i++);
		DBG(*((volatile uint8_t *)((uint16_t) &PORTA)),HEX);
		if(i != n)
			*((volatile uint8_t *)((uint16_t) &PORTC)) = (uint8_t)(value>>8*i++);
		else
			*((volatile uint8_t *)((uint16_t) &PORTC)) = 0x00;
		DBG(*((volatile uint8_t *)((uint16_t) &PORTC)),HEX);
		sendData();
	  }
  }
#esle
  //set_pin_out();
  //value = (uint16_t)(value << 11)|(value&0x7E)|(value>>11);
  while(count--){
        for(uint8_t i = 0; i < _bus_w; i++){//将数据搬运到数据总线上
            uint8_t offset = (count)*_bus_w + i;
            if(offset < bits)
                value & (1 << offset) ? (SET_PIN_HIGH(_pinList[i])) : (SET_PIN_LOW(_pinList[i]));
            else
                SET_PIN_LOW(_pinList[i]);
        }
        sendData();//将wr拉低再拉高，将数据写入RAM
  }
#endif
}

void DFRobot_Parallel::set_pin_in(){
  if(_dir != 1){
      for(int i = 0; i < _bus_w; i++){
          SET_PIN_IN(i);
      }
      _dir = 1;
  }
}
void DFRobot_Parallel::set_pin_out(){
  if(_dir != 0){
      for(int i = 0; i < _bus_w; i++){
          SET_PIN_OUT(i);
      }
      _dir = 0;
  }
}

void DFRobot_Parallel::contrl_8080_w(){
  SET_PIN_LOW(_wr);
  SET_PIN_HIGH(_wr);
  SET_PIN_HIGH(_rd);
}
void DFRobot_Parallel::contrl_8080_r(){
  SET_PIN_LOW(_rd);
  SET_PIN_HIGH(_rd);
  SET_PIN_HIGH(_wr);
}
void DFRobot_Parallel::contrl_6800_w(){
  SET_PIN_LOW(_wr);
  SET_PIN_LOW(_rd);
  delay(1);
  SET_PIN_HIGH(_rd);
  delay(1);
  SET_PIN_LOW(_rd);
}
void DFRobot_Parallel::contrl_6800_r(){
  SET_PIN_HIGH(_wr);
  SET_PIN_HIGH(_rd);//en
  delay(1);
  SET_PIN_LOW(_rd);
}
void DFRobot_Parallel::sendData(){
  (_mode == PARAL_MODE_8080) ? contrl_8080_w() : contrl_6800_w();
}
void DFRobot_Parallel::transfer(uint8_t value){
#ifdef ARDUINO_AVR_MEGA2560
  if(_bus_w == PARAL_BUS_WIDTH16){
	  *((volatile uint8_t *)((uint16_t) &PORTC)) = 0x00;
  }
  *((volatile uint8_t *)((uint16_t) &PORTA)) = value;
  sendData();
#endif
}
void DFRobot_Parallel::transfer16(uint16_t value){
#ifdef ARDUINO_AVR_MEGA2560
  *((volatile uint8_t *)((uint16_t) &PORTC)) = 0x00;
  *((volatile uint8_t *)((uint16_t) &PORTA)) = 0x1F;
  sendData();
  if(_bus_w == PARAL_BUS_WIDTH16){
	  *((volatile uint8_t *)((uint16_t) &PORTC)) = value>>8;
  }else{
	  *((volatile uint8_t *)((uint16_t) &PORTA)) = value>>8;
	  sendData();
  }
    *((volatile uint8_t *)((uint16_t) &PORTA)) = value;
  sendData();
#endif
}

