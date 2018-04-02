#include <ioavr.h>
#include <intrinsics.h>
#include "avr_watchdog.h"

#define LED0_ON()  (PORTB |= 1 << 0)
#define LED0_OFF()  (PORTB &=  ~(1 << 0) )
#define LED1_ON()  (PORTB |= 1 << 1)
#define LED1_OFF()  (PORTB &=  ~(1 << 1) )



int main( void )
{

    unsigned int led;
  


//   WDT_Prescaler_Change();
    DDRB =  1 << 1 | 1; // Set PORTB as output
    
    LED0_OFF();
    __delay_cycles(500000);  // Wait for 500 000 cycles
    __delay_cycles(500000);  // Wait for 500 000 cycles

    while(1)        // Eternal loop
    {
 //             PORTB = led;   // Invert the output since a zero means: LED on
 //       led = ~led;      // Move to next LED by performing a rotate left
 //         led++;    
       
/*      
        PORTB = ~led;   // Invert the output since a zero means: LED on
        led <<= 1;      // Move to next LED by performing a rotate left

        if (!led)
          led = 1;      // If overflow: start with LED0 again
*/
//        __delay_cycles(500000);  // Wait for 500 000 cycles


/*
      LED0_ON();
       __delay_cycles(500000);  // Wait for 500 000 cycles
       
      LED0_OFF();

       __delay_cycles(500000);  // Wait for 500 000 cycles
      
*/
//         LED0_ON(); // Watchdog enable microcontroller reset, the program re-run, we see LED flashing.
//         dog.Kick();/ / If here to join Kick(); feed the dog, will not reset the microcontroller. 
    }
}