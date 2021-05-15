// #ifndef SCHEDULER_H
// #define SCHEDULER_H

// #include <stdint.h>
// #include <lib.h>
// #include <initStack.h>
// #include <interrupts.h>
// #include <memory_manager.h>

// typedef struct
// {
//     char *name;
//     int pid;
//     void *function;
//     uint64_t *stackPointer;
//     uint64_t *memory;
//     int state;
//     int priority;
//     int innerPriority;
// } process;

// extern uint64_t *initStack(uint64_t *rsp, void *wrapper, void *func, int argc, char *argv[], int pid);
// void createprocesses();
// int getAvailableProcess(process *processes);
// int getPriority(char *name);
// int startProcess(char *name, void *func(int, char **), int argc, char *argv[]);
// uint64_t *activeProcess(uint64_t *rsp);
// void wrapper(void *func(int, char **), int argc, char *argv[], int pid);
// void exit(int status);
// void kill(int pid);
// int getPid();

// #endif
