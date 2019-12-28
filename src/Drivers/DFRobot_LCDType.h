#ifndef __DFROBOT_LCDTYPE_H
#define __DFROBOT_LCDTYPE_H
#include "DFRobot_Type.h"
#include "DFRobot_ST7735S.h"
#include "DFRobot_SSD1306.h"
#include "DFRobot_ILI9488.h"
#include "DFRobot_ST7789.h"

extern sGdlIFDev_t gdl_Dev_ST7789_R240x240_HW_SPI;
extern sGdlIFDev_t gdl_Dev_ST7789_R240x320_HW_SPI;
extern sGdlIFDev_t gdl_Dev_SSD1306_R128x32_HW_IIC;
extern sGdlIFDev_t gdl_Dev_ST7735S_R80x160_HW_SPI;
extern sGdlIFDev_t gdl_Dev_ILI9488_R480x320_HW_SPI;
#ifdef ARDUINO_SAM_ZERO
extern sGdlIFDev_t gdl_Dev_ST7789_R240x240_DMA_SPI;
extern sGdlIFDev_t gdl_Dev_ST7735S_R80x160_DMA_SPI;
#endif


/*
extern sGdl_dev_t gdl_dev_st7735s_80x160_hw_spi;
//extern sGdl_dev_t gdl_dev_st7735s_80x160_sw_spi;
extern sGdl_dev_t gdl_dev_ssd1306_128x32_hw_iic;
extern sGdl_dev_t gdl_dev_ssd1306_128x32_8080_p16;
extern sGdl_dev_t gdl_dev_ili9488_320x480_hw_spi;
extern sGdl_dev_t gdl_dev_st7789_240x240_hw_spi;
extern sGdl_dev_t gdl_dev_st7789_240x320_hw_spi;
#ifdef ARDUINO_SAM_ZERO
extern sGdl_dev_t gdl_dev_ili9488_320x480_dma_spi;
#endif
*/

#endif