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

#ifndef __SERIALIO_H__
#define	__SERIALIO_H__


#include "type.h"
#include "ringbuffer.h"
#include <assert.h>
#include <string>


class ISerialPort;
class SerialIO;

class SerialEvent{
protected:  
  SerialIO *sio;
public:
  SerialEvent(){};
  virtual ~SerialEvent(){};
protected:
  friend class SerialIO;
  virtual void Receive( unsigned char _data ) = 0;
private:
  void SetSerialIO(SerialIO &_sio){
//    assert(0 != _sio);
    sio = &_sio;
  }
};




class SerialIO
{

public:
  typedef enum { ANSYNC, SYNC }WRITE_OPT_T;

  SerialIO(ISerialPort & _sp, SerialEvent & _se, WRITE_OPT_T _write_opt = ANSYNC);
  SerialIO(ISerialPort & _sp);
  virtual ~SerialIO(){};
  
//  GetSerialPortMaxNum();//위치는 ? -> BCCComponent???
  char SetEvent(SerialEvent & _se);
  void rxFlush(void);
  void txFlush(void);  
  
//  char Write(std::vector< unsigned char > & _data);
  char Write( unsigned char  _byte);
  unsigned char Write( const unsigned char  _bytes[],unsigned char _size );
  unsigned char Write(   char CONST *_string);  
  unsigned char Write(  const char _string[]);
//  char Write( std::string & _s);  
  char evTick(void);// to do including on the infinite loop. SerialIO가 작동하기 위해서는 외부의 무한 루프에서 건들여주어햐함.
private:
friend class ISerialPort; 
  char PushBackRxBuff(unsigned char _d);//재진입 가능함수
  char PopRxBuff(unsigned char & _return);//재진입 가능함수
  
  char PushBackTxBuff(unsigned char _d);//재진입 가능함수
  char PopTxBuff(unsigned char & _return);//재진입 가능함수
 
private:
  const WRITE_OPT_T write_opt;
  SerialEvent * se;
  ISerialPort * sp;
  
   RingBuffer  RxBuff;
   RingBuffer  TxBuff;
};

//실제 uart장치가 상속받기 위한 인터페이스
class ISerialPort{
 
  SerialIO * seIO;
public:
  ISerialPort(unsigned long _baud = 38400): baud(_baud) ,seIO(0){};
  virtual ~ISerialPort(){};
  
 
  virtual void Init(void) = 0;
  virtual void Run(void) = 0;
protected:
  unsigned long baud; 
private:  
friend class SerialIO;

void SetSerialIO(SerialIO & _seIO)
{
    assert(0 == seIO);
    seIO = &_seIO;
}

virtual void SendTxEvent(void) = 0;

  
public:  
  void SendrxBuff(unsigned char _data)// incoming data. ISR에 의해 호출됨.
  {
    assert(0 != seIO);
    if(0 != seIO){
      seIO->PushBackRxBuff(_data);
    }
  }
  
  unsigned char SendtxBuff(unsigned char & _return)// outcoming data. ISR에 의해 호출됨.
  {
    assert(0 != seIO);
    if(0 != seIO){
      if(seIO->PopTxBuff(_return))
        return 1;
      else
        return 0;
    }
    return 0;
  }  
    
};

#endif // end of __SERIALIO_H__