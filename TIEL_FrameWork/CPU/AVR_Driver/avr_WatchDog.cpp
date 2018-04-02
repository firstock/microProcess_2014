#include "avr_watchdog.h"
#include <ioavr.h>
#include <intrinsics.h>

#ifdef WATCHDOG_ENABLE
avr_watchdog dog;
#endif

void WDT_Prescaler_Change(void)
{
#ifdef WATCHDOG_ENABLE  
__disable_interrupt();
__watchdog_reset();
/* Start timed equence */
#if defined(__ATmega164P__) | defined(__ATmega164PA__) | defined(__ATmega324P__)
WDTCSR |= (1<<WDCE) | (1<<WDE);
/* Set new prescaler(time-out) value = 64K cycles (~0.5 s) */
WDTCSR = (1<<WDE) | (1<<WDP3) | (1<<WDP0);
#endif
__enable_interrupt();
#endif
}

char isWDT_WoringBefore(void)
{
  
#if defined(__ATmega164P__) | defined(__ATmega164PA__) | defined(__ATmega324P__)  
  if(MCUSR & ( 1 << WDRF) )
  {
    MCUSR &= ~( 1 << WDRF);
    return 1;
  }
#endif
  
  return 0;
}

void WDT_Kick(void)
{
#ifdef WATCHDOG_ENABLE   
  __watchdog_reset(); 
#endif  
}

avr_watchdog::avr_watchdog()
{

Prescaler_Change();

}


void avr_watchdog::Kick(void)
{
#ifdef WATCHDOG_ENABLE   
    __watchdog_reset();
#endif 
}

void avr_watchdog::CPUReset(void)
{
  
  
}

void avr_watchdog::Prescaler_Change(void)  
{
#ifdef WATCHDOG_ENABLE   
__disable_interrupt();
__watchdog_reset();
/* Start timed equence */

#if defined(__ATmega164P__) | defined(__ATmega164PA__)|defined(__ATmega324P__)
//WDTCSR |= (1<<WDCE) | (1<<WDE);
/* Set new prescaler(time-out) value = 64K cycles (~0.5 s) */
//WDTCSR = (1<<WDE) | (1<<WDP3) | (1<<WDP0);//8.0s

     asm("lds r16, 0x60"); 
     asm("ori r16, 0x18"); 
     asm("sts 0x60, r16"); 
     asm("ldi r16, 0x29"); 
     asm("sts 0x60, r16");
#endif  
#if defined(__ATmega128__)
    
#endif  
     
__enable_interrupt();
#endif 
}

void avr_watchdog::Off(void)
{
  __disable_interrupt();
  __watchdog_reset();
  
#if defined(__ATmega164P__) | defined(__ATmega164PA__)|defined(__ATmega324P__)
  /* Clear WDRF in MCUSR */
  MCUSR &= ~(1<<WDRF);
  /* Write logical one to WDCE and WDE */
  /* Keep old prescaler setting to prevent unintentional time-out */
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  /* Turn off WDT */
  WDTCSR = 0x00;
#endif  
#if defined(__ATmega128__)
    
#endif   

  
  __enable_interrupt();  
  
}