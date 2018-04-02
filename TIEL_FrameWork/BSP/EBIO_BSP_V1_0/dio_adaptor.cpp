#include "dio_adaptor.h"

#include <assert.h>
#include <ioavr.h>

#define RELAY_DDR DDRB
#define RELAY_PORT PORTB
#define RELAY_PIN   PINB
#define RELAY_PORT_NUM 2
#define RELAY_ON()  (RELAY_PORT |= 1 << RELAY_PORT_NUM)
#define RELAY_OFF()  (RELAY_PORT &=  ~(1 << RELAY_PORT_NUM) )

EBIO_Relay::EBIO_Relay()
{
  RELAY_DDR |= 1 << RELAY_PORT_NUM;  
  
  SetPort(0);
}


void EBIO_Relay::SetPort(unsigned char _v)
{
  
  assert( (1 << RELAY_PORT_NUM) & RELAY_DDR);
  assert(0x01 >= _v);
  
  if(_v)
  {
    RELAY_ON();
  }
  else
  {
    RELAY_OFF(); 
  }
    
  
}

unsigned char EBIO_Relay::GetPort(void)
{

  assert( (1 << RELAY_PORT_NUM) & RELAY_DDR);
  
  if(  RELAY_PIN & ( 1 << RELAY_PORT_NUM ) )
  {
    return 1;
  }
  else
  {
    return 0; 
  }
}



#define WCS2702_DDR DDRD
#define WCS2702_PORT PORTD
#define WCS2702_PIN   PIND
#define WCS2702_PORT_NUM 4
#define WCS2702_OFF()  (WCS2702_PORT |= 1 << WCS2702_PORT_NUM)
#define WCS2702_ON()  (WCS2702_PORT &=  ~(1 << WCS2702_PORT_NUM) )
  
WCS2702POW::WCS2702POW()
{

  WCS2702_DDR |= 1 << WCS2702_PORT_NUM;  
  
  SetPort(0);  
}

void WCS2702POW::SetPort(unsigned char _v)
{
  assert( (1 << WCS2702_PORT_NUM) & WCS2702_DDR);
  assert(0x01 >= _v);
  
  if(_v)
  {
    WCS2702_ON();
  }
  else
  {
    WCS2702_OFF(); 
  }  
}
  
unsigned char WCS2702POW::GetPort(void)
{
  assert( (1 << WCS2702_PORT_NUM) & WCS2702_DDR);
  
  if(  WCS2702_PIN & ( 1 << WCS2702_PORT_NUM ) )
  {
    return 1;
  }
  else
  {
    return 0; 
  }  
}

#define ZIGBEE_DDR DDRD
#define ZIGBEE_PORT PORTD
#define ZIGBEE_PIN   PIND
#define ZIGBEE_PORT_NUM 6
#define ZIGBEE_ON()  (ZIGBEE_PORT |= 1 << ZIGBEE_PORT_NUM)
#define ZIGBEE_OFF()  (ZIGBEE_PORT &=  ~(1 << ZIGBEE_PORT_NUM) )

ZigBeePOW::ZigBeePOW()
{
  ZIGBEE_DDR |= 1 << ZIGBEE_PORT_NUM;  
  
  SetPort(0);  
}


void ZigBeePOW::SetPort(unsigned char _v)
{
  assert( (1 << ZIGBEE_PORT_NUM) & ZIGBEE_DDR);
  assert(0x01 >= _v);
  
  if(_v)
  {
    ZIGBEE_OFF();
  }
  else
  {
    ZIGBEE_ON();
  }    
}

unsigned char ZigBeePOW::GetPort(void)
{
  assert( (1 << ZIGBEE_PORT_NUM) & ZIGBEE_DDR);
  
  if(  ZIGBEE_PIN & ( 1 << ZIGBEE_PORT_NUM ) )
  {
    return 1;
  }
  else
  {
    return 0; 
  }    
  
}


#define ZIGBEE_RST_DDR DDRD
#define ZIGBEE_RST_PORT PORTD
#define ZIGBEE_RST_PIN   PIND
#define ZIGBEE_RST_PORT_NUM 7
#define ZIGBEE_RST_ON()  (ZIGBEE_RST_PORT |= 1 << ZIGBEE_RST_PORT_NUM)
#define ZIGBEE_RST_OFF()  (ZIGBEE_RST_PORT &=  ~(1 << ZIGBEE_RST_PORT_NUM) )

