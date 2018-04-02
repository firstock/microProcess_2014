#include "adc.h"

#include <cassert>

Adc::Adc(IAdcPort * _iadc)
 :ITimerEvent(REPEAT,100)
{
  assert(0 != _iadc);
  
  iadc = _iadc;
  ev = 0;
}

Adc::~Adc()
{
  
}
  
void Adc::evTick(void)
{
  if( 0 != ev)
  {
    ev->Converted( iadc->GetAdc() );
    
  }
}

void  Adc::TimeOutEvent(void)
{
  evTick();  
}

void Adc::Run(void)
{
  ITimerEvent::Resume();
}
void Adc::Stop(void)
{
  ITimerEvent::Stop();
}

void Adc::Addevent(AdcEvent * _ev)
{
  assert( 0 != _ev);
  
  if( 0 != _ev)
  {
    ev = _ev;
  }
}

void Adc::SetFrequency(unsigned char _Hz)
{
  float ms;
  
  ms = (1.0/_Hz)*1000;
  
  ITimerEvent::SetIntervalms(ms);

}
 