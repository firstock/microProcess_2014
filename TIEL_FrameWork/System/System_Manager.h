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

#ifndef __SYSTEM_MANAGER_H__
#define	__SYSTEM_MANAGER_H__

//이벤트 드리븐 방식.
//하부의 메세지 교환방식을 추상화하고,
// 임베디드 시스템에서 필요로하는 기본요소를 지원

//단일 테스크 프로그램 모델, 향후 테스크와 RTOS지원예정...
//이벤트 루프
//확장가능...

#include "type.h"
//#include <vector>


class IModule{
public:
  IModule(){}
  virtual ~IModule(){}
  
  virtual void Init(){};
  virtual char Execute(void) = 0;
};

class SystemManager{
  static SystemManager * instance;
 
public:
  
  static SystemManager * Instance(void);
  SystemManager();
  virtual~SystemManager();
  
  virtual void Init(void) = 0;
  void InitModule(void);
  void Run(unsigned char _loop = 1);
  void AddModule(IModule & _m);
  
//virtual void AddTask() = 0;
  virtual void Exit(void){};  
private:  
  void RunTail(void);

  
private:
//  std::vector<IModule *> ms;
  IModule * ms;
};


#endif //end of __SYSTEM_MANAGER_H__