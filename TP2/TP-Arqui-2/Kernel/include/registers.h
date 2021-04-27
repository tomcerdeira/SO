#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>
#define CANT_REGISTERS  19


void getRegisterState(uint64_t * buff, uint64_t * stackFrame);
void saveSnapShotRegister(uint64_t * stackFrame);




#endif
