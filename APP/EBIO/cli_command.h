
#ifndef __CLI_COMMAND_H__
#define	__CLI_COMMAND_H__

#include "type.h"

#include "TimerManager.h"
#include "terminal_service.h"


#include "serialio.h"
#include "dio.h"
#include "clcd.h"
#include "AutoOffTimer.h"
#include "led.h"

#include "Mcp3204.h"
#include "Dac7512.h"
#include "./APP/EBIO/DacAdc.h"



class Helpcmd: public ITerminalCommand
{

public:
  Helpcmd();
  
  void ExecuteCommand(std::vector<std::string> & params);
  
 

};

class PutDacCmd: public ITerminalCommand
{
  Dac7512 * dac; 
public:
  PutDacCmd();
  
  void ExecuteCommand(std::vector<std::string> & params);
  
  void SetDac(Dac7512 * _dac);

};

class PowerCmd: public ITerminalCommand
{
  TimerManager  * tm;
  
  AutoOffTimer    * wcs2702pow;
  AutoOffTimer    * relaypow;
  DOut       * lcdpow;
  AutoOffTimer * backlightpow;
  DOut       *  zigbeepow;
  AutoOffTimer * zigbeerst;
  DOut       *    PhotoDOut;
 
public:
  PowerCmd();
  
  void ExecuteCommand(std::vector<std::string> & params);
  
  void SetDevice(TimerManager  * _tm,DOut * _wcs2702pow , DOut * _relaypow, DOut * _lcdpow,DOut * _backlightpow,DOut * _zigbeepower,DOut * _zigbeerst);

};

class LedBlinkCmd: public ITerminalCommand
{

  Led * red;
  Led * blue;
public:
  LedBlinkCmd();
  
  void ExecuteCommand(std::vector<std::string> & params);
  
  void SetLed(Led * _red, Led * _blue);

};


extern CONST char ONMSG[];
extern CONST char OFFMSG[];
class Couting : public ITimerEvent
{
  unsigned char cnt,maxcnt;
  DIn * photoin;
  SerialIO * sio;
public:
  Couting()
    :ITimerEvent(0,1000)
  {
    cnt = 0;
  }
  
  void Run(unsigned char _cnt)
  {
    maxcnt = _cnt;
    Resume();
     
  }
  
  void SetDevice(DIn * _photoin,SerialIO *_sio)
  {
    photoin = _photoin;
    sio = _sio;
  }
protected:   
  void  TimeOutEvent(void){
    
  
    if(photoin->Get()){
      
      sio->Write(OFFMSG);
    }
    else{
      
      sio->Write(ONMSG);
    }
    
    cnt++;
    if( cnt >= maxcnt)
    {
     Stop();
     cnt = 0;
    }
  }
  
};
class GetdiCmd: public ITerminalCommand
{


DIn * photoin;
SerialIO *sio;
public:
  GetdiCmd();
  
  void ExecuteCommand(std::vector<std::string> & params);
  void SetDevice(DIn * _photoin,SerialIO *_sio);
Couting cnt;  
};


class RunAdc: public ITerminalCommand
{
  
  
  Mcp3204 * adc;
  Clcd    * lcd;
  DacAdc *dacadc;
public:
  RunAdc();
  
  void ExecuteCommand(std::vector<std::string> & params);
  
  void SetDevice(Mcp3204 * _adc ,DacAdc *_dacadc ,Clcd    * _lcd);
};


class Showcmd: public ITerminalCommand
{
  SerialIO  *sio;  
public:
  Showcmd();
  
  void ExecuteCommand(std::vector<std::string> & params);
  void SetSerialIO(SerialIO & _sio);

};

class Relaycmd: public ITerminalCommand
{
  DOut  *relay;  
public:
  Relaycmd();
  
  void ExecuteCommand(std::vector<std::string> & params);
  
  void SetRelay(DOut  & _dio);
};


class CLIBuilder
{
  TerminalService * tc;
  
  
  Showcmd   showcmd;
//  Relaycmd  relaycmd;
  LedBlinkCmd ledcmd;
  PutDacCmd   putdac;
  RunAdc    runadc;
  Helpcmd   helpcmd;
  PowerCmd  powercmd;
  GetdiCmd  getdicmd;
  
public:
  CLIBuilder(TerminalService & _tc);
  virtual ~CLIBuilder();
  
  void AddShowCmd(SerialIO & _sio);
  
  void AddRelayCmd(DOut  & _dio);
  
  void AddPutdacCmd(Dac7512 * _dac);
  
  void AddPowerCmd(TimerManager  * _tm, DOut * _wcs2702pow,DOut * _relaypow,DOut * _lcdpow, DOut * _backlightpow, DOut * _zigbeepower,DOut * _zigbeerst);
    
  void AddLedCmd(Led * _red, Led * _blue);
  
  void AddGetDinCmd(TimerManager * _tm, DIn * _photoin,SerialIO *_sio);
  
  void AddRunAdc(Mcp3204 * _adc,DacAdc *_dacadc ,Clcd    * _lcd);
  

 /* 
  void AddDefaultCLICommand(void)
  {
    
    
  } 
  */
  
};

#endif //end of __CLI_COMMAND_H__