//
// Created by labonne on 18/06/18.
//

#include "solveHash.h"


int solveHashLen4EarlyExitAndPrecompute(uint32_t* hashToFind, unsigned char* s) {

    float temps;
    clock_t t0, t;
    t0 = clock();

    uint32_t* M = malloc(sizeof(uint32_t)*16);
    uint32_t* W = malloc(sizeof(uint32_t)*80);
    uint32_t* PW = malloc(sizeof(uint32_t)*80);
    uint32_t* H = malloc(sizeof(uint32_t)*5);

    uint8_t M1,  M2,  M3, M4;
    uint32_t h4, h;
    uint64_t ml;
    int i = 0;
    unsigned char buffer[65];
    ml = strlen((char*)s);
    unsigned char* s2 = malloc(sizeof(unsigned char)*ml);
    s2 = (unsigned char*) strcpy((char*)s2,(char*)s);

    h4 = hashToFind[4] - 0xC3D2E1F0;

    while (s[i]!='\0') {
        buffer[i] = s[i];
        i++;
    }

    ml = i*8;
    if (ml < 32) exit(-1);
    buffer[i++] = (unsigned char) 0x80;
    memset(buffer+i,0,56-i);
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
                    h = hashStep75(W)[0];
                    if (h == h4) {
                        s2[0] = (unsigned char) M1;
                        s2[1] = (unsigned char) M2;
                        s2[2] = (unsigned char) M3;
                        s2[3] = (unsigned char) M4;
                        if (compareHash(sha1(s2),hashToFind)) {
                            printf("\nMessage trouvé: %s\n", s2);
                            t = clock();
                            temps = (float)(t-t0)/CLOCKS_PER_SEC;
                            printf("Temps d'execution : %f\n", temps);
                            return 1;
                        }
                    }
                }
            }
        }
    }

    printf("\nMessage non trouvé.\n");
    t = clock();
    temps = (float)(t-t0)/CLOCKS_PER_SEC;
    printf("Temps d'execution : %f\n", temps);

    return 0;
}

int solveHashLen4EarlyExit(uint32_t* hashToFind, unsigned char* s) {

    float temps;
    clock_t t0, t;
    t0 = clock();

    uint32_t* M = malloc(sizeof(uint32_t)*16);
    uint32_t* W = malloc(sizeof(uint32_t)*80);
    uint32_t* PW = malloc(sizeof(uint32_t)*80);
    uint32_t* H = malloc(sizeof(uint32_t)*5);

    uint8_t M1,  M2,  M3, M4;
    uint32_t h4, h;
    uint64_t ml;
    int i = 0;
    unsigned char buffer[65];
    ml = strlen((char*)s);
    unsigned char* s2 = malloc(sizeof(unsigned char)*ml);
    s2 = (unsigned char*) strcpy((char*)s2,(char*)s);

    h4 = hashToFind[4] - 0xC3D2E1F0;

    while (s[i]!='\0') {
        buffer[i] = s[i];
        i++;
    }

    ml = i*8;
    if (ml < 32) exit(-1);
    buffer[i++] = (unsigned char) 0x80;
    memset(buffer+i,0,56-i);
    for (i = 56; i < 64; i++) {
        buffer[i] = (unsigned char) (ml>>((63-i)*8) & 0xff );
    }
    buffer[i] = '\0';

    breakM(buffer,M);

    for (M1=0x20; M1<0x7F; M1++) {
        for (M2 = 0x20; M2 < 0x7F; M2++) {
            for (M3 = 0x20; M3 < 0x7F; M3++) {
                for (M4 = 0x20; M4 < 0x7F; M4++) {

                    M[0] = M1<<24 | M2<<16 | M3<<8 | M4;
                    extendM(M, W);
                    h = hashStep75(W)[0];
                    if (h == h4) {
                        s2[0] = (unsigned char) M1;
                        s2[1] = (unsigned char) M2;
                        s2[2] = (unsigned char) M3;
                        s2[3] = (unsigned char) M4;
                        if (compareHash(sha1(s2),hashToFind)) {
                            printf("\nMessage trouvé: %s\n", s2);
                            t = clock();
                            temps = (float)(t-t0)/CLOCKS_PER_SEC;
                            printf("Temps d'execution : %f\n", temps);
                            return 1;
                        }
                    }
                }
            }
        }
    }

    printf("\nMessage non trouvé.\n");
    t = clock();
    temps = (float)(t-t0)/CLOCKS_PER_SEC;
    printf("Temps d'execution : %f\n", temps);

    return 0;
}

