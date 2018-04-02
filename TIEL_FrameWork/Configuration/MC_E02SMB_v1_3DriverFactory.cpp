#include "DriverFactory.h"

#include "avr_timer.h"
#include "avr_uart.h"
#include "avr_pwm.h"
#include "avr_adc.h"

#include "dio_adaptor.h"
#include "clcd_adaptor.h"


#include <string.h>

//하드웨어를 추상화하고 장치를 생성함.


static Avr_timer0    timer;
static Avr_uart0     com0;
static Avr_pwm      pwm0;

static E02SMBLed  led0;
static DigialIn swDIn;
static ClcdAdaptor clcd;

class MC_E02SMBDriverFactory : public DriverFactory
{


   

public:
  MC_E02SMBDriverFactory()
  {    
    
  }
  
  ITimer * CreateTimer()
  {
    return &timer;
  }

  ISerialPort * CreateUart()
  {
    return &com0;    
  }
  
  Led * CreateLed(unsigned char _led)
  {

    if( 0 == _led)
    {
      return &led0;
    }
    
 
    return 0;
  }  
  Clcd * CreateClcd()
  {

    
    return &clcd;
    
  }  
  
    DIn * CreateDIn()
  { 
   
    return &swDIn;
  }

  IAdcPort * CreateAdc(void) {
    static Avr_adc avr_adc;
    
    return &avr_adc;  
  
  }
  
  IPwmPort * CreatePwm(void)
  {
    
    return &pwm0;
  
  };
  
};





/////////////////////////////////////////////////////////////
static MC_E02SMBDriverFactory MC_E02SMBDriver;

DriverFactory * GetDriverFactory(void)
{
  return &MC_E02SMBDriver;
}

