
#include "terminal_service.h"
#include "split.h"
#include "build_count.h"
#include <assert.h>


CONST  char  errormsg[]="\nCommand not found.please enter \"help\" command.\n";

TerminalService::TerminalService(unsigned char _defaultParamMax)
:defaultParams(_defaultParamMax)
{

}
void TerminalService::Init(void)
{
//  const std::string lic(clic);
//  Output("\n");
//  Output((const char *)clic);
  
//  Output("\n\n");
//  Output(">> "); 
}

void TerminalService::Input(char _ch)
{
  InputHook(_ch);
  /*
     char str[15];
      sprintf(str,"%x",_ch);
      Output(str);
      return;
  */
  
  static char ctrl =0;
  static unsigned char listpointer=0;
    if(0x1b == _ch)// control char
    {
      ctrl = 1;
      return;
    }
    
    if(0x5b == _ch)
    {
      ctrl++;
      return;
    }    
     if( 2 == ctrl)
    {
      if(0x41 == _ch )//key up
      {
        if(!cmdlist.empty()){
           listpointer++;
           if(cmdlist.size() < listpointer)
           {
             listpointer = 1;
           }
           Output("\r            ");
           Output("\r>> ");
           currCmd = cmdlist[cmdlist.size() - listpointer ];
           Output(currCmd);
           

        }
      }
      


      ctrl = 0;
      return;
    } 

      if( 0x08 == _ch )//backspace
      {
	if(!currCmd.empty())
        {
	  currCmd= std::string(currCmd.begin(),currCmd.end()-1);
          Output("\r>> "+currCmd+" ");
          Output(_ch);        
          return;
        }
      }    

      if('\n' == _ch  || '\r' == _ch  || STRING_SIZE <= currCmd.size()){
        if(!currCmd.empty()){
          cmdlist.push_back(currCmd);
          if(cmdlist.size() > 3)
          {
             cmdlist.erase(cmdlist.begin());
          }
          Input(currCmd);
          currCmd.clear();
          listpointer=1;
        }
        
      Output("\n>> ");
      return;
    }     
   

    if(isprint(_ch) )
    {
      currCmd.push_back(_ch);
      Output(_ch);
    }

     
  
      
  
}

char TerminalService::isprint(char _ch)
{
  if(' ' <= _ch &&  '}' >= _ch)
  {
    return 1;
  }
  
  return 0;
}

void TerminalService::Input(const std::string & _string)
{
  std::vector<std::string> str_split;
  
  unsigned char i;
  
  str_split = split(_string);
  
//  if(str_split.size() == 0){
//    Output("\n>> ");
//    return;
//  }
  if( 0 < str_split.size())
  {
    for( i = 0 ; i < tcs.size() ; i++)
    {
      if(*(tcs[i]) == str_split[0])
      {
        Output("\n");
        tcs[i]->ExecuteCommand(str_split);
        break;
      }
    }
  }
  if(tcs.size() == i)
    Output(errormsg);
  
//  Output("\n>> ");
}

void TerminalService::AddCommand(ITerminalCommand & _tc)  
//void TerminalService::AddCommand(std::shared_ptr<ITerminalCommand>  _tc)
{ 
//  assert(ptcs.size() <=defaultParams);
//  assert( 0 != _tc.get());
//  _tc->SetTerminalService(*this);
//  ptcs.push_back(_tc);
  
  assert(tcs.size() <=defaultParams);  
    _tc.SetTerminalService(*this);
     tcs.push_back(&_tc);
}