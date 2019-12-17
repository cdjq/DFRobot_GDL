#include "DFRobot_Interface.h"

uint8_t gdl_com_hw_spi(sGdlDev_t *pGdl, uint8_t function, uint8_t *pBuf, uint16_t len){
  switch(function){
    case GDL_COM_INTERFACE_INIT:
          pGdl->pro.spi = &SPI;
		  pGdl->pro.spi->begin();
          if(pGdl->freq != 0)
             //pGdl->pro.spi->setFrequency(pGdl->freq);/*avr编译不过*/
		  //Serial.println(pGdl->freq);
          pGdl->isBegin == true;
          break;
	case GDL_COM_DISPLAY_INIT:
	{     GDL_CS_LOW(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
		  uint8_t b = pgm_read_byte(pBuf);
		  //Serial.print("b = ");Serial.println(b,HEX);
		  pGdl->pro.spi->transfer(b);
		  GDL_CS_HIGH(pGdl->pinList[GDL_PIN_CS]);
	      GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
	}
	      break;
    case GDL_COM_WRITE_CMD:
          GDL_CS_LOW(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_LOW(pGdl->pinList[GDL_PIN_DC]);//dc 0:cmd
		  //delay(1);
          for(uint16_t i = 0; i < len; i++){
              pGdl->pro.spi->transfer(pBuf[i]);
          }
          GDL_CS_HIGH(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
		  //delay(1);
          break;
    case GDL_COM_WRITE_DATA:
	     // delay(1);
          GDL_CS_LOW(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
		  //delay(1);
          for(uint16_t i = 0; i < len; i++){
              pGdl->pro.spi->transfer(pBuf[i]);
          }
          GDL_CS_HIGH(pGdl->pinList[GDL_PIN_CS]);
          break;
    default:
            break;
  }
}