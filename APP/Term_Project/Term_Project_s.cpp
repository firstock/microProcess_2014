#include "Term_Project_s.h"
#include <cassert>
#include <cstring>
#include "BCComponentManager.h"


#include "CalClkFuncGen.h"

class myTimer1s : public ITimerEvent
{
  Led          * led;
  CalClkFuncGen * ccf;

public:
  myTimer1s(void)
    :ITimerEvent(0,1000) // 1000ms
  {
    
  }
  void SetLed(Led * _led)
  {
    led = _led;
  }
  
  void SetCalClkFuncGen(CalClkFuncGen *_ccf)
  {
    assert(0 != _ccf);
    
    ccf = _ccf;
  }
protected:  
  void  TimeOutEvent(void)
  {
      if(0 != led)
        led->Flip(0x01);
      
      if(0 != ccf){
        ccf->tm1s();
      }
    
  }

};

class myTimer500ms : public ITimerEvent
{
  Led          * led;
  CalClkFuncGen * ccf;

public:
  myTimer500ms(void)
    :ITimerEvent(0,500) // 500ms
  {
    
  }
  void SetLed(Led * _led)
  {
    led = _led;
  }
  
  void SetCalClkFuncGen(CalClkFuncGen *_ccf)
  {
    assert(0 != _ccf);
    
    ccf = _ccf;
  }
protected:  
  void  TimeOutEvent(void)
  {
      if(0 != led)
        led->Flip(0x02);
      
      if(0 != ccf){
        ccf->tm500ms();
      }
    
  }

};
class mySWEvent:public DInEvent
{
   Led    * led;
   CalClkFuncGen *ccf;

public:
  void SetLed(Led * _led)
  {
    led = _led;
  } 
  
  void SetCalClkFuncGen(CalClkFuncGen *_ccf)
  {
    assert(0 != _ccf);
    
    ccf = _ccf;
  }  
protected:
  void Changed(const EDGE _edge)
  {
    
    if(DInEvent::RISING == _edge)
    {
      if(0 != led){
//        led->Blink(1);
      }
      if(0 != ccf){
        ccf->Switch();
      }      
      
    }
    

  }
  
};
class myAdcAdaptor: public AdcEvent{
  
  CalClkFuncGen *ccf;

public:
  myAdcAdaptor(){}
  virtual ~myAdcAdaptor(){}
public:
  void SetCalClkFuncGen(CalClkFuncGen *_ccf)
  {
    assert(0 != _ccf);
    
    ccf = _ccf;
  }
protected:  
  void Converted( unsigned short _valueOfAdc)
  {
      if(0 != ccf){
        ccf->InputAdc(_valueOfAdc);
      }
    
  }
  
};

class myPwmAdaptor: public IPwmOut{
  Pwm * pwm;
public:
 void SetPwm(Pwm * _pwm)
 {
   assert( 0 != _pwm);
   pwm = _pwm;
 }
  void SetDuty(unsigned short _du)
  {
    if( 0 != pwm)
    {
      pwm->SetDuty(_du);
    }
  }
};

class mySerialEvent : public SerialEvent
{
  CalClkFuncGen *ccf;
  
  void Receive( unsigned char _data ){

    sio->Write(_data);
    if( '\r' == _data)// '\r' is 0x0d; 
    {
      sio->Write("\n");
    }
    
      if(0 != ccf){
        ccf->InputCh(_data); //echo back
      }
    
  }

public:

  void SetCalClkFuncGen(CalClkFuncGen *_ccf)
  {
    assert(0 != _ccf);
    
    ccf = _ccf;
  }  

  
};
class mySerialOutAdaptor: public IStringOut
{
  SerialIO      * serial;
public:
  
  void SetSerial(SerialIO * _serial)
  {
    assert( 0 != _serial);
    serial = _serial;
  }
  
  void Write(char * _str)
  {
    assert(0 != _str);
    
    if( 0 != serial)
    {
      serial->Write(_str);
    }
    
  }
  
};

class mylcdAdaptor:public IStringOut
{
  Clcd        *lcd;
  unsigned char line;
public:
  mylcdAdaptor(){}
  virtual ~mylcdAdaptor(){}
  
  
  void SetClcd(Clcd  *_lcd,unsigned char _line)
  {
    assert(0 != _lcd);
    lcd = _lcd;
    line = _line;
  } 
  
  void Write(char * _str)
  {
    if(0 != lcd)
    {
      lcd->Write(line,_str);
    }
  }
};

/////////////////////////////
Term_Project_s myApp;
////////////////////////////

CalClkFuncGen    ccf;
myAdcAdaptor  myadcEvent;
myPwmAdaptor  myPwmadp;
mylcdAdaptor   mylcdline1,mylcdline2;
mySerialOutAdaptor myserialadp;
mySerialEvent       myserialEvent;
myTimer1s     mytimer_1sec;
myTimer500ms  mytimer_500ms;

mySWEvent   mySW;


Term_Project_s::Term_Project_s()
{
  
}
   
#define LED_GREEN8B BCComponentManager::LED0

//Init() 함수 호출 시점에서 하드웨어 자원을 사용가능
void Term_Project_s::Init(void)
{
  driver = GetDriverFactory();
  tm = GetBCComponentManager()->CreateTimer();
  greenLed  = GetBCComponentManager()->CreateLed(LED_GREEN8B);
  swDin   =  GetBCComponentManager()->CreateDIn();
  serial = GetBCComponentManager()->CreateSerialIO();
  adc = GetBCComponentManager()->CreateAdc();
  pwm = GetBCComponentManager()->CreatePwm();
  lcd = driver->CreateClcd();
  
///////////////////////////////////////////////////////////////////////////////   

  mytimer_1sec.SetLed(greenLed);
  mytimer_1sec.SetCalClkFuncGen(&ccf);
  tm->AddEvent(&mytimer_1sec);
  mytimer_1sec.Resume();
  
  
  mytimer_500ms.SetLed(greenLed);
  mytimer_500ms.SetCalClkFuncGen(&ccf);
  tm->AddEvent(&mytimer_500ms);
  mytimer_500ms.Resume();
  
  mySW.SetLed(greenLed);
  mySW.SetCalClkFuncGen(&ccf);
  swDin->SetEvent(mySW);
  
  mylcdline1.SetClcd(lcd,Clcd::LINE1);
  mylcdline2.SetClcd(lcd,Clcd::LINE2);
  
  myadcEvent.SetCalClkFuncGen(&ccf);
  myserialadp.SetSerial(serial);
  
  myserialEvent.SetCalClkFuncGen(&ccf);
  serial->SetEvent(myserialEvent);
  
  adc->SetFrequency(100);// 100Hz
  adc->Addevent(&myadcEvent);
  adc->Run();
  
  myPwmadp.SetPwm(pwm);
  ccf.SetIStringOut(&mylcdline1,&mylcdline2,&myserialadp);
  ccf.SetPwm(&myPwmadp);
  
  serial->Write(gnu_lic);
  
  ccf.Init();

  
}
 