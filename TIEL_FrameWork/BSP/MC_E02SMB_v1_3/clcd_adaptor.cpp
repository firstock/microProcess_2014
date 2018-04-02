#include "clcd_adaptor.h"
#include "avr_common.h"
#include <ioavr.h>
#include <assert.h>

// LCD ���� �����ϱ� ���� �ܺ� �޸� �ּ� ����
#define LCD_EN (*(volatile unsigned char *)0x8000)
#define LCD_WRITE (*(volatile unsigned char *)0x8002)


ClcdAdaptor::ClcdAdaptor(void)
{
  Init();
  
}

void ClcdAdaptor::Init(void){
      
  MCUCR |= 1 << SRE;
    
 	XMCRA = 1 << SRL2; // �ܺ� �޸� ���� ����
	XMCRB = 1 << XMBK; // �ܺ� �޸� ���� ����   

    avr_delay_ms(50);  //Initial wating time
    

	LCD_EN = 0x38;  //FunctionSet
        
	avr_delay_us(40);
	LCD_EN = 0x0c; //DisplayOnOffControl();
        
	avr_delay_us(40);
	LCD_EN = 0x01; //DisplayClear();
	
        avr_delay_ms(2);
	LCD_EN = 0x06;
	avr_delay_us(40); //EntryModeSet();
  
}


void ClcdAdaptor::SetData(unsigned char _d)
{
  //assert()
  LCD_WRITE = _d;
  avr_delay_us(50); 
}

void ClcdAdaptor::SetInstruction(unsigned char _inst)
{
// ��巹�� ������ ���ؼ��� MSB�� ������ 1�� �Ǿ�� ��.
// ����ڰ� ���� �ּҸ� �޾� MSB�� 1�� ������ش�.
// Set DD RAM Address ����
	LCD_EN = 0x80 | _inst;
	avr_delay_us(50);
}
  

void ClcdAdaptor::Data4bit_out(unsigned char _d)
{
    //assert()
   
}