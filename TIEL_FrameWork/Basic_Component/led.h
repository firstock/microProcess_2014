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

#ifndef __LED_H__
#define	__LED_H__


#include "dio.h"


class Led : public DOut
{
typedef enum { OFF, ON, BLINK } DW_LED_STATE;
DW_LED_STATE     	LED_state;

unsigned int DW_LED_currunt_timer_tick;

unsigned char blink_Number;
unsigned char onoff_cyc_ms;
unsigned char duty_rate;
unsigned int  on_rate_ms;
unsigned char onoffcnt;
unsigned char isLEDon ;
public:  
  Led();
  void Blink(unsigned char _blink_Number, unsigned char _onoff_cyc_ms = 100U, unsigned char _duty_rate = 5U);  

  
  void evTimerExpir(void); //외부 타이머에 의해 호출. 비재진입 함수
  
protected:
  virtual void SetPort(unsigned char _v) = 0;
  virtual unsigned char GetPort(void) = 0; 
  
private:
  void Init();
};


#endif //end of __LED_H__