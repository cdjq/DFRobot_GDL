/*!
 * @file DFRobot_Type.h
 * @brief DFRobot_GDL类型定义文件
 * @n 访问ROM内存的方法
 * @n 不同主控操控通过寄存器操控IO口的方式
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Arya](xue.peng@dfrobot.com)
 * @version  V1.0
 * @date  2019-12-23
 * @https://github.com/DFRobot/DFRobot_GDL
 */
#ifndef __DFROBOT_TYPE_H
#define __DFROBOT_TYPE_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#ifndef ARDUINO_SAM_ZERO
#include "Interface/DFRobot_DMA.h"
#endif

/*访问flash内存方式*/
#ifndef pgm_read_byte
 #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
 #define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
 #define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#endif

/*无用引脚，空引脚*/
#define GDL_PIN_NC     255 
/*IO口操纵方式*/
#define SET_PIN_IN(pin)   if(pin != GDL_PIN_NC) pinMode(pin, INPUT)
#define SET_PIN_OUT(pin)  if(pin != GDL_PIN_NC) pinMode(pin, OUTPUT)
#define SET_PIN_HIGH(pin)  if(pin != GDL_PIN_NC) digitalWrite(pin, HIGH)
#define CLR_PIN_LOW(pin)  if(pin != GDL_PIN_NC) digitalWrite(pin, LOW)


#endif