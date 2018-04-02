// 변경사항을 알고 싶을시, '수정' 키워드로 검색한다
// MODE 변경사항에 대해서는, '모드' 키워드로 검색한다

//오후 12:38 2013-12-17
// 시계기능> 시각입력 까지 되는 소스
// 오후 4:56 2013-12-19 예전버전으로 돌림> 시험끝나니 예전에 수정한게 생각안남
// 오후 7:17 2013-12-19 아하하하 짜증난다. 두번째 엎음>첫 버전으로. inputCh에서 return 넘기는순간 flag에 쓰레기값 들어가는걸 해결못해서.
// 오후 9:52 2013-12-19 히히힛. 이제 광고문안 띄우는 것까지 깔끔하게 됨. 이제부터 광고문안 shift를해볼까.
// 오전 10:30 2013-12-20 이걸로 다시 엎음. 뒷컴에선 WatchDog 이었는데 앞컴에선 문안도 안나옴.
// 오전 12:08 2013-12-20 shift 됨
// 오후 1:52 2013-12-20  모드 변경 기본틀 짜놓음. test까지만. 본격적으로 바꾸기전에 저장.
// 오후 2:56 2013-12-20  바꾸다가 헷갈림. 느낌 아니까 이걸로 한번 뒤집자.
// 오후 3:19 2013-12-20  바꾸다가 헷갈림. 쓸데없는 주석을 날려버리자. > 15:24 주석제거.
// 오후 4:06 2013-12-20  히히힛 모드변경 완료. 되돌아와서도 Clock 잘 실행됨.
// 오후 4:18 2013-12-20  엔터조건 변수화: Enter_OVsize. 계산 한번만 하려고.
// - 모드변경 직후, flag 초기화 문제였음.
// 이제 InputCh에 이런저런 코드를 추가시키면 됨.
// & Switch 함수에서 모드변경 직후 뭘 입력하고 엔터치라고 알려줘야함.
// + flag_mode 나머지 계산 한번만> MODE - 수정 13.12.20 16:54
// 오후 6:36 2013-12-20  이제막 안에 내용 채우려는 중
// 오후 6:49 2013-12-20  yunsan_cnt 를 static으로 선언했더니 까닭을 알 수 없는 에러가났음
// - 해결해야하는 문제1: 연산자 전까지 받은 숫자를 버퍼에 넣어서 한뭉치로 출력.
// - 문제2: 연산자 앞뒤에 있었는지 구분하여 num1,2 배열에 알맞게 넣어놓기.
//      > goto문 쓰고 싶을 지경. 이걸 제대로 고치려면 index를 몇개 더 넣어야할지도 모르겠음.
// 5번째 엎음.
// 오후 6:56 2013-12-20  Function Gen가 쉽다고하니 이거 먼저 해보자.
// 오후 8:06 2013-12-20  FuncGen line1까지 함(사실, Lab10_Ex1 복붙에 가까움. _v를 의미를 안다면.)
// LAB10_HJ_EX1.c 참고

#include "CalClkFuncGen.h"
#include <cstdio>
#include <cstring>
#include <cassert>

#define LCD2empty lcd_line2->Write("        ")    //수정 13.12.20 17:46- 간편하게 LCD 한줄만 비우기.
#define LCD1empty lcd_line1->Write("        ")





char flag_Clock= 1; //만약 다른 모드에서 MODE1(Timer)으로 바꿀땐 flag_Clock를 1로 초기화해야함.    --(주의)

char flag_EnShift= 0; //수정 13.12.20 10:41 - Enable Shift> tm500ms 에서 실행됨.
// 모드가 바뀌면 멈추어야 하므로 바뀌자마자 flag_Shift=0 으로 만들어 주어야 한다.       --(주의)
// 아마 스위치에서?

int flag_mode= 0;    //수정 13.12.20 12:09 - 모드 변경       //수정 13.12.20 15:26- int로 switch~case 때 귀찮음방지.
// 0: Clock
// 1: 계산기
// 2: Function Gen


CalClkFuncGen::CalClkFuncGen() //클래스 내부의 변수 초기화. 이 시점에서는 하드웨어를 사용할 수 없다
{
  hour= 0;
  min = 0;
  sec = 0;
  
  serial_cnt= 0;
  
  mystate1= RESET;
}

