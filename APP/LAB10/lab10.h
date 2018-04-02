#ifndef __LAB10_H__
#define	__LAB10_H__
#include "DriverFactory.h"

#include "System_Manager.h"
#include "TimerManager.h"
#include "serialio.h"
#include "clcd.h"
#include "led.h"
#include "adc.h"

class Lab10App : public SystemManager
{
  TimerManager * tm;
  DriverFactory * driver;
  
  SerialIO      * serial; 
  Clcd          * lcd; 
  Led           * greenLed;
  Adc           * adc;
    
public:
  Lab10App();
   
  void Init(void);  
  
};

#endif //end of __LAB10_H__