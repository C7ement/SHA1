//
// Created by clement on 07/06/18.
//

#include "sha1.h"

int* sha1(char* s) {

    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    uint64_t ml;

    int i = 0;
    int j = 0;
    char buffer[64]; // 64 ou 65 ??

    uint32_t* M[16];
    uint32_t w;
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
            printf("%s\n",buffer);
            //
        }
    }
    ml = i*64+j;
    buffer[j++] = 0x80;

    if (j < 57) {
        memset(buffer+j,0,56-j);
    } else {
        memset(buffer+j,0,64-j);
        //appeler fonction haschage pour buffer
        printf("%s\n",buffer);
        //f560eda0
        memset(buffer,0,56);
    }
    for (j = 56; j < 64; j++) {
        buffer[j] = ml>>((63-j)*8) & 0xff ;
    }
    buffer[j] = '\0';
    //appeler fonction haschage pour buffer
    //printf("%d %d %d %d %d %d %d %d \n",buffer[56],buffer[57],buffer[58],buffer[59],buffer[60],buffer[61],buffer[62],buffer[63]);
    printf("%s\n",buffer);
    //


    return NULL;
}

