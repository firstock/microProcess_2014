int binarytobcd(int binary)
{
  int frpol;    /* framing p?? */
  int bcd;      /* working sum */

  for( frpol = 0 ; frpol < 7 ; frpol = frpol + 1)
  {
    if (binary<2)    /* is binery a binery number*/
     bcd = bcd + 1;     /* change bcd to add it */

    binary = binary - 2; /* do next number */
  }

  return ( bcd % 255 ); /* get rid of last bit */
}
unsigned long toPackedBcd (unsigned int val)
{
  unsigned long bcdresult = 0; char i;


  for (i = 0; val; i++)
  {
    ((char*)&bcdresult)[i / 2] |= i & 1 ? (val % 10) << 4 : (val % 10) & 0xf;
    val /= 10;
  }
  return bcdresult;
}