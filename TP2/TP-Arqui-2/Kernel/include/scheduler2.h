#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <interrupts.h>
#include <stdint.h>
#include <lib.h>
#include <libC.h>
#include <initStack.h>
#include <interrupts.h>
#include <memory_manager.h>

extern uint64_t *initStack(uint64_t *rsp, void *wrapper, void *func, int argc, char *argv[], int pid);
void initScheduler();
int chooseNextProcess();
int getFreeProcessIndex();
int createNewProcess(char *name, void *func(int, char **), int argc, char *argv[], int timeSlot);
uint64_t *sched(uint64_t *rsp);
void wrapper(void *func(int, char **), int argc, char *argv[], int pid);

#endif