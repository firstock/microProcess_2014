#ifndef __AVR_ADC_H__
#define	__AVR_ADC_H__

#include "adc.h"

class Avr_adc: public IAdcPort
{

public:
  Avr_adc();
  virtual ~Avr_adc();

protected:
  unsigned char isConverted(void);
  unsigned short GetAdc(void);
  
  void Init(void);
  void SetChannel(unsigned char _ch);
  void SetPrescaler(unsigned char _pre);
  
};

#endif //end of __AVR_ADC_H__