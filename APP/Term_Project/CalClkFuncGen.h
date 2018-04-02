// ���� 5:42 2013-12-19  CCFG class �ȿ� �ִ�enum �������� ������ ������.
// ���� 7:17 2013-12-19 �������� ¥������. �� �鼷.

#ifndef __CALCLKFUNCGEN_H__
#define	__CALCLKFUNCGEN_H__

class IStringOut;
class IPwmOut;


#define  STRING_SIZE  15  


class CalClkFuncGen         //1. Calculator  2. Clock  3. FunctionGenerator  >> class 3��¥���� �Ѱ��� !@!>> but, ���⼭ Ŭ����
                            //�߰���Ű����, .h*3��, .cpp*3��, tm1s �ȿ��� �ٸ� Ŭ�����Լ�ȣ��, h,m,sec�� �����Լ������... ��������.
{                           // Ȥ�� �θ�Ŭ���� ���θ� �� �ǵ������(Init, tm1s)> ���� �����ɸ���.
private:
  IStringOut * lcd_line1;
  IStringOut * lcd_line2;
  IStringOut * serial;
  IPwmOut    * pwm;
  
  char  serialbuff[STRING_SIZE];
  unsigned char  serial_cnt;  
  //char inShiftStr[STRING_SIZE]; // ���� 13.12.19 23:48    //���� 13.12.19 23:51 - �ּ�ȭ
                                // StrShift�� tm500ms���� �� ���ڿ� ����Ʈ�� ����.
  
  unsigned char hour,min,sec;
  
  typedef enum { RESET, USER_STATE1, USER_STATE2} states1_t;
//  typedef enum { RESET, USER_STATE1, USER_STATE2} states2_t;    //�����̸��� ���ٸ��� �ϱ�.
  
  states1_t mystate1;
//  states2_t mystate2;
    
public:
  CalClkFuncGen();
  virtual ~CalClkFuncGen();     //��������/�����Ҵ� �Ⱦ��ٸ� ����..

  void Init(void);
  void SetIStringOut(IStringOut * _lcd_line1, IStringOut * _lcd_line2, IStringOut * _serial);
  void SetPwm( IPwmOut * _pwm);

//====================================================//
  
  void Switch(void);
  void InputCh(char _ch);
  void InputAdc(unsigned short _v);
  void InputTime(char* _ti);        //���1. �ʱ�ð� �Է�    //ERROR1?- �迭ũ�� �������� �� �����ִ���?
  // ���� 13.12.17 12:07                                      // > serialbuff�� ���� �־ �ߵ�.
  
  void tm1s(void);        //tm 1(one) s
  void tm500ms(void);     //tm 500    ms
  
  //-------- ���� SHIFT�� �غ��� ---------//  13.12.19 21:57 ����.
  void StrShift(char* _serialbuff);     //char  serialbuff[15]; ���� ����.
                                        // ���� 13.12.19 23:41 _serial ���� inShiftStr< �ٸ��Ŷ� ��ġ����.
                                        // ���� 13.12.20 11:25 return���� void -> char* �ٲ�, ������ oneShiftStr
                                        // ���� 13.12.20 11:51 void return���� ����ҵ�. ������ _serialbuff
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
  
  virtual void Write(char * _str) = 0; //���
};

#endif //end of __CALCLKFUNCGEN_H__