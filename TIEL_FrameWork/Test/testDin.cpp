
#include "avr_timer.h"

#include "DInTimerAdaptor.h"
#include "dio_adaptor.h"

#include <ioavr.h>

class myDInEvent:public DInEvent
{
public:

protected:
  void Change(const EDGE _edge)
  {
    
    if(DInEvent::RISING == _edge)
    {
      DDRB |= 1 | 1 << 1;  // LED on the EBIO Board
      
      PORTB ^= 2;  
    }
  }
  
};


int main( void )
{
  Avr_timer0  timer0;
  TimerManager    tm(&timer0);
  
  myDInEvent mydinev;
  DigialIn din(mydinev);
  
  DInTimerAdaptor dinadpt(din,10);
  

  tm.AddEvent(&dinadpt);

  while(1)//event loop
  {
      if(tm.evTick())
      {
        continue;
      }      
  }
  
}