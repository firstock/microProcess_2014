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

#ifndef __DIO_H__
#define	__DIO_H__

//Digtal I/O


class DOut
{
  unsigned char stat;
public:
  DOut(void);
  virtual ~DOut(){};
  void Set(unsigned char _v);
  unsigned char Get(void);
  void Flip(unsigned char _mask = 0xff);
//  void Flip(unsigned char);
  //void Mask(unsigned char _m);

protected:
  virtual void SetPort(unsigned char _v) = 0;
  virtual unsigned char GetPort(void) = 0;
};

class DIn;
class DInEvent
{
friend class DIn;
public:
  DInEvent(){};
  virtual ~DInEvent(){};
  enum EDGE{RISING,FALLING};
protected:
  virtual void Changed(const EDGE _edge) = 0; // user define function. 핀 상태가가 바뀌면 채터링 후 Dio 클래스에 의해 호출됨.  
};



class DIn
{
unsigned char timerInterval_MS;
unsigned char buff;
unsigned char pressed;
DInEvent *ev;
public:
  DIn(DInEvent & _ev,unsigned char _timerInterval_MS = 50U);//mode
  DIn();
  virtual ~DIn(){};
  
  char SetEvent(DInEvent & _ev);
  
  unsigned char Get(void);
 
  void evISR(void);// It's called CPU ISR. 재진입 가능 함수
  void SetTimerInterval(unsigned char _timerInterval_MS);

  void evTimerExpir(void); //외부 타이머에 의해 호출. 비재진입 함수 
protected:
  virtual unsigned char GetPort(void) = 0;
};



#endif //end of __DIO_H__