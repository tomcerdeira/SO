#include "synchro.h"

////////////
#define CANT_SEMAPHORES 10

int cantSemaphores = 0;

semT semaphores[CANT_SEMAPHORES];
int globalSemID = 0;

int mySemWait(semT *s){
    semT * sem = getSemByName(s->name);
    if(sem == -1){
        return -1;
    }
    while(_xadd(-1,&(s->value)) <= 0)
    _xadd(1,&(s->value));
    return 0;
}

int mySemPost(semT *s){
    semT * sem = getSemByName(s->name);
    if(sem == -1){
        return -1;
    }
    _xadd(1,&(s->value));
    return 0;
}

void initSemaphores(){
    int i=0;
    semT newSem;
    newSem.semID= 0;
    newSem.value= 0;
    newSem.cantGiven= 0;
    for(;i<CANT_SEMAPHORES;i++){
        semaphores[i] = newSem;
    }
}

/////////////sacar de aka
int strcmp(char *s1, char *s2)
{
    int cmp = 1;
    int i;
    for (i = 0; s1[i] != 0 && s2[i] != 0 && cmp; i++)
    {
        if (s1[i] != s2[i])
        {
            cmp = 0;
        }
    }

    if ((s1[i] == 0 && s2[i] != 0) || (s1[i] != 0 && s2[i] == 0))
    {
        cmp = 0;
    }
    return cmp;
}

int getIndex(){
    int j=0;
    for(;j<CANT_SEMAPHORES;j++){
        if(semaphores[j].cantGiven == 0){
            return j;
        }
    }
    return -1;
}

semT * semOpen(char * name,int initValue){
    int i = 0;
    for(;i<CANT_SEMAPHORES;i++){
        if(strcmp(name,semaphores[i].name) != 0){
            semaphores[i].cantGiven  += 1;
            return &semaphores[i];
        }
    }
    // No encontro el semaforo, por que no esta creado --> debe crearlo
    if(cantSemaphores < CANT_SEMAPHORES){
        semT nuevoSem;
        nuevoSem.name = name;
        nuevoSem.value = initValue;
        nuevoSem.semID = globalSemID++;
        nuevoSem.cantGiven +=1;
        int index = getIndex();
        semaphores[index] = nuevoSem;
        cantSemaphores++;
        return &semaphores[index];
    }
    else
    {
        return -1; //ERROR --> No se pudo crear el semaforo
    }
    print("__ACA NO DEBERIA ESTAR__",0x32,0xFE);
    return -1;
}

int semClose(char* name){
    int i = 0;
    for (; i < CANT_SEMAPHORES; i++)
    {
        if(strcmp(semaphores[i].name,name)!= 0)
        {
            semaphores[i].cantGiven -= 1;
            if(semaphores[i].cantGiven ==0){
                cantSemaphores--;
                return 0;
            }
        }
    }   
    return -1;
}

semT *getSemByName(char *name)
{
    int i = 0;
    for (; i < CANT_SEMAPHORES; i++)
    {
        if (strcmp(name, semaphores[i].name) != 0)
        {
            return &semaphores[i];
        }
    }
    return -1;
}

semT * getSemByName(char * name){
    int i =0;
    for (; i < CANT_SEMAPHORES; i++)
    {
        if (strcmp(name, semaphores[i].name) != 0)
        {
            return &semaphores[i];
        }
    }
    return -1;
}
