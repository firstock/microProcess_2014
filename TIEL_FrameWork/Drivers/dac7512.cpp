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

#include "dac7512.h"
#include <assert.h>

Dac7512::Dac7512(ISpi & _spi )
{
  mode = NORMAL;
  spi = &_spi;
}

void Dac7512::Init()
{
  Init_Spi();
  Spi_CS_H();  
}

void Dac7512::SetMode(unsigned char _mode)
{
  assert( 0x03 >= _mode);
  assert( 0x00 <= _mode);
  
  mode =  0x03 & _mode;
  mode <<=4;
}
  
void Dac7512::Write(unsigned short _dac12)
{
  assert(0xfff >=_dac12);
  
  Spi_CS_L();
  spi->WriteByte(mode | (0xf & (_dac12 >> 8)));  
  spi->WriteByte(0xff & _dac12);
  Spi_CS_H();
}

void Dac7512::Write(unsigned short _dac12, unsigned char _mode )
{
  SetMode(_mode);
  Write(_dac12);  
}