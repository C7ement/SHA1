//
// Created by labonne on 18/06/18.
//

#include "earlyExit.h"

#ifndef SHA1PROJECT_SOLVEHASH_H
#define SHA1PROJECT_SOLVEHASH_H

int solveHashLen4EarlyExitAndPrecompute(uint32_t* hashToFind,unsigned char* s);

int solveHashLen4EarlyExit(uint32_t* hashToFind,unsigned char* s);

int solveHashLen4Precompute(uint32_t* hashToFind,unsigned char* s);

int solveHashLen4(uint32_t* hashToFind, unsigned char* s);

#endif //SHA1PROJECT_SOLVEHASH_H
