#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <lib.h>
#include <initStack.h>
#include <interrupts.h>
#include <memory_manager.h>

typedef struct
{
    char *name;
    int pid;
    void *function;
    //TODO int prioridad;
    uint64_t *stackPointer;
    uint64_t *memory;
    int state;
} process;