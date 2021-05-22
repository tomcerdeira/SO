#include <registers.h>
static uint64_t registers [CANT_REGISTERS];
//ORDEN DE LOS REGISTROS
// GS,FS,R15,R14,R13,R12,R11,R10,R9,R8,RSI,RDI,RBP,RDX,RCX,RBX,RAX,RIP
void getRegisterState(uint64_t * buff, uint64_t * stackFrame){
    for(int i=0; i<CANT_REGISTERS;i++){
        buff[i]=registers[i];
    }
}

void saveSnapShotRegister(uint64_t * stackFrame){
    
    for(int i=0; i<CANT_REGISTERS;i++){
        registers[i]=stackFrame[i];
    }
    
}


