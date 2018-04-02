
#include "cli_command.h"


CONST  char  HELP_GETADC[] =
                      "-----------------------\n"
                      "usage: getadc channel [count]\n"
                      "\nOption:\n"
                      "       channel = 0 : Battery Voltage.(fixed 1 time)\n"
                      "       channel = 1 : wcs2702 Voltage\n"
                      "\n       count = 1 ~ 9 : It set getting times.(default 1)\n"
                      "\n   ex) getadc 0\n"
                      "   ex) getadc 0 5\n";
CONST  char  HELP_PUTDAC[] =
                      "-----------------------\n"
                      "usage: putdac value\n"
                      "\nOption:\n"
                      "       value = 0 ~ 4095\n"
                      "\n   ex) putdac 1256\n";
CONST  char  HELP_POWER[] =
                      "-----------------------\n"                        
                      "usage: power device on/off\n"
                      "\nOption:\n"
                      "       device = 0 : power on wcs2702 in  10 sec.\n"
                      "       device = 1 : power on relay in  10 sec.\n"
                      "       device = 2 : power on lcd\n"
                      "       device = 3 : power on lcd backLigth in 5 sec.\n"
                      "       device = 4 : power on ZigBee\n"
                      "       device = 5 : resetting ZigBee in 100ms.\n"
                      "\n       on/off = 0 : OFF\n"
                      "       on/off = 1 : ON\n"
                      "\n   ex) power 5 1\n";
CONST  char  HELP_POWER1[] =
                      "-----------------------\n"                        
                      "usage: power device on/off [sec/ms]\n"
                      "\nOption:\n"
                      "       device = 0 : power on wcs2702 in a few sec(default 10 sec. max 60 sec).\n"
                      "       device = 1 : power on relay in a few sec(default 10 sec. max 60 sec).\n"
                      "       device = 2 : power on lcd\n"
                      "       device = 3 : power on lcd backLigth in 5 sec(fixed 5 sec).\n"
                      "       device = 4 : power on ZigBee\n"
                      "       device = 5 : resetting ZigBee in 100ms(default 100ms. max 1000 ms).\n"
                      "       device = 6 : Digtal output(Photo coupler)\n"
                      "\n       on/off = 0 : OFF\n"
                      "       on/off = 1 : ON\n"
                      "\n   ex) power 5 1\n"
                      "   ex) power 0 1 30\n"
                      "   ex) power 6 1 900\n";
CONST  char  HELP_LEDBLINK[] =
                      "-----------------------\n"
                      "usage: ledblink led [count]\n"
                      "\nOption:\n"
                      "       led = 0 : red\n"
                      "       led = 1 : blue\n"
                      "\n       count = 1 ~ 9 : It set blinking times.(default 1)\n"
                      "\n   ex) ledblink 1\n"
                      "   ex) ledblink 1 5\n";
CONST  char  HELP_GETDI[] =
                      "-----------------------\n"
                      "usage: getdi [count]\n"
                      "\nOption:\n"
                      "       count = 1 ~ 9 : It set getting times.(default 1)\n"
                      "\n   ex) getdi\n"
                      "   ex) getdi 3\n";

                      


 
Helpcmd::Helpcmd()
:ITerminalCommand((const char *)"help")
{
  
}

  
void Helpcmd::ExecuteCommand(std::vector<std::string> & params)
{
  Output(HELP_GETADC);
  Output(HELP_PUTDAC);
  Output(HELP_POWER);
  Output(HELP_LEDBLINK);
  Output(HELP_GETDI);
}
  


CONST  char  RUNCMD[]="run";

PutDacCmd::PutDacCmd():ITerminalCommand((const char *)"putdac")
{
    
}
  
void PutDacCmd::ExecuteCommand(std::vector<std::string> & params)  
{
    
      unsigned int v;

      if(params.size() < 2){
          Output(HELP_PUTDAC);
          return;
      }  
      
      v = atoi(&(params[1][0]));
      
      if( 0xfff < v)
      {
          Output(HELP_PUTDAC);
          return;
      }
        
        
      v &= 0xfff;
      dac->Write(v);
        


}
  
void PutDacCmd::SetDac(Dac7512 * _dac)
{
    assert( 0 != _dac);
    dac = _dac;
}  


PowerCmd::PowerCmd():ITerminalCommand((const char *)"power")
{
    
}
  
