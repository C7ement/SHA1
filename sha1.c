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
            printBreakM(M);
            extendM(M,W);
            printW(W);
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
        printf("\n%s\n",buffer);
        printBreakM(M);
        extendM(M,W);
        printW(W);
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
    printf("\n%s\n",buffer);
    //printf("%d %d %d %d %d %d %d %d \n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[60],buffer[61],buffer[62],buffer[63]);
    printBreakM(M);
    extendM(M,W);
    printW(W);
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

/*----------------------------------------------------------------------------*/

uint32_t* SHA1_opt_0(unsigned char* s) {

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
            precompute_opt_0(M,W);
            extendM_opt_0(M,W);
            printW(W);
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
        printf("\n%s\n",buffer);
        precompute_opt_0(M,W);
        extendM_opt_0(M,W);
        printW(W);
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
    printf("\n%s\n",buffer);
    //printf("%d %d %d %d %d %d %d %d \n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[60],buffer[61],buffer[62],buffer[63]);
    precompute_opt_0(M,W);
    extendM_opt_0(M,W);
    printW(W);
    hashW(W,K,H);

    //finalHash = H[0]<<128 | H[1]<<96 | H[2]<<64 | H[3]<<32 | H[4];

    return H;
}

void precompute_opt_0(uint32_t* M, uint32_t* W) {
  int i;
  uint32_t tmp;
  W[0] = 0x0000;
  for (i=1; i<16; i++) {
    W[i] = M[i];
  }
  for (i=16; i<80; i++) {
    tmp = W[i-3] ^ W[i-8] ^ W[i-14] ^ W[i-16];
    W[i] = tmp<<1 | tmp>>31;
  }
}

