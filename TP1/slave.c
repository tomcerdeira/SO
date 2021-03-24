#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

typedef struct sumapar
{
    char * nameFile;
    int valorSuma;
}suma_t;
void suma(suma_t * s);

int main (int argc, char * argv[]){


   // suma(&s1);
    write(STDOUT_FILENO,&(s1.valorSuma),sizeof(s1.valorSuma));
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
            // printf("%d \n", s->valorSuma);
             //printf(c);
        }
        if (flag == 2){
            s->valorSuma += (c - 48);
            //printf("%d \n", s->valorSuma);
            //printf(c);
        }
     }
        flag++;
    }
    close(id);
    // s->valorSuma = car1+car2;
}