void PowerCmd::ExecuteCommand(std::vector<std::string> & params)  
{
    
    assert( 0 != wcs2702pow);
    assert( 0 != relaypow);

    if(0 == wcs2702pow)
      return;
    if(0 == relaypow)
      return;
  
    unsigned char cnt,opt1,opt2;
    
    char    str[20];
  
      if(params.size() < 3 ){
          Output(HELP_POWER);
          return;
      }
      
      opt1 = atoi(&(params[1][0]));
      opt2 = atoi(&(params[2][0]));
      
      if(0 > opt1 ||  5 < opt1){
          Output(HELP_POWER);
          return;
      }      
      
      if(!( 0 == opt2 ||  1 == opt2 ))
      {
          Output(HELP_POWER);
          return;
      }

      switch(opt1)
      {
        case 0:
          if(0 == opt2)
            wcs2702pow->Off();
          else
            wcs2702pow->On();
          break;

        case 1:
          if(0 == opt2)
            relaypow->Off();
          else
            relaypow->On();
          break;
          
        case 2:
            lcdpow->Set(opt2);
          break;   
          
        case 3:
          if(0 == opt2)
            backlightpow->Off();
          else
            backlightpow->On();
          break;
          
        case 4:
          zigbeepow->Set(opt2);
          break;
        
        case 5: 
          if(0 == opt2)
            zigbeerst->Off();
          else
            zigbeerst->On();
          break;
          
        default:          
        
      }
      
 
}
void PowerCmd::SetDevice(TimerManager  * _tm, DOut * _wcs2702pow, DOut * _relaypow,DOut * _lcdpow,DOut * _backlightpow,DOut * _zigbeepower,DOut * _zigbeerst)
{
  tm = _tm;
  
  static AutoOffTimer   wcs(10000,_wcs2702pow);
  wcs2702pow = &wcs;
  tm->AddEvent(wcs2702pow);
  
  static AutoOffTimer   rel(10000,_relaypow);
  relaypow = &rel;
  tm->AddEvent(relaypow);
  
  lcdpow = _lcdpow;
  
  static AutoOffTimer   bl(5000,_backlightpow);
  backlightpow = &bl;
  tm->AddEvent(backlightpow);
  
  zigbeepow=_zigbeepower;
  
  static AutoOffTimer zigrst(100,_zigbeerst);
  zigbeerst = &zigrst;
  tm->AddEvent(zigbeerst);
    
}



LedBlinkCmd::LedBlinkCmd():ITerminalCommand((const char *)"ledblink")
{
    
}
  
void LedBlinkCmd::ExecuteCommand(std::vector<std::string> & params)  
{
    
    unsigned char opt1,opt2;
    
  
  
      if(params.size() < 2 ){
          Output(HELP_LEDBLINK);
          return;
      }
      
      opt1 = atoi(&(params[1][0]));
      
      opt2 = 1;
      if(params.size() == 3  ){
        opt2 = atoi(&(params[2][0]));
      }
      
      if(0 > opt1 ||  1 < opt1){
          Output(HELP_LEDBLINK);
          return;
      }      
      
      if(!( 1 <= opt2 &&  9 >= opt2 ))
      {
          Output(HELP_LEDBLINK);
          return;
      }
      
      switch(opt1)
      {
        
        case 0:
          red->Blink(opt2);
          break;
          
        case 1:
          blue->Blink(opt2);
          break;
          
          
        default:
        
      }


}

void LedBlinkCmd::SetLed(Led * _red, Led * _blue)
{
  red = _red;
  blue = _blue;
}

CONST char ONMSG[]="On(1)\n";
CONST char OFFMSG[]="Off(0)\n";


GetdiCmd::GetdiCmd():ITerminalCommand((const char *)"getdi")
{
    
}
  
void GetdiCmd::ExecuteCommand(std::vector<std::string> & params)  
{
    
    unsigned char opt1;

      opt1 = 1;
      if(params.size() == 2)
      {
        opt1 = atoi(&(params[1][0]));
      }
      

      if(!( 1 <= opt1 &&  9 >= opt1 ))
      {
          Output(HELP_GETDI);
          return;
      }
      
      cnt.Run(opt1);
  
}

void GetdiCmd::SetDevice(DIn * _photoin,SerialIO *_sio)
{
  photoin = _photoin;
  sio = _sio;
  cnt.SetDevice(_photoin,_sio);
  
}

