#include "EBIOApplication.h"


#include "BCComponentManager.h"
#include "DriverFactory.h"
#include "./APP/EBIO/DacAdc.h"
#include "build_count.h"


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
CONST  char  BATCMSG2[]="Battery";
CONST char p[]="-+|/-+|/";
#define RESOLUTION 0.8056640625f //mV
#define SCALE 0.25373134328358208955223880597015f
class LcdDisplayTimer : public ITimerEvent
{
  Clcd    * lcd;
  Mcp3204 * adc;
  unsigned char i;

public:
  LcdDisplayTimer(void)
    :ITimerEvent(0,10000)
  {
    
  }
  void SetDevice(Clcd * _lcd,Mcp3204 * _adc)
  {
    lcd = _lcd;
    adc = _adc;
  }
protected:  
  void  TimeOutEvent(void)
  {
    char    str[15];
    if(0 != lcd && 0 != adc){
      lcd->Write(Clcd::LINE1,BATCMSG2);
        sprintf(str,"%c",p[i]);
        lcd->Write(Clcd::LINE1+7,str);
        
        sprintf(str,"[%2.2f]V ",((((float)adc->GetADC(1))*RESOLUTION)/SCALE)*0.001); //bat_vol
        lcd->Write(Clcd::LINE2,str); 
        
        i++;
        if( 7 < i)
        {
          i = 0; 
        }
    }
  }
  
};


ConvertTimer ct(200);
DacAdc da;
myTimer mt;
SerialtoTerm sev;
myDInEvent photoEvent;
LcdDisplayTimer lcdtimer;

TerminalAdaptor tsa;
//CLIBuilder  clibuilder(tsa);
///////////////////////////////////////////////////////////////////
EBIOApp ebioapp;

EBIOApp::EBIOApp()
{
  term = &tsa;
}


#define LED_RED BCComponentManager::LED0
#define LED_BLUE BCComponentManager::LED1

CONST  char  PROMPT[]="\n>> ";
CONST  char  WTD[]="\nPower-on Reset by WDT.\n";
CONST  char  EBIO_MSG[]="EBIO ";

void EBIOApp::Init(void)
{
 
  DriverFactory *driver = GetDriverFactory();
  
  tm      = GetBCComponentManager()->CreateTimer();
  serial0 = GetBCComponentManager()->CreateSerialIO();
  redLed  = GetBCComponentManager()->CreateLed(LED_RED);
  blueLed = GetBCComponentManager()->CreateLed(LED_BLUE);
  adc   = driver->CreateMcp3204();
  dac   = driver->CreateDac7512();
  relay = driver->CreateDOut("relay");
  wcs2702power = driver->CreateDOut("wcs2702pow");
  lcdpower     = driver->CreateDOut("lcdpow");
  zigbeepower  = driver->CreateDOut("zigbeepow");
  zigbeereset  = driver->CreateDOut("zigbeerst");
  lcdbacklight = driver->CreateDOut("clcdBL");
  lcd = driver->CreateClcd();
  photoDin = driver->CreateDIn();
  photoDout = driver->CreateDOut("photoout");
  
  
/////////////////////////////////////////////////////////////////////////////// 
  static AutoOffTimer  sbacklightTimer(5000,lcdbacklight);
  backlightTimer = &sbacklightTimer;
  tm->AddEvent(backlightTimer);
  
  photoEvent.SetLed(blueLed);
  photoEvent.SetDacAdc(&da);
  photoDin->SetEvent(photoEvent);
  
  
  mt.SetLed( redLed );
  tm->AddEvent(&mt);
//  mt.Resume();
  
  lcdtimer.SetDevice(lcd,adc);
  tm->AddEvent(&lcdtimer);
  lcdtimer.Resume();
  
  
  tsa.SetSerial(serial0);

  static CLIBuilder  clibuilder(*term);
  
  clibuilder.AddShowCmd(*serial0);
  clibuilder.AddRelayCmd(*relay);
  clibuilder.AddRunAdc(adc,&da,lcd);
  clibuilder.AddPutdacCmd(dac);
  clibuilder.AddPowerCmd(tm,wcs2702power,relay, lcdpower, lcdbacklight,zigbeepower,zigbeereset);
  clibuilder.AddLedCmd(redLed,blueLed);
  clibuilder.AddGetDinCmd(tm,photoDin,serial0);
  da.SetDevice(&ct,adc,dac,relay,wcs2702power,serial0,lcd,photoDout);
  tm->AddEvent(&ct);

  
  serial0->SetEvent(sev);
  sev.SetTerminal(term);
  sev.SetDevice(backlightTimer);
  
  serial0->Write(gnu_lic);
  
  char isWDT_WoringBefore(void);
  if(isWDT_WoringBefore())
  {
      serial0->Write(WTD); 
  }  
  serial0->Write(PROMPT);

  char str[15];
  
  sprintf(str, "B %d",BUILD_NUM);
    
  lcd->Write(Clcd::LINE1,EBIO_MSG);
  lcd->Write(Clcd::LINE2,str);
  wcs2702power->Set(0);

backlightTimer->On();



}
 