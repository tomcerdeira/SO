// #ifndef SCHEDULER_H
// #define SCHEDULER_H

// #include <stdint.h>
// #include <lib.h>
// #include <libC.h>
// #include <initStack.h>
// #include <interrupts.h>
// #include <memory_manager.h>

// #define MAX_PROCESSES_PER_PRIO 10
// #define STACK_SIZE_PROCESS 4096
// #define CANT_PRIO 3

// #define KILLED 0
// #define ACTIVE 1
// #define BLOCKED 2

// typedef struct
// {
//     char *name;
//     int pid;
//     void *function;
//     int priority;
//     uint64_t *stackPointer;
//     uint64_t *memory;
//     int state;
// } process;

// void initScheduler();
// process *getNextActiveProcess();
// process *getProcessIndexByPid(int pid);
// uint64_t *changeProcess(uint64_t *sp);
// void wrapper(void *func(int, char **), int argc, char *argv[], int pid);
// void exit(int status);
// int startProcess(char *name, void *func(int,char **), int argc, char *argv[]);
// void kill(int pid);
// void killCurrent();
// #endif