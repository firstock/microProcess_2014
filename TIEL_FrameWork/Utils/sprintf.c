/*+-------------------------------------------------------------------------+
  |  FILE: sprintf.c                                                        |
  |  Version: 0.1                                                           |
  |                                                                         |
  |  Copyright (c) 2003 Chun Joon Sung                                      |
  |  Email: chunjoonsung@hanmail.net / 
  +-------------------------------------------------------------------------+*/
 
char *itoa( char *a, int i)
{
    int sign=0;
    int temp=0;
    char buf[16];
    char *ptr;

    ptr = buf;

    /* zero then return */
    if( i )
    {
        /* make string in reverse form */
        if( i < 0 ){ 
                    i = ~i + 1; 
                    sign++; }
 
        while( i ){ 
                    *ptr++ = (i % 10) + '0'; 
                    i = i / 10; }
 
        if(sign)
            *ptr++ = '-';
 
        *ptr = '\0';

        /* copy reverse order */
        for( i=0; i < strlen(buf); i++ )
            *a++ = buf[strlen(buf)-i-1];
    }    
    else
        *a++ = '0';

    return a;
}

char *xtoa( char *a, unsigned int x, int opt)
{
    int i;
    int sign=0;
    int temp=0;
    char buf[16];
    char *ptr;

    ptr = buf;

    /* zero then return */
    if( x )
    {
        /* make string in reverse form */
        while( x )
            { *ptr++ = (x&0x0f)<10 ? (x&0x0f)+'0' : (x&0x0f)-10+opt; x>>= 4; }

        *ptr = '\0';

        /* copy reverse order */
        for( i=0; i < strlen(buf); i++ )
            *a++ = buf[strlen(buf)-i-1];
    }
    else    
        *a++ = '0';

    return a;
}

long _sprintf(buf, format, arg)
char *buf;
char *format;
long  arg;
{
    int cont_flag;
    int value;
    int quit;
    char *start=buf;
    long *argp=(long *)&arg;
    char *p;

    while( *format )
    {
        if( *format != '%' )    /* 일반적인문자*/
        {
            *buf++ = *format++;
            continue;
        }

        format++;                /* skip '%' */

        if( *format == '%' )    /* '%' 문자가연속두번있는경우*/
        {
            *buf++ = *format++;
            continue;
        }
        
        switch( *format )
        {
            case 'c' :
                *buf++ = *(char *)argp++;
                break;

            case 'd' :
                buf = itoa(buf,*(int *)argp++);
                break;

            case 'x' : 
                buf = xtoa(buf,*(unsigned int *)argp++,'a');
                break;

            case 'X' : 
                buf = xtoa(buf,*(unsigned int *)argp++,'A');
                break;

            case 's' :
                p=*(char **)argp++;
                while(*p) 
                        *buf++ = *p++;
                break;

            default :
                *buf++ = *format; /* % 뒤에엉뚱한문자인경우*/
                break;
        }

        format++;
    }
    *buf = '\0';

    return(buf-start);
}

main()
{
    char buf[80];

    _sprintf( buf, "%d, %x, %X, %s\n", 1234, 0xabcd, 0xabcd, "abcd"); 
    puts(buf);
}