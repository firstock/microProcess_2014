#ifndef __DISPLAYADC_H__
#define	__DISPLAYADC_H__


class IDisplay;

class DisplayAdc
{
  IDisplay *idisp;
public:
  DisplayAdc();
  virtual ~DisplayAdc();
  void SetAdcValue(unsigned short _v);
  
  void SetIDisplay(IDisplay * _idisp);
  
};

class IDisplay{
public:
  IDisplay(){}
  virtual ~IDisplay(){}
  virtual void OutPutVolt(float _v) = 0;
  virtual void OutPutBar(unsigned char _bar) = 0;
};
#endif //end of __DISPLAYADC_H__