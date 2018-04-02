#ifndef __LAB9_H__
#define	__LAB9_H__

#include "DriverFactory.h"

#include "System_Manager.h"
#include "TimerManager.h"
#include "serialio.h"
#include "clcd.h"
#include "led.h"

class Lab9App : public SystemManager
{
  TimerManager * tm;
  DriverFactory * driver;
  
  SerialIO      * serial; 
  Clcd          * lcd; 
  Led           * greenLed;

    
public:
  Lab9App();
   
  void Init(void);  
  
};

#endif //end of __LAB9_H__