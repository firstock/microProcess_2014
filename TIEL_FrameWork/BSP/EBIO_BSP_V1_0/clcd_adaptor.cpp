#include "clcd_adaptor.h"
#include "avr_common.h"
#include <ioavr.h>
#include <assert.h>

#define DDR_LCD         DDRA
#define PORT_LCD       PORTA
#define LCD_RS    6
#define LCD_RW    5
#define LCD_E    4

#define LCD_D7_H()  (PORTC |= (1 << 0))  
#define LCD_D7_L()  (PORTC &= ~(1 << 0))  
#define LCD_D6_H()  (PORTC |= (1 << 1))  
#define LCD_D6_L()  (PORTC &= ~(1 << 1))  
#define LCD_D5_H()  (PORTA |= (1 << 2))  
#define LCD_D5_L()  (PORTA &= ~(1 << 2))  
#define LCD_D4_H()  (PORTA |= (1 << 3))  
#define LCD_D4_L()  (PORTA &= ~(1 << 3))  


#define LCD_DATA  (PORT_LCD |=  (1 << LCD_RS))  // RS=1
#define LCD_INST  (PORT_LCD &= ~(1 << LCD_RS))  // RS=0
#define LCD_READ  (PORT_LCD |=  (1 << LCD_RW))  // RW=1
#define LCD_WRITE (PORT_LCD &= ~(1 << LCD_RW))  // RW=0
#define LCD_EN    (PORT_LCD |=  (1 << LCD_E)) // LCD enable
#define LCD_DIS   (PORT_LCD &= ~(1 << LCD_E))// LCD disable

ClcdAdaptor::ClcdAdaptor(void)
{
  Init();
  
}

void ClcdAdaptor::Init(void){
    DDR_LCD |= 0xFC; // 수정해야함
    DDRC |= (1 << 0 | 1 << 1);
    
    PORT_LCD=0x00;  
    

    avr_delay_ms(50);  //Initial wating time
    SetInstruction(0x28);
    avr_delay_us(100);
    SetInstruction(0x28);
    avr_delay_us(100);
    SetInstruction(0x28);
    avr_delay_us(100);

    //Display On/Off Control
    SetInstruction(0x0C);   //LCD DISPLAY ON, CURSOR OFF, BLINK OFF
    avr_delay_us(50);

    //Entry mode Set
    SetInstruction(0x06);
    avr_delay_us(50);

    //Display Clear
    SetInstruction(0x01);   //LCD CLEAR
    avr_delay_ms(50);  
  
}


void ClcdAdaptor::SetData(unsigned char _d)
{
  //assert()
    avr_delay_ms(1);
 //상위 4BIT 출력
    Data4bit_out(_d >> 4);    
    LCD_DATA; LCD_WRITE;  //RS=1,RW=0

    LCD_DIS; avr_delay_us(1);
    LCD_EN;  avr_delay_us(1); LCD_DIS;     //E=0
    avr_delay_us(1);

 //하위 4BIT 출력
    Data4bit_out(_d);
    LCD_DATA; LCD_WRITE;  //RS=1,RW=0

    LCD_DIS; avr_delay_us(1);
    LCD_EN;  avr_delay_us(20); LCD_DIS;     //E=0  
}

void ClcdAdaptor::SetInstruction(unsigned char _inst)
{
    //assert()
     avr_delay_ms(1);
   //상위 4BIT 출력
    Data4bit_out(_inst >> 4);
    LCD_INST;   LCD_WRITE;   //RS=0,RW=0

    LCD_DIS; avr_delay_us(1);
    LCD_EN;  avr_delay_us(1); LCD_DIS;     //E=0
    avr_delay_us(1);

  //하위 4BIT 출력
    Data4bit_out(_inst);
    LCD_INST;   LCD_WRITE;   //RS=0,RW=0,EN=0

    LCD_DIS; avr_delay_us(1);
    LCD_EN;  avr_delay_us(1); LCD_DIS;     //E=0 
}
  

void ClcdAdaptor::Data4bit_out(unsigned char _d)
{
    //assert()
  if(_d & 0x01)
    LCD_D4_H(); 
  else
    LCD_D4_L();
      
  if(_d & 0x02)
    LCD_D5_H(); 
  else
    LCD_D5_L();   

  if(_d & 0x04)
    LCD_D6_H(); 
  else
    LCD_D6_L();
      
  if(_d & 0x08)
    LCD_D7_H(); 
  else
    LCD_D7_L();  
}