#include<sodium.h>
#include<stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  unsigned char pk[crypto_sign_PUBLICKEYBYTES];
  unsigned char sk[crypto_sign_SECRETKEYBYTES];

  // Alice public key
  unsigned char alicepk[32] = {
    0x85,0x20,0xf0,0x09,0x89,0x30,0xa7,0x54
    ,0x74,0x8b,0x7d,0xdc,0xb4,0x3e,0xf7,0x5a
    ,0x0d,0xbf,0x3a,0x0d,0x26,0x38,0x1a,0xf4
    ,0xeb,0xa4,0xa9,0x8e,0xaa,0x9b,0x4e,0x6a
  } ;
  

  long long alicepklen = sizeof alicepk;
  unsigned char sm[alicepklen+crypto_sign_BYTES]; unsigned long long smlen;


  

  crypto_sign_keypair(pk,sk);
  int i;
  printf ("Master s'Public key\n");
   for (i = 0;i < crypto_sign_PUBLICKEYBYTES;++i) {
    printf(",0x%02x",(unsigned int) pk[i]);
    if (i % 8 == 7) printf("\n");
  }

  crypto_sign(sm,&smlen,alicepk,alicepklen,sk);
  printf ("Kich thuoc chu ky:%lld", smlen);
  printf ("\n Signature of Alice's pk \n");
  for (i = 0;i < smlen;++i) {
   printf(",0x%02x",(unsigned int) sm[i]);
   if (i % 8 == 7) printf("\n");
 }

  // // Lay lai message tu chu ky.
//   unsigned char m2[163];
//   long long mlen2;
//
//   if (!crypto_sign_open(m2,&mlen2,sm,smlen,pk))
//     printf ("\nOK!");
//   else
//     printf ("\nFail!");

  return 0;
}
