#include "sha1.h"

int main() {
    unsigned char s[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    //0a0a9f2a6772942557ab5355d76af442f8f65e01
    uint32_t* H = sha1(s);
    for (int i=0; i<5; i++) {
      printf("%08lx ",H[i]);
    }
    printf("\n");
    return 0;
}
