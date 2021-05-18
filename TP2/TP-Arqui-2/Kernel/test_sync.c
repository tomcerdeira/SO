#include <stdint.h>
#include <stdio.h>
#include "synchro.h"
#include "scheduler.h"

uint64_t my_create_process(char *name, void *func(int, char **), int argc, char *argv[])
{
  startProcess(name, func, argc, NULL, 1);
}

uint64_t my_sem_open(char *name, uint64_t initialValue)
{
  return semOpen(name, initialValue);
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
  // if(aux < 0 ){
  //   print("(slowInc) value negativo: ", 0x32, 0xFE);
  //   int aux2 = aux * -1;
  //   printBase(aux2,10);
  // }else{
  //   print("(slowInc) value: ", 0x32, 0xFE);
  //   printBase(aux,10);
  // }
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
  int64_t N = 100000;
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

// void inc(uint64_t sem, int64_t value, uint64_t N){
//   uint64_t i;

//   if (sem && !my_sem_open(SEM_ID, 1)){
//     printf("ERROR OPENING SEM\n");
//     return;
//   }

//   for (i = 0; i < N; i++){
//     if (sem) my_sem_wait(SEM_ID);
//     slowInc(&global, value);
//     if (sem) my_sem_post(SEM_ID);
//   }

//   if (sem) my_sem_close(SEM_ID);

//   printf("Final value: %d\n", global);
// }

void test_sync()
{
  uint64_t i;

  global = 0;

  print("CREATING PROCESSES...(WITH SEM)\n", 0xFFFFFF, 0x000000);

  for (i = 0; i < TOTAL_PAIR_PROCESSES; i++)
  {
    my_create_process("incNUESTRO", &incNUESTROCONSEM, 1, NULL);
    my_create_process("incNUESTRO", &incNUESTROCONSEM, -1, NULL);
    // my_create_process("inc", 1, 1, 1000000);
    // my_create_process("inc", 1, -1, 1000000);
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
    //print("Antes de creaer el 1/3 value: ", 0x32, 0xFE);
    // printBase(global,10);
    my_create_process("incNUESTRO", &incNUESTROSINSEM, 1, NULL);

    // print("Antes de creaer el 2/4 value: ", 0x32, 0xFE);
    // printBase(global,10);

    my_create_process("incNUESTRO", &incNUESTROSINSEM, -1, NULL);
    //my_create_process("inc", 0, 1, 1000000);
    //my_create_process("inc", 0, -1, 1000000);
  }
}

// int main(){
//   test_sync();
//   return 0;
// }
