#ifndef __TERMINALADAPTOR_H__
#define	__TERMINALADAPTOR_H__

#include "terminal_service.h"
#include "serialio.h"
#include "AutoOffTimer.h"

class TerminalAdaptor: public TerminalService
{
  SerialIO  *sio;
  
public:
  TerminalAdaptor()
  {
    
  }
  void SetSerial(SerialIO * _sio)
  {
    sio = _sio;
    
  }
  void Output(char _ch)
  {
    if( 0 != sio);
      sio->Write(_ch);    
  }
  void Output(const std::string   _string)
  {
    if( 0 != sio);
    sio->Write((const char *)&_string[0]);
  }
  void Output(CONST char _s[])
  {
    if( 0 != sio);
      sio->Write(_s);  
    
  }


  
};

class SerialtoTerm : public SerialEvent
{
  static const unsigned char STRING_SIZE = 10;  
  TerminalService * ts;
  AutoOffTimer * backlightTimer;

  char  s[STRING_SIZE+1];
  char cnt;
/*  
  void Receive1( unsigned char _data ){


    
    if('\n' == _data  || '\r' == _data  || STRING_SIZE <= cnt){
      s[cnt] = 0;

      if(0 != ts)
        ts->Input(s);

      cnt = 0;
      s[0] = 0;
      return;
    }
    
    s[cnt] = _data;    
    cnt++;
    
    
  } 
  */

  void Receive( unsigned char _data ){

 //      if(isprint(_data))
 //        sio->Write(_data);
         
       if(0 != ts)
        ts->Input(_data); 
       
    if(0 != backlightTimer)
    {
      
      backlightTimer->On();
    }
    
    
  } 

  
public:

  void SetTerminal(TerminalService * _ts)
  {
    ts = _ts;
  }
  
  void SetDevice(AutoOffTimer * _backlightTimer)
  {
    backlightTimer = _backlightTimer;
  }

};

#endif //end of __TERMINALADAPTOR_H__