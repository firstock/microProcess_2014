#include "DacAdc.h"
#include "util.h"
#include "assert.h"


DacAdc::DacAdc()
:pendingStop(0) 
{

}
  
void DacAdc::SetDevice(ConvertTimer * _ct,Mcp3204 * _adc,Dac7512 * _dac,DOut * _relay,DOut * _wcs2702power, SerialIO *_sio,Clcd    * _lcd,DOut * _photoOut)
{
  relay = _relay;
  wcs2702power = _wcs2702power;
  ct = _ct;
  adc = _adc;
  dac = _dac;
  sio = _sio;
  lcd = _lcd;
  photoOut = _photoOut;
  ct->SetDacAdc(this); 
  
}
  
void DacAdc::_run(void)
{
  if(0 == ct)
    return;
  if(0 == relay)
    return;
  if(0 == wcs2702power)
    return;
  
  wcs2702power->Set(1);
  relay->Set(1);
  
  ct->Resume();
  
}

void DacAdc::Run(unsigned char _cnt)
{
  
  assert(0 != _cnt);
  if( 0 == _cnt)
    return;
  
  _run();
  cnt = _cnt;
  
}

void DacAdc::Stop(void)
{
pendingStop = 1;
 
}
void DacAdc::_stop(void)
{
  if(0 == ct)
    return;
  if(0 == relay)
    return;
  if(0 == wcs2702power)
    return;
   
  
    ct->Stop();
    
    relay->Set(0);
    wcs2702power->Set(0); 
    pendingStop = 0;
}

#define RESOLUTION 0.8056640625f //mV
#define OFFSET_250MV  (250.0/RESOLUTION)
void DacAdc::ConvertEvent(void)
{
  if(0 == dac)
    return;
  if(0 == adc)
    return;
  
  if(0 == ct)
    return;
  if(0 == relay)
    return;
  if(0 == wcs2702power)
    return;
  
static   CONST  char  WCSCMSG[]="wcs2702";  
    unsigned short v;
    char str[20];
    
      
    v = adc->GetADC(2);
    dac->Write(v+OFFSET_250MV);
    
    photoOut->Set(0);
    photoOut->Set(1);//set photoOut
    DELAY_US(5);
    photoOut->Set(0);//clr photoOut
    
    if(cnt != 0)
    {
      if( 0 != sio)
      {
        sprintf(str,"[%2.4f]V\n",((float)v)*RESOLUTION*0.001);
          sio->Write(str);
          lcd->Write(Clcd::LINE1,WCSCMSG);
        lcd->Write(Clcd::LINE2,str);
      }
       cnt--;
       if(0 == cnt)
         _stop();
       if( 1 == pendingStop)
         _stop();
    }
       
       

    
}

unsigned short DacAdc::GetAdc(void)//»èÁ¦
{
  unsigned short v;
  
      wcs2702power->Set(1);
      relay->Set(1);
      
//delay_ms(10);
      v = adc->GetADC(2);
      
      relay->Set(0);
//      wcs2702power->Set(0);
      
      return v;
  
}