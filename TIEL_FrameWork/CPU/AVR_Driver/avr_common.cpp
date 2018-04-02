#include "avr_common.h"

#include <ioavr.h>
#include <inavr.h> //__delay_cycles()

#if defined(__ATmega128__) 
void avr_delay_us(unsigned char time_us) //at 16.000MHZ
{ // time delay(us)
  register unsigned char i;
  for(i = 0; i < time_us; i++) {        // 4 cycle
    __delay_cycles(12);  
    // 16 cycle * 62.5 ns = 1000 ns = 1 us at 16.000MHZ
  }
}
#else
void avr_delay_us(unsigned char time_us)//at 8.000MHZ
{ // time delay(us)
  register unsigned char i;
  for(i = 0; i < time_us; i++) {        // 4 cycle
    __delay_cycles(4);  

  }
}
#endif
void avr_delay_ms(unsigned int m)
{
    unsigned int i;

    for(i=0; i<m; i++)
    {
      avr_delay_us(250);
      avr_delay_us(250);
      avr_delay_us(250);
      avr_delay_us(250);
    }
}