#include "sha1.h"

int main() {
    char s[] = "Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!";
    //0a0a9f2a6772942557ab5355d76af442f8f65e01
    sha1(s);
    return 0;
}