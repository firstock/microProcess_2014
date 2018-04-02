#ifndef __CLCD_ADAPTOR_H__
#define	__CLCD_ADAPTOR_H__


#include "clcd.h"


class ClcdAdaptor: public Clcd{
public:
  ClcdAdaptor();  
protected:

  void Init(void);
  void SetData(unsigned char _d);
  void SetInstruction(unsigned char _inst);

private:
  void Data4bit_out(unsigned char _d);
  
};


#endif //end of __CLCD_ADAPTOR_H__