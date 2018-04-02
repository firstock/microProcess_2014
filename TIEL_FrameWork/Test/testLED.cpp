
#include "avr_timer.h"

#include "DInTimerAdaptor.h"
#include "dio_adaptor.h"

#include <ioavr.h>

class myTimer : public ITimerEvent
{
public:
  myTimer(void)
    :ITimerEvent(0,100)
  {
    
  }
protected:  
  void  TimeOutEvent(void)
  {
    DDRB |= 1 | 1<< 1;
    
    PORTB ^= 2;
    
  }
  
  
};
class myTimerWithLed : public ITimerEvent
{
  Led * led;
public:
  myTimerWithLed(Led * _led)
    :ITimerEvent(0,50),led(_led)
  {
//    led->SetInterval(50);
    Resume();
  }
protected:  
  void  TimeOutEvent(void)
  {
    led->evTimerExpir();
    
  }
  
  
};

int main( void )
{
  Avr_timer0  timer0;
  TimerManager    tm(&timer0);
  myTimer     userTimer;
  EBIOLedRed  led;
  myTimerWithLed ledtm(&led);

  

  tm.AddEvent(&userTimer);
  tm.AddEvent(&ledtm);
  userTimer.Resume();

  led.Blink(5);
  while(1)//event loop
  {
      if(tm.evTick())
      {
        continue;
      }      
  }
  
}