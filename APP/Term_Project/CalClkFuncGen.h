// 오후 5:42 2013-12-19  CCFG class 안에 있던enum 전역으로 꺼내기 전까지.
// 오후 7:17 2013-12-19 아하하하 짜증난다. 또 백섭.

#ifndef __CALCLKFUNCGEN_H__
#define	__CALCLKFUNCGEN_H__

class IStringOut;
class IPwmOut;


#define  STRING_SIZE  15  


class CalClkFuncGen         //1. Calculator  2. Clock  3. FunctionGenerator  >> class 3개짜리가 한곳에 !@!>> but, 여기서 클래스
                            //추가시키려면, .h*3개, .cpp*3개, tm1s 안에서 다른 클래스함수호출, h,m,sec에 접근함수만들고... 복잡해짐.
{                           // 혹은 부모클래스 내부를 좀 건드려야함(Init, tm1s)> 몹시 오래걸릴듯.
private:
  IStringOut * lcd_line1;
  IStringOut * lcd_line2;
  IStringOut * serial;
  IPwmOut    * pwm;
  
  char  serialbuff[STRING_SIZE];
  unsigned char  serial_cnt;  
  //char inShiftStr[STRING_SIZE]; // 수정 13.12.19 23:48    //수정 13.12.19 23:51 - 주석화
                                // StrShift와 tm500ms에서 쓸 문자열 시프트용 변수.
  
  unsigned char hour,min,sec;
  
  typedef enum { RESET, USER_STATE1, USER_STATE2} states1_t;
//  typedef enum { RESET, USER_STATE1, USER_STATE2} states2_t;    //내부이름은 좀다르게 하기.
  
  states1_t mystate1;
//  states2_t mystate2;
    
public:
  CalClkFuncGen();
  virtual ~CalClkFuncGen();     //깊은복사/동적할당 안쓴다면 딱히..

  void Init(void);
  void SetIStringOut(IStringOut * _lcd_line1, IStringOut * _lcd_line2, IStringOut * _serial);
  void SetPwm( IPwmOut * _pwm);

//====================================================//
  
  void Switch(void);
  void InputCh(char _ch);
  void InputAdc(unsigned short _v);
  void InputTime(char* _ti);        //기능1. 초기시간 입력    //ERROR1?- 배열크기 지정없이 잘 들어갈수있는지?
  // 수정 13.12.17 12:07                                      // > serialbuff를 통해 넣어서 잘됨.
  
  void tm1s(void);        //tm 1(one) s
  void tm500ms(void);     //tm 500    ms
  
  //-------- 이제 SHIFT를 해볼까 ---------//  13.12.19 21:57 부터.
  void StrShift(char* _serialbuff);     //char  serialbuff[15]; 넣을 예정.
                                        // 수정 13.12.19 23:41 _serial 말고 inShiftStr< 다른거랑 겹치더라.
                                        // 수정 13.12.20 11:25 return형을 void -> char* 바꿈, 변수명 oneShiftStr
                                        // 수정 13.12.20 11:51 void return으로 충분할듯. 변수명 _serialbuff
};

class IPwmOut{
public:
  IPwmOut(){};
  virtual ~IPwmOut(){};
  virtual void SetDuty(unsigned short _du) = 0;
};

class IStringOut
{

public:
  IStringOut(){};
  virtual ~IStringOut(){};
  
  virtual void Write(char * _str) = 0; //출력
};

#endif //end of __CALCLKFUNCGEN_H__