ZigBeeRST::ZigBeeRST()
{
  ZIGBEE_RST_DDR |= 1 << ZIGBEE_RST_PORT_NUM;  
  
  SetPort(0);  
}


void ZigBeeRST::SetPort(unsigned char _v)
{
  assert( (1 << ZIGBEE_RST_PORT_NUM) & ZIGBEE_RST_DDR);
  assert(0x01 >= _v);
  
  if(_v)
  {
    ZIGBEE_RST_OFF();
  }
  else
  {
     ZIGBEE_RST_ON();
  }   
}


unsigned char ZigBeeRST::GetPort(void)
{
  assert( (1 << ZIGBEE_RST_PORT_NUM) & ZIGBEE_RST_DDR);
  
  if(  ZIGBEE_RST_PIN & ( 1 << ZIGBEE_RST_PORT_NUM ) )
  {
    return 1;
  }
  else
  {
    return 0; 
  }    
}


#define SUBBOARD_POW_DDR DDRA
#define SUBBOARD_POW_PORT PORTA
#define SUBBOARD_POW_PIN   PINA
#define SUBBOARD_POW_PORT_NUM 7
#define SUBBOARD_POW_OFF()  (SUBBOARD_POW_PORT |= 1 << SUBBOARD_POW_PORT_NUM)
#define SUBBOARD_POW_ON()  (SUBBOARD_POW_PORT &=  ~(1 << SUBBOARD_POW_PORT_NUM) )

#define LCD_D7_H()  (PORTC |= (1 << 0))  
#define LCD_D7_L()  (PORTC &= ~(1 << 0))  
#define LCD_D6_H()  (PORTC |= (1 << 1))  
#define LCD_D6_L()  (PORTC &= ~(1 << 1))  
#define LCD_D5_H()  (PORTA |= (1 << 2))  
#define LCD_D5_L()  (PORTA &= ~(1 << 2))  
#define LCD_D4_H()  (PORTA |= (1 << 3))  
#define LCD_D4_L()  (PORTA &= ~(1 << 3)) 

LcdPOW::LcdPOW()
{
  SUBBOARD_POW_DDR |= 1 << SUBBOARD_POW_PORT_NUM;  
  
  SetPort(0);   
}


void LcdPOW::SetPort(unsigned char _v)
{
  assert( (1 << SUBBOARD_POW_PORT_NUM) & SUBBOARD_POW_DDR);
  assert(0x01 >= _v);
  
  if(_v)
  {
    SUBBOARD_POW_ON();
  }
  else
  {
    SUBBOARD_POW_OFF();
    LCD_D7_L();
    LCD_D6_L();
    LCD_D5_L();
    LCD_D4_L();
  }      
  
}

unsigned char LcdPOW::GetPort(void)
{
  assert( (1 << SUBBOARD_POW_PORT_NUM) & SUBBOARD_POW_DDR);
  
  if(  SUBBOARD_POW_PIN & ( 1 << SUBBOARD_POW_PORT_NUM ) )
  {
    return 1;
  }
  else
  {
    return 0; 
  }   
}


#define LCD_BACKLIGHTP_DDR   DDRA
#define LCD_BACKLIGHTP_PORT  PORTA
#define LCD_BACKLIGHTP_PIN   PINA
#define LCD_BACKLIGHTP_PORT_NUM 0
#define LCD_BACKLIGHTP_ON()  (LCD_BACKLIGHTP_PORT |= 1 << LCD_BACKLIGHTP_PORT_NUM)
#define LCD_BACKLIGHTP_OFF()  (LCD_BACKLIGHTP_PORT &=  ~(1 << LCD_BACKLIGHTP_PORT_NUM) )


#define LCD_BACKLIGHTM_DDR   DDRA
#define LCD_BACKLIGHTM_PORT  PORTA
#define LCD_BACKLIGHTM_PIN   PINA
#define LCD_BACKLIGHTM_PORT_NUM 1
#define LCD_BACKLIGHTM_ON()  (LCD_BACKLIGHTM_PORT |= 1 << LCD_BACKLIGHTM_PORT_NUM)
#define LCD_BACKLIGHTM_OFF()  (LCD_BACKLIGHTM_PORT &=  ~(1 << LCD_BACKLIGHTM_PORT_NUM) )

