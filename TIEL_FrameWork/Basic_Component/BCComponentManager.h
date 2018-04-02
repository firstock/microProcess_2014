//////////////////////////////////////////////////////////////////////////////////////////
 
// Project description
 
// Author: Yoo Joo-Hyoung (potato97@naver.com)
 
// Site: ccrs.hanyang.ac.kr
 
// Copyright (C) 2013-2013 TIEF(TIEF is Embedded S/W Framework) Project.
 
//
 
//////////////////////////////////////////////////////////////////////////////////////////
//
//    License type: GNU General Public License (GPL)
//      
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __BCCOMPONENTMANAGER_H__
#define	__BCCOMPONENTMANAGER_H__

#include "DriverFactory.h"

#include "TimerManager.h"
#include "serialio.h"
#include "dio.h"
#include "led.h"
#include "adc.h"
#include "pwm.h"

class BCComponentManager
{
static BCComponentManager * Instantce; 
static DriverFactory *Driver;


TimerManager *tm;
SerialIO *serial0;
SerialIO *serial1;
Led *led0;
Led *led1;
public:
  BCComponentManager();
  
//  static BCComponentManager * GetInstance(void);

  TimerManager * CreateTimer(void);
  SerialIO * CreateSerialIO(unsigned char portnum = 0);
  
  enum LED{LED0,LED1,LED2,LED3};
  Led * CreateLed(LED _led);
  
  DIn * CreateDIn();
  DOut * CreateDOut();
  Adc * CreateAdc(void);
  Pwm * CreatePwm(void);
//private:  
  void Init(void);
  
};

BCComponentManager * GetBCComponentManager(void);
#endif //end of __BCCOMPONENTMANAGER_H__