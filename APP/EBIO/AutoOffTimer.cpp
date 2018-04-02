#include "AutoOffTimer.h"


AutoOffTimer::AutoOffTimer(unsigned int _ms,DOut * _photoOut)
:ITimerEvent(0,_ms),photoOut(_photoOut)
{
  ITimerEvent::Stop();
}

void AutoOffTimer::On(void)
{
  photoOut->Set(1);
  ITimerEvent::Stop();
  ITimerEvent::Resume();
  
}

void AutoOffTimer::Off(void)
{
  photoOut->Set(0);
  ITimerEvent::Stop();
}


void  AutoOffTimer::TimeOutEvent(void)
{
  Off();    
}
  
