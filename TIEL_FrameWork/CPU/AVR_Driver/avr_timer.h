#ifndef __AVR_TIMER_H__
#define	__AVR_TIMER_H__


#include "TimerManager.h"

class Avr_timer0: public ITimer
{
public:
  Avr_timer0(void);

  void Init(void);
  
  unsigned short GetTimeOutMS(void);
  
  char isTimeOut(void);// 반드시 isTimeOut()호출후 타이머를 재가동해야함.  
  
};




#endif // end of __AVR_TIMER_H__