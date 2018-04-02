#ifndef __AUTOOFFTIMER_H__
#define	__AUTOOFFTIMER_H__

#include "TimerManager.h"
#include "dio.h"

class AutoOffTimer : public ITimerEvent
{
  DOut * photoOut;
public:
  AutoOffTimer(unsigned int _ms,DOut * _photoOut);
  void On(void);
  void Off(void);
protected:  
  void  TimeOutEvent(void);
  
};


#endif //end of __AUTOOFFTIMER_H__