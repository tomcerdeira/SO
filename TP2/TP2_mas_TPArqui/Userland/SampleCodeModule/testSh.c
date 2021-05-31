#include <libasm.h>
#include <stdint.h>

#define SEMID 5
//#define N 1000;
void slowInc(int64_t *p, int64_t inc);
void inc();
void dec();
void testSh();

void slowInc(int64_t *p, int64_t inc)
{
  int k= 0;
  uint64_t aux = *p;
  aux += inc;
  for (; k < 1000; k++);
  *p = aux;
}


void inc(){
	int i=0;

    char * ptr;
	shOpen(ptr,5, 8);

	if (ptr == 0){
		printf("Error sem_open\n");
    }

  	for (; i < 1000; i++){
		slowInc(ptr, 1);
    }

}



void dec(){
	char * ptr;
    shOpen(ptr,5, 8);

	if (ptr == 0)
		printf("Error sem_open\n");
    int i =0;
	for (; i < 1000; i++)
		slowInc(ptr, -1);

}

void testSh(){
    createP("INC",&inc,0,0);
    createP("DEC",&dec,0,0);

}