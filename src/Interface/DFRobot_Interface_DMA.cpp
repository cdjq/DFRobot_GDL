#include "DFRobot_Interface.h"
#ifdef ARDUINO_SAM_ZERO
#define DF_DMA_SPI_TX_REG 0x42001828

uint8_t gdl_com_dma_spi(sGdlDev_t *pGdl, uint8_t function, uint8_t *pBuf, uint16_t len){
  switch(function){
    case GDL_COM_INTERFACE_INIT:
          pGdl->pro.dma = &DMASPI;
		  pGdl->pro.dma->begin();
          break;
	case GDL_COM_DISPLAY_INIT:
	{     GDL_CS_LOW(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
		  uint8_t b = pgm_read_byte(pBuf);
		  pGdl->pro.dma->transfer(&b, 1);
		  GDL_CS_HIGH(pGdl->pinList[GDL_PIN_CS]);
	      GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
	}
	      break;
    case GDL_COM_WRITE_CMD:
          GDL_CS_LOW(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_LOW(pGdl->pinList[GDL_PIN_DC]);//dc 0:cmd
          pGdl->pro.dma->transfer(pBuf, len);
          GDL_CS_HIGH(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
          break;
    case GDL_COM_WRITE_DATA:
          GDL_CS_LOW(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
          pGdl->pro.dma->transfer(pBuf, len);
          GDL_CS_HIGH(pGdl->pinList[GDL_PIN_CS]);
          break;
    default:
            break;
  }
}

#endif