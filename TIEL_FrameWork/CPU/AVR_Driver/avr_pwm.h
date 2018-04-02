#ifndef __AVR_PWM_H__
#define	__AVR_PWM_H__

#include "pwm.h"

class Avr_pwm: public IPwmPort
{
  unsigned char preScaler;
public:
  Avr_pwm(unsigned char _preScaler = 4);
  virtual ~Avr_pwm();
protected:
  void Init(void);
  void Run(void);
  void Stop(void);
  void SetDuty(unsigned short _du);
  unsigned char GetResolution();
  
  void SetOcr(unsigned char _ocr);
  void SetPreScaler(unsigned char _s);
};

#endif //end of __AVR_PWM_H__