CalClkFuncGen::~CalClkFuncGen(){}

void CalClkFuncGen::Init(void)//이 함수의 호출 직후 부터 하드웨어 사용가능
{
  mystate1= USER_STATE1;     // 1
 
  serial->Write("##Watch mode##\n");//하이퍼터미널에 떠있음
  serial->Write("1.현재 시간: ");   // 입력> line2에 들어감.

}

// 시간 갱신
void CalClkFuncGen::InputTime(char* _ti)
{
  //char tmp_reTime[15];
    
  hour= (_ti[0]-48)*10+ (_ti[1]-48);  // ex. 현재시간 091153
  min = (_ti[2]-48)*10+ (_ti[3]-48);
  sec = (_ti[4]-48)*10+ (_ti[5]-48);
  
  // 시간이 정정될때마다 표시?? - 입력하는 순간 표시되서 굳이 추가할 필요 없을듯.
  //sprintf(tmp_reTime,"%02d:%02d:%02d",hour,min,sec);
  //serial->Write(tmp_reTime);
} 

void CalClkFuncGen::SetIStringOut(IStringOut * _lcd_line1, IStringOut * _lcd_line2, IStringOut * _serial)
{
  assert( 0 != _lcd_line1);
  assert( 0 != _lcd_line2);
  assert( 0 != _serial);
  
  lcd_line1 = _lcd_line1;
  lcd_line2 = _lcd_line2;
  serial = _serial;
  
}

void CalClkFuncGen::SetPwm( IPwmOut * _pwm)
{
  assert( 0 != _pwm);
  
  pwm = _pwm;
}

//==============================================================================//

// -----------------------    스위치    --------------------------//
void CalClkFuncGen::Switch(void)     // 스위치가 눌리때 마다 호출됨
{
  ///
  flag_mode++;
  int MODE= flag_mode%3;             //수정 13.12.20 16:48 - 계산은 한번만.
  
  // test
  if(MODE== 0)               // Clock모드
  {
    flag_Clock= 1;                  //수정 13.12.20 16:04 - > 0으로 되돌아와서도 Clock 잘 실행됨.
    LCD2empty;                      //수정 13.12.20 20:19 - FuncGen 에서 Clock올때 두번째줄 비우기.
      
    serial->Write("##Watch mode##\n");
    serial->Write("1.현재 시간:\n");
    
  }
  else if(MODE== 1)          // 계산기 모드
  {
    LCD2empty;                      // 수정 13.12.20 18:24- line2 비우기. 포맷 맞추기
    flag_EnShift= 0;                // string 그만 밀기.
    serial->Write("##Calcul mode##\n");
    lcd_line1->Write("##Calc##");   // 수정 13.12.20 18:20- 포맷 지키기.
    //여기서 뭔가 입력한 후 엔터 치란 말을 해야함.
       
  }
  else if(MODE== 2)                 // Function Gen 모드
  {
    LCD1empty;              //수정 13.12.20 19:11- LCD 첫줄 비우기.
    serial->Write("##Function Generator mode##\n");
    //lcd_line1->Write("ADC:");   // 여기다 말고. 수정 13.12.20 19:46

    //여기서 뭔가 입력한 후 엔터 치란 말을 해야함.
    
  }
  //serial->Write("Switch\n");        // test
}
// ----------------------    스위치 영역   --------------------------//



