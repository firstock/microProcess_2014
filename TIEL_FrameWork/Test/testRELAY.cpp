#include "dio_adaptor.h"


#include <intrinsics.h> //__delay_cycles()


int main( void )
{
  EBIO_Relay rbRelay;
  DOut &relay = rbRelay;
  
  
  relay.Set(1);
  __delay_cycles(500000);
  relay.Set(0);
  __delay_cycles(500000);
  __delay_cycles(500000);
 

 while(1)
 {
    relay.Flip();
          __delay_cycles(500000);  // Wait for 500 000 cycles
          __delay_cycles(500000);  // Wait for 500 000 cycles
          __delay_cycles(500000);  // Wait for 500 000 cycles
          __delay_cycles(500000);  // Wait for 500 000 cycles
          __delay_cycles(500000);  // Wait for 500 000 cycles
          __delay_cycles(500000);  // Wait for 500 000 cycles          

 }
 
}