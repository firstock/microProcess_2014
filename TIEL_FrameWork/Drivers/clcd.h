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


#ifndef __CLCD_H__
#define	__CLCD_H__

#include "type.h"

class Clcd
{
//  typedef enum { IDLE, BUSY } LCD_STATE;
//  LCD_STATE LCD_state;
public:
  typedef enum { LINE1 = 0x80, LINE2 = 0xC0} LCD_LINE;
  
 // unsigned char isBusy();
  Clcd(void);
  virtual ~Clcd(void){};
  

  unsigned char Write(unsigned char _line,  CONST  char  _string[]);
  unsigned char Write(unsigned char _line,  char  *_string);
  

//  void TimerExpir_1ms(void); //외부 타이머에 의해 호출. 비재진입 함수 
protected:
  virtual void Init(void){};
  virtual void SetData(unsigned char _d) = 0;
  virtual void SetInstruction(unsigned char _inst) = 0;

};

#endif //end of __CLCD_H__