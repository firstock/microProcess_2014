#ifndef __AVR_SPI_H__
#define	__AVR_SPI_H__

#include "ispi.h"

class AvrSpi: public ISpi
{
  
public:
  AvrSpi(void);
  
  void Init(void);
  
  unsigned char WriteByte(unsigned char _byte);
  
  unsigned char ReadByte(unsigned char _byte=0);  
  
};

#endif //end of __AVR_SPI_H__