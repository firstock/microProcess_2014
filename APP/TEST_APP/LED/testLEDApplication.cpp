#include "testLEDApplication.h"


#include "BCComponentManager.h"
#include "DriverFactory.h"



class myTimer : public ITimerEvent
{
  Led          * led;
  unsigned char i ;

public:
  myTimer(void)
    :ITimerEvent(REPEAT,500)
  {
    i =0;
    
  }
  void SetLed(Led * _led)
  {
    led = _led;
  }
  
protected:  
  void  TimeOutEvent(void)
  {
    /*
      if(0 != led)
         led->Flip();
    */
    
    /*
    if(0 != led)
      led->Set(0xf & i);
    
    i++;
    if( 0x0f < i)
      i = 0;
    */
    
    if(0 != led)
      led->Blink(3);

  }
  
};

myTimer mt;

myApp myapp;

myApp::myApp()
{
  
}

#define LED_GREEN8B BCComponentManager::LED0


void myApp::Init(void)
{

  tm = GetBCComponentManager()->CreateTimer();
  greenLed  = GetBCComponentManager()->CreateLed(LED_GREEN8B);
  
  
  mt.SetLed( greenLed );
  tm->AddEvent(&mt);
  mt.Resume();
  
  
}
 