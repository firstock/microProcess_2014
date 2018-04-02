#include "System_Manager.h"
#include "avr_common.h"
#include <ioavr.h>


class testMod:public IModule
{
public:

  
  void Init()
  {
    DDRB =  1 << 1;
  }
  
  char Execute(void)
  {
    PORTB ^= 2;
    avr_delay_ms(500);
    
    return 0;
  }
};

testMod tmod;

class testApp: public SystemManager
{
public:
  testApp()
  {
    
  }
   
  void Init(void)
  {
    AddModule(tmod);
  }
  
  
  
};


testApp MyApp;