#ifndef __USERAPPLICATION_H__
#define	__USERAPPLICATION_H__

#include "System_Manager.h"
#include "TimerManager.h"
#include "led.h"
#include "clcd.h"

class myApp : public SystemManager
{
  TimerManager * tm;
  Clcd         * lcd;

    
public:
  myApp();
   
  void Init(void);  
  
};

#endif //end of __USERAPPLICATION_H__