#include<sodium.h>
#include<stdio.h>
#include <string.h>

#define BUFSIZE 100000
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
unsigned char alicepk[32] = {
  0x85,0x20,0xf0,0x09,0x89,0x30,0xa7,0x54
  ,0x74,0x8b,0x7d,0xdc,0xb4,0x3e,0xf7,0x5a
  ,0x0d,0xbf,0x3a,0x0d,0x26,0x38,0x1a,0xf4
  ,0xeb,0xa4,0xa9,0x8e,0xaa,0x9b,0x4e,0x6a
} ;
unsigned char bobpk[32] = {
  0xde,0x9e,0xdb,0x7d,0x7b,0x7d,0xc1,0xb4
  ,0xd3,0x5b,0x61,0xc2,0xec,0xe4,0x35,0x37
  ,0x3f,0x83,0x43,0xc8,0x5b,0x78,0x67,0x4d
  ,0xad,0xfc,0x7e,0x14,0x6f,0x88,0x2b,0x4f
} ;

unsigned char nonce[24] = {
  0x69,0x69,0x6e,0xe9,0x55,0xb6,0x2b,0x73
  ,0xcd,0x62,0xbd,0xa8,0x75,0xfc,0x73,0xd6
  ,0x82,0x19,0xe0,0x03,0x6b,0x7a,0x0b,0x37
} ;


unsigned char m[BUFSIZE + crypto_box_ZEROBYTES] = {
  0, 0, 0,  0,  0, 0, 0, 0
  , 0, 0, 0, 0, 0, 0, 0, 0
  , 0, 0, 0, 0, 0, 0, 0, 0
  ,0, 0, 0, 0, 0, 0, 0, 0
  ,0xbe,0x07,0x5f,0xc5,0x3c,0x81,0xf2,0xd5
  ,0xcf,0x14,0x13,0x16,0xeb,0xeb,0x0c,0x7b
  ,0x52,0x28,0xc5,0x2a,0x4c,0x62,0xcb,0xd4
  ,0x4b,0x66,0x84,0x9b,0x64,0x24,0x4f,0xfc
  ,0xe5,0xec,0xba,0xaf,0x33,0xbd,0x75,0x1a
  ,0x1a,0xc7,0x28,0xd4,0x5e,0x6c,0x61,0x29
  ,0x6c,0xdc,0x3c,0x01,0x23,0x35,0x61,0xf4
  ,0x1d,0xb6,0x6c,0xce,0x31,0x4a,0xdb,0x31
  ,0x0e,0x3b,0xe8,0x25,0x0c,0x46,0xf0,0x6d
  ,0xce,0xea,0x3a,0x7f,0xa1,0x34,0x80,0x57
  ,0xe2,0xf6,0x55,0x6a,0xd6,0xb1,0x31,0x8a
  ,0x02,0x4a,0x83,0x8f,0x21,0xaf,0x1f,0xde
  ,0x04,0x89,0x77,0xeb,0x48,0xf5,0x9f,0xfd
  ,0x49,0x24,0xca,0x1c,0x60,0x90,0x2e,0x52
  ,0xf0,0xa0,0x89,0xbc,0x76,0x89,0x70,0x40
  ,0xe0,0x82,0xf9,0x37,0x76,0x38,0x48,0x64
  ,0x5e,0x07,0x05
} ;

unsigned char c[BUFSIZE + crypto_box_ZEROBYTES];

int main(int argc, char *argv[])
{
  FILE *fp;

  fp =  fopen(argv[1], "r");
  if (!fp)
    {
      printf ("Khong mo duoc file!\n");
      return 1;
    }

  FILE *fpout;

  fpout =  fopen(argv[2], "w+");
  if (!fpout)
    {
      printf ("Khong mo duoc file de ghi!\n");
      return 1;
    }


  int mlen;
  
  unsigned char k[crypto_box_BEFORENMBYTES];

  
  crypto_box_beforenm(k, alicepk, bobsk);

  randombytes(nonce, crypto_box_NONCEBYTES);
  
  int len = fwrite (nonce, 1, crypto_box_NONCEBYTES, fpout);
  
  if (len != crypto_box_NONCEBYTES)
    {
      printf ("Loi ghi file!\n");
      return 1;
    }

  while (mlen= fread(m+crypto_box_ZEROBYTES, 1, BUFSIZE, fp))
    {
      mlen += crypto_box_ZEROBYTES;
      crypto_box_afternm(c,m,mlen,nonce,k);
      fwrite(c, 1, mlen, fpout);
      sodium_increment(nonce, crypto_box_NONCEBYTES);
    }
  fclose(fp);
  fclose (fpout);

  
  
  return 0;
}
