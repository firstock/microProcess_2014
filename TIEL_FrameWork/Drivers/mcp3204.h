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

#ifndef __MCP3204_H__
#define	__MCP3204_H__

#include "ispi.h"

//CPU & Board독립적인 코드 
class Mcp3204
{
  unsigned char ch;
  ISpi * spi;  
public:
  Mcp3204(ISpi & _spi);
  void SetChannel(unsigned char _ch);
  unsigned short GetADC(void);
  unsigned short GetADC(unsigned char _ch);
  void Init(void);
 protected:
  virtual void Init_Spi(void) = 0;

  virtual void Spi_CS_H(void) = 0;
  virtual void Spi_CS_L(void) = 0; 
};


#endif //end of __MCP3204_H__