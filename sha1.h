//
// Created by clement on 07/06/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef SHA1_SHA1_H
#define SHA1_SHA1_H

uint32_t* sha1(unsigned char *s1);

void breakM(unsigned char* s, uint32_t* M);

void printBreakM(uint32_t* M);

void extendM(uint32_t* M, uint32_t* W);

void printW(uint32_t* W);

void hashW(uint32_t* W, uint32_t* H);

uint32_t* findHash(char* filename, unsigned char* c);

void printHash(uint32_t* H);

#endif //SHA1_SHA1_H
