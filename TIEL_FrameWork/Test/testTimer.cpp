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
#include "avr_timer.h"
#include "serialio.h"
#include "clcd_adaptor.h"
#include "avr_common.h"

#include "terminal_service.h"
#include "cli_command.h"
#include "dio_adaptor.h"

#include <ioavr.h>
class myTimer : public ITimerEvent
{
public:
  myTimer(void)
    :ITimerEvent(0,100)
  {
    
  }
protected:  
  void  TimeOutEvent(void)
  {
    DDRB |= 1 | 1<< 1;
    
    PORTB ^= 2;
    
  }
  
  
};


class myEvent : public SerialEvent
{
  static const unsigned char STRING_SIZE = 10;  
  TerminalService * ts;

  Clcd * lcd ;
  char  s[STRING_SIZE+1];
  char cnt;
  void Receive( unsigned char _data ){

    sio->Write(_data);
    
    if('\n' == _data  || '\r' == _data  || STRING_SIZE <= cnt){
      s[cnt] = 0;
      lcd->Write(Clcd::LINE2, s);
      if(0 != ts)
        ts->Input(s);
//      sio->Write('\n');
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
  void SetTerminal(TerminalService & _ts)
  {
    ts = &_ts;
  }
  

  
};


class TerminalAdaptor: public TerminalService
{
  SerialIO  *sio;
public:
  TerminalAdaptor(SerialIO & _sio):sio(&_sio)
  {
    
  }
  
  void Output(const std::string   _string)
  {
    sio->Write((const char *)&_string[0]);
  }
  
};



int main( void )
{
  
  ClcdAdaptor lcd;
  myEvent     ev(lcd);
  Avr_uart0   com0;
  Avr_timer0  timer0;
  myTimer     myt;
  EBIO_Relay rbRelay;
  

  SerialIO    serial(com0,ev);
  
  TerminalAdaptor term(serial);
  TimerManager    tm(&timer0);
  
  tm.AddEvent(&myt);

  CLIBuilder  clibuilder(term);
  ev.SetTerminal(term);
  term.Init();
  
  

  clibuilder.AddShowCmd(serial);
  clibuilder.AddRelayCmd(rbRelay);
  clibuilder.AddRunTran(myt);
  serial.Write(gnu_lic);
  
    
    while(1)//event loop
    {
      if(tm.evTick())
      {
        continue;
      }
      
      if(!serial.evTick())
      {
        continue;
      }
      
      //avr_sleep(); 
     
    }
}

