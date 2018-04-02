#include "clcd_adaptor.h"
#include "avr_common.h"
#include "dio_adaptor.h"

int main( void )
{

  ClcdAdaptor l;
  Clcd & lcd  = l;
  LcdBackLight bl;
  
  bl.Set(1);

  


    lcd.Write(Clcd::LINE1, "  hello CLCD  "); 
    lcd.Write(Clcd::LINE2, "  HELLO CLCD  ");

    while(1)
    {
          lcd.Write(Clcd::LINE1, "  HELLO CLCD  "); 
          lcd.Write(Clcd::LINE2, "  HELLO CLCD  ");
          avr_delay_ms(2000);
          lcd.Write(Clcd::LINE2, "1234567891023456");
          avr_delay_ms(2000);
          lcd.Write(Clcd::LINE1, "1234567891023456");
          avr_delay_ms(2000);
    }
}

