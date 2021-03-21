// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

struct suma1
{
    char * nameFile;
    int valorSuma;
} ;

void *thread(void *arg);
typedef struct suma1 suma_t;

void suma(suma_t *s);

int main(int argc, char *argv[])
{
    suma_t s1,s2;

    s1.nameFile = argv[1];
    s2.nameFile = argv[2];
  

    pthread_t th1,th2;
    pthread_create(&th1, NULL, (void *)suma, (void *)&s1);
    //sleep(1);
    pthread_create(&th2, NULL, (void *)suma, (void *)&s2);
    
    int ret = 0;
    ret =  pthread_join(th1,NULL);
    if(ret!=0){
        perror("ERROR PTHREAD_JOIN 1");
    }
    ret = pthread_join(th2,NULL);
   if(ret!=0){
          perror("ERROR PTHREAD_JOIN 2");
      }

printf("%d \n", s1.valorSuma);
printf("%d \n", s2.valorSuma);
return 0;
   
}


void suma(suma_t * s){
    int id;
    
    id = open(s->nameFile,O_RDONLY);
    if(id<0){
        perror("ERROR EN OPEN: ");
        abort();
    }

    s->valorSuma = 0;

    dup2(id,STDIN_FILENO);
    int c=0;
    //int car1 = 0;
    //int car2 = 0;
    int flag = 0;

    while((c = getchar())!=EOF){
     if(c != '+'){
        if (flag == 0){
             s->valorSuma += (c - 48);
        }
        if (flag == 2){
            s->valorSuma += (c - 48);
        }
     }
        flag++;
    }
    close(id);
    //s->valorSuma = car1+car2;
}