#include "lab9.h"
#include <cassert>
#include "BCComponentManager.h"


#include "stringprocessing.h"

class myTimerAdaptor : public ITimerEvent
{
  StringProcess *sp;
public:
  myTimerAdaptor(void)
    :ITimerEvent(REPEAT,500)
  {
    
  }
  
  void SetStringProcess(StringProcess *_sp)
  {
    assert(0 != _sp);
    
    sp = _sp;
  }
  
protected:  
  void  TimeOutEvent(void)
  {
    if(0 != sp){
        sp->tm500ms();
    }
  }
  
};


class mySerialAdaptor : public SerialEvent
{
  StringProcess *sp;
public:
  void SetStringProcess(StringProcess *_sp)
  {
    assert(0 != _sp);
    
    sp = _sp;
  }
  
protected:  
  void Receive( unsigned char _data ){
    
    if(0 != sp){
        sp->InputCh(_data);    
    }

    sio->Write(_data); //echo back
    
    if('\r' == _data) // '\r' is 0x0d;
    {
      sio->Write("\n");
    }
    
  }; 
  
};

class LcdAdaptor: public IStringOutPut
{
  Clcd * lcd;
public:
  LcdAdaptor()
  {
    lcd = 0;
  }
  virtual ~LcdAdaptor(){};
  
  void SetCLCD(Clcd * _lcd)
  {
    assert(0 != _lcd);
    
    lcd = _lcd;    
  }
  
  void Display(char *_str)
  {
    assert(0 != _str);
    assert(0 != lcd);
    
    lcd->Write(Clcd::LINE2,_str);
  }
};

Lab9App myapp;

StringProcess sp;
myTimerAdaptor mytimer;
mySerialAdaptor mySerial;
LcdAdaptor myOutPut;

Lab9App::Lab9App()
{
  
}
   
#define LED_GREED BCComponentManager::LED0

void Lab9App::Init(void)
{
  driver = GetDriverFactory();
  tm = GetBCComponentManager()->CreateTimer();
  serial = GetBCComponentManager()->CreateSerialIO();
  lcd = driver->CreateClcd();

///////////////////////////////////////////////////////////////////////////////   

  mytimer.SetStringProcess(&sp);
  tm->AddEvent(&mytimer);
  mytimer.Resume();
  
  mySerial.SetStringProcess(&sp);
  serial->SetEvent(mySerial);
  
  myOutPut.SetCLCD(lcd);
  sp.SetIStringOutPut(&myOutPut);
  
  
  serial->Write(gnu_lic);
  serial->Write("\nEnter a message: ");
}
 