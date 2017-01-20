#include <sodium.h>
int main(void)
{
  if (sodium_init() == -1) {
    return 1;
  }

  unsigned char alicesk[32] = {
    0x77,0x07,0x6d,0x0a,0x73,0x18,0xa5,0x7d
    ,0x3c,0x16,0xc1,0x72,0x51,0xb2,0x66,0x45
    ,0xdf,0x4c,0x2f,0x87,0xeb,0xc0,0x99,0x2a
    ,0xb1,0x77,0xfb,0xa5,0x1d,0xb9,0x2c,0x2a
  } ;

  unsigned char bobsk[32] = {
    0x5d,0xab,0x08,0x7e,0x62,0x4a,0x8a,0x4b
    ,0x79,0xe1,0x7f,0x8b,0x83,0x80,0x0e,0xe6
    ,0x6f,0x3b,0xb1,0x29,0x26,0x18,0xb6,0xfd
    ,0x1c,0x2f,0x8b,0x27,0xff,0x88,0xe0,0xeb
  } ;

  unsigned char alicepk[32];
  unsigned char bobpk[32];
  unsigned char k[32];
  int i;

  unsigned char zero[32] = {0};
  unsigned char c[16] = {
    0x65,0x78,0x70,0x61,0x6e,0x64,0x20,0x33
    ,0x32,0x2d,0x62,0x79,0x74,0x65,0x20,0x6b
  } ;
  unsigned char firstkey[32];

  crypto_scalarmult_curve25519_base(alicepk,alicesk);
  crypto_scalarmult_curve25519_base(bobpk, bobsk);
  printf("Alice--\n");
  for (i = 0;i < 32;++i) {
    if (i > 0) printf(","); else printf(" ");
    printf("0x%02x",(unsigned int) alicepk[i]);
    if (i % 8 == 7) printf("\n");
  }

  
  
  printf("Shared key 1--\n");
  crypto_scalarmult_curve25519 (k, bobsk, alicepk);
  for (i = 0;i < 32;++i) {
    if (i > 0) printf(","); else printf(" ");
    printf("0x%02x",(unsigned int) k[i]);
    if (i % 8 == 7) printf("\n");
  }

  printf("first key:\n");
  crypto_core_hsalsa20(firstkey, zero, k, c);
  for (i = 0;i < 32;++i) {
    if (i > 0) printf(","); else printf(" ");
    printf("0x%02x",(unsigned int) firstkey[i]);
    if (i % 8 == 7) printf("\n");
  }

  printf ("second key:\n");

  unsigned char nonceprefix[16] = {
    0x69,0x69,0x6e,0xe9,0x55,0xb6,0x2b,0x73
    ,0xcd,0x62,0xbd,0xa8,0x75,0xfc,0x73,0xd6
  } ;

  unsigned char secondkey[32];
  crypto_core_hsalsa20(secondkey, nonceprefix, firstkey, c);

  for (i = 0;i < 32;++i) {
    if (i > 0) printf(","); else printf(" ");
    printf("0x%02x",(unsigned int) secondkey[i]);
    if (i % 8 == 7) printf("\n");
  }

  unsigned char noncesuffix[8] = {
    0x82,0x19,0xe0,0x03,0x6b,0x7a,0x0b,0x37
  } ;

  unsigned char in[16] = { 0 } ;
  unsigned char outputblock[64];

  printf("Output:" );
  for (i = 0;i < 8;++i) in[i] = noncesuffix[i];
  do {
    do {
      crypto_core_salsa20(outputblock,in,secondkey,c);
      for (i = 0;i < 64;++i) putchar(outputblock[i]);
    } while (++in[8]);
  } while (++in[9]);


  return 0;
 
}
