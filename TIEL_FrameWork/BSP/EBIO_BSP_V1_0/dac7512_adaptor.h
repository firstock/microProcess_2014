#ifndef __DAC7512_ADAPTOR_H__
#define	__DAC7512_ADAPTOR_H__


#include "dac7512.h"
#include "ispi.h"


//CPU & Board 종속적인 코드 
class Dac7512Adaptor: public Dac7512{


public:
  Dac7512Adaptor(ISpi & _spi);
private:
  void Init_Spi(void);

  void Spi_CS_H(void);
  void Spi_CS_L(void);
  
};


#endif //end of __DAC7512_ADAPTOR_H__