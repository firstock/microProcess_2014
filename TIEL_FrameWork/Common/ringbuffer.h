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


#ifndef __RINGBUFFER_H__
#define	__RINGBUFFER_H__



class RingBuffer{
   static const  unsigned char Buff_size = 10;  

public:
  RingBuffer(void);
  virtual ~RingBuffer(void){};
  char PushBack(unsigned char _d);//재진입 가능함수
  char Pop(unsigned char & _return);//재진입 가능함수
  
  void Flush(void);
  
//  char isFull(void);
  char isEmpty(void);

private:  
  unsigned char Head, Tail;
  unsigned char buff[Buff_size]; //개선되어야 할 코드  
};

#endif // end of __RINGBUFFER_H__