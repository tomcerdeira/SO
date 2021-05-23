#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <lib.h>
#include <libC.h>
#include <initStack.h>
#include <interrupts.h>
#include <memory_manager.h>
//#include <buddy_system2.h>

#define MATADO 0
#define ACTIVO 1
#define BLOQUEADO 2
#define CANT_PROCESS 11
#define STACK_SIZE 4096
#define TIME_SLOT 3
#define SHELL_POSITION 1
#define HALTER_POSITION 0
#define FD_STDIN 1
#define FD_STOUT 2
#define NOT_SETED -1
#define STACK_HALTER_SIZE 128
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
void nice(int pid, int newTimeSlot);
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
void unblockMultiple(int *pids, int cant);

void setFDNextNewProcess(int fdInput, int fdOutPut);
#endif
