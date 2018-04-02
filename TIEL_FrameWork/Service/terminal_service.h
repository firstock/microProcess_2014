#ifndef __TERMINAL_SERVICE_H__
#define	__TERMINAL_SERVICE_H__

#include "type.h"
#include <vector>
#include <string>
#include "shared_ptr.h"
#include <assert.h>
#include <string>
#include <vector>
#include "type.h"

class ITerminalCommand;


class TerminalService{
  const unsigned char defaultParams;
  
  static const unsigned char STRING_SIZE = 12;  

  std::vector<std::string> cmdlist;
  std::string currCmd;

//  char  s[STRING_SIZE+1];
//  char cnt;  
public:  
  TerminalService(unsigned char _defaultParamMax = 10);
  void Init(void);
  void Input(const std::string & _string);
  void Input(char _ch);
  virtual void Output(const std::string  _string)=0;
  virtual void Output(char _ch)=0;
  virtual void Output(CONST char _s[])=0;
  char isprint(char _ch);
//  void Parsing(void);
  void AddCommand(ITerminalCommand & _tc);
//  void AddCommand(std::shared_ptr<ITerminalCommand>  _tc);
  
protected:  
  virtual void InputHook(char _ch){}
private:
  std::vector<ITerminalCommand*> tcs;
//  std::vector<std::shared_ptr<ITerminalCommand> > ptcs;

  
  
};


//io서비스를 제공해야하는가??
//자동완성?
//약식 명령?
class ITerminalCommand
{
  friend class TerminalService;
  TerminalService * ts;
  const std::string cmdtype;
//  const std::string descr;
public:
 
  ITerminalCommand(std::string _cmdtype)//,std::string & _descr);
    :cmdtype(_cmdtype),ts(0)
  {
  }
  virtual ~ITerminalCommand(){};
  virtual const std::string & GetDescription(void){};
  char operator==(const std::string & _cmd){
    return cmdtype == _cmd;
  }
  
  void Output(const std::string  _string)
  {
    assert(0 != ts);
    ts->Output(_string);
  }
  void Output(CONST char _s[])
  {
    assert(0 != ts);
    ts->Output(_s);
  }
private:  
  void SetTerminalService(TerminalService & _ts)
  {
    ts = &_ts;
  }
protected:
  virtual void ExecuteCommand(std::vector<std::string> & params) = 0;
  
};

#endif //end of __TERMINAL_SERVICE_H__