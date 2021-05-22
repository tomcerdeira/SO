
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
            if(semaphores[i].cantGiven == 0){
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
void semsInfo(char *buffer)
{
    int i = 0;
    int j = 0;

    char *header = "Name\tID\tValue\tCant. Given\tCantPidBlocked\tPidsBlocked\n";

    memcpy(buffer, header, strlen(header));
    j = strlen(header);

    for (; i < CANT_SEMAPHORES; i++)
    {
        if(semaphores[i].cantGiven > 0)
        {
            //Name
            memcpy(buffer + j, semaphores[i].name, strlen(semaphores[i].name));
            j += strlen(semaphores[i].name);
            memcpy(buffer + j, "\t\t\t\t", strlen( "\t\t\t\t"));
            j += strlen("\t\t\t\t");

            //ID
            char auxId[1];
            numToStr(auxId,semaphores[i].semID);
            memcpy(buffer + j, auxId, strlen(auxId));
            j += strlen(auxId);
            memcpy(buffer + j, "\t\t\t\t\t\t", strlen("\t\t\t\t\t\t"));
            j += strlen("\t\t\t\t\t\t");

            //Value
            char auxValue[2];
            numToStr(auxValue, semaphores[i].value);
            memcpy(buffer + j, auxValue, strlen(auxValue));
            j += strlen(auxValue);
            memcpy(buffer + j, "\t\t\t", strlen("\t\t\t"));
            j += strlen("\t\t\t");

            memcpy(buffer + j, "\t\t\t", strlen("\t\t\t"));
            j += strlen("\t\t\t");

            //Cant given
            char auxCant[2];
            numToStr(auxCant, semaphores[i].cantGiven);
            memcpy(buffer + j, auxCant, strlen(auxCant));
            j += strlen(auxCant);
            memcpy(buffer + j, "\t\t\t", strlen("\t\t\t"));
            j += strlen("\t\t\t");

             //CantPidBlockeds
            char auxPidBlockeds[2];
            numToStr(auxPidBlockeds, semaphores[i].cantBlockedPids);
            memcpy(buffer + j, auxPidBlockeds, strlen(auxPidBlockeds));
            j += strlen(auxPidBlockeds);
            memcpy(buffer + j, "\t\t\t", strlen("\t\t\t"));
            j += strlen("\t\t\t");

            //Blocked PIDs
            int k =0;
            for(;k<semaphores[i].cantBlockedPids;k++)
            {
                char auxPid[2];
                numToStr(auxPid, semaphores[i].blockedPids[k]);
                memcpy(buffer + j, auxPid, strlen(auxPid));
                j += strlen(auxPid);
                memcpy(buffer + j, ", ", strlen(", "));
                j += strlen(", ");
            }

            memcpy(buffer + j, "\n", strlen("\n"));
            j += strlen("\n");
        }
    }
}

