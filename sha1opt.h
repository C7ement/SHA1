//
// Created by labonne on 13/06/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "sha1.h"

#ifndef SHA1PROJECT_SHA1OPT_H
#define SHA1PROJECT_SHA1OPT_H

uint32_t* SHA1_opt_0(unsigned char* s1);

void precompute_opt_0(uint32_t* M, uint32_t* W);

void extendM_opt_0(uint32_t* M, uint32_t* W);

void printW_opt_0(uint32_t* W);

void wt_occurence(int t);

#endif //SHA1PROJECT_SHA1OPT_H
