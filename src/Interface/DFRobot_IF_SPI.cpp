#include "DFRobot_IF.h"
#include <DFRobot_Type.h>

#if defined(__AVR__)
#define AVR_SPI_WRITE(d) for(SPDR = d; (!(SPSR & _BV(SPIF))); )
#endif

uint8_t interfaceComHardwareSPI(sGdlIF_t *p, uint8_t cmd, uint8_t *pBuf, uint32_t len){
  if((p == NULL))
      return 0;
  if(p->isBegin){
      #if defined(SPI_HAS_TRANSACTION)
      p->pro.spi->beginTransaction(SPISettings(p->freq, MSBFIRST, SPI_MODE0));
      #if defined(ARDUINO_SAM_ZERO)
       if(p->freq > 12000000)
      {
          sercom4.disableSPI();
          while(SERCOM4->SPI.SYNCBUSY.bit.ENABLE);
          SERCOM4->SPI.BAUD.reg = 0; 
          sercom4.enableSPI();
      }
      #endif
      #else // No transactions, configure SPI manually...
      #if defined(__AVR__)
             p->pro.spi->setClockDivider(SPI_CLOCK_DIV2);
      #elif defined(ESP8266) || defined(ESP32)
             p->pro.spi->setFrequency(p->freq);
      #endif
             p->pro.spi->setBitOrder(MSBFIRST);
             p->pro.spi->setDataMode(SPI_MODE0);
      #endif 
  }
  switch(cmd){
      case IF_COM_PROTOCOL_INIT:
      {
           //Serial.println("IF_COM_PROTOCOL_INIT");
           //Serial.println(p->isBegin);
           p->pro.spi = &SPI;
           p->pro.spi->begin();
           if(p->freq == 0) {
             p->freq = DEFAULT_SPI_FREQ;
           }else{
               #if defined(SPI_HAS_TRANSACTION)
               #if defined(ARDUINO_SAM_ZERO)
               if(p->freq > 12000000)
               {
                   sercom4.disableSPI();
                   while(SERCOM4->SPI.SYNCBUSY.bit.ENABLE);
                   SERCOM4->SPI.BAUD.reg = 0; 
                   sercom4.enableSPI();
               }else{
                   p->pro.spi->beginTransaction(SPISettings(p->freq, MSBFIRST, SPI_MODE0));
               }
               #else
                    p->pro.spi->beginTransaction(SPISettings(p->freq, MSBFIRST, SPI_MODE0));
               #endif
               #else
               #if defined(__AVR__)
                      p->pro.spi->setClockDivider(SPI_CLOCK_DIV2);
               #elif defined(ESP8266) || defined(ESP32)
                      p->pro.spi->setFrequency(p->freq);
               #endif
                      p->pro.spi->setBitOrder(MSBFIRST);
                      p->pro.spi->setDataMode(SPI_MODE0);
               #endif 
           }
           p->isBegin = true;
           //SerialUSB.println(p->freq);
      }
           break;
      case IF_COM_SET_FREQUENCY:
      {
           //Serial.println("IF_COM_SET_FREQUENCY");
           if(!p->freq) return 0;
           #if defined(SPI_HAS_TRANSACTION)
           #if defined(ARDUINO_SAM_ZERO)
            if(p->freq > 12000000)
           {
               sercom4.disableSPI();
               while(SERCOM4->SPI.SYNCBUSY.bit.ENABLE);
               SERCOM4->SPI.BAUD.reg = 0; 
               sercom4.enableSPI();
           }else{
               p->pro.spi->beginTransaction(SPISettings(p->freq, MSBFIRST, SPI_MODE0));
           }
           #else
                p->pro.spi->beginTransaction(SPISettings(p->freq, MSBFIRST, SPI_MODE0));
           #endif
           #else // No transactions, configure SPI manually...
           #if defined(__AVR__)
                  p->pro.spi->setClockDivider(SPI_CLOCK_DIV2);
           #elif defined(ESP8266) || defined(ESP32)
                  p->pro.spi->setFrequency(p->freq);
           #endif
                  p->pro.spi->setBitOrder(MSBFIRST);
                  p->pro.spi->setDataMode(SPI_MODE0);
           #endif 
      }
           break;
      case IF_COM_WRITE_CMD:
      {
           if(!(p->isBegin)) return 0;
           CLR_PIN_LOW(p->pinList[IF_PIN_CS]);
           if(p->dev->devType == DEV_TYPE_SCREEN)
               CLR_PIN_LOW(p->pinList[IF_PIN_DC]);
           for(uint32_t i = 0; i < len; i++){
               #if defined(ESP8266)
               if(i%100000 == 0) yield();
               #endif
               p->pro.spi->transfer(pBuf[i]);
           }
           SET_PIN_HIGH(p->pinList[IF_PIN_CS]); 
           if(p->dev->devType == DEV_TYPE_SCREEN)
               SET_PIN_HIGH(p->pinList[IF_PIN_DC]);
      }
           break;
      case IF_COM_READ_DATA:
      {
           //Serial.println("IF_COM_READ_DATA");
           if(!(p->isBegin)) return 0;
           CLR_PIN_LOW(p->pinList[IF_PIN_CS]);
           for(uint8_t i = 0; i < pBuf[0]; i++){
               p->pro.spi->transfer(pBuf[i+1]);
           }
           for(uint32_t i = 0; i < len; i++){
               #if defined(ESP8266)
               if(i%100000 == 0) yield();
               #endif
               pBuf[i] = p->pro.spi->transfer(0x00);
           }
           SET_PIN_HIGH(p->pinList[IF_PIN_CS]); 
           if(p->dev->devType == DEV_TYPE_SCREEN)
               SET_PIN_HIGH(p->pinList[IF_PIN_DC]);
      }
           break;
      case IF_COM_WRITE_FLASH_FIXED:   //只能一次处理4个字节
      {
           //Serial.println("IF_COM_WRITE_FLASH_FIXED");
           uint8_t num = pgm_read_byte(&pBuf[0]);
           if(!(p->isBegin) || num > 4) return 0;
           CLR_PIN_LOW(p->pinList[IF_PIN_CS]);
           uint8_t *addr = pBuf + 1;
           uint8_t buf[num];
           do{
               uint32_t datBytes = len;
               uint32_t args = 100000/num;
               if(datBytes > args) datBytes = args;
               #if defined(ESP8266)
               yield();
               #endif
               len -= datBytes;
               while(datBytes--){
                   switch(num){
                       case 1: 
                               #if defined(__AVR__)
                               AVR_SPI_WRITE(pgm_read_byte(&pBuf[1]));
                               #else
                               p->pro.spi->transfer(pgm_read_byte(&pBuf[1]));
                               #endif
                               break;
                       case 2: 
                               #if defined(__AVR__)
                               AVR_SPI_WRITE(pgm_read_byte(&pBuf[1]));
                               AVR_SPI_WRITE(pgm_read_byte(&pBuf[2]));
                               #else
                               p->pro.spi->transfer(pgm_read_byte(&pBuf[1]));
                               p->pro.spi->transfer(pgm_read_byte(&pBuf[2]));
                               #endif
                               break;
                       case 3: 
                               #if defined(__AVR__)
                               AVR_SPI_WRITE(pgm_read_byte(&pBuf[1]));
                               AVR_SPI_WRITE(pgm_read_byte(&pBuf[2]));
                               AVR_SPI_WRITE(pgm_read_byte(&pBuf[3]));
                               #else
                               p->pro.spi->transfer(pgm_read_byte(&pBuf[1]));
                               p->pro.spi->transfer(pgm_read_byte(&pBuf[2]));
                               p->pro.spi->transfer(pgm_read_byte(&pBuf[3]));
                               break;
                               #endif
                       case 4: 
                               #if defined(__AVR__)
                               AVR_SPI_WRITE(pgm_read_byte(&pBuf[1]));
                               AVR_SPI_WRITE(pgm_read_byte(&pBuf[2]));
                               AVR_SPI_WRITE(pgm_read_byte(&pBuf[3]));
                               AVR_SPI_WRITE(pgm_read_byte(&pBuf[4]));
                               #else
                               p->pro.spi->transfer(pgm_read_byte(&pBuf[1]));
                               p->pro.spi->transfer(pgm_read_byte(&pBuf[2]));
                               p->pro.spi->transfer(pgm_read_byte(&pBuf[3]));
                               p->pro.spi->transfer(pgm_read_byte(&pBuf[4]));
                               #endif
                               break;
                       default:
                              break;
                   }
               }
           }while(len);
           SET_PIN_HIGH(p->pinList[IF_PIN_CS]); 
           if(p->dev->devType == DEV_TYPE_SCREEN)
               SET_PIN_HIGH(p->pinList[IF_PIN_DC]);
      }
           break;
      case IF_COM_WRITE_FLASH_INC:
      {
           if(!(p->isBegin)) return 0;
           
           //Serial.println("IF_COM_WRITE_FLASH_INC");
           CLR_PIN_LOW(p->pinList[IF_PIN_CS]);
           do{
               uint32_t datBytes = len;
               #if defined(ESP8266)
               if(datBytes > 100000) datBytes = 100000;
               yield();
               #endif
               len -= datBytes;
               while(datBytes--){
                   #if defined(__AVR__)
                   AVR_SPI_WRITE(pgm_read_byte(pBuf));
                   #else
                   p->pro.spi->transfer(pgm_read_byte(pBuf));
                   #endif
                   pBuf++;
               }
           }while(len);
           SET_PIN_HIGH(p->pinList[IF_PIN_CS]); 
           if(p->dev->devType == DEV_TYPE_SCREEN)
               SET_PIN_HIGH(p->pinList[IF_PIN_DC]);
      }
           break;
      case IF_COM_WRITE_RAM_FIXED:
      {
           //Serial.println("IF_COM_WRITE_RAM_FIXED");
           if(!(p->isBegin)) return 0;
           CLR_PIN_LOW(p->pinList[IF_PIN_CS]);
           #if defined(ESP32) // ESP32 has a special SPI pixel-writing function
           while(len--){
               p->pro.spi->writePixels(pBuf+1, pBuf[0]);
           }
           #else  // !ESP32
           do{
               uint32_t datBytes = len;
               uint32_t args = 100000/pBuf[0];
               if(datBytes > args) datBytes = args;
               #if defined(ESP8266)
               yield();
               #endif
               len -= datBytes;
               while(datBytes--){
                   switch(pBuf[0]){
                       case 1:
                               #if defined(__AVR__)
                               AVR_SPI_WRITE(pBuf[1]);
                               #else
                                p->pro.spi->transfer(pBuf[1]);
                               #endif
                               break;
                       case 2: 
                               #if defined(__AVR__)
                               AVR_SPI_WRITE(pBuf[1]);
                               AVR_SPI_WRITE(pBuf[2]);
                               #else
                               p->pro.spi->transfer(pBuf[1]);
                               p->pro.spi->transfer(pBuf[2]);
                               #endif
                               break;
                       case 3: 
                               #if defined(__AVR__)
                               AVR_SPI_WRITE(pBuf[1]);
                               AVR_SPI_WRITE(pBuf[2]);
                               AVR_SPI_WRITE(pBuf[3]);
                               #else
                               p->pro.spi->transfer(pBuf[1]);
                               p->pro.spi->transfer(pBuf[2]);
                               p->pro.spi->transfer(pBuf[3]);
                               #endif
                               break;
                       case 4: 
                               #if defined(__AVR__)
                               AVR_SPI_WRITE(pBuf[1]);
                               AVR_SPI_WRITE(pBuf[2]);
                               AVR_SPI_WRITE(pBuf[3]);
                               AVR_SPI_WRITE(pBuf[4]);
                               #else
                               p->pro.spi->transfer(pBuf[1]);
                               p->pro.spi->transfer(pBuf[2]);
                               p->pro.spi->transfer(pBuf[3]);
                               p->pro.spi->transfer(pBuf[4]);
                               #endif
                               break;
                       default:
                              for(uint8_t i = 0; i < pBuf[0];i++){
                                  #if defined(__AVR__)
                                  AVR_SPI_WRITE(pBuf[1+i]);
                                  #else
                                  p->pro.spi->transfer(pBuf[1]);
                                  #endif
                              }
                              break;
                   }
               }
           }while(len);
#endif
           SET_PIN_HIGH(p->pinList[IF_PIN_CS]); 
           if(p->dev->devType == DEV_TYPE_SCREEN)
               SET_PIN_HIGH(p->pinList[IF_PIN_DC]);
      }
           break;
      case IF_COM_WRITE_RAM_INC:
      {
           //Serial.println("IF_COM_WRITE_RAM_INC");
           if(!(p->isBegin)) return 0;
           CLR_PIN_LOW(p->pinList[IF_PIN_CS]);
           do{
               uint32_t datBytes = len;
               #if defined(ESP8266)
               if(datBytes > 100000) datBytes = 100000;
               yield();
               #endif
               len -= datBytes;
               while(datBytes--){
                   #if defined(__AVR__)
                   AVR_SPI_WRITE(*pBuf);
                   #else
                   p->pro.spi->transfer(*pBuf);
                   #endif
                   pBuf++;
               }
           }while(len);
           SET_PIN_HIGH(p->pinList[IF_PIN_CS]); 
           if(p->dev->devType == DEV_TYPE_SCREEN)
               SET_PIN_HIGH(p->pinList[IF_PIN_DC]);
      }
           break;
      default:
            break;
  }
#if defined(ESP8266)
  yield();
#endif
  
  return 1;
}