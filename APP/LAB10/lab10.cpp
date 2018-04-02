#include "lab10.h"
#include <cassert>
#include <cstring>
#include "BCComponentManager.h"


#include "displayadc.h"


class myAdcAdaptor: public AdcEvent{
  
  DisplayAdc *disadc;

public:
  myAdcAdaptor(){}
  virtual ~myAdcAdaptor(){}
public:
  void SetDisplayAdc(DisplayAdc *_disadc)
  {
    assert(0 != _disadc);
    
    disadc = _disadc;
  }
protected:  
  void Converted( unsigned short _valueOfAdc)
  {
      if(0 != disadc){
        disadc->SetAdcValue(_valueOfAdc);
      }
    
  }
  
};

class mylcdAdaptor: public IDisplay{
  
  Clcd        *lcd;
public:
  mylcdAdaptor(){}
  virtual ~mylcdAdaptor(){}
  
  void SetClcd(Clcd  *_lcd)
  {
    assert(0 != _lcd);
    lcd = _lcd;
  } 
  
  void OutPutVolt(float _v)
  {
    char str[10];
    
    sprintf(str,"%4.2f     ",_v);
    if(0 != lcd)
    {
      lcd->Write(Clcd::LINE1,str);
    }
  }
  
  void OutPutBar(unsigned char _bar)
  {
    char str[10]="         ";
    
    if(0 != lcd)
    {
      if( 9 <= _bar){
        _bar = 9; 
      }
      memset(str,'#',_bar);

      lcd->Write(Clcd::LINE2,str);
    }
  }
};

Lab10App myapp;

DisplayAdc    disadc;
myAdcAdaptor  myadcEvent;
mylcdAdaptor   mylcdadp;

Lab10App::Lab10App()
{
  
}
   
#define LED_GREEN8B BCComponentManager::LED0

void Lab10App::Init(void)
{
  driver = GetDriverFactory();
  tm = GetBCComponentManager()->CreateTimer();
  greenLed  = GetBCComponentManager()->CreateLed(LED_GREEN8B);
  serial = GetBCComponentManager()->CreateSerialIO();
  adc = GetBCComponentManager()->CreateAdc();
  lcd = driver->CreateClcd();
  
///////////////////////////////////////////////////////////////////////////////   

  mylcdadp.SetClcd(lcd);
  myadcEvent.SetDisplayAdc(&disadc);
  disadc.SetIDisplay(&mylcdadp);
  
  adc->SetFrequency(100);// 100Hz
  adc->Addevent(&myadcEvent);
  adc->Run();
  
  
  
  serial->Write(gnu_lic);

}
 