#include "clcd_adaptor.h"
#include "avr_common.h"
#include <ioavr.h>
#include <assert.h>

// LCD 모듈로 접근하기 위한 외부 메모리 주소 선언
#define LCD_EN (*(volatile unsigned char *)0x8000)
#define LCD_WRITE (*(volatile unsigned char *)0x8002)


ClcdAdaptor::ClcdAdaptor(void)
{
  Init();
  
}

void ClcdAdaptor::Init(void){
      
  MCUCR |= 1 << SRE;
    
 	XMCRA = 1 << SRL2; // 외부 메모리 섹터 설정
	XMCRB = 1 << XMBK; // 외부 메모리 섹터 설정   

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
// 어드레스 세팅을 위해서는 MSB는 무조건 1이 되어야 함.
// 사용자가 원한 주소를 받아 MSB를 1로 만들어준다.
// Set DD RAM Address 참조
	LCD_EN = 0x80 | _inst;
	avr_delay_us(50);
}
  

void ClcdAdaptor::Data4bit_out(unsigned char _d)
{
    //assert()
   
}