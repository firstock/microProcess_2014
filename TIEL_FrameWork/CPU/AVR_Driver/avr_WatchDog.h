#ifndef __AVR_WATCHDOG__
#define	__AVR_WATCHDOG__

class avr_watchdog {
public:  
  avr_watchdog();
 
static  void Kick(void);
   
private:
  void CPUReset(void);
  void Prescaler_Change(void); 
  void Off(void);
};


#endif // end of __AVR_WATCHDOG__