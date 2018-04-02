#ifndef __AVR_COMMOM_H__
#define	__AVR_COMMOM_H__


//static const unsigned long F_CPU = 1000000L;
//static const unsigned long F_CPU = 8000000L;
static const unsigned long F_CPU = 16000000L;

//#define AVR_TIMER 0 
#define AVR_TIMER 2 

#define TIMER_0 0
#define TIMER_2 2

void avr_delay_ms(unsigned int m);
void avr_delay_us(unsigned char time_us);




#endif //end of __AVR_COMMOM_H__