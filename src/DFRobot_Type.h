#ifndef __DFROBOT_TYPE_H
#define __DFROBOT_TYPE_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "DFRobot_Parallel.h"
#ifdef ARDUINO_SAM_ZERO
#include "DFRobot_DMA.h"
#endif


#ifndef pgm_read_byte
 #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
 #define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
 #define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#endif

//connected type
#define COLOR_MODE_RGB444 0
#define COLOR_MODE_RGB565 1
#define COLOR_MODE_RGB666 2



#define DF_GDL_HW_IIC 3  //3代表硬件IIC的最大参数个数，即(rst pin)，(bl pin),addr
#define DF_GDL_SF_IIC 5  //5代表软件IIC的最大参数个数，即(rst),(bl),addr,scl,sda,
#define DF_GDL_HW_SPI 4  //4代表硬件SPI的最大参数个数，即(rst),(bl),dc,(cs)
#define DF_GDL_SW_SPI 7  //7代表硬件SPI的最大参数个数，即(rst),(bl),dc,(cs),sck,mosi,(miso)
#define DF_GDL_8080   6  //6代表16位8080并口
#define DF_GDL_6800   5  //5代表16位8080并口
#define DF_GDL_D8     8
#define DF_GDL_D16    16
#define DF_GDL_80_P16 22 //22代表16位8080并口最大参数个数，即(rst),(bl),dc,(cs),D0~D15,wr,rd
#define DF_GDL_68_P16 23 //23代表16位6800并口的最大参数个数+1，即(rst),(bl),dc,(cs),D0~D15,wr,en
#define DF_GDL_80_P8  (DF_GDL_8080+8) //14代表16位8080并口最大参数个数，即(rst),(bl),dc,(cs),D0~D7,wr,rd
#define DF_GDL_68_P8  (DF_GDL_6800+8) //13代表16位6800并口的最大参数个数，即(rst),(bl),dc,(cs),D0~D7,wr
#define DF_GDL_PARAL_6800 6
#define DF_GDL_PARAL_8080 6
//pin position
//reset pin
#define GDL_PIN_RST 0 //all
#define TOUCH_PIN_RST  0

//backlight pin
#define GDL_PIN_BL  1 //all
#define TOUCH_PIN_INT  1

//IIC addr / data or cmd instruction
#define GDL_PIN_ADDR 2 //IIC
#define GDL_PIN_DC 2
#define TOUCH_PIN_ADDR  2
#define TOUCH_PIN_DC   2
//chip select
#define GDL_PIN_CS 3 //spi 8080 6800
#define TOUCH_PIN_CS  3

//clock
#define GDL_PIN_SCL 3
#define GDL_PIN_SCK 4
#define TOUCH_PIN_SCL  3
#define TOUCH_PIN_SCK  4

#define GDL_PIN_WR  4
#define GDL_PIN_RD  5
#define GDL_PIN_EN  5


//data bus
#define TOUCH_PIN_SDA  4
#define TOUCH_PIN_MOSI  5
#define TOUCH_PIN_MISO  6
#define GDL_PIN_SDA 4
#define GDL_PIN_MOSI 5
#define GDL_PIN_MISO 6
#define GDL_PIN_D0 6
#define GDL_PIN_D1 7
#define GDL_PIN_D2 8
#define GDL_PIN_D3 9
#define GDL_PIN_D4 10
#define GDL_PIN_D5 11
#define GDL_PIN_D6 12
#define GDL_PIN_D7 13
#define GDL_PIN_D8 14
#define GDL_PIN_D9 15
#define GDL_PIN_D10 16
#define GDL_PIN_D11 17
#define GDL_PIN_D12 18
#define GDL_PIN_D13 19
#define GDL_PIN_D14 20
#define GDL_PIN_D15 21

//#define GDL_PIN_WR(type, n) (((type - n) == DF_GDL_8080)?(type - 2):(type - 1))
//#define GDL_PIN_RD(type) (type - 1)

#define GDL_PIN_NONE 255

typedef struct _sGdlDev sGdlDev_t;
typedef struct sGdlIF sGdlIF_t;

typedef uint8_t(*gdl_dev_interface_fp)(sGdlDev_t *gdl, uint8_t step, uint8_t *addr, uint16_t len);
typedef uint8_t(*devInterfaceFunctionPtr)(sGdlIF_t *gdl, uint8_t step, uint8_t *addr, uint16_t len);//FP->function pointer函数指针


typedef struct{
  uint8_t *addr;/**<记录屏的初始化数组*/
  gdl_dev_interface_fp talk;/**<记录屏的通信接口*/
}sGdl_dev_t;

typedef struct{
  uint8_t *addr;  //设备初始化数组或配置参数
  devInterfaceFunctionPtr talk;//设备通信方式
}sGdlIFDev_t;

typedef union{
  TwoWire *iic;
  SPIClass *spi;
  DFRobot_Parallel *paral;
#ifdef ARDUINO_SAM_ZERO
  DFRobot_DMA_SPI *dma;
#endif
}uProtocol_t;

struct sGdlIF{
  uint8_t interface;//通信接口，保存的是通信接口的引脚数，及pinList的长度
  uint8_t freq;//通信频率
  uProtocol_t pro;//通信协议：IIC，并口，SPI，DMA等等
  bool  isBegin;/*判断初始化是否成功*/
  uint8_t *pinList;//保存通信接口的引脚数据，它的长度由某种通信接口的最大引脚数决定
  uint16_t length;//通信的最大字节数，默认0xFFFF
  sGdlIFDev_t *dev;
}__attribute__ ((packed));

struct _sGdlDev{
  uint8_t interface;/**<存储屏的显示通信类型*/
  uint32_t freq;
  uProtocol_t pro; /**<存储IIC和SPI接口的类*/
  sGdl_dev_t *dev;/**<记录屏的初始化数组和通信接口*/
  uint8_t rotation;/**旋转角度 0：不旋转，1：旋转90°，2：旋转180°，3：旋转270°*/
  bool  isBegin;/*判断初始化是否成功*/
  uint8_t cMode;
  uint8_t *buffer;/**<屏的显示buf*/
  uint8_t *pinList;/**<保存通信接口的引脚数据，它的长度由某种通信接口的最大引脚数决定*/
} __attribute__ ((packed));

typedef struct{
  sGdlIF_t interface;//设备的通信接口
  union{
	  struct{
		  uint8_t cMode;
		  uint8_t *buffer;
	  }screen;
  }dev;
}sDev_t;

#define GDL_PB_DEV(name, init, interface) \
sGdl_dev_t name = {init, interface};


#endif