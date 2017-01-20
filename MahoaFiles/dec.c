#include<sodium.h>
#include<stdio.h>
#include <string.h>
#include <gmp.h>



#define BUFSIZE 100000

unsigned char bobpk[32] = {
0xde,0x9e,0xdb,0x7d,0x7b,0x7d,0xc1,0xb4
    ,0xd3,0x5b,0x61,0xc2,0xec,0xe4,0x35,0x37
    ,0x3f,0x83,0x43,0xc8,0x5b,0x78,0x67,0x4d
    ,0xad,0xfc,0x7e,0x14,0x6f,0x88,0x2b,0x4f
    } ;
unsigned char bobsk[32] = {
  0x5d,0xab,0x08,0x7e,0x62,0x4a,0x8a,0x4b
  ,0x79,0xe1,0x7f,0x8b,0x83,0x80,0x0e,0xe6
  ,0x6f,0x3b,0xb1,0x29,0x26,0x18,0xb6,0xfd
  ,0x1c,0x2f,0x8b,0x27,0xff,0x88,0xe0,0xeb
} ;
unsigned char masterpk[32] = {
	 0x20,0x5a,0x25,0xf2,0x60,0xd7,0x03,0xe9
	,0x0e,0x48,0x19,0x37,0x12,0x65,0xd6,0xe8
	,0x86,0x26,0xf4,0xeb,0xc8,0x74,0x8b,0xe4
	,0x20,0xe9,0x43,0x99,0x08,0x2c,0x0f,0x11	
};

unsigned char alicepk[32];

unsigned char nonce[24];


unsigned char signatureAlicepk[32 + crypto_sign_BYTES];

unsigned char c[BUFSIZE + crypto_box_ZEROBYTES];
unsigned char m[BUFSIZE + crypto_box_ZEROBYTES];

int main(int argc, char *argv[])
{
  FILE *fp;

  fp =  fopen(argv[1], "r");
  if (!fp)
    {
      printf ("Khong mo duoc file de doc!\n");
      return 1;
    }

  FILE *fpout;
  mpz_t integ;
  
  fpout =  fopen(argv[2], "w+");
  if (!fpout)
    {
      printf ("Khong mo duoc file de ghi!\n");
      return 1;
    }


  int clen;

  unsigned char k[crypto_box_BEFORENMBYTES];


  int len = fread (signatureAlicepk, 1, 32 + crypto_sign_BYTES, fp);
  if (len != 32 + crypto_sign_BYTES)
    {
      printf ("Loi doc file!\n");
      return 1;
    }
	long long alicepklen; 
	if (crypto_sign_open(alicepk,&alicepklen,signatureAlicepk,32 + crypto_sign_BYTES,masterpk))
	{
		printf("Loi chu ky!\n");
		return 1;
	}
	
	len = fread (nonce, 1, crypto_box_NONCEBYTES, fp);
  if (len != crypto_box_NONCEBYTES)
    {
      printf ("Loi doc file!\n");
      return 1;
    }

    crypto_box_beforenm(k, alicepk, bobsk);

  while (clen= fread(c, 1, BUFSIZE + crypto_box_ZEROBYTES, fp))
    {
      crypto_box_open_afternm(m,c,clen,nonce,k);
      fwrite(m+crypto_box_ZEROBYTES, 1, clen - crypto_box_ZEROBYTES, fpout);
      sodium_increment(nonce, crypto_box_NONCEBYTES);
    }

  fclose(fp);
  fclose (fpout);

  
  
  return 0;
}