//------------------------------------------------------------------------------//
void CalClkFuncGen::InputCh(char _ch) // 시리얼로부터 입력이 들어 오면 실행됨       [A1]
{
    int Enter_OVsize= ('\n' == _ch  || '\r' == _ch  || STRING_SIZE - 1 <= serial_cnt);  //엔터 혹은 사이즈초과.
    int MODE= flag_mode%3;      //수정 13.12.20 16:48 - 계산은 한번만. 모드변경.
    
    float num_1[3], num_2[3];   // 첫번째, 두번째 입력값 각기 저장
    float result[3];

    char yunsan_cnt= 0;         // 연산자를 몇번째 눌렀는지
                                // 시도1. 초기화가 불만이라고 static으로 선언하면 ERROR.- 는 확실치않음.
                                // 수정 시도1 13.12.20 18:56

    char cal_state;             // (+ - * /)
    const int PLUS= 0, MINUS= 1, MUL= 2, DIV= 3, EQUAL= 4;
    
    /// 수정 시작 13.12.20 16:43 - Calcul 통째 계산을 위한 n번째 스파게티 소스.
    // 구상: ex) 28+16=' '
    // - 계산대상은 2개까지, 하이퍼터미널에 입력하는 중에 serialbuff 속 다음 글자가 뭐인지에 따라
    //   if~else 문으로 바쁘게 판단.
    // - 3자리+2자리 계산에 대비하여 다음글자 넣기전에 lcd_line2->Write("      ");등으로 LCD비우기.
    //      > 나눗셈 예외 /0 따위.
    // - 계산 및 계산 결과는 출력(함수)에서 한방에 처리.
    
    
    
// ----------------------- 계산기- 한글자씩 처리 -------------------//
    // 시간부족 ㅂㅂ. 틀만 되어있고 구현 못함 // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                              // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                              // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                              // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                              // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                              // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    
    if(MODE== 1)
    {
      ///
      if(48<= _ch && _ch <= 57)   //숫자일때. 조건문 보는 시간 줄이려고. <수정 13.12.20 17:48
      {
        //lcd_line2->Write("number"); //test
        lcd_line2->Write(&_ch);     //수정 13.12.20 18:16 - 인자는 pointer로!
                                    //수정 13.12.20 18:29 - buff 좀 모아서 한번에 출력해야함!
                                    // 일단 test용도로 살려둠.
        
        if(yunsan_cnt== 0)        // num / --- / ---
        {
          //하려는것: 첫번째 피연산자 일때 serial_cnt 순서대로 num_1[]에 넣고
        }
        else if(yunsan_cnt== 1)   // --- / num / ---
        {
          //하려는것: 두번째 피연산자 일때 serial_cnt 순서대로 num_2[]에 넣고
        }
        else if(yunsan_cnt== 2)   // --- / --- / res
        {
          // 꼭필요? 밑에 '=' 이후에 하는거랑 중복..?
        }
      }
      else
      {
        //[M] 여기서 LCD2empty 안빼도 됨. 포맷고려해도
        if(_ch== '+')         {LCD2empty; cal_state= PLUS;   lcd_line2->Write("PLUS");}  //test '}//'로 test O/X
        else if(_ch== '-')    {LCD2empty; cal_state= MINUS;  lcd_line2->Write("MINUS");} //test
        else if(_ch== '*')    {LCD2empty; cal_state= MUL;    lcd_line2->Write("MUL");}   //test
        else if(_ch== '/')    {LCD2empty; cal_state= DIV;   }// lcd_line2->Write("DIV");}   //test
        
        else if(_ch== '=')    
        {
          LCD2empty; cal_state= EQUAL; 
        }
                
        yunsan_cnt++;        // 연산자를 눌렀다.
      }
      /// 수정 13.12.20 17:58- else~if_ 숫자,연산자 반응확인
    }
    
// ----------------------- 계산기- 한글자씩 처리 영역 -------------------//
    
    
    

    
///////////////////   엔터  //////////////////////
    if(Enter_OVsize)
                         // 수정 13.12.20 16:17 - 왠지 앞으로 '엔터'조건 많이 쓸것 같아서.
    {
      serialbuff[serial_cnt] = 0;     // char*
      serial_cnt = 0;
 
      
// ------------------ Clock ----------------------- //
      if(MODE== 0)
      {
        if(flag_Clock== 2)
        {
          flag_EnShift=1;       //수정 13.12.20 10:41 - 이 순간부터 문자열 Shift 됨.
          

          //lcd_line2->Write(serialbuff);   // test
  
          flag_Clock= 0;        // 수정 13.12.19 20:18 - 한번만 실행되도록.  
                                // 만약 다른 모드에서 MODE1으로 바꿀땐 flag_Clock를 1로 초기화해야함.   --(주의)
        }
        else if(flag_Clock== 1)
        {
          lcd_line2->Write("        ");
          InputTime(serialbuff);                // 수정 13.12.17 12:07

          serial->Write("2.광고(15자 이내): "); // 수정 13.12.19 21:46
        
          flag_Clock= 2;   
        }
        return;
      }
// ------------------ Calcul ------------------ //   // 수정 13.12.20 15:37 - 기본틀
      //return;   //수정 13.12.20 15:49 윗 괄호로 옮김.- 엔터로 들어왔지만 clock mode가 아니면 return 안됨.
 
      else if(MODE== 1)   // 스위치 한번더 누르고 엔터를 누르면 반응함.
      {
        // 결과값 출력.
        serial->Write("계산기\n");  //test
        return;         //수정 13.12.20 17:00 이게 없어야 엔터치면 값 초기화??? (보류)        --(*)
      }
      
// ------------------  Function Gen  ------------------ // 
      else if(MODE== 2)
      {
        serial->Write("Function Gen\n");     //test
        return;
      }
    }
// return 하면 serial_cnt랑 buff가 0으로 초기화. 값 안 늘고.
////////////////////  엔터의 영역  //////////////////////   
    
    
    
    serialbuff[serial_cnt] = _ch;    
    serial_cnt++;  
}





