#include "DFRobot_3WireSPI.h"
SoftwareSPI::SoftwareSPI(){
  
}
void SoftwareSPI::begin(){
  pinMode(SW_SPI_CS,OUTPUT);
  pinMode(SW_SPI_MOSI,OUTPUT);
  pinMode(SW_SPI_SCK,OUTPUT);
  pinMode(SW_SPI_MISO,INPUT);
}
void SoftwareSPI::spiSendByte(uint8_t val){
#ifdef SPI_3WIRE
SPI_SDA_OUT;
#endif
  for(uint8_t count = 0; count < 8; count++){
      CLR_SPI_SCK;
      if(val & 0x80)
          SET_SPI_SDA;
      else
          CLR_SPI_SDA;
      SET_SPI_SCK;
      val <<= 1;
  }
  CLR_SPI_SCK;
  CLR_SPI_SDA;
}
uint8_t SoftwareSPI::spiReadByte(){
#ifdef SPI_3WIRE
SPI_SDA_IN;
#endif
  uint8_t val = 0;
  for(uint8_t count = 0; count < 8; count++){
      val <<= 1;
      CLR_SPI_SCK;
#if defined(__AVR__)
      _NOP();
      _NOP();
#else
      delayMicroseconds(10);
#endif
      bool(READ_SPI_SDA) ? val |= 1 : val &= 0xFE;
      SET_SPI_SCK;
  }
  CLR_SPI_SCK;
  return val;
}
SoftwareSPI sw3WireSPI;