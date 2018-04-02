#ifndef __TESTAPPLICATION_H__
#define	__TESTAPPLICATION_H__

#include "System_Manager.h"
#include "TimerManager.h"
#include "led.h"

class myApp : public SystemManager
{
  TimerManager * tm;
  
  Led           * greenLed;

    
public:
  myApp();
   
  void Init(void);  
  
};

#endif //end of __TESTAPPLICATION_H__