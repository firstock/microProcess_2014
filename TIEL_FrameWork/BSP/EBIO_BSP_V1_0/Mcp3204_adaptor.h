#ifndef __MCP3204_ADAPTOR_H__
#define	__MCP3204_ADAPTOR_H__


#include "mcp3204.h"
#include "ispi.h"


//CPU & Board 종속적인 코드 
class Mcp3204Adaptor: public Mcp3204{


public:
  Mcp3204Adaptor(ISpi & _spi);
private:
  void Init_Spi(void);

  void Spi_CS_H(void);
  void Spi_CS_L(void);
  
};


#endif //end of __MCP3204_ADAPTOR_H__