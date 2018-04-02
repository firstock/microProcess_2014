//////////////////////////////////////////////////////////////////////////////////////////
 
// Project description
 
// -------------------------------------------
 
// Description: for test
 
//
 
// Author: Yoo Joo-Hyoung (potato97@naver.com)
 
// Site: ccrs.hanyang.ac.kr
 
// Copyright (C) 2013-2013 TIEL(TIEL is Embedded S/W library) Project.
 
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
#include "avr_uart.h"
#include "serialio.h"
#include "clcd_adaptor.h"
#include "avr_common.h"





class myEvent : public SerialEvent
{
  static const unsigned char STRING_SIZE = 50;  

  Clcd * lcd ;
  char s[STRING_SIZE+1];
  char cnt;
  void Receive( unsigned char _data ){

    sio->Write(_data);
    
    if('\n' == _data  || '\r' == _data  || STRING_SIZE <= cnt){
      s[cnt] = 0;
      lcd->Write(Clcd::LINE2, s);

      sio->Write('\n');
      cnt = 0;
      s[0] = 0;
      return;
    }
    
    s[cnt] = _data;    
    cnt++;
    
    
  } 
  
public:
  myEvent(Clcd & _l)
  {
    lcd = &_l;
    cnt = 0;
  }
  

  
};


int main( void )
{
  
  ClcdAdaptor l;
  myEvent     ev(l);
  Avr_uart0   port0;

  SerialIO    serial(port0,ev);


  l.Write(Clcd::LINE1, "test serial");
  serial.Write('B');
  serial.Write("\ntest serial");
  
    while(1)//event loop
    {
      if(!serial.evTick())
      {
        continue;
      }
      serial.Write("\ntest serial");
      //avr_sleep(); 
     
    }
}

