#ifndef __STRINGPROCESSING_H__
#define	__STRINGPROCESSING_H__

#define STRING_MAX 20

class IStringOutPut;

class StringProcess
{
  IStringOutPut *iout;
  
  char tempBuff[STRING_MAX];
  char stringShiftBuff[STRING_MAX];
  unsigned char str_count;
  
  typedef enum { WATING_SHIFT_EVENT, WATING_TIMER_EVENT} states_t;
  states_t state;
public:
  StringProcess();
  virtual ~StringProcess();
  
  void SetIStringOutPut(IStringOutPut *_iout);
  
  void tm500ms(void);
  void InputCh(char _ch);
  
private:
   void Start_Shift(void);
   void Shift_StringLeft(char *_str); //helper function
   void update_string(void);          //helper function
 };

class IStringOutPut
{
public:
  IStringOutPut(){}
  virtual ~IStringOutPut(){};
  virtual void Display(char *_str) = 0;
};

#endif //end of __STRINGPROCESSING_H__