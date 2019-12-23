#ifndef __DFROBOT_INTERFACE_H
#define __DFROBOT_INTERFACE_H
#include <DFRobot_Type.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "DFRobot_Parallel.h"
#ifndef ARDUINO_SAM_ZERO
#include "DFRobot_DMA.h"
#endif

#define IF_PIN_NC     255

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

#define SET_PIN_IN(pin)   if(pin != IF_PIN_NC) pinMode(pin, INPUT)
#define SET_PIN_OUT(pin)  if(pin != IF_PIN_NC) pinMode(pin, OUTPUT)
#define SET_PIN_HIGH(pin)  if(pin != IF_PIN_NC) digitalWrite(pin, HIGH)
#define CLR_PIN_LOW(pin)  if(pin != IF_PIN_NC) digitalWrite(pin, LOW)

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
#define IF_COM_WRITE_COLOR 9 
 /*
    IF_COM_WRITE_COLOR: 第一个字节代表一个像素点用几个字节表示,紧接着的是像素点数据
*/

uint8_t gdl_com_hw_spi(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint32_t len);
uint8_t gdl_com_hw_iic(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint32_t len);
uint8_t gdl_com_hw_iic(sGdlIF_t *pGdl, uint8_t function, uint8_t *addr, uint32_t len);
//extern uint8_t gdl_com_sw_spi(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint16_t len);
//extern uint8_t gdl_com_hw_iic(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint16_t len);
//extern uint8_t gdl_com_sw_iic(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint16_t len);
//extern uint8_t gdl_com_6800_p16(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint16_t len);
uint8_t gdl_com_8080_p16(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint32_t len);
#ifdef ARDUINO_SAM_ZERO
uint8_t gdl_com_dma_spi(sGdlDev_t *pGdl, uint8_t function, uint8_t *addr, uint32_t len);
#define GDL_COM_DMA_SPI gdl_com_dma_spi
#endif

#define GDL_COM_HW_SPI gdl_com_hw_spi
#define GDL_COM_HW_IIC gdl_com_hw_iic
#define GDL_COM_8080_P16 gdl_com_8080_p16

#endif