void extendM_opt_0(uint32_t* M, uint32_t* W) {
  int i;
  uint32_t w0[23];
  w0[0] = M[0];
  for (i=1; i<23; i++) {
    w0[i] = w0[i-1]<<1 | w0[i-1]>>31;
  }
  W[0] = M[0];

  uint32_t w_2_3 = w0[2] ^ w0[3];
  uint32_t w_2_4 = w0[2] ^ w0[4];
  uint32_t w_4_6 = w0[4] ^ w0[6];//
  uint32_t w_4_8 = w0[4] ^ w0[8];
  uint32_t w_4_9 = w0[4] ^ w0[9];
  uint32_t w_4_11 = w0[4] ^ w0[11];
  uint32_t w_6_8 = w0[6] ^ w0[8];
  uint32_t w_8_12 = w0[8] ^ w0[12];
  uint32_t w_8_16 = w0[8] ^ w0[16];
  uint32_t w_8_18 = w0[8] ^ w0[18];
  uint32_t w_8_22 = w0[8] ^ w0[22];
  uint32_t w_12_16 = w0[12] ^ w0[16];
  uint32_t w_12_19 = w0[12] ^ w0[19];
  uint32_t w_14_16 = w0[14] ^ w0[16];
  uint32_t w_3_6_7 =
  uint32_t w_3_4_5_8_10 =
  uint32_t w_4_6_7_8_12_17 =
  uint32_t w_4_6_7_10_11 =
  uint32_t w_4_6_8_12 =
  uint32_t w_4_7_8_12_14 =
  uint32_t w_4_8_13 =
  uint32_t w_4_8_15 =
  uint32_t w_5_11_12_13_16_18 =
  uint32_t w_6_12_14 =
  uint32_t w_7_8_12_16_21 =
  uint32_t w_7_8_15_18_20 =
  uint32_t w_7_10_12 =
  uint32_t w_11_14_15 =

  W[16] = W[16] ^ w0[1];
  W[19] = W[19] ^ w0[2];
  W[22] = W[22] ^ w0[3];
  W[24] = W[24] ^ w0[2];
  W[25] = W[25] ^ w0[4];
  W[28] = W[28] ^ w0[5];
  W[30] = W[30] ^ w_2_4;
  W[31] = W[31] ^ w0[6];
  W[32] = W[32] ^ w_2_3;
  W[34] = W[34] ^ w0[7];
  W[35] = W[35] ^ w0[4];
  W[36] = W[36] ^ w_4_6;
  W[37] = W[37] ^ w0[8];
  W[38] = W[38] ^ w0[4];
  W[40] = W[40] ^ w_4_9;
  W[42] = W[42] ^ w_6_8;
  W[43] = W[43] ^ w0[10];
  W[44] = W[44] ^ w0[3] ^ w0[6] ^ w0[7];
  W[46] = W[46] ^ w_4_11;



  W[47] = W[47] ^ w_4_8;
  W[48] = W[48] ^ w0[3] ^ w0[4] ^ w0[5] ^ w0[8] ^ w0[10];
  W[49] = W[49] ^ w0[12];
  W[50] = W[50] ^ w0[8];
  W[51] = W[51] ^ w_4_6;
  W[52] = W[52] ^ w0[4] ^ w0[8] ^ w0[13];
  W[54] = W[54] ^ w0[7] ^ w0[10] ^ w0[12];
  W[55] = W[55] ^ w0[14];
  W[56] = W[56] ^ w0[4] ^ w0[6] ^ w0[7] ^ w0[10] ^ w0[11];
  W[57] = W[57] ^ w0[8];
  W[58] = W[58] ^ w0[4] ^ w0[8] ^ w0[15];
  W[59] = W[59] ^ w_8_12;
  W[60] = W[60] ^ w0[4] ^ w0[7] ^ w0[8] ^ w0[12] ^ w0[14];
  W[61] = W[61] ^ w0[16];
  W[62] = W[62] ^ w0[4] ^ w0[6] ^ w0[8] ^ w0[12];
  W[63] = W[63] ^ w0[8];
  W[64] = W[64] ^ w0[4] ^ w0[6] ^ w0[7] ^ w0[8] ^ w0[12] ^ w0[17];
  W[66] = W[66] ^ w_14_16;
  W[67] = W[67] ^ w0[8] ^ w0[18];
  W[68] = W[68] ^ w0[11] ^ w0[14] ^ w0[15];
  W[70] = W[70] ^ w_12_19;
  W[71] = W[71] ^ w_12_16;
  W[72] = W[72] ^ w0[5] ^ w0[11] ^ w0[12] ^ w0[13] ^ w0[16] ^ w0[18];
  W[73] = W[73] ^ w0[20];
  W[74] = W[74] ^ w_8_16;
  W[75] = W[75] ^ w0[6] ^ w0[12] ^ w0[14];
  W[76] = W[76] ^ w0[7] ^ w0[8] ^ w0[12] ^ w0[16] ^ w0[21];
  W[78] = W[78] ^ w0[7] ^ w0[8] ^ w0[15] ^ w0[18] ^ w0[20];
  W[79] = W[79] ^ w_8_22;

}

/**
 *Fonction permettant de déterminer la rotation de w[t] à ajouter à chaque PW.
 *
 */
void w0_occurence(int t) {
  int i,j;
  int** wt = malloc(sizeof(int*)*80);
  for (i=0; i<16; i++) {
    wt[i] = calloc(sizeof(int),32);
  }
  wt[t][0] = 1;
  for (i=16; i<80; i++) {
    wt[i] = calloc(sizeof(int),32);
    //printf ("W[%d] = W[%d]",i,i);
    printf ("uint32_t w",i,i);
    for (j=0; j<32; j++) {
      wt[i][(j+1)%32] = (wt[i-3][j] + wt[i-8][j] + wt[i-14][j] + wt[i-16][j])%2;

      if (wt[i][(j+1)%32]) {
        //printf (" ^ w%d[%d]",t,j+1);
        printf ("_%d",j+1);
      }
    }
    //printf (";\n");
    printf (" = \n");
  }
}
