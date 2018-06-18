//
// Created by labonne on 13/06/18.
//

#include "sha1.h"
#include "sha1opt.h"
#include <time.h>

#ifndef SHA1PROJECT_PASSWORDGENERATOR_H
#define SHA1PROJECT_PASSWORDGENERATOR_H

void generatePassword(unsigned char* s);
void generatePassword_opt(unsigned char* s);

#endif //SHA1PROJECT_PASSWORDGENERATOR_H
