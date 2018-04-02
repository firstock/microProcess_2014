#ifndef __TESTSWAPPLICATION_H__
#define	__TESTSWAPPLICATION_H__

#include "System_Manager.h"
#include "TimerManager.h"


#include "DriverFactory.h"
#include "led.h"

class myApp : public SystemManager
{
  DriverFactory *driver;
  
  TimerManager * tm;
  DIn           * swDin;
  Led           * led0;

    
public:
  myApp();
   
  void Init(void);  
  
};

#endif //end of __TESTSWAPPLICATION_H__