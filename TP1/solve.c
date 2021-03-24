// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define CANT_PROCESSES 5


typedef struct 
{
    char * nameFile;
    int valorSuma;
}suma_t;
void suma(suma_t * s);
// Proceso padre
// Crear hijos y sus respectivas tuberias
int main(int argc, char * argv[]){


    int i=0;

    suma_t fileArray[argc-1];

    for (i=0;i<argc-1;i++){
        fileArray[i].nameFile= argv[i+1];
    }

    int fd[CANT_PROCESSES][2];



    for(i=0;i<CANT_PROCESSES;i++){ //VER SI SE PUEDE MEJORAR
        if(pipe(fd[i]) != 0){
            perror("Pipe error: ");
            abort();
        }
    }


 
    int processes[CANT_PROCESSES];

    for(i=0;i<CANT_PROCESSES;i++){ 
        if( ( processes[i]=fork() ) == 0){
            // codigo para el hijo i              
            suma(&fileArray[i]);
            sleep(i*i);
            write(fd[i][1],&(fileArray[i].valorSuma),sizeof(fileArray[i].valorSuma));
            return 1;
         
        }
    }

    for(i=0;i<CANT_PROCESSES;i++){
         read(fd[i][0],&fileArray[i].valorSuma,sizeof(fileArray[i].valorSuma));
         printf("Valor suma %d : %d \n",i,fileArray[i].valorSuma);
    }
   
    // codigo padre
    // Padre finaliza a los hijos
    for(i=0;i<CANT_PROCESSES;i++){
        printf("Esperando proceso %d a que termine..... \n",processes[i]);
        waitpid(processes[i],NULL,0);
    }
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
    // s->valorSuma = car1+car2;
}