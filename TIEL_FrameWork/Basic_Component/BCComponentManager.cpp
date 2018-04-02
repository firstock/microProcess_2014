//사용자가 구성하기 원하는 컴포넌트를 만들어냄

#include "BCComponentManager.h"
#include "DriverFactory.h"
#include "System_Manager.h"
#include "DInTimerAdaptor.h"
#include <assert.h>
#include "util.h"


//하드웨어를 추상화하고 장치를 생성함.
BCComponentManager * BCComponentManager::Instantce = 0;
DriverFactory * BCComponentManager::Driver = 0;

//TimerManager  BCComponentManager::tm (DriverFactory::GetInstance()->CreateTimer() );


class BCComponentMod:public IModule
{
  TimerManager * tm;
  SerialIO *serial0;
public:

  
  void Init()
  {
//    GetBCComponentManager()->Init();
    
//    tm = BCComponentManager::GetInstance()->CreateTimer();
    tm = GetBCComponentManager()->CreateTimer();
    serial0 = GetBCComponentManager()->CreateSerialIO(0);
    assert( 0 != tm);
  }
  
  char Execute(void)
  {
    assert( 0 != tm);
    if(0 != tm){
      if(tm->evTick())
      return 1;
    }
    
    assert( 0 != serial0);
    if( 0 != serial0){
      if(serial0->evTick())
      return 1;
    }

    WATCH_DOG_KICK();
    return 0;
  }
};

BCComponentMod bcmod;

BCComponentManager::BCComponentManager()
{
  assert( 0 == Instantce);
  if(0 == Instantce)
  {
    Instantce = this;
  }
  

}

void BCComponentManager::Init(void)
{
//  Driver = DriverFactory::GetInstance();
  Driver = GetDriverFactory();
  assert( 0 != Driver);
  
  
//  static TimerManager ttm(Driver->CreateTimer());
//  tm = &ttm;
  tm = TimerManager::GetInstance(Driver->CreateTimer());
  
  static SerialIO _serial0(*(Driver->CreateUart()));
  serial0 = &_serial0;

  DIn * photoDin = Driver->CreateDIn();
  if(0 != photoDin)
  {
  static DInTimerAdaptor timer(*photoDin,10);  
  tm->AddEvent(&timer);
  }
  
  SystemManager *sys;
  sys = SystemManager::Instance();

  assert(0 != sys);
  
    led0 = Driver->CreateLed(LED0);
    if( 0 != led0)
    {
      static TimerWithLedAdapter ta0(led0);
      tm->AddEvent(&ta0);  
    }
    
    led1 = Driver->CreateLed(LED1);
    if( 0 != led1)
    {
      static TimerWithLedAdapter ta1(led1);
      tm->AddEvent(&ta1);  
    }

  sys->AddModule(bcmod);
  
  
}

//BCComponentManager * BCComponentManager::GetInstance(void)
//{
//  return Instantce ;
//}

TimerManager * BCComponentManager::CreateTimer(void)
{
  return tm;
}

Led * BCComponentManager::CreateLed(LED _led)
{
    if(LED0 == _led)
    return led0;


    if(LED1 == _led)
    return led1;    
      
}

SerialIO * BCComponentManager::CreateSerialIO(unsigned char portnum )
{
  if( 0 == portnum)
  {
    return serial0;
  }
  
  return 0;
}

DIn * BCComponentManager::CreateDIn()
{

  
  return Driver->CreateDIn();
  
  
}

Adc * BCComponentManager::CreateAdc(void)
{
  static Adc adc(Driver->CreateAdc());
  tm->AddEvent(&adc);
  
  return &adc;
}


Pwm * BCComponentManager::CreatePwm(void)
{
  static Pwm pwm(Driver->CreatePwm());
  
  return &pwm;
  
}
/////////////////////////////////////////////////////////////////////////////////
static BCComponentManager bc;

BCComponentManager * GetBCComponentManager(void)
{
  
  return &bc; 
}


