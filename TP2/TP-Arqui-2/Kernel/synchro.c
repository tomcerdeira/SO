
#include <synchro.h>



////////////
#define CANT_SEMAPHORES 10

int cantSemaphores = 0;

semT semaphores[CANT_SEMAPHORES];
int globalSemID = 0;

int mySemWait(char * name){
    semT * sem = getSemByName(name);
    if(sem == -1){
        return -1;
    }
    while(_xadd(-1,&(sem->value)) <= 0){
        _xadd(1,&(sem->value));
        int currentProcessPid = getPid();
        sem->blockedPids[sem->cantBlockedPids++] = currentProcessPid;
        block(currentProcessPid); //bloquea el proceso
    }

    return 0;
}

int mySemPost(char * name){
    semT * sem = getSemByName(name);

    //int i=0;
     unblockMultiple(sem->blockedPids, sem->cantBlockedPids);
     sem->cantBlockedPids = 0;
    // for (; i < sem->cantBlockedPids ; i++)
    // {
    //     if(sem->blockedPids[i] != -1){
    //         sem->cantBlockedPids--;
    //         block(sem->blockedPids[i]);
    //         sem->blockedPids[i] = -1;
    //     }
    // }
    if(sem == -1){
        return -1;
    }
    _xadd(1,&(sem->value));
    //block(getPid()); //debloquea el proceso
    return 0;
}

void initSemaphores(){
    int i=0;
    semT newSem;
    newSem.semID= 0;
    newSem.value= 0;
    newSem.cantGiven= 0;
    newSem.cantBlockedPids = 0;
    for (; i < CANT_SEMAPHORES; i++)
    {
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

semT * semOpen(char * name,int initValue, int * retValue){
    int i = 0;
    for(;i<CANT_SEMAPHORES;i++){
        if(strcmp(name,semaphores[i].name) != 0){
            semaphores[i].cantGiven  += 1;
            *retValue = 1;
            return &semaphores[i];
        }
    }
    // No encontro el semaforo, por que no esta creado --> debe crearlo
    if(cantSemaphores < CANT_SEMAPHORES){
        semT nuevoSem;
        nuevoSem.name = name;
        nuevoSem.value = initValue;
        nuevoSem.semID = globalSemID++;
        nuevoSem.cantGiven =1;
        nuevoSem.cantBlockedPids = 0;
        int index = getIndex();
        semaphores[index] = nuevoSem;
        cantSemaphores++;
        *retValue = 1;
        return &semaphores[index];
    }
    else
    {
        *retValue = -1;
        return -1; //ERROR --> No se pudo crear el semaforo
    }
    print("__ACA NO DEBERIA ESTAR__",0x32,0xFE);
    *retValue = -1;
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

void getSemStatus(char * name, int * status)
{
    semT * sem = getSemByName(name);
    *status = sem->value;
}


// HACER!!!!!
// Ver como hacer con el tema de "los procesos bloqueados en cada uno"
//
// void semsInfo(char *buffer)
// {
//     int i = 0;
//     int j = 0;

//     char *header = "Name\tState\tFD\t\tCant. proc\n";

//     memcpy(buffer, header, strlen(header));
//     j = strlen(header);

//     for (; i < CANT_SEMAPHORES; i++)
//     {
//         // if (!pipes[i].isFree)
//         // {
//         //     //Read
//         //     char auxRead[1];
//         //     numToStr(auxRead, pipes[i].readIndex);
//         //     memcpy(buffer + j, auxRead, strlen(auxRead));
//         //     j += strlen(auxRead);
//         //     memcpy(buffer + j, "\t\t\t\t\t\t", strlen("\t\t\t\t\t\t"));
//         //     j += strlen("\t\t\t\t");

//         //     //Write
//         //     char auxWrite[1];
//         //     numToStr(auxWrite, pipes[i].writeIndex);
//         //     memcpy(buffer + j, auxWrite, strlen(auxWrite));
//         //     j += strlen(auxWrite);
//         //     memcpy(buffer + j, "\t\t\t\t\t\t", strlen("\t\t\t\t\t\t"));
//         //     j += strlen("\t\t\t\t\t\t");

//         //     //FD
//         //     char auxFD[2];
//         //     numToStr(auxFD, pipes[i].fd);
//         //     memcpy(buffer + j, auxFD, strlen(auxFD));
//         //     j += strlen(auxFD);
//         //     memcpy(buffer + j, "\t\t\t", strlen("\t\t\t"));
//         //     j += strlen("\t\t\t");

//         //     memcpy(buffer + j, "\t\t\t", strlen("\t\t\t"));
//         //     j += strlen("\t\t\t");

//         //     //Cant of processes
//         //     char auxCant[10];
//         //     numToStr(auxCant, pipes[i].cantOfProcessesConsuming);
//         //     memcpy(buffer + j, auxCant, strlen(auxCant));
//         //     j += strlen(auxCant);

//         //     memcpy(buffer + j, "\n", strlen("\n"));
//         //     j += strlen("\n");
//         // }
//     }
// }
