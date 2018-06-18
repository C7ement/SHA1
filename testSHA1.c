#include "sha1.h"
#include "sha1opt.h"
#include "passwordGenerator.h"
#include "earlyExit.h"
#include "solveHash.h"


int main() {

    //wt_occurence(0);

    /*
    unsigned char s[] = "abc";
    printf("\nSHA-1:\t\t");
    printHash(sha1(s));
    printf("\nSHA-1 opt:\t");
    printHash(sha1_opt_0(s));*/

    char s[] = "Babar";
    generatePassword((unsigned char*)s);
    generatePassword_opt((unsigned char*)s);

    //printf("\nMessage: aaaa\n");
    //printHash(findHash("../txt/sha1-opt.txt","aaaa"));

    //findMessageEarlyExit75(sha1("Babar"),"Babar");


    char s1[] = "Babar";
    char s2[] = "aaaar";

    solveHashLen4EarlyExitAndPrecompute(sha1((unsigned char*)s1),(unsigned char*)s2);
    solveHashLen4EarlyExit(sha1((unsigned char*)s1),(unsigned char*)s2);
    solveHashLen4Precompute(sha1((unsigned char*)s1),(unsigned char*)s2);
    solveHashLen4(sha1((unsigned char*)s1),(unsigned char*)s2);

    return 0;
}