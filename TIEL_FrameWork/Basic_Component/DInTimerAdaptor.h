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

#ifndef __DINTIMERADAPTOR_H__
#define	__DINTIMERADAPTOR_H__

#include "dio.h"
#include "TimerManager.h"


class DInTimerAdaptor :public ITimerEvent
{
  DIn * din;
public:
  DInTimerAdaptor(DIn & _din, unsigned char _timerInterval_MS)
    :ITimerEvent(1,_timerInterval_MS),din(&_din)
  {
    din->SetTimerInterval(_timerInterval_MS);
    Resume();
  }
protected:  
  void  TimeOutEvent(void)
  {
    din->evTimerExpir();
  }
};

class TimerWithLedAdapter : public ITimerEvent
{
  Led * led;
public:
  TimerWithLedAdapter(Led * _led)
    :ITimerEvent(0,50),led(_led)
  {
//    led->SetInterval(50);
    Resume();
  }
protected:  
  void  TimeOutEvent(void)
  {
    led->evTimerExpir();
    
  }
  
  
};
#endif //end of __DINTIMERADAPTOR_H__