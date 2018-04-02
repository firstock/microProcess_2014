//////////////////////////////////////////////////////////////////////////////////////////
 
// Project description
 
// Author: Yoo Joo-Hyoung (potato97@naver.com)
 
// Site: ccrs.hanyang.ac.kr
 
// Copyright (C) 2013-2013 TIEF(TIEF is Embedded S/W Framework) Project.
 
//
 
//////////////////////////////////////////////////////////////////////////////////////////
//
//    License type: GNU General Public License (GPL)
//      
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TIMERMANAGER_H__
#define	__TIMERMANAGER_H__

#include <vector>
#include "type.h"
#include <cassert>

class TimerManager;

//실제 HW타이머 인터페이스
class ITimer
{
public:
  ITimer(){}
  virtual ~ITimer(){}
  
  virtual void Init(void) = 0;
  
  virtual unsigned short GetTimeOutMS(void) = 0;
  virtual char isTimeOut(void) = 0;// 반드시 isTimeOut()호출후 타이머를 재가동해야함.//재진입가능 함수

protected:  
//  void evTimeOut(void);
  
};


//이벤트에 관심있는 클래스들이 상속받음
class ITimerEvent{
  friend class TimerManager;
  unsigned char eventType;
  //const unsigned short timeInterval_ms;
  unsigned short timeInterval_ms;
  unsigned short currentTime_ms;
  unsigned char state;
public:
   enum EVENTYPE{ REPEAT, ONCE };
  ITimerEvent(unsigned char _eventType, unsigned short _timeInterval_ms)
    :eventType(_eventType),timeInterval_ms(_timeInterval_ms)
  {
    state = 0;
  }
  virtual ~ITimerEvent(){}
  
  unsigned short GetTimerInterval(void)
  {
//    assert( 0 != timeInterval_ms);
    return timeInterval_ms;
  }
  char SetIntervalms(unsigned short _timeInterval_ms)//???
  {
    assert(0 != _timeInterval_ms);
    
    if(0 != _timeInterval_ms)
    {
      timeInterval_ms = _timeInterval_ms;
      return 1;
    }
    
    return 0;
    
  }
  
  void Stop(void)
  {
   currentTime_ms = 0;
   state = 0;
  }
  
  void Resume(void)
  {
   state = 1;
  }
  char GetState(void)
  {
    return state;
  }  
private:
  char CalTime(unsigned short _time)
  {
//    assert();
    //eventType
    currentTime_ms += _time;
    if( timeInterval_ms <= currentTime_ms)
    {
      currentTime_ms = 0;
      return 1;      
    }
    
    return 0;
    
  }


protected:  
  virtual void  TimeOutEvent(void) = 0;
  
};


class TimerManager{
  std::vector<ITimerEvent*> te;
  //std::vector< std::shared_ptr<ITimerEvent> > te;  
  ITimer * timer;
  unsigned short timeOutMS;
  
  static TimerManager *pInstance;
  
  TimerManager(ITimer * _timer);  
public:
  
  static TimerManager * GetInstance(ITimer * _timer = 0);
  
  virtual ~TimerManager();
  
  char AddEvent(ITimerEvent * _ev);
//  char AddEvent( std::shared_ptr<ITimerEvent> _ev);
  
//  char RemoveEvent(ITimerEvent & _ev);
  
  char evTick(void);  
  
};


#endif //end of __TIMERMANAGER_H__