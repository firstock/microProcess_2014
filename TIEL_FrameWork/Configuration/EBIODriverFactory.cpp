#include "DriverFactory.h"

#include "avr_timer.h"
#include "avr_uart.h"
#include "avr_spi.h"
#include "dio_adaptor.h"

#include "clcd_adaptor.h"

#include "dac7512_adaptor.h"
#include "mcp3204_adaptor.h"

#include <string.h>

//하드웨어를 추상화하고 장치를 생성함.


static Avr_timer0    timer;
static Avr_uart0     com0;
static AvrSpi        spi;

static EBIO_Relay relay;
static WCS2702POW wcs2702pow;
static LcdPOW lcdpow;
static LcdBackLight lcd_bl;
static DigialOut    photoOut;
static DigialIn photoDIn;
static EBIOLedRed red;
static EBIOLedBlue Blue;
static ClcdAdaptor clcd;
static ZigBeePOW  zigbeepow;
static ZigBeeRST  zigbeerst;


class EBIODriverFactory : public DriverFactory
{
static Dac7512Adaptor dac; 
static Mcp3204Adaptor adc;

   

public:
  EBIODriverFactory()
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
  
  ISpi * CreateSPI()
  {
    return &spi;
  }
  
  DIn * CreateDIn()
  { 
   
    return &photoDIn;
  }
  
  DOut * CreateDOut( char * _str)
  {

    if(!strcmp(_str,"relay"))
    {
      return &relay;
    }
    
    if(!strcmp(_str,"wcs2702pow"))
    {
      return &wcs2702pow;
    }
    
    if(!strcmp(_str,"lcdpow"))
    {
      return &lcdpow;
    }

    if(!strcmp(_str,"clcdBL"))
    {
      return &lcd_bl;
    }
    
    if(!strcmp(_str,"photoout"))
    {
      return &photoOut;
    }
    
     if(!strcmp(_str,"zigbeepow"))
    {
      return &zigbeepow;
    }
    
     if(!strcmp(_str,"zigbeerst"))
    {
      return &zigbeerst;
    }    
    assert(0);
    return 0;    
  }
//  virtual Adcport * CreateAdc() = 0;
  
  
  Dac7512 * CreateDac7512()
  {
    dac.Init();
    
    return &dac;
  }
  
  Mcp3204 * CreateMcp3204()
  {
    adc.Init();
    return &adc;    
  }
  
  Led * CreateLed(unsigned char _led)
  {

    if( 0 == _led)
    {
      return &red;
    }
    
    if( 1 == _led)
    {
      return &Blue;
    }
    
    return 0;
  }
  
  Clcd * CreateClcd()
  {

    
    return &clcd;
    
  }
};





/////////////////////////////////////////////////////////////
static EBIODriverFactory EBIODriver;

DriverFactory * GetDriverFactory(void)
{
  return &EBIODriver;
}

Dac7512Adaptor EBIODriverFactory::dac(spi);
Mcp3204Adaptor EBIODriverFactory::adc(spi);
