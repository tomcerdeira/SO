#include <libasm.h>
#include <stdint.h>
#include <standardLib.h>

#define SEMID 5
//#define N 1000;
void slowInc(int64_t *p, int64_t inc);
void inc();
void dec();
void testSh();

char *mutexTest = "mutexTest";

void slowInc(int64_t *p, int64_t inc)
{
  int k = 0;
  uint64_t aux = *p;
  aux += inc;
  yield();
  for (; k < 1000; k++){
    *p = aux;
  }
  
}

 uint64_t *ptr1 = 1;
 int * auxSem;
 
void inc()
{
  int i = 0;
 
  shOpen(&ptr1, 5, 8);

  if (ptr1 == 0)
  {
    printf("Error sh_open\n");
  }
  *ptr1 = 0;

  for (; i < 1000; i++)
  {
    semWait(mutexTest);
    slowInc(ptr1, 1);
    semPost(mutexTest);
  }
  printf("inc: %d\n", *ptr1);
  shClose(5);
  semClose(mutexTest);
}

 uint64_t *ptr2 = 1;
void dec()
{
 

  shOpen(&ptr2, 5, 8);
  *ptr2 = 0;

  if (ptr2 == 0)
    printf("Error sh_open\n");
  int i = 0;
  for (; i < 1000; i++){
    semWait(mutexTest);
    slowInc(ptr2, -1);
    semPost(mutexTest);
}
  printf("dec: %d\n", *ptr2);
  shClose(5);
  semClose(mutexTest);
}

void testSh()
{
  
  semOpen(mutexTest,1,auxSem);
  if(*auxSem < 0){
   printf("Error semOpen TEST\n");
  }
  
  createProcess("INC", &inc, 0, 0, 0);
  createProcess("DEC", &dec, 0, 0, 0);

  return;
}