#ifndef SYNCRO_H
#define SYNCRO_H


#include "lib.h"

#define CANT_PROCESS 11
#define CANT_SEMAPHORES 10

////////

typedef struct
{
    int semID;
    char *name;
    int value;
    int cantGiven;
    int cantBlockedPids;
    int blockedPids[CANT_PROCESS];
} semT;

extern int _xadd(int inc, int *value);
extern int _xchg(int *lock, int value);

int mySemWait(char *name);
int mySemPost(char *name);
void initSemaphores();
int strcmp(char *s1, char *s2);
int getIndex();
semT * semOpen(char * name,int initValue,int * retValue);
void getSemStatus(char * name, int * status);
int semClose(char *name);
semT * getSemByName(char * name);

#endif