#include "avr_spi.h"
#include "dac7512_adaptor.h"
#include "Mcp3204_adaptor.h"
#include "dio_adaptor.h"

#include <ioavr.h>
#include <intrinsics.h> //__delay_cycles()


int main( void )
{
  EBIO_Relay rbRelay;
  DOut &relay = rbRelay;
  
  DDRD |= 1 << 4;
  PORTD &=  ~(1 << 4); // turn on WCS2702 


  
  AvrSpi spi;
  Dac7512Adaptor tidac(spi);
  Mcp3204Adaptor adc(spi);
  
  relay.Set(1);
  
   unsigned short adcv;


 while(1)
 {
    adcv=adc.GetADC(2);
    tidac.Write(adcv);

 }
 
}