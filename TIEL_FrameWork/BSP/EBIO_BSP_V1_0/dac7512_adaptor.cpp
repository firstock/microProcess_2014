#include "dac7512_adaptor.h"

#include <assert.h>
#include <ioavr.h>

#define DAC7512_PORT_NUM 5
#define DAC7512_CS_H()  (PORTD |= 1 << DAC7512_PORT_NUM)
#define DAC7512_CS_L()  (PORTD &=  ~(1 << DAC7512_PORT_NUM) )

Dac7512Adaptor::Dac7512Adaptor(ISpi & _spi):Dac7512(_spi)
{

  Init_Spi();
  
}

void Dac7512Adaptor::Init_Spi(void)
{
   DDRD |= 1 << DAC7512_PORT_NUM;
  Spi_CS_H();
}   

 
void Dac7512Adaptor::Spi_CS_H(void)
{
  assert( (1 << DAC7512_PORT_NUM) & DDRD);
  
  DAC7512_CS_H();
  
}

void Dac7512Adaptor::Spi_CS_L(void)
{
  assert( (1 << DAC7512_PORT_NUM) & DDRD);
  
  DAC7512_CS_H();
  DAC7512_CS_L();
  
}