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


#include "clcd.h"
#include <assert.h>

Clcd::Clcd(void)
{
  Init();
}
  
unsigned char Clcd::Write(unsigned char _line,  char  *_string)
{
      
    SetInstruction(_line); //LCD 위치 지정
    assert( 0 != _string);

    while(*_string != '\0')
    {
        SetData(*_string);
        _string++;
    }
    
    return 1;
  
}
unsigned char Clcd::Write(unsigned char _line, CONST  char  _string[])
{
      unsigned char i =0;
    SetInstruction(_line); //LCD 위치 지정
    assert( 0 != _string);

    while(_string[i] != '\0')
    {
        SetData(_string[i]);
        i++;
    }
    
    return 1;
  
}