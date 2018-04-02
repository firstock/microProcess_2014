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

#include "TimerManager.h"
#include <assert.h>

TimerManager *TimerManager::pInstance = 0;
//  std::vector<ITimerEvent*> te;
//  ITimer * timer;

TimerManager::TimerManager(ITimer * _timer)
:timer(_timer)
{
  assert( 0 != _timer);
  timeOutMS = timer->GetTimeOutMS();
  
  assert( 0 != timeOutMS);
//  te.reserve(10); //메모리예약
  
}

TimerManager * TimerManager::GetInstance(ITimer * _timer)
{
  
  if( 0 == pInstance)
  {
    assert( 0 != _timer);
    //pInstance = new TimerManager(_timer);
    static TimerManager tm(_timer);
    pInstance = &tm;
    
  }
  
  return pInstance;
    
}

TimerManager::~TimerManager() 
{
  
}


char TimerManager::AddEvent(ITimerEvent * _ev)
{
  unsigned char i;
  
  assert( 0 != _ev);
  assert(te.size() < 20);
  
  if( 0 == _ev ) 
    return 0;
  
    for( i = 0 ; i < te.size() ; i++)
    {
      if(_ev == te[i])
      {
        return 0;
      }
    }
  
  te.push_back(_ev);
  
  return 1;
  
}
  
  
char TimerManager::evTick(void)
{
  unsigned char i;
  
  assert( 0 != timer);
  
  if(timer->isTimeOut() )
  {
    for( i = 0 ; i < te.size() ; i++)
    {
      if(te[i]->GetState())
      {
        if(te[i]->CalTime(timeOutMS))
        {
          te[i]->TimeOutEvent();
  //        return 1;
        }
      }
    }
  
  }
  
  return 0;
}
  