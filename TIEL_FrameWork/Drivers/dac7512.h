///////////////////////////////////////////////////////////////////////////////////////
 
// Project description
 
// -------------------------------------------
 
// Description: SerialIO Class
 
//
 
// Author: Yoo Joo-Hyoung (potato97@naver.com)
 
// Site: ccrs.hanyang.ac.kr
 
// Copyright (C) 2013-2013 TIEL(TIEL is Embedded S/W library) Project.
 
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

#ifndef __DAC7512_H__
#define	__DAC7512_H__

#include "ispi.h"

//CPU & Board독립적인 코드 
class Dac7512 {
  ISpi * spi;
  unsigned char mode;
    
public:
  enum MODES{ NORMAL, POWERDOWN_1K, POWERDOWN_100K, HIGH_Z};
  
  Dac7512(ISpi & _spi);
  ~Dac7512(void){};
  void Init();
  void SetMode(unsigned char _mode);
  
  void Write(unsigned short _dac12);
  void Write(unsigned short _dac12, unsigned char _mode );
  
protected:
  virtual void Init_Spi(void) = 0;

  virtual void Spi_CS_H(void) = 0;
  virtual void Spi_CS_L(void) = 0;

};



#endif //end of __DAC7512_H__