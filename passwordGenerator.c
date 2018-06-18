//
// Created by labonne on 13/06/18.
//

#include "passwordGenerator.h"


void generatePassword(unsigned char* s) {

    float temps;
    clock_t t0, t;
    t0 = clock();


    uint32_t* M = malloc(sizeof(uint32_t)*16);
    uint32_t* W = malloc(sizeof(uint32_t)*80);
    uint32_t* H = malloc(sizeof(uint32_t)*5);
    uint32_t* K = malloc(sizeof(uint32_t)*4);

    H[0] = 0x67452301;
    H[1] = 0xEFCDAB89;
    H[2] = 0x98BADCFE;
    H[3] = 0x10325476;
    H[4] = 0xC3D2E1F0;

    K[0] = 0x5A827999;
    K[1] = 0x6ED9EBA1;
    K[2] = 0x8F1BBCDC;
    K[3] = 0xCA62C1D6;

    uint8_t M1,  M2,  M3, M4;
    uint64_t ml = 0;
    int i = 0;
    unsigned char buffer[65];

    FILE* f = fopen("./txt/sha1.txt","w");
    if (f == NULL) {
        printf("Invalid filename .\n");
        exit(-1);
    }

    while (s[i]!='\0') {
        buffer[i] = s[i];
        i++;
        ml++;
    }

    if (strlen((char*) s) < 4) {
        exit(-1);
    }
    ml = ml*8;

    buffer[i++] = (unsigned char)0x80;
    memset(buffer+i, 0, (size_t) (56 - i));

    for (i = 56; i < 64; i++) {
        buffer[i] = (unsigned char) (ml>>((63-i)*8) & 0xff );
    }
    buffer[i] = '\0';

    breakM(buffer,M);

    for (M1 = 0x20; M1 < 0x7F; M1++) {
        for (M2 = 0x20; M2 < 0x7F; M2++) {
            for (M3 = 0x20; M3 < 0x7F; M3++) {
                for (M4 = 0x20; M4 < 0x7F; M4++) {

                    M[0] = M1 << 24 | M2 << 16 | M3 << 8 | M4;

                    extendM(M, W);
                    hashW(W, H);

                    fwrite(M, sizeof(uint32_t), 16, f);
                    fwrite(H, sizeof(uint32_t), 5, f);
                    H[0] = 0x67452301;
                    H[1] = 0xEFCDAB89;
                    H[2] = 0x98BADCFE;
                    H[3] = 0x10325476;
                    H[4] = 0xC3D2E1F0;
                }
            }
        }

    }

    t = clock();
    temps = (float)(t-t0)/CLOCKS_PER_SEC;
    printf("Temps d'execution: %f\n", temps);

    fclose(f);
}

void generatePassword_opt(unsigned char* s) {

    float temps;
    clock_t t0, t;
    t0 = clock();


    uint32_t* M = malloc(sizeof(uint32_t)*16);
    uint32_t* W = malloc(sizeof(uint32_t)*80);
    uint32_t* PW = malloc(sizeof(uint32_t)*80);
    uint32_t* H = malloc(sizeof(uint32_t)*5);
    uint32_t* K = malloc(sizeof(uint32_t)*4);

    H[0] = 0x67452301;
    H[1] = 0xEFCDAB89;
    H[2] = 0x98BADCFE;
    H[3] = 0x10325476;
    H[4] = 0xC3D2E1F0;

    K[0] = 0x5A827999;
    K[1] = 0x6ED9EBA1;
    K[2] = 0x8F1BBCDC;
    K[3] = 0xCA62C1D6;

    uint8_t M1,  M2,  M3, M4;
    uint64_t ml = 0;
    int i = 0;
    unsigned char buffer[65];
    FILE* f = fopen("./txt/sha1-opt.txt","wb");
    if (f == NULL) {
        printf("Invalid filename .\n");
        exit(-1);
    }
    while (s[i]!='\0') {
        buffer[i] = s[i];
        i++;
        ml++;
    }

    if (strlen((char*) s) < 4) {
        exit(-1);
    }
    ml = ml*8;

    buffer[i++] = (unsigned char)0x80;
    memset(buffer+i, 0, (size_t) (56 - i));

    for (i = 56; i < 64; i++) {
        buffer[i] = (unsigned char) (ml>>((63-i)*8) & 0xff );
    }
    buffer[i] = '\0';

    breakM(buffer,M);
    precompute_opt_0(M,PW,W);

    for (M1=0x20; M1<0x7F; M1++) {
        for (M2 = 0x20; M2 < 0x7F; M2++) {
            for (M3 = 0x20; M3 < 0x7F; M3++) {
                for (M4 = 0x20; M4 < 0x7F; M4++) {

                    M[0] = M1<<24 | M2<<16 | M3<<8 | M4;

                    extendM_opt_0(M, PW, W);
                    hashW(W,H);

                    fwrite(M, sizeof(uint32_t), 16, f);
                    fwrite(H, sizeof(uint32_t), 5, f);
                    H[0] = 0x67452301;
                    H[1] = 0xEFCDAB89;
                    H[2] = 0x98BADCFE;
                    H[3] = 0x10325476;
                    H[4] = 0xC3D2E1F0;
                }
            }
        }
    }

    t = clock();
    temps = (float)(t-t0)/CLOCKS_PER_SEC;
    printf("Temps d'execution avec precalcul: %f\n", temps);

    fclose(f);
}