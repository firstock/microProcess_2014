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

#include "pwm.h"
#include <cassert>

Pwm::Pwm(IPwmPort  *_ipwm)
{
  assert( 0 != _ipwm);
  
  ipwm = _ipwm;
}

Pwm::~Pwm()
{
  
}

void Pwm::SetDuty(unsigned short _du)
{
  assert( 0 != ipwm);
  unsigned char r;
  
  r = ipwm->GetResolution();
  
  assert(8 == r || 16 == r);
  
  ipwm->SetDuty(_du  );
  
  Run();
}
//  unsigned short SetFrequency(unsigned short _hz);

void Pwm::Run(void)
{
  assert( 0 != ipwm);
  ipwm->Run();
}

void Pwm::Stop(void)
{
  assert( 0 != ipwm);
  
  ipwm->Stop();
  
}