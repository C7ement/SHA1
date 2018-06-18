//
// Created by labonne on 13/06/18.
//

#include "sha1opt.h"

uint32_t* sha1_opt_0(unsigned char *s) {

    uint32_t* M = malloc(sizeof(uint32_t)*16);
    uint32_t* W = malloc(sizeof(uint32_t)*80);
    uint32_t* PW = malloc(sizeof(uint32_t)*80);
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

    int i = 0;
    int j = 0;
    unsigned char buffer[65]; // 64 ou 65 ??

    while (s[i*64+j]!='\0') {
        buffer[j] = s[i*64+j];
        if (j < 63) {
            j++;
        } else {
            j++;
            buffer[j] = '\0';
            i++;
            j = 0;

            breakM(buffer,M);
            precompute_opt_0(M,PW,W);
            extendM_opt_0(M,PW,W);
            hashW(W,H);
        }
    }

    ml = (i*64+j)*8;
    buffer[j++] = (unsigned char)0x80;

    if (j < 57) {
        memset(buffer+j,0,56-j);
    } else {
        memset(buffer+j,0,64-j);
        breakM(buffer,M);
        precompute_opt_0(M,PW,W);
        extendM_opt_0(M,PW,W);
        hashW(W,H);
        memset(buffer,0,56);
    }

    for (j = 56; j < 64; j++) {
        buffer[j] = (unsigned char) (ml>>((63-j)*8) & 0xff );
    }

    buffer[j] = '\0';
    breakM(buffer,M);
    precompute_opt_0(M,PW,W);
    extendM_opt_0(M,PW,W);
    hashW(W,H);
    return H;
}

void precompute_opt_0(uint32_t* M, uint32_t* PW, uint32_t* W) {
    int i;
    uint32_t tmp;
    W[0] = 0x0000;
    PW[0] = 0x0000;
    for (i=1; i<16; i++) {
        W[i] = M[i];
        PW[i] = M[i];
    }
    for (i=16; i<80; i++) {
        tmp = PW[i-3] ^ PW[i-8] ^ PW[i-14] ^ PW[i-16];
        PW[i] = tmp<<1 | tmp>>31;
        W[i] = PW[i];
    }
}

void extendM_opt_0(uint32_t* M, uint32_t* PW, uint32_t* W) {
    int i;
    uint32_t w0[23];
    w0[0] = M[0];
    for (i=1; i<23; i++) {
        w0[i] = w0[i-1]<<1 | w0[i-1]>>31;
    }
    W[0] = M[0];

    uint32_t w_4_6 = w0[4] ^ w0[6];
    uint32_t w_4_8 = w0[4] ^ w0[8];
    uint32_t w_7_8 = w0[7] ^ w0[8];
    uint32_t w_8_12 = w0[8] ^ w0[12];
    uint32_t w_12_16 = w0[12] ^ w0[16];
    uint32_t w_4_6_7 = w_4_6 ^ w0[7];
    uint32_t w_4_8_12 = w_4_8 ^ w0[12];

    W[16] = PW[16] ^ w0[1];
    W[19] = PW[19] ^ w0[2];
    W[22] = PW[22] ^ w0[3];
    W[24] = PW[24] ^ w0[2];
    W[25] = PW[25] ^ w0[4];
    W[28] = PW[28] ^ w0[5];
    W[30] = PW[30] ^ w0[2] ^ w0[4];
    W[31] = PW[31] ^ w0[6];
    W[32] = PW[32] ^ w0[2] ^ w0[3];
    W[34] = PW[34] ^ w0[7];
    W[35] = PW[35] ^ w0[4];
    W[36] = PW[36] ^ w_4_6;
    W[37] = PW[37] ^ w0[8];
    W[38] = PW[38] ^ w0[4];
    W[40] = PW[40] ^ w0[4] ^ w0[9];
    W[42] = PW[42] ^ w0[6] ^ w0[8];
    W[43] = PW[43] ^ w0[10];
    W[44] = PW[44] ^ w0[3] ^ w0[6] ^ w0[7];
    W[46] = PW[46] ^ w0[4] ^ w0[11];
    W[47] = PW[47] ^ w_4_8;
    W[48] = PW[48] ^ w0[3] ^ w_4_8 ^ w0[5] ^ w0[10];
    W[49] = PW[49] ^ w0[12];
    W[50] = PW[50] ^ w0[8];
    W[51] = PW[51] ^ w_4_6;
    W[52] = PW[52] ^ w_4_8 ^ w0[13];
    W[54] = PW[54] ^ w0[7] ^ w0[10] ^ w0[12];
    W[55] = PW[55] ^ w0[14];
    W[56] = PW[56] ^ w_4_6_7 ^ w0[10] ^ w0[11];
    W[57] = PW[57] ^ w0[8];
    W[58] = PW[58] ^ w_4_8 ^ w0[15];
    W[59] = PW[59] ^ w_8_12;
    W[60] = PW[60] ^ w_4_8_12 ^ w0[7] ^ w0[14];
    W[61] = PW[61] ^ w0[16];
    W[62] = PW[62] ^ w0[6] ^ w_4_8_12;
    W[63] = PW[63] ^ w0[8];
    W[64] = PW[64] ^ w_4_6_7 ^ w_8_12 ^ w0[17];
    W[66] = PW[66] ^ w0[14] ^ w0[16];
    W[67] = PW[67] ^ w0[8] ^ w0[18];
    W[68] = PW[68] ^ w0[11] ^ w0[14] ^ w0[15];
    W[70] = PW[70] ^ w0[12] ^ w0[19];
    W[71] = PW[71] ^ w_12_16;
    W[72] = PW[72] ^ w0[5] ^ w0[11] ^ w_12_16 ^ w0[13] ^ w0[18];
    W[73] = PW[73] ^ w0[20];
    W[74] = PW[74] ^ w0[8] ^ w0[16];
    W[75] = PW[75] ^ w0[6] ^ w0[12] ^ w0[14];
    W[76] = PW[76] ^ w_7_8 ^ w_12_16 ^ w0[21];
    W[78] = PW[78] ^ w_7_8 ^ w0[15] ^ w0[18] ^ w0[20];
    W[79] = PW[79] ^ w0[8] ^ w0[22];

}

/**
 * Fonction permettant de déterminer la rotation de w[t] à ajouter à chaque PW
 * Et donc d'obtenir W[i] en fonction de sa valeur pre calculé et des rotations de w0
 */
void wt_occurence(int t) {
    int i,j;
    int** wt = malloc(sizeof(int*)*80);
    for (i=0; i<16; i++) {
        wt[i] = calloc(sizeof(int),32);
    }
    wt[t][0] = 1;
    for (i=16; i<80; i++) {
        wt[i] = calloc(sizeof(int),32);
        printf("W[%d] = W[%d]",i,i);
        //printf("uint32_t w",i,i);
        for (j=0; j<32; j++) {
            wt[i][(j+1)%32] = (wt[i-3][j] + wt[i-8][j] + wt[i-14][j] + wt[i-16][j])%2;

            if (wt[i][(j+1)%32]) {
                printf(" ^ w%d[%d]",t,j+1);
                //printf("_%d",j+1);
            }
        }
        printf(";\n");
        //printf (" = \n");
    }
}
