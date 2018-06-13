//
// Created by clement on 07/06/18.
//

#include "sha1.h"

uint32_t* SHA1(unsigned char* s) {

    uint32_t* M = malloc(sizeof(uint32_t)*16);
    uint32_t* W = malloc(sizeof(uint32_t)*80);
    uint32_t* H = malloc(sizeof(uint32_t)*5);
    uint32_t* K = malloc(sizeof(uint32_t)*4);
    H[0]  = 0x67452301;
    H[1]  = 0xEFCDAB89;
    H[2]  = 0x98BADCFE;
    H[3]  = 0x10325476;
    H[4]  = 0xC3D2E1F0;
    K[0] = 0x5A827999;
    K[1] = 0x6ED9EBA1;
    K[2] = 0x8F1BBCDC;
    K[3] = 0xCA62C1D6;

    uint64_t ml;
    //uint160_t finalHash;

    int i = 0;
    int j = 0;
    unsigned char buffer[65]; // 64 ou 65 ??
    /*      PADDING     */
    while (s[i*64+j]!='\0') {
        buffer[j] = s[i*64+j];
        if (j < 63) {
            j++;
        } else {
            j++;
            buffer[j] = '\0';
            i++;
            j = 0;
            //appeler fonction haschage pour buffer
            breakM(buffer,M);
            printf("\n%s\n",buffer);
            //printBreakM(M);
            extendM(M,W);
            //printW(W);
            hashW(W,K,H);
            //
        }
    }
    ml = (i*64+j)*8;
    buffer[j++] = (unsigned char)0x80;

    if (j < 57) {
        memset(buffer+j,0,56-j);
    } else {
        memset(buffer+j,0,64-j);
        //appeler fonction haschage pour buffer
        breakM(buffer,M);
        //printf("\n%s\n",buffer);
        //printBreakM(M);
        extendM(M,W);
        //printW(W);
        hashW(W,K,H);
        //f560eda0
        memset(buffer,0,56);
    }
    for (j = 56; j < 64; j++) {
        buffer[j] = (unsigned char) (ml>>((63-j)*8) & 0xff );
    }
    buffer[j] = '\0';
    //appeler fonction haschage pour buffer
    breakM(buffer,M);
    //printf("\n%s\n",buffer);
    //printf("%d %d %d %d %d %d %d %d \n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[60],buffer[61],buffer[62],buffer[63]);
    //printBreakM(M);
    extendM(M,W);
    //printW(W);
    hashW(W,K,H);

    //finalHash = H[0]<<128 | H[1]<<96 | H[2]<<64 | H[3]<<32 | H[4];

    return H;
}

void breakM(unsigned char* buffer, uint32_t* M) {
  int i;
  for (i=0; i<16; i++) {
    M[i] = (buffer[4*i]<<24) | (buffer[4*i+1])<<16 | (buffer[4*i+2]<<8) | (buffer[4*i+3]);
  }
}

void printBreakM(uint32_t* M) {
  int i;
  for (i=0; i<16; i++) {
    printf("%08lx ",M[i]);
  }
  printf("\n");
}

void extendM(uint32_t* M, uint32_t* W) {
  int i;
  uint32_t tmp;
  for (i=0; i<16; i++) {
    W[i] = M[i];
  }
  for (i=16; i<80; i++) {
    tmp = W[i-3] ^ W[i-8] ^ W[i-14] ^ W[i-16];
    W[i] = tmp<<1 | tmp>>31;
  }
}

void printW(uint32_t* W) {
  int i;
  printf("W: \n");
  for (i=0; i<80; i++) {
    printf("%08lx\t",W[i]);
  }
  printf("\n");
}

void hashW(uint32_t* W, uint32_t* K, uint32_t* H) {
  int i;
  uint32_t tmp;
  uint32_t a = H[0];
  uint32_t b = H[1];
  uint32_t c = H[2];
  uint32_t d = H[3];
  uint32_t e = H[4];
  for (i=0; i<20; i++) {
    tmp = (a<<5 | a>>27) + (b&c | ~b&d) + e + K[0] + W[i];
    e = d;
    d = c;
    c = b<<30 | b>>2;
    b = a;
    a = tmp;
  }
  for (i=20; i<40; i++) {
    tmp = (a<<5 | a>>27) + (b^c^d) + e + K[1] + W[i];
    e = d;
    d = c;
    c = b<<30 | b>>2;
    b = a;
    a = tmp;
  }
  for (i=40; i<60; i++) {
    tmp = (a<<5 | a>>27) + (b&c | b&d | c&d) + e + K[2] + W[i];
    e = d;
    d = c;
    c = b<<30 | b>>2;
    b = a;
    a = tmp;
  }
  for (i=60; i<80; i++) {
    tmp = (a<<5 | a>>27) + (b^c^d) + e + K[3] + W[i];
    e = d;
    d = c;
    c = b<<30 | b>>2;
    b = a;
    a = tmp;
  }
  H[0] += a;
  H[1] += b;
  H[2] += c;
  H[3] += d;
  H[4] += e;
}
