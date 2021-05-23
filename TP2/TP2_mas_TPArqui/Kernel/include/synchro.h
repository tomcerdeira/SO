#ifndef SYNCRO_H
#define SYNCRO_H


#include "lib.h"

#define CANT_PROCESS 11
#define CANT_SEMAPHORES 10

////////
extern int getPid();
extern void block(int pid);
extern void unblockMultiple(int* pids, int cant);
extern void print(char * buffer, int fontColor,int backColor);
extern void *memcpy(void *destination, const void *source, uint64_t length);
extern int numToStr(char *str, int num);
extern int strlen(char * buffer);


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
void semsInfo(char *buffer);
#endif