CONST  char  RUNADCCMD[]="getadc";
CONST  char  BATCMSG[]="Battery";
CONST  char  WCSCMSG[]="wcs2702";
#define RESOLUTION 0.8056640625f //mV
#define SCALE 0.25373134328358208955223880597015f
  RunAdc::RunAdc():ITerminalCommand((const char *)"getadc")
  {
    
  }
  
  void RunAdc::ExecuteCommand(std::vector<std::string> & params)  
  {
    
    assert( 0 != adc);
    assert( 0 != lcd);
    if(0 == adc)
      return;
    if(0 == lcd)
      return;
    
    unsigned char cnt;
    
    char    str[20];
  
      if(params.size() < 2){
          Output(HELP_GETADC);
          return;
      }
      
      cnt = 1;
      if(params.size() == 3){
        cnt = atoi(&(params[2][0]));
        if( 0 == cnt || 9 < cnt)
          cnt = 1;
      }
      
      if(params[1] == "0")
      {
        
        sprintf(str,"[%2.4f]V",((((float)adc->GetADC(1))*RESOLUTION)/SCALE)*0.001); //bat_vol
        lcd->Write(Clcd::LINE1,BATCMSG);
        lcd->Write(Clcd::LINE2,str);
 //       Output((char *)BATCMSG);
        Output(str);
        
        return;
        
      }
      if(params[1] == "1")
      {
        

        dacadc->Run(cnt);

        return;
      } 
      
      Output(HELP_GETADC);

 
  }
  
  void RunAdc::SetDevice(Mcp3204 * _adc,DacAdc *_dacadc, Clcd    * _lcd)
  {
    adc = _adc;
    lcd = _lcd;
    dacadc = _dacadc;
  }  


CONST  char  SHOWCCMD[]="show";

  Showcmd::Showcmd():ITerminalCommand((const char*)"show")
  {
    
  }
  
  void Showcmd::ExecuteCommand(std::vector<std::string> & params)  
  {

    sio->Write(gnu_lic);
  }
  
  void Showcmd::SetSerialIO(SerialIO & _sio)
  {
    sio = &_sio;
  }  

CONST  char  RELAYCCMD[]="relay";
  Relaycmd::Relaycmd():ITerminalCommand((const char*)"relay")
  {
    
  }
  
  void Relaycmd::ExecuteCommand(std::vector<std::string> & params)  
  {
    if(params[1] == "0")
    {
      relay->Set(0);
    }
    
    if(params[1] == "1")
    {
      relay->Set(1);      
    }

  }
  
  void Relaycmd::SetRelay(DOut  & _dio)
  {
    relay = & _dio;
  }




  CLIBuilder::CLIBuilder(TerminalService & _tc):tc(&_tc)
  {
    tc->AddCommand(helpcmd);
  
  }
  
  CLIBuilder::~CLIBuilder()
  {
  
  }
  
  void CLIBuilder::AddShowCmd(SerialIO & _sio)
  {
    showcmd.SetSerialIO(_sio);
    tc->AddCommand(showcmd);
  }
  
  void CLIBuilder::AddRelayCmd(DOut  & _dio)
  {
//    relaycmd.SetRelay(_dio); 
//   tc->AddCommand(relaycmd);
  }
  
void CLIBuilder::AddPutdacCmd(Dac7512 * _dac)  
{
    putdac.SetDac(_dac); 
   tc->AddCommand(putdac);
}

void CLIBuilder::AddPowerCmd(TimerManager  * _tm, DOut * _wcs2702pow, DOut * _relaypow,DOut * _lcdpow, DOut * _backlightpow,DOut * _zigbeepower,DOut * _zigbeerst)
{
  powercmd.SetDevice( _tm,_wcs2702pow,_relaypow,_lcdpow, _backlightpow,_zigbeepower,_zigbeerst); 
  tc->AddCommand(powercmd);
  
}
  void CLIBuilder::AddRunAdc(Mcp3204 * _adc ,DacAdc *_dacadc,Clcd    * _lcd)
  {
    runadc.SetDevice( _adc,_dacadc, _lcd);
    tc->AddCommand(runadc);
  }
    
  void CLIBuilder::AddLedCmd(Led * _red, Led * _blue)
    {
      ledcmd.SetLed(_red,_blue);
      tc->AddCommand(ledcmd);
    }
    
    void CLIBuilder::AddGetDinCmd(TimerManager * _tm,DIn * _photoin,SerialIO *_sio)
    {
      getdicmd.SetDevice(_photoin, _sio);
      tc->AddCommand(getdicmd);
      _tm->AddEvent(&getdicmd.cnt);
    }
 /* 
  void AddDefaultCLICommand(void)
  {
    
    
  } 
  */
