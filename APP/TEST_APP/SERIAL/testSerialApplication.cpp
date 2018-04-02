#include "testSerialApplication.h"


#include "BCComponentManager.h"
#include "DriverFactory.h"

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


class myEvent : public SerialEvent
{
  static const unsigned char STRING_SIZE = 10;  

  char  s[STRING_SIZE+1];
  char cnt;
  void Receive( unsigned char _data ){

    sio->Write(_data);
    
    if('\n' == _data  || '\r' == _data  || STRING_SIZE <= cnt){
      s[cnt] = 0;
      cnt = 0;
      s[0] = 0;
      
      sio->Write("\n>> ");
      return;
    }
    
    s[cnt] = _data;    
    cnt++;
    
    
  }; 

public:

  

  
};

myTimer mt;
myEvent se;
myApp myapp;

myApp::myApp()
{
  
}
   
#define LED_RED BCComponentManager::LED0

void myApp::Init(void)
{

  tm = GetBCComponentManager()->CreateTimer();
  mt.SetLed( GetBCComponentManager()->CreateLed(LED_RED) );
  tm->AddEvent(&mt);
  mt.Resume();
  
  serial = GetBCComponentManager()->CreateSerialIO();
  serial->Write(gnu_lic);
  serial->SetEvent(se);
  
}
 