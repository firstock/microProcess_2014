#ifndef __TYPE_H__
#define	__TYPE_H__




#ifdef  __IAR_SYSTEMS_ICC__
#define std  //for IAR Compiler
#define CONST __flash
#define CONCHARPTR (const char *)
#define PSTR(s) ( {static __flash char c[] = s; c;} ) 
#define LCD_Puts_FLASH(s) {static __flash unsigned char str[] = s; LCD_Putsf(str);}
#endif
 
#ifndef CONST
#define CONST const
#endif

namespace tief{

typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned long   uint32;

};


 
#define GNU_LICENSE "    TIEF(TIEF is Embedded S/W Framework)\n"\
                    "    Copyright (C) 2013-2013  Yoo Joo-Hyoung (potato97@naver.com)\n"\
                    "    Site: http:\/\/ccrs.hanyang.ac.kr\n"\
                    "    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"\
                    "    This is free software, and you are welcome to redistribute it\n"\
                    "    under certain conditions; type `show c' for details.\n"
extern CONST char  gnu_lic[];

#define TIEL_VER 0.8
#endif // end of __TYPE_H__