LcdBackLight::LcdBackLight()
{
  LCD_BACKLIGHTP_DDR |= 1 << LCD_BACKLIGHTP_PORT_NUM;  
  LCD_BACKLIGHTM_DDR |= 1 << LCD_BACKLIGHTM_PORT_NUM;
  
  SetPort(0);    
}


void LcdBackLight::SetPort(unsigned char _v)
{
  assert( (1 << LCD_BACKLIGHTP_PORT_NUM) & LCD_BACKLIGHTP_DDR);
  assert( (1 << LCD_BACKLIGHTM_PORT_NUM) & LCD_BACKLIGHTM_DDR);
  assert(0x01 >= _v);

LCD_BACKLIGHTM_OFF();  
  if(_v)
  {
    LCD_BACKLIGHTP_ON();
  }
  else
  {
    LCD_BACKLIGHTP_OFF(); 
  }      
    
}

unsigned char LcdBackLight::GetPort(void)
{

  assert( (1 << LCD_BACKLIGHTP_PORT_NUM) & LCD_BACKLIGHTP_DDR);
  assert( (1 << LCD_BACKLIGHTM_PORT_NUM) & LCD_BACKLIGHTM_DDR);  
  
  if(  LCD_BACKLIGHTP_PIN & ( 1 << LCD_BACKLIGHTP_PORT_NUM ) )
  {
    return 1;
  }
  else
  {
    return 0; 
  }   
  
}



#define DIGITAL_IN_DDR   DDRC
#define DIGITAL_IN_PORT  PORTC
#define DIGITAL_IN_PIN   PINC
#define DIGITAL_IN_PORT_NUM 6
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
  assert( (1 << DIGITAL_IN_PORT_NUM) & DIGITAL_IN_DDR);
 
  if(  DIGITAL_IN_PIN & ( 1 << DIGITAL_IN_PORT_NUM ) )
  {
    return 1;
  }
  else
  {
    return 0; 
  }     
  
}



#define DIGITAL_OUT_DDR   DDRC
#define DIGITAL_OUT_PORT  PORTC
#define DIGITAL_OUT_PIN   PINC
#define DIGITAL_OUT_PORT_NUM 7
#define DIGITAL_OUT_ON()    (DIGITAL_OUT_PORT |= 1 << DIGITAL_OUT_PORT_NUM)
#define DIGITAL_OUT_OFF()   (DIGITAL_OUT_PORT &=  ~(1 << DIGITAL_OUT_PORT_NUM) )
DigialOut::DigialOut()
{
  DIGITAL_OUT_DDR |= 1 << DIGITAL_OUT_PORT_NUM;  
  
  SetPort(0);    
}

void DigialOut::SetPort(unsigned char _v)
{
  assert( (1 << DIGITAL_OUT_PORT_NUM) & DIGITAL_OUT_DDR);
  assert(0x01 >= _v);
  
  if(_v)
  {
    DIGITAL_OUT_ON();
  }
  else
  {
    DIGITAL_OUT_OFF(); 
  }    
}

unsigned char DigialOut::GetPort(void)
{

  assert( (1 << DIGITAL_OUT_PORT_NUM) & DIGITAL_OUT_DDR);
  
  if(  DIGITAL_OUT_PIN & ( 1 << DIGITAL_OUT_PORT_NUM ) )
  {
    return 1;
  }
  else
  {
    return 0; 
  }     
  
}





EBIOLedRed::EBIOLedRed()
{
    DDRB |= 1 | 1<< 1;
}


void EBIOLedRed::SetPort(unsigned char _v)
{ 
  if(_v)
  {
    PORTB |= 1;
  }
  else
  {
    PORTB &= ~1;
  }
}

unsigned char EBIOLedRed::GetPort(void)
{
  if(  PINB & 1 )
  {
    return 1;
  }
  else
  {
    return 0; 
  }     
}



EBIOLedBlue::EBIOLedBlue()
{
    DDRB |= 1 | 1<< 1;
}


void EBIOLedBlue::SetPort(unsigned char _v)
{
  if(_v)
  {
    PORTB |= 2;
  }
  else
  {
    PORTB &= ~2;
  }
}

unsigned char EBIOLedBlue::GetPort(void)
{
  if(  PINB & 2 )
  {
    return 1;
  }
  else
  {
    return 0; 
  }  
}
