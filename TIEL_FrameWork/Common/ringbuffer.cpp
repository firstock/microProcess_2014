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

#include "ringbuffer.h"

RingBuffer::RingBuffer(void)
:Head(0), Tail(0)
{
  
}

void RingBuffer::Flush(void)
{
  Head = Tail;
}

char RingBuffer::isEmpty(void)
{
   return Head == Tail;
}

char RingBuffer::PushBack(unsigned char _d)
{
    if( !( (Head+1 == Tail) || ( Head == Buff_size - 1 && Tail == 0) ) )
    {
      buff[Head] = _d;
      Head++;
      if(Buff_size == Head)
        Head = 0;
      
      return 1;
    }
    
    return 0; //buffer is full
  
}


char RingBuffer::Pop(unsigned char & _return)
{
 
  if(Head != Tail)
  {
    _return =  buff[Tail];
    Tail++;
    if(Buff_size == Tail)
    {
      Tail = 0;
    }
    
    return 1;
  }
  
  return 0;//fail. Buffer is empty.
  
}