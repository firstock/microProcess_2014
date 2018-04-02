#include "avr_spi.h"
//#include "dac7512_adaptor.h"


#include <intrinsics.h> //__delay_cycles()


int main( void )
{

//  AvrSpi spi;
//  Dac7512Adaptor tidac(spi);
  

  
  unsigned short cnt= 0;

 while(1)
 {
//      tidac.Write(cnt++);
//          __delay_cycles(500000);  // Wait for 500 000 cycles
          
      if(cnt > 0xfff)
        cnt = 0;
 }
 
}