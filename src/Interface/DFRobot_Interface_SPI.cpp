#include "DFRobot_Interface.h"
#include "DFRobot_IF.h"

uint8_t gdl_com_hw_spi(sGdlDev_t *pGdl, uint8_t function, uint8_t *pBuf, uint32_t len){
  switch(function){
    case GDL_COM_INTERFACE_INIT:
          pGdl->pro.spi = &SPI;
          pGdl->pro.spi->begin();
          //if(pGdl->freq != 0)
             //pGdl->pro.spi->setFrequency(pGdl->freq);/*avr编译不过*/
          //Serial.println(pGdl->freq);
          pGdl->isBegin == true;
          break;
    case IF_COM_WRITE_COLOR:
    {
          GDL_CS_LOW(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
          do{
              uint32_t pixelNums = len;
			  uint32_t arg = 50000/(14*12);
              if(pixelNums > arg) pixelNums = arg;
			  len -= pixelNums;
			  #if defined(ESP8266)
              yield();
              #endif
			  while(pixelNums--){
				  for(uint8_t i = 0; i < 14;i++){
					  //pGdl->pro.spi->transfer(pBuf[i+1]);
					  pGdl->pro.spi->transfer(0xF8);
					  pGdl->pro.spi->transfer(0x00);
					  pGdl->pro.spi->transfer(0xF8);
					  pGdl->pro.spi->transfer(0x00);
					  pGdl->pro.spi->transfer(0xF8);
					  pGdl->pro.spi->transfer(0x00);
					  pGdl->pro.spi->transfer(0xF8);
					  pGdl->pro.spi->transfer(0x00);
					  pGdl->pro.spi->transfer(0xF8);
					  pGdl->pro.spi->transfer(0x00);
					  pGdl->pro.spi->transfer(0xF8);
					  pGdl->pro.spi->transfer(0x00);
				  }
			  }
          }while(len);
		  GDL_CS_HIGH(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
    }
          break;
    case GDL_COM_DISPLAY_INIT:
    {     GDL_CS_LOW(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
          uint8_t b = pgm_read_byte(pBuf);
          pGdl->pro.spi->transfer(b);
          GDL_CS_HIGH(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
    }
          break;
    case GDL_COM_WRITE_CMD:
          GDL_CS_LOW(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_LOW(pGdl->pinList[GDL_PIN_DC]);//dc 0:cmd
          for(uint16_t i = 0; i < len; i++){
              pGdl->pro.spi->transfer(pBuf[i]);
          }
          GDL_CS_HIGH(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
          break;
    case GDL_COM_WRITE_DATA:
          GDL_CS_LOW(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
          for(uint32_t i = 0; i < len; i++){
              pGdl->pro.spi->transfer(pBuf[i]);
          }
          GDL_CS_HIGH(pGdl->pinList[GDL_PIN_CS]);
           pGdl->pro.spi->endTransaction();
          break;
    default:
            break;
  }
                #if defined(ESP8266)
       
                      yield();
              #endif
}