#ifndef __EBIOAPPLICATION_H__
#define	__EBIOAPPLICATION_H__

#include "System_Manager.h"
#include "TerminalAdaptor.h"

#include "cli_command.h"
#include "TimerManager.h"
#include "led.h"
#include "serialio.h"
#include "clcd.h"

#include "Mcp3204.h"
#include "Dac7512.h"
#include "AutoOffTimer.h"

class EBIOApp : public SystemManager
{
  TimerManager  * tm;
  SerialIO      * serial0;
  SerialIO      * serial1;
  TerminalService * term;
  DIn           * photoDin;
  Led           * redLed;
  Led           * blueLed;
  DOut * relay;
  DOut * wcs2702power;
  DOut * zigbeepower;
  DOut * zigbeereset;
  DOut * lcdpower;
  DOut * lcdbacklight;
  DOut * photoDout;
  AutoOffTimer * backlightTimer;

  Mcp3204 * adc;
  Dac7512 * dac;
  Clcd    * lcd;
  
public:
  EBIOApp();
   
  void Init(void);  
  
};

#endif //end of __EBIOAPPLICATION_H__