#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

typedef struct
{
    char *name;
    int pid;
    void *function;
    //TODO prioridad
    uint64_t *stackPointer;
    uint64_t *memory;
    int state;
} process;

void createprocesses(process *processes);
int getAvailableProcess(process *processes);
void startProcess(char *name, void *func, int argc, char *argv[]);
uint64_t *activeProcess(uint64_t *rsp);
extern void timerTickInterrupt();

#endif