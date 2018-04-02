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

#include "serialio.h"

SerialIO::SerialIO(ISerialPort & _sp, SerialEvent & _se, WRITE_OPT_T _write_opt)
:sp(&_sp),se(&_se), write_opt(_write_opt)
{
 sp->SetSerialIO(*this);
 se->SetSerialIO(*this);
  
}

SerialIO::SerialIO(ISerialPort & _sp)
:sp(&_sp),se(0), write_opt(ANSYNC)
{
 sp->SetSerialIO(*this);

}

char SerialIO::SetEvent(SerialEvent & _se)
{
  assert(0 == se);
  if(0 == se)
  {
   se = &_se; 
   se->SetSerialIO(*this);
   return 1;
  } 
  
  return 0;
  
}


void SerialIO::rxFlush(void)
{
  RxBuff.Flush();
}

void SerialIO::txFlush(void)
{
  TxBuff.Flush();;
}
  

char SerialIO::Write( unsigned char  _byte)
{
//  if(ANSYNC == write_opt)
//    ;

//  if(!PushBackTxBuff(_byte) )
 //   return 0;
  while(!PushBackTxBuff(_byte));
  assert(0 != sp);
  if(0 != sp ){
    sp->SendTxEvent();
  }
  
  return 1;
}

unsigned char SerialIO::Write(const unsigned char  _bytes[],unsigned char _size)
{
  unsigned char i;
  
  assert( 0 != _bytes);
  assert( 0 != _size);
  
  if(0 == _bytes || 0 == _size) 
    return 0;//throw error
  
  for(i = 0 ; i < _size ; i++)
  {
    if(!Write(_bytes[i]))
      return i;
  }
  
  return i;
}
unsigned char SerialIO::Write( const char   _string[])
{
  unsigned int i;
  
  assert( 0 != _string);
//  assert( 0 != _size);
  
  if(0 == _string ) 
    return 0;//throw error
  
  for(i = 0 ; _string[i] != '\0' ; i++)
  {
    if('\n' == _string[i])
    {
      if(!Write('\r'))
        return i; 
    }
    if(!Write(_string[i]))
      return i;
  }
  
  return i;  
}
unsigned char SerialIO::Write(   char  CONST  *_string)
{
  unsigned int i;
  
  assert( 0 != _string);
//  assert( 0 != _size);
  
  if(0 == _string ) 
    return 0;//throw error
  
  for(i = 0 ; _string[i] != '\0' ; i++)
  {
    if('\n' == _string[i])
    {
      if(!Write('\r'))
        return i; 
    }
    if(!Write(_string[i]))
      return i;
  }
  
  return i;  
}
  
char SerialIO::evTick(void)
{
  unsigned char data;
  
  if(PopRxBuff(data))
  {
    if(0 != se)
      se->Receive(data);
    return 1;
  }
  else
  {
    return 0;
  }
    
            
}

char SerialIO::PushBackRxBuff(unsigned char _d)
{
   return RxBuff.PushBack(_d);
  
}


char SerialIO::PopRxBuff(unsigned char & _return)
{
 
  return RxBuff.Pop(_return);
  
}
  
char SerialIO::PushBackTxBuff(unsigned char _d)
{
  return TxBuff.PushBack(_d);
}

char SerialIO::PopTxBuff(unsigned char & _return)
{
  return TxBuff.Pop(_return);
}