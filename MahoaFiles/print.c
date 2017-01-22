#include "print.h"

void print (unsigned char *m, long long mlen)
{
  int i;
  for (i = 0;i < mlen;++i) {
    printf(",0x%02x",(unsigned int) m[i]);
    if (i % 8 == 7) printf("\n");
  }
  printf("\n");

}

