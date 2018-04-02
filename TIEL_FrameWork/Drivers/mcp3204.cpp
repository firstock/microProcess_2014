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

#include "mcp3204.h"
#include <assert.h>

Mcp3204::Mcp3204(ISpi & _spi)
{
  spi = &_spi;
  
  ch = 0;
}

void Mcp3204::Init(void)
{
  ch = 0;
  Init_Spi();
  Spi_CS_H();
}
void Mcp3204::SetChannel(unsigned char _ch)
{
  assert(0x03 >= _ch);
  
  ch = 0x03 & _ch;  
  
}

unsigned short Mcp3204::GetADC(void)
{
  unsigned short v = 0;
  Spi_CS_H();
  Spi_CS_L();
  spi->WriteByte(0x06);
  v = spi->ReadByte(ch << 6) & 0x0f;
  v <<=8;
  v |= spi->ReadByte();
  Spi_CS_H();
  
  return v & 0xfff;
  
}

unsigned short Mcp3204::GetADC(unsigned char _ch)
{
  SetChannel(_ch);
  return GetADC();
}

