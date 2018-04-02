#include "testCLCDApplication.h"


#include "BCComponentManager.h"
#include "DriverFactory.h"


class ledTimer : public ITimerEvent
{
  Led          * led;

public:
  ledTimer(unsigned char interval_ms)
    :ITimerEvent(0,interval_ms)
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

class LCDTimer : public ITimerEvent
{

  Clcd        *lcd;
  char    string[15];
  
  unsigned char i;
public:
  LCDTimer(void)
    :ITimerEvent(0,500)
  {
    
  }

  void SetClcd(Clcd  *_l)
  {
    lcd = _l;

  }  
protected:  
  void  TimeOutEvent(void)
  {

      
      if(0 != lcd)
      {
        sprintf(string,"[%d]  ",i);
        lcd->Write(Clcd::LINE2,string);
        
        i++;
      }
  }
  
};

ledTimer ledtimer(100);


LCDTimer lcdtimer;

myApp myapp;

myApp::myApp()
{
  
}
#define LED BCComponentManager::LED0   
void myApp::Init(void)
{

  tm = GetBCComponentManager()->CreateTimer();
  lcd = GetDriverFactory()->CreateClcd();
  
  ledtimer.SetLed( GetBCComponentManager()->CreateLed(LED) );
  
  tm->AddEvent(&ledtimer);

  
 
  ledtimer.Resume();

  
  lcdtimer.SetClcd(lcd);
  tm->AddEvent(&lcdtimer);
  
  lcdtimer.Resume();
  
  lcd->Write(Clcd::LINE1,"Hello");

  
}
 