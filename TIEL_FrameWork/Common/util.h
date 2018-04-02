#ifndef __UTIL_H__
#define	__UTIL_H__

#if  defined(__IAR_SYSTEMS_ICC__) & defined(WATCHDOG_ENABLE)

#define WATCH_DOG_ON() {void WDT_Prescaler_Change(void);WDT_Prescaler_Change();}
#define WATCH_DOG_KICK() {void WDT_Kick(void);WDT_Kick();}
  
#else
#define WATCH_DOG_ON()
#define WATCH_DOG_KICK()
#endif

#if  defined(__IAR_SYSTEMS_ICC__)
#define DELAY_US(X) {void avr_delay_us(unsigned char time_us);avr_delay_us(X);}
#else
#define DELAY_US(X)
#endif


#endif // end of __TYPE_H__