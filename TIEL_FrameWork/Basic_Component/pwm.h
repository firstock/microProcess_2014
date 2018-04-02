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

#ifndef __PWM_H__
#define	__PWM_H__

class Pwm;
class IPwmPort
{
  friend class Pwm;
public:
  IPwmPort(){}
  virtual ~IPwmPort(){}
protected:
  virtual void Run(void) = 0;
  virtual void Stop(void) = 0;
  virtual void SetDuty(unsigned short _du) = 0;
  virtual unsigned char GetResolution() = 0;
  
};

class Pwm
{
  IPwmPort  *ipwm;
  unsigned char resolution;
public:
  Pwm(IPwmPort  *_ipwm);
  virtual ~Pwm();
//  void SetDuty(unsigned float _du); // 1 : 0 ~ 1
  void SetDuty(unsigned short _du); 
//  unsigned short SetFrequency(unsigned short _hz);
  void Run(void);
  void Stop(void);
  
};

#endif //end of __PWM_H__