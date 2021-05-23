// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include <stdio.h>
#include "synchro.h"
#include "scheduler.h"

uint64_t my_create_process(char *name, void *func(int, char **), int argc, char *argv[])
{
  startProcess(name, (void *)func, argc, NULL, 1);
  return 1;
}

uint64_t my_sem_open(char *name, uint64_t initialValue)
{
  int *retValue = 0;
  semOpen(name, initialValue, retValue);
  if (retValue != 0)
  {
    return *retValue;
  }
  else
  {
    return (uint64_t)-1;
  }
}

uint64_t my_sem_wait(char *name)
{
  return mySemWait(name);
}

uint64_t my_sem_post(char *name)
{
  return mySemPost(name);
}

uint64_t my_sem_close(char *name)
{
  return semClose(name);
}

#define TOTAL_PAIR_PROCESSES 2
#define SEM_ID "sem"

int64_t global; //shared memory
int64_t globalInitial;

void slowInc(int64_t *p, int64_t inc)
{
  int64_t aux = *p;
  aux += inc;
  yield();
  *p = aux;
}

void incNUESTROSINSEM(int value)
{
  int64_t N = 100000;
  int i;
  for (i = 0; i < N; i++)
  {
    slowInc(&global, value);
  }
  if (global < 0)
  {
    print("Final value: -", 0xFFFFFF, 0x000000);
    int aux = global * -1;
    printBase(aux, 10);
  }
  else
  {
    print("Final value: ", 0xFFFFFF, 0x000000);
    printBase(global, 10);
  }
}

void incNUESTROCONSEM(int value)
{
  if (!my_sem_open(SEM_ID, 1))
  {
    print("ERROR OPENING SEM\n", 0xFFFFFF, 0x000000);
    return;
  }
  int64_t N = 1000000;
  int i;

  for (i = 0; i < N; i++)
  {
    my_sem_wait(SEM_ID);
    slowInc(&global, value);
    my_sem_post(SEM_ID);
  }

  my_sem_close(SEM_ID);

  if (global < 0)
  {
    print("Final value: -", 0xFFFFFFF, 0x000000);
    int aux = global * -1;
    printBase(aux, 10);
  }
  else
  {
    print("Final value : ", 0xFFFFFFF, 0x000000);
    printBase(global, 10);
  }
}

void test_sync()
{
  uint64_t i;

  global = 0;

  print("CREATING PROCESSES...(WITH SEM)\n", 0xFFFFFF, 0x000000);

  for (i = 0; i < TOTAL_PAIR_PROCESSES; i++)
  {
    my_create_process("incNUESTRO", (void *)&incNUESTROCONSEM, 1, NULL);
    my_create_process("incNUESTRO", (void *)&incNUESTROCONSEM, -1, NULL);
  }
}

void test_no_sync()
{
  uint64_t i;

  global = 0;
  nice(getPid(), 10);
  print("CREATING PROCESSES...(WITHOUT SEM)\n", 0xFFFFFF, 0x000000);

  for (i = 0; i < TOTAL_PAIR_PROCESSES; i++)
  {

    my_create_process("incNUESTRO", (void *)&incNUESTROSINSEM, 1, NULL);
    my_create_process("incNUESTRO", (void *)&incNUESTROSINSEM, -1, NULL);
  }
}