int solveHashLen4Precompute(uint32_t* hashToFind, unsigned char* s) {

    float temps;
    clock_t t0, t;
    t0 = clock();

    uint32_t* M = malloc(sizeof(uint32_t)*16);
    uint32_t* W = malloc(sizeof(uint32_t)*80);
    uint32_t* H = malloc(sizeof(uint32_t)*5);
    uint32_t* PW = malloc(sizeof(uint32_t)*80);
    H[0] = 0x67452301; H[1] = 0xEFCDAB89; H[2] = 0x98BADCFE; H[3] = 0x10325476; H[4] = 0xC3D2E1F0;

    int i = 0;
    unsigned char buffer[65];
    uint8_t M1,  M2,  M3, M4;
    uint64_t ml = strlen((char*)s);
    unsigned char* s2 = malloc(sizeof(unsigned char)*ml);
    s2 = (unsigned char*) strcpy((char*)s2,(char*)s);


    while (s[i]!='\0') {
        buffer[i] = s[i];
        i++;
    }

    ml = i*8;
    if (ml < 32) exit(-1);
    buffer[i++] = (unsigned char) 0x80;
    memset(buffer+i,0,56-i);
    for (i = 56; i < 64; i++) {
        buffer[i] = (unsigned char) (ml>>((63-i)*8) & 0xff );
    }
    buffer[i] = '\0';

    breakM(buffer,M);
    precompute_opt_0(M, PW, W);

    for (M1 = 0x20; M1 < 0x7F; M1++) {
        for (M2 = 0x20; M2 < 0x7F; M2++) {
            for (M3 = 0x20; M3 < 0x7F; M3++) {
                for (M4 = 0x20; M4 < 0x7F; M4++) {
                    M[0] = M1 << 24 | M2 << 16 | M3 << 8 | M4;
                    extendM_opt_0(M, PW, W);
                    hashW(W, H);
                    if (compareHash(H,hashToFind)) {
                        s2[0] = (unsigned char) M1;
                        s2[1] = (unsigned char) M2;
                        s2[2] = (unsigned char) M3;
                        s2[3] = (unsigned char) M4;
                        printf("\nMessage trouvé: %s\n",s2);
                        t = clock();
                        temps = (float)(t-t0)/CLOCKS_PER_SEC;
                        printf("Temps d'execution : %f\n", temps);
                        return 1;
                    }
                    H[0] = 0x67452301;
                    H[1] = 0xEFCDAB89;
                    H[2] = 0x98BADCFE;
                    H[3] = 0x10325476;
                    H[4] = 0xC3D2E1F0;
                }
            }
        }
    }

    printf("\nMessage non trouvé.\n");
    t = clock();
    temps = (float)(t-t0)/CLOCKS_PER_SEC;
    printf("Temps d'execution : %f\n", temps);

    return 0;
}

int solveHashLen4(uint32_t* hashToFind, unsigned char* s) {

    float temps;
    clock_t t0, t;
    t0 = clock();

    uint32_t* M = malloc(sizeof(uint32_t)*16);
    uint32_t* W = malloc(sizeof(uint32_t)*80);
    uint32_t* H = malloc(sizeof(uint32_t)*5);
    H[0] = 0x67452301; H[1] = 0xEFCDAB89; H[2] = 0x98BADCFE; H[3] = 0x10325476; H[4] = 0xC3D2E1F0;

    int i = 0;
    unsigned char buffer[65];
    uint8_t M1,  M2,  M3, M4;
    uint64_t ml = strlen((char*)s);
    unsigned char* s2 = malloc(sizeof(unsigned char)*ml);
    s2 = (unsigned char*) strcpy((char*)s2,(char*)s);


    while (s[i]!='\0') {
        buffer[i] = s[i];
        i++;
    }

    ml = i*8;
    if (ml < 32) exit(-1);
    buffer[i++] = (unsigned char) 0x80;
    memset(buffer+i,0,56-i);
    for (i = 56; i < 64; i++) {
        buffer[i] = (unsigned char) (ml>>((63-i)*8) & 0xff );
    }
    buffer[i] = '\0';

    breakM(buffer,M);

    for (M1=0x20; M1<0x7F; M1++) {
        for (M2 = 0x20; M2 < 0x7F; M2++) {
            for (M3 = 0x20; M3 < 0x7F; M3++) {
                for (M4 = 0x20; M4 < 0x7F; M4++) {
                    M[0] = M1<<24 | M2<<16 | M3<<8 | M4;
                    extendM(M, W);
                    hashW(W, H);
                    if (compareHash(H,hashToFind)) {
                        s2[0] = (unsigned char) M1;
                        s2[1] = (unsigned char) M2;
                        s2[2] = (unsigned char) M3;
                        s2[3] = (unsigned char) M4;
                        printf("\nMessage trouvé: %s\n",s2);
                        t = clock();
                        temps = (float)(t-t0)/CLOCKS_PER_SEC;
                        printf("Temps d'execution : %f\n", temps);
                        return 1;
                    }
                    H[0] = 0x67452301;
                    H[1] = 0xEFCDAB89;
                    H[2] = 0x98BADCFE;
                    H[3] = 0x10325476;
                    H[4] = 0xC3D2E1F0;
                }
            }
        }
    }

    printf("\nMessage non trouvé.\n");
    t = clock();
    temps = (float)(t-t0)/CLOCKS_PER_SEC;
    printf("Temps d'execution : %f\n", temps);

    return 0;
}