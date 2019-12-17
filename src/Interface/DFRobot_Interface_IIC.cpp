#include "DFRobot_Interface.h"
#ifndef I2C_BUFFER_LENGTH//ESP32(fireBeetle系列定义了I2C_BUFFER_LENGTH)
#ifdef ARDUINO_ARCH_AVR  //AVR系列单片机一次最多传32字节数据
#define I2C_BUFFER_LENGTH  32
#endif
#endif

/*寄存器的底层处理数据不超过I2C_BUFFER_LENGTH*/
uint8_t gdl_com_hw_iic(sGdlDev_t *pGdl, uint8_t function, uint8_t *pBuf, uint16_t len){
  switch(function){
    case GDL_COM_INTERFACE_INIT:
          pGdl->pro.iic = &Wire;
          pGdl->pro.iic->begin();
          if(pGdl->freq != 0)
              pGdl->pro.iic->setClock(pGdl->freq);
          //Serial.println(pGdl->freq);
          pGdl->isBegin == true;
          break;
    case GDL_COM_WRITE_CMD:
          pGdl->pro.iic->beginTransmission(pGdl->pinList[GDL_PIN_ADDR]);
          for(uint16_t i = 0; i < len; i++){
              pGdl->pro.iic->write(0x00);
              pGdl->pro.iic->write(pBuf[i]);
          }
          pGdl->pro.iic->endTransmission();
          break;
    case GDL_COM_WRITE_DATA:
    {     
          while(len){
              pGdl->pro.iic->beginTransmission(pGdl->pinList[GDL_PIN_ADDR]);
              uint16_t n = 0;
              (len > 16)?n = 16:n=len;
              len -= n;
              pGdl->pro.iic->write(0x40);
              for(uint16_t i = 0; i < n; i++){
                  
                  pGdl->pro.iic->write(pBuf[i]);
                  //Serial.print("j = ");Serial.println(i);
                  //Serial.print("buf = ");Serial.println(pBuf[i]);
              }
              pBuf += n;
              pGdl->pro.iic->endTransmission();
          }
    }
          break;
    case GDL_COM_WRITE_REG16:
    {
          pGdl->pro.iic->beginTransmission(pGdl->pinList[GDL_PIN_ADDR]);
          uint8_t regLen = pBuf[0];/*pBuf[0]装的是寄存器的字节数*/
          uint8_t *reg = &pBuf[1];
          pGdl->pro.iic->write(reg,regLen);
          for(uint16_t i = 0; i < len - regLen - 1; i++){
              pGdl->pro.iic->write(pBuf[i]);
          }
          pGdl->pro.iic->endTransmission();
    }
          break;
          
    case GDL_COM_READ_REG16:
    {
          pGdl->pro.iic->beginTransmission(pGdl->pinList[GDL_PIN_ADDR]);
          uint8_t regLen = pBuf[0];/*pBuf[0]装的是寄存器的字节数*/
          uint8_t *reg = pBuf + 1;
          pGdl->pro.iic->write(reg,regLen);
          if( pGdl->pro.iic->endTransmission() != 0){
                return 0;
          }
          pGdl->pro.iic->requestFrom(pGdl->pinList[GDL_PIN_ADDR], (len - regLen - 1));
          for(uint16_t i = 0; i < len - regLen - 1; i++){
              pBuf[i] = pGdl->pro.iic->read();
          }
    }
          break;
    default:
            break;
  }
}
uint8_t gdl_com_hw_iic(sGdlIF_t *pGdl, uint8_t function, uint8_t *pBuf, uint16_t len){
  switch(function){
    case GDL_COM_INTERFACE_INIT:
          pGdl->pro.iic = &Wire;
          pGdl->pro.iic->begin();
          if(pGdl->freq != 0)
              pGdl->pro.iic->setClock(pGdl->freq);
          //Serial.println(pGdl->freq);
          pGdl->isBegin == true;
          break;
    case GDL_COM_WRITE_CMD:
          pGdl->pro.iic->beginTransmission(pGdl->pinList[GDL_PIN_ADDR]);
          for(uint16_t i = 0; i < len; i++){
              pGdl->pro.iic->write(0x00);
              pGdl->pro.iic->write(pBuf[i]);
          }
          pGdl->pro.iic->endTransmission();
          break;
    case GDL_COM_WRITE_DATA:
    {     
          while(len){
              pGdl->pro.iic->beginTransmission(pGdl->pinList[GDL_PIN_ADDR]);
              uint16_t n = 0;
              (len > 16)?n = 16:n=len;
              len -= n;
              pGdl->pro.iic->write(0x40);
              for(uint16_t i = 0; i < n; i++){
                  
                  pGdl->pro.iic->write(pBuf[i]);
                  //Serial.print("j = ");Serial.println(i);
                  //Serial.print("buf = ");Serial.println(pBuf[i]);
              }
              pBuf += n;
              pGdl->pro.iic->endTransmission();
          }
    }
          break;
    case GDL_COM_WRITE_REG16:
    {
          pGdl->pro.iic->beginTransmission(pGdl->pinList[GDL_PIN_ADDR]);
          uint8_t regLen = pBuf[0];/*pBuf[0]装的是寄存器的字节数*/
          uint8_t *reg = &pBuf[1];
          pGdl->pro.iic->write(reg,regLen);
          for(uint16_t i = 0; i < len - regLen - 1; i++){
              pGdl->pro.iic->write(pBuf[i]);
          }
          pGdl->pro.iic->endTransmission();
    }
          break;
          
    case GDL_COM_READ_REG16:
    {
          pGdl->pro.iic->beginTransmission(pGdl->pinList[GDL_PIN_ADDR]);
          uint8_t regLen = pBuf[0];/*pBuf[0]装的是寄存器的字节数*/
          uint8_t *reg = pBuf + 1;
          pGdl->pro.iic->write(reg,regLen);
          if( pGdl->pro.iic->endTransmission() != 0){
                return 0;
          }
          pGdl->pro.iic->requestFrom(pGdl->pinList[GDL_PIN_ADDR], (len - regLen - 1));
          for(uint16_t i = 0; i < len - regLen - 1; i++){
              pBuf[i] = pGdl->pro.iic->read();
          }
    }
          break;
    case GDL_COM_WRITE_BUFFER:/*第一个字节为寄存器的字节数*/
          pGdl->pro.iic->beginTransmission(pGdl->pinList[GDL_PIN_ADDR]);
          pGdl->pro.iic->write((const uint8_t *)(pBuf+1),(size_t)pBuf[0]);
          if(len > I2C_BUFFER_LENGTH)
              return 0;
          pGdl->pro.iic->write(&pBuf[(1+pBuf[0])],len);
		  // Serial.println(pBuf[0],HEX);
		  // Serial.println(pBuf[1],HEX);
		  // Serial.println(pBuf[2],HEX);
		  // Serial.println(pBuf[(1+pBuf[0])],HEX);
          if( pGdl->pro.iic->endTransmission() != 0){
                return 0;
          }
          break;
    case GDL_COM_READ_BUFFER:
          pGdl->pro.iic->beginTransmission(pGdl->pinList[GDL_PIN_ADDR]);
          pGdl->pro.iic->write((const uint8_t *)(pBuf+1),(size_t)pBuf[0]);
          if( pGdl->pro.iic->endTransmission() != 0){
                return 0;
          }
		  pGdl->pro.iic->requestFrom(pGdl->pinList[GDL_PIN_ADDR], len);
          for(uint16_t i = 0; i < len; i++){
              pBuf[i] = pGdl->pro.iic->read();
			  //Serial.print("pbuf[i] = ");Serial.println(pBuf[i],HEX);
          }
          break;
    default:
            break;
  }
  return 1;
}
/*寄存器有8位寄存器和16位寄存器之分
pBuf[0]:

  len的长度代表 写入或读取的数据的长度
*/