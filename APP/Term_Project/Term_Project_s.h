#ifndef __TERM_PROJECT_S_H__
#define	__TERM_PROJECT_S_H__
#include "DriverFactory.h"

#include "System_Manager.h"
#include "TimerManager.h"
#include "serialio.h"
#include "clcd.h"
#include "led.h"
#include "adc.h"
#include "pwm.h"

class Term_Project_s : public SystemManager
{
  TimerManager * tm;
  DriverFactory * driver;
  
  SerialIO      * serial; 
  Clcd          * lcd; 
  Led           * greenLed;
  Adc           * adc;
  Pwm           * pwm;
  DIn           * swDin;
    
public:
  Term_Project_s();
   
  void Init(void);  
  
};

#endif //end of __TERM_PROJECT_S_H__