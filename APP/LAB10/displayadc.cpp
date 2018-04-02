#include "displayadc.h"
#include <cassert>

DisplayAdc::DisplayAdc()
{
  
}

DisplayAdc::~DisplayAdc()
{
  
}

void DisplayAdc::SetIDisplay(IDisplay * _idisp)
{
  assert(0 != _idisp);
  
  idisp = _idisp;
}


void DisplayAdc::SetAdcValue(unsigned short _v)
{
  float volt;
  if(0 != idisp)
  {  
    volt = (5/1024.0) * _v;
    
    idisp->OutPutVolt(volt);
    idisp->OutPutBar((_v >> 7) & 0x07);

  }
  
 
  
}
