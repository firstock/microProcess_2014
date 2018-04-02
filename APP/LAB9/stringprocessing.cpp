#include "stringprocessing.h"
#include <cstring>
#include <cassert>

StringProcess::StringProcess()
{
  str_count = 0;  
  iout = 0;
  state = WATING_SHIFT_EVENT;
}

StringProcess::~StringProcess()
{
  
}
void StringProcess::SetIStringOutPut(IStringOutPut *_iout)
{
  assert(0 != _iout);
  
  iout = _iout;
}

void StringProcess::tm500ms(void)
{
  if(WATING_TIMER_EVENT == state)
  {
    if( 0 != iout )
    {
      iout->Display(stringShiftBuff);
      Shift_StringLeft(stringShiftBuff);
    }
    return;
  }
}

void StringProcess::InputCh(char _ch)
{
  if( 0x0d == _ch)
  {
    Start_Shift();        
  }
  else // save to tempBuff( save_string() )
  {
    if(STRING_MAX == str_count)
    {
      str_count = 0;
    }
    
    tempBuff[str_count] = _ch;
    str_count++;
  }

}
void StringProcess::update_string(void)
{
   memcpy(stringShiftBuff,tempBuff,str_count);
   stringShiftBuff[str_count] = 0; //NULL
   str_count = 0;  
   
   iout->Display("        ");
}

void StringProcess::Start_Shift(void)
{
  if(WATING_SHIFT_EVENT == state)
  {
    state = WATING_TIMER_EVENT;
    update_string();
    return;
  }
  
    if(WATING_TIMER_EVENT == state)
  {
    update_string();
    return;
  }
 
  
}

void StringProcess::Shift_StringLeft(char *_str)
{
  char tmp,len;
  
  len = strlen(_str);
  
  if( 1 >= len) {
    return;  
  }
  
  tmp = _str[0];
  strcpy(_str, &(_str[1]) );
  _str[len - 1] = tmp;
  _str[len] = 0; //NULL
  
}
  

