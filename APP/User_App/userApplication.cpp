#include "userApplication.h"


#include "BCComponentManager.h"


class mySWEvent:public DInEvent
{
   Led    * led;

public:
  void SetLed(Led * _led)
  {
    led = _led;
  } 
protected:
  void Changed(const EDGE _edge)
  {
    
    if(DInEvent::RISING == _edge)
    {
      if(0 != led){
//        led->Blink(1);
        led->Flip();
      }

    }
    

  }
  
};


class myTimer : public ITimerEvent
{
  Led          * led;

public:
  myTimer(void)
    :ITimerEvent(0,100)
  {
    
  }
  void SetLed(Led * _led)
  {
    led = _led;
  }
protected:  
  void  TimeOutEvent(void)
  {
      if(0 != led)
        led->Flip();
    
  }
  
  
};


myTimer mt;
mySWEvent mySw;


myApp myapp;

myApp::myApp()
{
  
}

#define LED_GREEN8B BCComponentManager::LED0 

void myApp::Init(void)
{

  driver = GetDriverFactory();
  
  tm = GetBCComponentManager()->CreateTimer();
  swDin = driver->CreateDIn();
  led0 = GetBCComponentManager()->CreateLed(LED_GREEN8B );
  
  mt.SetLed( led0 );
  
//  tm->AddEvent(&mt);
  mt.Resume();
  
  mySw.SetLed(led0);
  swDin->SetEvent(mySw);
  
}
 