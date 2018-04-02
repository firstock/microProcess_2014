#ifndef __DIO_ADAPTOR_H__
#define	__DIO_ADAPTOR_H__

#include "dio.h"
#include "led.h"

class EBIO_Relay: public DOut
{
public:
  EBIO_Relay();
protected:
  void SetPort(unsigned char _v);
  unsigned char GetPort(void);
};

class WCS2702POW: public DOut
{
public:
  WCS2702POW();
protected:
  void SetPort(unsigned char _v);
  unsigned char GetPort(void);
};



class ZigBeePOW: public DOut
{
public:
  ZigBeePOW();
protected:
  void SetPort(unsigned char _v);
  unsigned char GetPort(void);
};

class ZigBeeRST: public DOut
{
public:
  ZigBeeRST();
protected:
  void SetPort(unsigned char _v);
  unsigned char GetPort(void);
};

class LcdPOW: public DOut
{
public:
  LcdPOW();
protected:
  void SetPort(unsigned char _v);
  unsigned char GetPort(void);
};

class LcdBackLight: public DOut
{
public:
  LcdBackLight();
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

class DigialOut: public DOut
{
public:
  DigialOut();
protected:
  void SetPort(unsigned char _v);
  unsigned char GetPort(void);
};

class EBIOLedRed : public Led
{
public:
  EBIOLedRed();
protected:
  void SetPort(unsigned char _v);
  unsigned char GetPort(void);  
};

class EBIOLedBlue : public Led
{
public:
  EBIOLedBlue();
protected:
  void SetPort(unsigned char _v);
  unsigned char GetPort(void);  
};
#endif //end of __DIO_ADAPTOR_H__