#include "dio_adaptor.h"

#include <assert.h>
#include <ioavr.h>

#define E02SMB_LED_DDR   DDRD
#define E02SMB_LED_PORT  PORTD
#define E02SMB_LED_PIN   PIND
#define E02SMB_LED_PORT_MASK 0xf0

E02SMBLed::E02SMBLed()
{
  E02SMB_LED_DDR |= E02SMB_LED_PORT_MASK;  
  
  SetPort(0);    
}

void E02SMBLed::SetPort(unsigned char _v)
{
  assert( (E02SMB_LED_DDR & E02SMB_LED_PORT_MASK) == E02SMB_LED_PORT_MASK);
//  assert(0x0f >= _v);
  
  _v = _v & 0x0f;
  
  E02SMB_LED_PORT = ~((E02SMB_LED_PORT & 0x0f) | ( _v  << 4));
  
}

unsigned char E02SMBLed::GetPort(void)
{

  assert( (E02SMB_LED_DDR & E02SMB_LED_PORT_MASK) == E02SMB_LED_PORT_MASK);
  
  return ~( E02SMB_LED_PORT >> 4);
  
}



#define DIGITAL_IN_DDR   DDRG
#define DIGITAL_IN_PORT  PORTG
#define DIGITAL_IN_PIN   PING
#define DIGITAL_IN_PORT_NUM 3

DigialIn::DigialIn(DInEvent & _ev)
:DIn(_ev,50)
{
  DIGITAL_IN_DDR &= ~(1 << DIGITAL_IN_PORT_NUM);   //clear
  
  
  //ISR
}
DigialIn::DigialIn()
{
  DIGITAL_IN_DDR &= ~(1 << DIGITAL_IN_PORT_NUM);   //clear
}

unsigned char DigialIn::GetPort(void)
{
  assert( 0 == ( DIGITAL_IN_DDR & (1 << DIGITAL_IN_PORT_NUM) ));
 
  if(  DIGITAL_IN_PIN & ( 1 << DIGITAL_IN_PORT_NUM ) )
  {
    return 1;
  }
  else
  {
    return 0; 
  }     
  
}
