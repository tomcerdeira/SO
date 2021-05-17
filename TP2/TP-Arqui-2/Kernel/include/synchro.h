#ifndef SEMAPHORES

typedef struct
{
    int semID;
    char *name;
    int value;
    int cantGiven;
} semT;

extern int _xadd(int inc, int *value);
extern int _xchg(int *lock, int value);

int mySemWait(char *name);
int mySemPost(char *name);
void initSemaphores();
int strcmp(char *s1, char *s2);
int getIndex();
semT * semOpen(char * name,int initValue);
int semClose(char *name);
semT * getSemByName(char * name);

#endif