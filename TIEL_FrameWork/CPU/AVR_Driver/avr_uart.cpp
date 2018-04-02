///////////////////////////////////////////////////////////////////////////////////////
 
// Project description
 
// -------------------------------------------
 
// Description: avr_uart Class
 
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

#include "avr_uart.h"
#include "avr_common.h"
#include <ioavr.h>
#include <inavr.h>

static Avr_uart0 * uart0 = 0;

#define UDRIE 5

#if defined(__ATmega128__)
#pragma vector = USART0_RXC_vect
#endif

#if defined(__ATmega164P__) | defined(__ATmega164PA__) | defined(__ATmega324P__)
#pragma vector = USART0_RX_vect // for atmega164/324
#endif
__interrupt void usart0_rxc(void)
{
  if(0 != uart0)
    uart0->SendrxBuff(UDR0);
}

#pragma vector = USART0_UDRE_vect // for atmega164
__interrupt void usart0_txc(void)
{
  unsigned char t;
  
  if(0 != uart0){
    if(uart0->SendtxBuff(t))
    {
      UDR0 = t;
    }
    else
    {
      UCSR0B &= ~(1 << UDRIE);
    }
  }
}

Avr_uart0::Avr_uart0()
{
  Init();
  uart0 = this;
}

void Avr_uart0::Init(void)
{
 // unsigned long baud = 38400;  
  /*================================
    BAUD = F_CPU / (16 * (UBRR + 1) )
    UBRR = (F_CPU / (16L*baud)) - 1
  ==================================*/
  
  __disable_interrupt();
  
   baud = (F_CPU / (16L*baud)) - 1;    
// buad 로 인자로 받아온 buad로 초기화..
      
  //uart1 register baud setting
   UBRR0H = (unsigned char)(baud>>8);            // 클경우 상위 8bit만 잘리기에..
   UBRR0L = (unsigned char)(baud);
  
   DDRD|= 1 << 1;     
   
  
   UCSR0A=0x00;
  // UCSR0B=0x18;   // Receive enable, Transmitte enable
  // UCSR0C=0x06;   // 비동기 방식, No parity bit, 1 stop bit   

//   UBRR0H=0x00;
//   UBRR0L=0x67;   // 16MHz에서 9600 bps  (10진수 103)
    
    // UCSR0B 설정
    // bit7:수신완료 인터럽허용 , 
    // bit6:송신완료 인터럽허용, 
    // bit4:uart rx enable, 
    // bit3: uart tx enable
    // bit2 : sendding size setting UCSR0C 같이 설정 => 0 : 8bit
    // 11011000 

//    UCSR0B = (1<<7) | (1<<6) | (1<<4) | (1<<3) | (0<<2) ; // 00011000 
    UCSR0B = (1<<7) | (1<<4) | (1<<3) | (0<<2) ; // 00011000 
  
    // UCSR0C 설정
    // bit6 : synchro setting => 0: dissynchro mode
    // bit5,bit4 : parity bit setting => 00 : not used
    // bit3 : stop bit setting => 0 : stop bit 2 use
    // bit2,bit1 : data sendding size => 11 : 8bit
    // 00001010
        
    UCSR0C = (0<<3) | (1<<2) | (1<<1) | (0<<5) | (0<<4);
  
  __enable_interrupt();
}

void Avr_uart0::Run(void)
{
  //assert()
  
  
}

void Avr_uart0::SendTxEvent(void)
{
  
  UCSR0B |= (1 << UDRIE);
}

unsigned char Avr_uart0::Write(unsigned char _data)
{
//  assert()
  
  // UCSRnA 
  // bit5 : 송신 버퍼가 비어서 데이터를 받을 준비되면 1
//   while (!(UCSR0A & 0x20))
//      ;    //wait xmit ready

   if(UCSR0A & 0x20)
   {
     UDR0 = (unsigned char) _data;
     return 1;
   }
   else
   {
     return 0;
   }

  
  
}