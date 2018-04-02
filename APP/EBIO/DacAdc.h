#ifndef __DACADC_H__
#define	__DACADC_H__

#include "dio.h"
#include "Mcp3204.h"
#include "Dac7512.h"
#include "TimerManager.h"
#include "led.h"
#include "serialio.h"
#include "clcd.h"

class ConvertTimer;
class DacAdc
{
  
  DOut * relay;
  DOut * wcs2702power;
  Mcp3204 * adc;
  Dac7512 * dac;
  ConvertTimer * ct;
  SerialIO * sio;
  Clcd    * lcd;
  DOut * photoOut;
  unsigned char cnt;
  
  unsigned char pendingStop;

  
public:
  DacAdc();
  
  void SetDevice(ConvertTimer * _ct,Mcp3204 * _adc,Dac7512 * _dac,DOut * _relay,DOut * _wcs2702power,SerialIO *_sio, Clcd    * _lcd,DOut * _photoOut);
  
  void Run(void);
  void Stop(void);
  void Run(unsigned char _cnt);
  
  void ConvertEvent(void);
  
 unsigned short GetAdc(void);
 
private:
  void _stop(void);
  void _run(void);
};

//다중 상속????
class ConvertTimer : public ITimerEvent
{

  DacAdc * da;
public:
  ConvertTimer(unsigned int interval_ms)
    :ITimerEvent(0,interval_ms),da(0)
  {
    
  }
  void SetDacAdc(DacAdc * _da)
  {
    da = _da;
  }
protected:  
  void  TimeOutEvent(void)
  {
      if(0 != da)
        da->ConvertEvent();
  }
  
};


class myDInEvent:public DInEvent
{
   Led    * led;
   DacAdc * da;
public:
   void SetLed(Led * _led)
  {
    led = _led;
  }
  void SetDacAdc(DacAdc * _da)
  {
    da = _da;
  }

protected:
  void Changed(const EDGE _edge)
  {
    
    if(DInEvent::RISING == _edge)
    {
      if(0 != led){
//        led->Set(1);
        led->Blink(1);
      }
      if(0 != da)
      {
        da->Run(100);
      }
    }
    
    
    if(DInEvent::FALLING == _edge)
    {
//      if(0 != led)
//        led->Set(0);
      
      if(0 != da)
      {
        da->Stop();
      }
    }
  }
  
};
#endif //end of __DACADC_H__