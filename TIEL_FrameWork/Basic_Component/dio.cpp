#include "dio.h"

#include <assert.h>

DOut::DOut(void):stat(0)
{
}

void DOut::Set(unsigned char _v)
{
//  assert(0x01 >= _v);
  
//  _v &= 0x01;
  SetPort(_v);
//?  assert(GetPort() == _v);
  
  stat = _v;
}

unsigned char DOut::Get(void)
{
//  assert(0x01 >= GetPort());
  
  stat = GetPort();// & 0x01;
  
  return stat;
}

void DOut::Flip(unsigned char _mask)
{
//  assert(0x01 >= stat);
  
  Set( stat ^ _mask  );//& 0x01) );
}



DIn::DIn(DInEvent & _ev,unsigned char _timerInterval_MS)
:ev(&_ev),buff(0xff),pressed(0)
{
  
}

DIn::DIn()
:ev(0),buff(0xff),pressed(0)
{
  
}

char DIn::SetEvent(DInEvent & _ev)
{
  assert(0 == ev);
  
  if(0 == ev)
  {
    ev = &_ev;
    return 1;
  }
  
  return 0;
    
  
}
unsigned char DIn::Get(void)
{

  return GetPort() & 0x01;
//  return pressed;
}
void DIn::SetTimerInterval(unsigned char _timerInterval_MS)
{

  assert(0 != _timerInterval_MS);
  
  if(0 == _timerInterval_MS)
    return ;

  timerInterval_MS = _timerInterval_MS;  
  
}

// It's called ISR. 재진입 가능 함수
//
void DIn::evISR(void)
{
  
}


 //외부 타이머에 의해 호출. 비재진입 함수 
void DIn::evTimerExpir(void)
{
  
  buff = (buff << 1) | (GetPort() & 0x01);
  
  if( (buff&0x0f) == 0x0f){ //버퍼의 모든 키 값이 1이라면 노이즈가 없는 것으로 간주.
    if( pressed == 0)
    {
      //key |= FALLING; // 이전 키값이 0 이고 현재 키값이 1이므로 FALLING???
      if(0 != ev)
        ev->Changed(DInEvent::FALLING);
    }
    pressed = 1; // 현재 키값으로 대체
  }
			 
  if( (buff&0x0f) == 0x00){
    if( pressed == 1)
    {
      //key |= RISING;
      if(0 != ev)
        ev->Changed(DInEvent::RISING);
    }
     pressed = 0;
  }
    
}