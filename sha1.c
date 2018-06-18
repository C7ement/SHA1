//
// Created by clement on 07/06/18.
//

#include "sha1.h"

uint32_t* sha1(unsigned char *s) {

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
            printf("\n%s\n",buffer);
            extendM(M,W);
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
        extendM(M,W);
        hashW(W,H);
        memset(buffer,0,56);
    }

    for (j = 56; j < 64; j++) {
        buffer[j] = (unsigned char) (ml>>((63-j)*8) & 0xff );
    }

    buffer[j] = '\0';
    breakM(buffer,M);
    extendM(M,W);
    hashW(W,H);

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
        printf("%08lx ",(unsigned long) M[i]);
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
        printf("%08lx\t",(unsigned long) W[i]);
    }
    printf("\n");
}

void hashW(uint32_t* W, uint32_t* H) {

    uint32_t* K = malloc(sizeof(uint32_t)*4);
    K[0] = 0x5A827999;
    K[1] = 0x6ED9EBA1;
    K[2] = 0x8F1BBCDC;
    K[3] = 0xCA62C1D6;

    int i;
    uint32_t tmp, a, b, c, d, e;
    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
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

uint32_t* findHash(char* filename, unsigned char* c) {

    FILE *f = fopen(filename, "rb");
    uint32_t* M = malloc(sizeof(uint32_t)*16);
    uint32_t* H = malloc(sizeof(uint32_t)*5);
    long long t;
    int fr;

    t = (((c[0]-32)*95+c[1]-32)*95+c[2]-32)*95+c[3]-32;

    fseek(f, t * 4 * 21, SEEK_SET);
    fr = fread(M, sizeof(uint32_t), 16, f);
    fr = fread(H, sizeof(uint32_t), 5, f);

    fclose(f);

    if ( M[0] == (uint32_t) c[0]<<24 | c[1]<<16 | c[2]<<8 | c[3]) {
        return H;
    } else {
        exit(fr);
    }
}

void printHash(uint32_t* H) {
    int i;
    for (i=0; i<5; i++) {
        printf("%08lx ",(unsigned long)H[i]);
    }
    printf("\n");
}
