#ifndef __DFROBOT_DISPLAY_SERIES_H
#define __DFROBOT_DISPLAY_SERIES_H
#include "Interface/DFRobot_Interface.h"

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


#endif