#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <lib.h>
#include <libC.h>
#include <initStack.h>
#include <interrupts.h>
#include <memory_manager.h>

typedef struct
{
    char *name;
    int pid;
    void *function;
    uint64_t *stackPointer;
    uint64_t *memory;
    int state;
    int timeSlot;
    int timeRunnig;
    int fdInput;
    int fdOutput;
    // int priority;
    // int innerPriority;
} process;

extern uint64_t *initStack(uint64_t *rsp, void *wrapper, void *func, int argc, char *argv[], int pid);
void createprocesses();
int getAvailableProcess();
int startProcess(char *name, void *func(int, char **), int argc, char *argv[], int isForeground);
uint64_t *sched(uint64_t *rsp);
void wrapper(void *func(int, char **), int argc, char *argv[], int pid);
void exit(int status);
void kill(int pid);
int getPid();
void block(int pid);
void halterProcess();
void ps(char *buffer);
void yield();
int currentProcessIsForeground();
void unblockReaders();
void blockReader(int pid);
void getPidByName(char *name, int *pid);
void changeOutputFd(int pid, int fd);
void changeInputFd(int pid, int fd);
int getIndexOfPid(int pid);
int getFdInput(int pid);
int getFdOutput(int pid);

#endif
