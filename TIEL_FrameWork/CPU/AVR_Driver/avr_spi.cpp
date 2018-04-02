#include "avr_spi.h"
#include <ioavr.h>
#include <assert.h>

#define PORT_SS_NUM 4
#define PORT_MOSI_NUM 5
#define PORT_MISO_NUM 6
#define PORT_SCK_NUM  7
#define SPI_DDR       DDRB 

// bit number of SPI control register
#define SPI_SPE       6
#define SPI_MSTR      4
#define SPI_SPR0      0
#define SPI_SPI2X     0
#define SPI_SPIF      7

AvrSpi::AvrSpi(void)
{
  Init();
}

void AvrSpi::AvrSpi::Init(void)
{

  SPI_DDR |= (1 << PORT_MOSI_NUM) | (1 << PORT_SCK_NUM) | ( 1 << PORT_SS_NUM);

  SPCR = (1 << SPI_SPE) | (1 << SPI_MSTR) | (1 << SPI_SPR0) ;//|  (1<<2);
  SPSR |= 1 << SPI_SPI2X;
}

  
unsigned char AvrSpi::WriteByte(unsigned char _byte)
{
  assert( (1 << PORT_MOSI_NUM ) & SPI_DDR);
  assert( (1 << PORT_SCK_NUM ) & SPI_DDR);
  
  assert( (1 << SPI_SPE ) & SPCR);
  assert( (1 << SPI_MSTR ) & SPCR);
  assert( (1 << SPI_SPR0 ) & SPCR);
  
  SPDR = _byte;
 while(!(SPSR & (1<<SPI_SPIF)));
  
  return SPDR;
}
  
unsigned char AvrSpi::ReadByte(unsigned char _byte)
{
  
  assert( (1 << PORT_MOSI_NUM ) & SPI_DDR);
  assert( (1 << PORT_SCK_NUM ) & SPI_DDR);
  
  assert( (1 << SPI_SPE ) & SPCR);
  assert( (1 << SPI_MSTR ) & SPCR);
  assert( (1 << SPI_SPR0 ) & SPCR);
  SPDR = _byte;
  while (!(SPSR & (1<<SPI_SPIF) ));
  
  return SPDR;  
  
}