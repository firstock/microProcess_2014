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

#include "System_Manager.h"
#include <assert.h>


SystemManager * SystemManager::instance = 0;
SystemManager::SystemManager()
{
  assert(0 == instance);
  if(0 == instance  )
  {
    instance = this;
  }
  
}

SystemManager::~SystemManager()
{
  
}

SystemManager * SystemManager::Instance(void)
{

  if(0 != instance  )
  {
    return instance;
  }
   
  return 0;
}

void SystemManager::InitModule(void)
{
//  unsigned char idx;
  
//    for(idx = 0 ; idx < ms.size(); idx++)
//    {
//      ms[idx]->Init();
//    }
  ms->Init();
}

void SystemManager::Run(unsigned char _loop)
{
  unsigned char idx;
  
  while(_loop)
  {
//    for(idx = 0 ; idx < ms.size(); idx++)
//    {
//      ms[idx]->Execute();

    //      if(ms[idx]->Execute())
    //      {
    //        idx = 0;
    //      }
  
//    }  
    
    ms->Execute();

    RunTail();//wdt kick,슬립모드 진입
    

  
  }
  
}

void SystemManager::AddModule(IModule & _m)
{
//  ms.push_back(&_m);  
  ms = &_m;
}
  

void SystemManager::RunTail(void)
{
  
  
}