// ----------------------------  Function Gen  ---------------------------- //  ●

void CalClkFuncGen::InputAdc(unsigned short _v) //ADC 값이 주기적으로 들어옴- tm_xx_s 마냥 자동실행되는듯.
{
  //구상:  _v 변수에 예전에 했던 ADC형식을 그대로 대입.
  /// 조언굿.
  char tmp_c[13], tmp_v[13];

  // 숫자큰 변수가 MSB
  unsigned short c1,c2,c3;  
  unsigned short v1,v2,v3,v4;
    
  if(flag_mode%3== 2)     //Function Gen
  {
    c3 = _v *5/1023;      // 0~1023 -> 0.00~5.00
    c2 = (_v*50/1023) %10;
    c1 = _v *500/1023 %10 ;
   
    v4 = _v / 1000;       // 0~1023 -> 0~1
    v3 = (_v % 1000) / 100;
    v1 = _v % 100;
    v2 = v1/10;
    v1 = v1 % 10;
                
    sprintf(tmp_c,"ADC:%d.%d%d",c3,c2,c1);
    lcd_line1->Write(tmp_c);
    
    sprintf(tmp_v,"%d%d%d%%duty",v4,v3,v2);
    lcd_line2->Write(tmp_v);

  }
  /// 수정 13.12.20 19:59
  // 수정 13.12.20 20:04- line1
  // 수정 13.12.20 20:16- line2
  
  pwm->SetDuty(_v);				// _v 에 0~1023값이 계속 들어옴.
}


// --------------------------  Function Gen  영역---------------------------- //






// 매초 시간표시
void CalClkFuncGen::tm1s(void)// 1초 마다 실행됨
{
  char tmp[15];
  sec++;
  if(60<= sec)  {min++; sec=0;}
  if(60<= min)  {hour++; min=0;}
  if(24<= hour) {hour= 0;}
  
  sprintf(tmp,"%02d:%02d:%02d",hour,min,sec);
  
  if(flag_mode%3== 0)    lcd_line1->Write(tmp);   // Clock 모드 일때만 시간출력
                              // 수정 13.12.20 15:37 - (주의)사항 적용

}


//-------- 이제 SHIFT를 해볼까 ---------//  13.12.19 21:57 부터 오전 12:08 2013-12-20 까지.
void CalClkFuncGen::StrShift(char* _serialbuff)      //serialbuff 넣을예정
{
  unsigned char i=0, j, tmp=0;
  j = strlen(_serialbuff)-1;
   
  tmp= _serialbuff[0];	  // 첫 글자 임시 저장 
  for(i=0; i<j; i++)      // 한글자 씩 앞으로 이동 
  {
    _serialbuff[i] = _serialbuff[i+1];
  }
  _serialbuff[j] = tmp;	  // 마지막 메모리에 첫 글자 저장 
}


// --------------                           ----------------- //

void CalClkFuncGen::tm500ms(void) //0.5초마다 실행됨
{
  if(flag_EnShift==1)
  {
    StrShift(serialbuff);
    lcd_line2->Write(serialbuff);    // test
  }
}
 
// ----------------------------------------------------------- //
