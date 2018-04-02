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

#ifndef __DRIVERFACTORY_H__
#define	__DRIVERFACTORY_H__

#include "TimerManager.h"
#include "serialio.h"
#include "ispi.h"
#include "dio.h"
#include "led.h"
#include "clcd.h"
#include "adc.h"
#include "pwm.h"

//추상화 해야함.
#include "dac7512.h"
#include "mcp3204.h"

#include <assert.h>

//확장할 수 있는 다른 메커니즘 필요.

class DriverFactory
{
  static DriverFactory * instance;
public:
  DriverFactory()
  {
    assert(0 == instance);
    if( 0 == instance )
    {
      instance = this;
    }

  }
  
//  static DriverFactory * GetInstance()
//  {
//    return instance;
//  }
  
  virtual ITimer * CreateTimer() { return 0;};
  virtual ISerialPort * CreateUart() { return 0;};
  virtual ISpi * CreateSPI() { return 0;};
  virtual DIn * CreateDIn() { return 0;};
  virtual DOut * CreateDOut(char * _str) { return 0;};
  virtual Led * CreateLed(unsigned char _led) { return 0;};

  
  virtual Clcd * CreateClcd() { return 0;};
  CreateWatchDog();
 
  virtual Dac7512 * CreateDac7512() { return 0;};
  
  virtual Mcp3204 * CreateMcp3204() { return 0;};
  
  virtual IAdcPort * CreateAdc(void) { return 0;};
  
  virtual IPwmPort * CreatePwm(void) { return 0;};

};

DriverFactory * GetDriverFactory(void);
#endif //end of __DRIVERFACTORY_H__