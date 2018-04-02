#include "avr_pwm.h"

// Include I/O definition file
#include <ioavr.h>
#include <inavr.h> //_interrupt()
#include <cassert>



Avr_pwm::Avr_pwm(unsigned char _preScaler)
:preScaler(_preScaler)
{

  Init();
//  SetPreScaler(preScaler);
}

Avr_pwm::~Avr_pwm()
{

}

void Avr_pwm::Init(void)
{
  __disable_interrupt();
  DDRB = 1 << DDB4;
TCCR0 = ( 1 << WGM00) | ( 1 << COM01) | ( 1 << COM00) | ( 1 << WGM01);// | ( 1 << CS02); /* Timer0 Fast PWM clk/64 */
 
  __enable_interrupt();  
  
}

void Avr_pwm::SetOcr(unsigned char _ocr)
{
  
  OCR0 = _ocr;  
}

void Avr_pwm::SetPreScaler(unsigned char _s)
{
 assert( 0x07 >= _s);

 TCCR0 = (TCCR0 & 0xf8) | (0x07 & _s);

}

void Avr_pwm::Run(void)
{
 SetPreScaler(preScaler); 
}

void Avr_pwm::Stop(void)
{
  SetPreScaler(0);
}

void Avr_pwm::SetDuty(unsigned short _du)
{
  SetOcr(_du);
}

unsigned char Avr_pwm::GetResolution()
{
  return 8;
}
