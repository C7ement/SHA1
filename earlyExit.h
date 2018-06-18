//
// Created by labonne on 15/06/18.
//

#include "sha1.h"
#include "sha1opt.h"
#include <time.h>

#ifndef SHA1PROJECT_EARLYEXIT_H
#define SHA1PROJECT_EARLYEXIT_H

int compareHash(uint32_t* H, uint32_t* Hbis);

uint32_t* hashStep75(uint32_t* W);

uint32_t sha1Step75(unsigned char* s);

int findMessageEarlyExit75(uint32_t* H, unsigned char* s);

#endif //SHA1PROJECT_EARLYEXIT_H
