#ifndef __AVR_TIMER_H__
#define	__AVR_TIMER_H__


#include "TimerManager.h"

class Avr_timer0: public ITimer
{
public:
  Avr_timer0(void);

  void Init(void);
  
  unsigned short GetTimeOutMS(void);
  
  char isTimeOut(void);// �ݵ�� isTimeOut()ȣ���� Ÿ�̸Ӹ� �簡���ؾ���.  
  
};




#endif // end of __AVR_TIMER_H__