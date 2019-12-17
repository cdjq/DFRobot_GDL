#include "DFRobot_Interface.h"

uint8_t gdl_com_8080_p16(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint16_t len){
  switch(function){
    case GDL_COM_INTERFACE_INIT:
          pGdl->pro.paral =&PARAL;
		  pGdl->pro.paral->config(pGdl->pinList[GDL_PIN_WR], pGdl->pinList[GDL_PIN_RD]);
		  pGdl->pro.paral->setPins((pGdl->pinList + GDL_PIN_D0), 16);
		  pGdl->pro.paral->begin();
          pGdl->isBegin == true;
          break;
	case GDL_COM_DISPLAY_INIT:
	{     GDL_CS_LOW(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
		  uint8_t b = pgm_read_byte(addr);
		  //Serial.print("b = ");Serial.println(b,HEX);
		  pGdl->pro.paral->write(b);
		  GDL_CS_HIGH(pGdl->pinList[GDL_PIN_CS]);
	      GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
	}
	      break;
    case GDL_COM_WRITE_CMD:
          GDL_CS_LOW(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_LOW(pGdl->pinList[GDL_PIN_DC]);//dc 0:cmd
		  //Serial.print("cmd = ");Serial.println(addr[0],HEX);
          pGdl->pro.paral->write(addr, (uint8_t)len);
          GDL_CS_HIGH(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
          break;
    case GDL_COM_WRITE_DATA:
          GDL_CS_LOW(pGdl->pinList[GDL_PIN_CS]);
          GDL_DC_HIGH(pGdl->pinList[GDL_PIN_DC]);
		  //Serial.print("data1 = ");Serial.println(addr[0],HEX);
		  //Serial.print("data2 = ");Serial.println(addr[1],HEX);
          pGdl->pro.paral->write(addr, (uint8_t)len);
          GDL_CS_HIGH(pGdl->pinList[GDL_PIN_CS]);
          break;
    default:
            break;
  }
  return 0;
}