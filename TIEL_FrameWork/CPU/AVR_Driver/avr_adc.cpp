#include "avr_adc.h"

// Include I/O definition file
#include <ioavr.h>
#include <inavr.h> //_interrupt()
#include <cassert>

volatile unsigned short adc_result;
volatile unsigned char isconv =0;
#pragma vector = ADC_vect
__interrupt void ADC_conv_done(void)
{
  adc_result = ADCL;
  adc_result |= ((unsigned short)ADCH)<<8;
 
  isconv=1;
}

void Avr_adc::SetChannel(unsigned char _ch)
{
  __disable_interrupt();
  ADMUX = (ADMUX & 0xf8) | ( _ch & 0x07);
  __enable_interrupt();  
}

void Avr_adc::SetPrescaler(unsigned char _pre)
{
  __disable_interrupt();
  ADCSR = (ADCSR & 0xf8 )|(_pre & 0x07);
  __enable_interrupt();
}


void Avr_adc::Init(void)
{
  __disable_interrupt();
  ADMUX = 0x00;
  ADCSR = ( 1 << ADEN) | ( 1 << ADFR) |( 1 << ADPS2) |( 1 << ADPS1) |( 1 << ADPS0) ;
  
  ADCSR |= ( 1 << ADIE);
  ADCSR |= ( 1 << ADSC);
  
  __enable_interrupt();
}


Avr_adc::Avr_adc()
{

  Init();
  SetPrescaler(7);
}

Avr_adc::~Avr_adc()
{

}

unsigned char Avr_adc::isConverted(void)
{
  return isconv & 0x01;  
}

unsigned short Avr_adc::GetAdc(void)
{
   unsigned short r;
  
  __disable_interrupt();
   r = adc_result;
   isconv = 0;
   __enable_interrupt();
   
   return r; 
}