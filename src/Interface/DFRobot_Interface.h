#ifndef __DFROBOT_INTERFACE_H
#define __DFROBOT_INTERFACE_H
#include <DFRobot_TypeDefine.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "DFRobot_Parallel.h"
#ifndef ARDUINO_SAM_ZERO
#include "DFRobot_DMA.h"
#endif



#define GDL_PIN_OUT(pin) if(pin != GDL_PIN_NONE){pinMode(pin, OUTPUT);}
#define GDL_PIN_IN(pin) if(pin != GDL_PIN_NONE){pinMode(pin, INPUT);}

#define GDL_CS_LOW(pin) if(pin != GDL_PIN_NONE){digitalWrite(pin, LOW);}
#define GDL_CS_HIGH(pin) if(pin != GDL_PIN_NONE){digitalWrite(pin, HIGH);}

#define GDL_DC_LOW(pin) if(pin != GDL_PIN_NONE){digitalWrite(pin, LOW);}
#define GDL_DC_HIGH(pin) if(pin != GDL_PIN_NONE){digitalWrite(pin, HIGH);}

#define GDL_RST_LOW(pin) if(pin != GDL_PIN_NONE){digitalWrite(pin, LOW);}
#define GDL_RST_HIGH(pin) if(pin != GDL_PIN_NONE){digitalWrite(pin, HIGH);}

#define GDL_BL_LOW(pin) if(pin != GDL_PIN_NONE){digitalWrite(pin, LOW);}
#define GDL_BL_HIGH(pin) if(pin != GDL_PIN_NONE){digitalWrite(pin, HIGH);}

#define GDL_INT_LOW(pin) if(pin != GDL_PIN_NONE){digitalWrite(pin, LOW);}
#define GDL_INT_HIGH(pin) if(pin != GDL_PIN_NONE){digitalWrite(pin, HIGH);}

#ifndef pgm_read_byte
 #define pgm_read_byte(addr)  (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
 #define pgm_read_word(addr)  (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
 #define pgm_read_dword(addr)  (*(const unsigned long *)(addr))
#endif

#define GDL_COM_INTERFACE_INIT 0
#define GDL_COM_WRITE_CMD 1
#define GDL_COM_WRITE_DATA 2
#define GDL_COM_READ_DATA 3
#define GDL_COM_WRITE_REG16 4
#define GDL_COM_READ_REG16 5
#define GDL_COM_DISPLAY_INIT 6
#define GDL_COM_WRITE_BUFFER 7
#define GDL_COM_READ_BUFFER 8

uint8_t gdl_com_hw_spi(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint16_t len);
uint8_t gdl_com_hw_iic(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint16_t len);
uint8_t gdl_com_hw_iic(sGdlIF_t *pGdl, uint8_t function, uint8_t *addr, uint16_t len);
//extern uint8_t gdl_com_sw_spi(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint16_t len);
//extern uint8_t gdl_com_hw_iic(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint16_t len);
//extern uint8_t gdl_com_sw_iic(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint16_t len);
//extern uint8_t gdl_com_6800_p16(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint16_t len);
uint8_t gdl_com_8080_p16(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint16_t len);
#ifdef ARDUINO_SAM_ZERO
uint8_t gdl_com_dma_spi(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint16_t len);
#define GDL_COM_DMA_SPI gdl_com_dma_spi
#endif

#define GDL_COM_HW_SPI gdl_com_hw_spi
#define GDL_COM_HW_IIC gdl_com_hw_iic
#define GDL_COM_8080_P16 gdl_com_8080_p16

#endif