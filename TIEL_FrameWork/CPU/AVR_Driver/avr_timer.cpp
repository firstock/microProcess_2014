
#include "avr_timer.h"
#include "avr_common.h"

#include <ioavr.h> 
#include <inavr.h>



//static Avr_timer0 * timer0 = 0;

volatile unsigned char timeout;

#if defined(__ATmega164P__) | defined(__ATmega164PA__)|defined(__ATmega324P__)
#pragma vector = TIMER0_OVF_vect // for atmega164
__interrupt void timer0_ovf(void)
{
 //8ms @ 8Mhz
  
  timeout = 1;

}
#endif


#if defined(__ATmega128__)

#if AVR_TIMER == TIMER_0
#pragma vector = TIMER0_COMP_vect
#elif AVR_TIMER == TIMER_2
#pragma vector = TIMER2_COMP_vect
#endif
__interrupt void timer_cmp(void)
{
 //10ms @ 16Mhz
  
  timeout = 1;
 

}

#endif


Avr_timer0::Avr_timer0(void)
{
  timeout=0;
  Init();
 
}


#define TICKS_PER_SEC 100 //10ms
//#define TICKS_PER_SEC 1000 //1ms

void Avr_timer0::Init(void)
{
#if defined(__ATmega164P__) | defined(__ATmega164PA__)|defined(__ATmega324P__)
    TIMSK0 |= (1 << TOIE0);  //8ms @ 8Mhz
    TCCR0B |= (1 << CS02); //8ms @ 8Mhz
#endif 
    
#if defined(__ATmega128__)
#if AVR_TIMER == TIMER_0    
       TCCR0 =  ( 1 << WGM01) | ( 1 << CS02) | ( 1 << CS01) | (1 << CS00); //1024
       OCR0 = (F_CPU/TICKS_PER_SEC/1024) - 1;   
       TCNT0 = 0x00;   
       TIMSK |= ( 1 << OCIE0); 
#elif AVR_TIMER == TIMER_2
       TCCR2 =  ( 1 << WGM21) | ( 1 << CS22) | (1 << CS20); //1024
       OCR2 = (F_CPU/TICKS_PER_SEC/1024) - 1;   
       TCNT2 = 0x00;   
       TIMSK |= ( 1 << OCIE2); 
#endif       
#endif

   __enable_interrupt();

#if defined(__ATmega164P__) | defined(__ATmega164PA__)| defined(__ATmega324P__)
    
#endif
   
#if defined(__ATmega128__)
    
#endif    
    // set prescaler to 256 and start the timer
    
  
}
  
unsigned short Avr_timer0::GetTimeOutMS(void)
{
#if defined(__ATmega164P__) | defined(__ATmega164PA__)| defined(__ATmega324P__)  
  return 8; //8ms
#endif
  
#if defined(__ATmega128__)
  return 10; //10ms    
#endif   
  
}



char Avr_timer0::isTimeOut(void)
{
  
  if(timeout)
  {
    timeout = 0;
    return 1;
  }
  
  return 0;
}