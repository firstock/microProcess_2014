/**************************************************
 *
 * This is a LED chaser example program for the AVR
 * STK500 starter kit evaluation board. This program
 * works for all AVRs.
 *
 * Description:
 * This program will turn on the User LEDs one at
 * a time and circulate this procedure in a forever
 * loop.
 *
 * Copyright 1996 -2005 IAR Systems. All rights reserved.
 *
 * $Revision: 1.1 $
 *
 **************************************************/

// Include I/O definition file
#include <ioavr.h>
#include <intrinsics.h>
    
#define ZIGBEE_RST_H()  (PORTD |= 1 << 7)
#define ZIGBEE_RST_L()  (PORTD &=  ~(1 << 7) )
#define ZIGBEE_POW_H()  (PORTD |= 1 << 6)
#define ZIGBEE_POW_L()  (PORTD &=  ~(1 << 6) )



int main( void )
{
// unsigned char  led;
    unsigned int led;
    
    PORTD = 0;
    PORTB   = 1 << 4 | 1 << 6; // Give PORTB and the User LEDs an initial startvalue
    PORTB = 0;

    led     = 1;    // Start with LED0

//    DDRB    = 1 << 4 | 1 << 6; // Set PORTB as output
    DDRB =  1 << 1;
     DDRD = 1 << 1| 1 << 7 | 1 << 6| 1 << 3;

     ZIGBEE_POW_H();
    ZIGBEE_POW_L();
    ZIGBEE_RST_L();
    __delay_cycles(500000);  // Wait for 500 000 cycles
    ZIGBEE_RST_H();
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

//      PORTB ^= 1 << 4;
//        PORTB ^= 1;
        PORTB ^= 2;
//      PORTE ^= 1;
/*      
      PORTB |= 1 << 0;
       __delay_cycles(500000);  // Wait for 500 000 cycles
      PORTB &=  ~( 1 << 0) ;        
       __delay_cycles(500000);  // Wait for 500 000 cycles
*/      
        
        if(PIND & 1)
        {
          PORTD |= 1 << 3;
        }
        else
        {
          PORTD &=  ~( 1 << 3) ;
        }
        
        if(PIND & ( 1 << 2) )
        {
          PORTD |= 1 << 1;
        }
        else
        {
          PORTD &=  ~( 1 << 1) ;
        }
         
    }
}
