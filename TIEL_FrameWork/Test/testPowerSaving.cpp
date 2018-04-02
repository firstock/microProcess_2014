#include <ioavr.h>
#include <intrinsics.h>
//#include "avr_watchdog.h"

#define LED0_ON()  (PORTB |= 1 << 0)
#define LED0_OFF()  (PORTB &=  ~(1 << 0) )
#define LED1_ON()  (PORTB |= 1 << 1)
#define LED1_OFF()  (PORTB &=  ~(1 << 1) )


#define WCS2702_DDR DDRD
#define WCS2702_PORT PORTD
#define WCS2702_PIN   PIND
#define WCS2702_PORT_NUM 4
#define WCS2702_ON()  (WCS2702_PORT |= 1 << WCS2702_PORT_NUM)
#define WCS2702_OFF()  (WCS2702_PORT &=  ~(1 << WCS2702_PORT_NUM) )
 
void avr_power_saving(void)
{
//  SMCR = (1 << SM0) | (1 << SE); //ADC Noise Reduction
    SMCR = (1 << SM1) | (1 << SE); // Power-down
//  SMCR = (1 << SM1) | (1 << SM0) | (1 << SE); // Power-save
//  SMCR = (1 << SE); // idle mode

PRR=0xff;    
    SMCR |=(1 << SE);

__sleep(); 
 //   asm("sleep");
  
 
}

int main( void )
{
//  WCS2702_DDR |= 1 << WCS2702_PORT_NUM; 
//  WCS2702_ON();
  
//  ADCSRA = 0; 

//   MCUCR =  (1 << BODS) |  (1 << BODSE);
//  MCUCR =  (1 << BODS);
//  MCUCR|= 1 << PUD;
  avr_power_saving();
  
  while(1)
  {
    
  }
  
}