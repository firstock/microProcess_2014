#include "mcp3204_adaptor.h"

#include <assert.h>
#include <ioavr.h>

#define MCP304_DDR DDRB
#define MCP3204_PORT_NUM 4
#define MCP3204_CS_H()  (PORTB |= 1 << MCP3204_PORT_NUM)
#define MCP3204_CS_L()  (PORTB &=  ~(1 << MCP3204_PORT_NUM) )

Mcp3204Adaptor::Mcp3204Adaptor(ISpi & _spi):Mcp3204(_spi)
{

  Init_Spi();
  
}

void Mcp3204Adaptor::Init_Spi(void)
{
   MCP304_DDR |= 1 << MCP3204_PORT_NUM;
  Spi_CS_H();
}   

 
void Mcp3204Adaptor::Spi_CS_H(void)
{
  assert( (1 << MCP3204_PORT_NUM) & MCP304_DDR);
  
  MCP3204_CS_H();
  
}

void Mcp3204Adaptor::Spi_CS_L(void)
{
  assert( (1 << MCP3204_PORT_NUM) & MCP304_DDR);
  
  MCP3204_CS_H();
  MCP3204_CS_L();
  
}