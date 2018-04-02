#ifndef __DIO_ADAPTOR_H__
#define	__DIO_ADAPTOR_H__

#include "dio.h"
#include "led.h"

class E02SMBLed : public Led
{
public:
  E02SMBLed();
protected:
  void SetPort(unsigned char _v);
  unsigned char GetPort(void);  
};

class DigialIn:public DIn
{
 
public:
  DigialIn(DInEvent & _ev);
  DigialIn();
  
 protected:
  unsigned char GetPort(void);
};

#endif //end of __DIO_ADAPTOR_H__