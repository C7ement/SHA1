#include "sha1.h"

int main() {
    unsigned char s[] = "";

    uint32_t* H = SHA1(s);
    printf("\nSHA-1:  ");
    for (int i=0; i<5; i++) {
      printf("%08lx ",H[i]);
    }
    printf("\n");

    w0_occurence(0);

    uint32_t* H2 = SHA1_opt_0(s);
    printf("\nSHA-1:  ");
    for (int i=0; i<5; i++) {
      printf("%08lx ",H2[i]);
    }
    printf("\n");
    return 0;
}
