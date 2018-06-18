//
// Created by labonne on 15/06/18.
//

#include "earlyExit.h"

/**
 * Function checking if two hashes are equal.
 * @param H a table of 5 uint32_t containing a hash.
 * @param Hbis a table of 5 uint32_t containing a hash.
 * @return true if the hashes correspond and 0 otherwise.
 */

int compareHash(uint32_t* H, uint32_t* Hbis) {
    return H[0] == Hbis[0] && H[1] == Hbis[1] && H[2] == Hbis[2] && H[3] == Hbis[3] && H[4] == Hbis[4];
}

uint32_t* hashStep75(uint32_t* W) {

    uint32_t* K = malloc(sizeof(uint32_t)*4);
    uint32_t* H = malloc(sizeof(uint32_t)*5);
    K[0] = 0x5A827999;
    K[1] = 0x6ED9EBA1;
    K[2] = 0x8F1BBCDC;
    K[3] = 0xCA62C1D6;

    int i;
    uint32_t tmp;
    uint32_t a = 0x67452301;
    uint32_t b = 0xEFCDAB89;
    uint32_t c = 0x98BADCFE;
    uint32_t d = 0x10325476;
    uint32_t e = 0xC3D2E1F0;
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
    for (i=60; i<76; i++) {
        tmp = (a<<5 | a>>27) + (b^c^d) + e + K[3] + W[i];
        e = d;
        d = c;
        c = b<<30 | b>>2;
        b = a;
        a = tmp;
    }
    H[0] = a<<30 | a>>2;
    return H;
}
/**
 * Function calculating the hash of a message stopping at thhe step 75 and not adding the initial H value.
 * @param s message to hash.
 * @return table of uint32_t containing the hash.
 */
uint32_t sha1Step75(unsigned char* s) {

    uint32_t* M = malloc(sizeof(uint32_t)*16);
    uint32_t* W = malloc(sizeof(uint32_t)*80);

    uint64_t ml;

    int i = 0;
    unsigned char buffer[65];

    while (s[i]!='\0') {
        buffer[i] = s[i];
        i++;
    }

    ml = i*8;
    buffer[i++] = (unsigned char)0x80;
    memset(buffer+i,0,56-i);
    for (i = 56; i < 64; i++) {
        buffer[i] = (unsigned char) (ml>>((63-i)*8) & 0xff );
    }
    buffer[i] = '\0';

    breakM(buffer,M);
    extendM(M,W);

    return hashStep75(W)[0];
}


int findMessageEarlyExit75(uint32_t* H, unsigned char* s) {
    uint32_t h = sha1Step75(s);
    //printHash(H);
    H[0] -= 0x67452301;
    H[1] -= 0xEFCDAB89;
    H[2] -= 0x98BADCFE;
    H[3] -= 0x10325476;
    H[4] -= 0xC3D2E1F0;
    //printHash(H);
    printf("%lx\n",(unsigned long) h);
    printf("Comparaison: %d\n",H[4] == h);
    return 0;
}
