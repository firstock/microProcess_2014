
#include "led.h"
#include <assert.h>


// �⺻ �ð� ������ ms
#define TIME_INTERVAL_MS			50			// Ÿ�̸� �̺�Ʈ�� �ֱ�. �� ��⿡�� ���Ǵ� �ð��� �⺻ ��������̵�.
#define MAX_ON_TIME_MS				10000		// �ִ�� LED�� ���� �� �ִ� �ð�. �߸��Ǿ� ��� ������ ���� ����. (��� ���� ����)
#define MAX_ON_OFF_CNT				10			// �ִ�� blink�� �� �ִ� Ƚ��.
#define DEFAULE_ONOFF_CYC_MS	500			// on,off�� �⺻�ֱ�
#define DEFAULE_DUTY_RATE	5				// on�ð��� off�ð��� ��
// 1 = 1:9
// 2 = 2:8
// 3 = 3:7
// 4 = 4:6
// 5 = 5:5
// 6 = 6:4
// ~~
// 9 = 9:1

Led::Led()
{

Init();

}

void Led::Init()
{
  LED_state = OFF;
  
  DW_LED_currunt_timer_tick = 0;
  
//  blink_Number = 5;
  onoff_cyc_ms = 500;
//duty_rate		= 5;
 
  onoffcnt = 0;
  isLEDon = 0;  
  
}

void Led::Blink(unsigned char _blink_Number, unsigned char _onoff_cyc_ms, unsigned char _duty_rate)
{
        if(BLINK == LED_state)
          return;
 
        
	LED_state = BLINK;
		
	if( 0 != _blink_Number)
		blink_Number = _blink_Number;
	if( 0 != _onoff_cyc_ms)
		onoff_cyc_ms = _onoff_cyc_ms;
        if( 1 <= _duty_rate && 9 >= _duty_rate)
		duty_rate 	 = _duty_rate;
        DW_LED_currunt_timer_tick = 0;

	onoffcnt = 0;

        on_rate_ms=(unsigned int)((float)onoff_cyc_ms*((float)duty_rate/10.0));
        
        Set(0);
  
}

  
void Led::evTimerExpir(void) //�ܺ� Ÿ�̸ӿ� ���� ȣ��. �������� �Լ�
{
	if(OFF != LED_state && MAX_ON_TIME_MS < DW_LED_currunt_timer_tick ) // ��� ��忡 �ִ� �ִ� �ð��� �ʰ��ϸ� �ʱ�ȭ �ȴ�.
	{
		Init();
 //               Set(0);
	}

	
	if( OFF != LED_state )
	{
		DW_LED_currunt_timer_tick += TIME_INTERVAL_MS;		
	}
	
	if( BLINK == LED_state ){
		unsigned char now;
	
		if(on_rate_ms > (DW_LED_currunt_timer_tick % onoff_cyc_ms) ) //on time
		{
			//Set(1);
                        Flip();
			now = 1;
		}
		else //off time
		{
			//Set(0);
                        Flip();
			now = 0;
		}
		
		if( isLEDon == 1 && now == 0 )
		{
			onoffcnt++;
		}
		
		isLEDon = now;
		if( (onoffcnt >= blink_Number ) || onoffcnt >= MAX_ON_OFF_CNT )
		{
			Init();
                        Set(0);
		}

	}
  
  
}
  
