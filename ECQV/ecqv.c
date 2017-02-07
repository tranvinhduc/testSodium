#include <sodium.h>
#include <string.h>

#define DEVICE "A"

void deviceInit (unsigned char *RA, unsigned char  *deviceName);


int main(int argc, char *argv[])
{
  if (sodium_init() == -1)
    {
      return 1;
    }
    

  
    
  return 0;
}

void deviceInit (unsigned char *RA, unsigned char  *deviceName)
{
  unsigned char rA[crypto_scalarmult_SCALARBYTES];
  randombytes_buf(rA, crypto_scalarmult_SCALARBYTES); //sinh ngau nhien rA

  crypto_scalarmult_base(RA, rA);
  strcpy (deviceName, DEVICE);  
}

void CA_GenCert (unsigned char *PA, unsigned char *gammaA, unsigned char *RA, unsigned char *deviceName)
{
   unsigned char  k[crypto_scalarmult_SCALARBYTES];
   unsigned char kG[crypto_scalarmult_BYTES];
   randombytes_buf(k, crypto_scalarmult_SCALARBYTES); //sinh ngau nhien rA

  crypto_scalarmult_base(kG, k);
  //Phai cai dat ham cong diem cho Curve25519
   
}
