#ifndef __DFROBOT_3WIRESPI_H
#define __DFROBOT_3WIRESPI_H
#include "Arduino.h"

//PD0~7 map 0~7
#define SW_SPI_CS   3
#define SW_SPI_MOSI 4
#define SW_SPI_SCK  5
#define SW_SPI_MISO 6

#ifdef ARDUINO_AVR_UNO
#define MODE_REG (volatile uint8_t *)(uint16_t)&DDRD//位为0为输入，1为输出
#define OUTPUT_REG (volatile uint8_t *)(uint16_t)&PORTD//输出寄存器，方向（模式）寄存器为输出时有效
#define INPUT_REG (volatile uint8_t *)(uint16_t) &PIND
#define SPI_SDA_IN   *MODE_REG &= ~(1<<SW_SPI_MOSI)
#define SPI_SDA_OUT  *MODE_REG |= (1<<SW_SPI_MOSI)
#define SET_SPI_CS *OUTPUT_REG |= (1<<SW_SPI_CS)
#define CLR_SPI_CS *OUTPUT_REG &= ~(1<<SW_SPI_CS)
#define SET_SPI_SDA  *OUTPUT_REG |= (1<<SW_SPI_MOSI)
#define CLR_SPI_SDA  *OUTPUT_REG &= ~(1<<SW_SPI_MOSI)
#define SET_SPI_SCK  *OUTPUT_REG |= _BV(SW_SPI_SCK)
#define CLR_SPI_SCK  *OUTPUT_REG &= ~_BV(SW_SPI_SCK)

#define SPI_3WIRE//3线SPI CS SCK SDA
#ifdef SPI_3WIRE
#define READ_SPI_SDA  *INPUT_REG & (1<<SW_SPI_MOSI)
#else
#define READ_SPI_SDA  *INPUT_REG & (1<<SW_SPI_MISO)
#endif

#else
#define MODE_REG
#define OUTPUT_REG
#define SPI_SDA_IN
#define SPI_SDA_OUT
#define READ_SPI_SDA
#define CLR_SPI_SDA
#define SET_SPI_SDA
#define SET_SPI_CS
#define CLR_SPI_CS
#define SET_SPI_SCK
#define CLR_SPI_SCK
#endif


class SoftwareSPI{
public:
  SoftwareSPI();
  void begin();
  void spiSendByte(uint8_t value);
  uint8_t spiReadByte();
};
extern SoftwareSPI sw3WireSPI;

#endif