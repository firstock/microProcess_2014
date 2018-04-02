
#include "led.h"
#include <assert.h>


// 기본 시간 단위는 ms
#define TIME_INTERVAL_MS			50			// 타이머 이벤트의 주기. 이 모듈에서 사용되는 시간의 기본 레졸루션이됨.
#define MAX_ON_TIME_MS				10000		// 최대로 LED가 켜질 수 있는 시간. 잘못되어 계속 켜지는 것을 방지. (기능 삭제 예정)
#define MAX_ON_OFF_CNT				10			// 최대로 blink할 수 있는 횟수.
#define DEFAULE_ONOFF_CYC_MS	500			// on,off의 기본주기
#define DEFAULE_DUTY_RATE	5				// on시간과 off시간의 비
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

  
void Led::evTimerExpir(void) //외부 타이머에 의해 호출. 비재진입 함수
{
	if(OFF != LED_state && MAX_ON_TIME_MS < DW_LED_currunt_timer_tick ) // 어떠한 모드에 있던 최대 시간을 초과하면 초기화 된다.
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
  
