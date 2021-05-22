#include <libasm.h>
#include <standardLib.h>

#define N 8
#define PHILOSOPHIZING 2
#define HUNGRY 1
#define EATING 0
#define LEFT ((i + cant-1) % cant)
#define RIGHT ((i + 1) % cant)
#define FD_STDIN 1
#define FD_STOUT 2
#define MAX_PROCESS 10
#define FOREGROUND 1
#define BACKGROUND 0

static void putNames();
void printPhilos(int i);
void test(int i);
void takeFork(int i);
void putFork(int i);
int philospher(int argc, char **argv);
int addPhiloinit(int i);
int addPhilo(int i);
void killPhil(int i);
void exitPhilo();
int philosphers();


int state[N];
char *mutex;
 char * names[N] = {0};
 int philPID[N];
 int cant = 0;
 int numPhil = 0;

static void putNames(){
     for (int i = 0; i < N; i++)
    {
        mallocNUESTRO(names+i, 3);
        if (names[i] == 0)
        {
            printf("No se pudo realizar malloc con i= %d \n",i);
            return;
        }
        names[i] = itoa(i, names[i], 10);
    }   
}

void printPhilos(int i){
    for (int j = 0; j < cant; j++)
    {
        if (state[j] == EATING){
            printf(" E ");
        }
        else printf(" . ");
    }
    printf("\n");
}

void test(int i){
    if (state[i] == HUNGRY && 
    ((i == 0)? state[cant -1] != EATING : state[i - 1] != EATING) &&
    ((i == cant - 1)? state[0] != EATING : state[i + 1] != EATING)) {    
        state[i] = EATING;
        yield();
        semPost(names[i]);
    }
}

void takeFork(int i){
    semWait(mutex);
    state[i] = HUNGRY;
    test(i);
    semPost(mutex);
    semWait(names[i]);
    yield();

    
    
}

void putFork(int i){
    semWait(mutex);
    state[i] = PHILOSOPHIZING;
    if (i == cant - 1) test(0);
    else    test(i + 1);
    if (i == 0) test(cant - 1);
    else    test(i - 1);
    yield();
    semPost(mutex);
}

int philospher(int argc, char ** argv){
    printf("Filosofo creado\n");
    if (argc != 0){
        printf("Error al iniciar filosofo");
        return -1;
    }
    int i = numPhil++;
    while (1) {
        yield();
        takeFork(i);
        printPhilos(i);
        putFork(i);
    }
    return 0;
}

int addPhiloinit(int i){
    if (cant >= N) return -1;
    semOpen(names[i], 0, 0);
    if (names[i] == 0) {
        printf("Error al crear semaforo");
        return -1;
    }

    // aseguro ambos lados
    int waited[2]={0};
    int * status = 0;
    getSemStatus(names[0],status);
     if (*status==1) {
         semWait(names[0]);
         waited[0]++;
     }
    //  *status = 0;
    //  getSemStatus(names[i-1],status);
    //  if (*status==1) {
    //      semWait(names[i-1]);
    //      waited[1]++;
    // }
     *status = 0;
     getSemStatus(names[cant-1],status);
     if (*status==1) {
         semWait(names[cant-1]);
         waited[1]++;
    }
    createProcess(names[i], &philospher, 0, 0, BACKGROUND);
    getPidByName(names[i], philPID+i);
    cant++;
    
    if (waited[0]==1) {
        semPost(names[0]);
    }
    if (waited[1]==1) {
        semPost(names[i-1]);
    }
    return 0;    
}

int addPhilo(int i){
    semWait(mutex);
    addPhiloinit(i);
    semPost(mutex); //suelto los tenedores si los tengo
    return 0;    
}


void killPhil(int i){
    semWait(mutex);
     int * status;
    getSemStatus(names[i],status);
    if (*status==1) {
        semWait(names[i]);
    } 
    kill(philPID[i]);   
    semClose(names[i]);
   
    cant--;
    numPhil--;
    semPost(mutex);
    printf("Filosofo muerto \n");
}

void exitPhilo(){
    for (int i = cant - 1; i >= 0; i--) {
        killPhil(i);
    }
    for (int i = 0; i < N; i++)
    {
        freeMemory(names[i]);
    }
    
    semClose(mutex);
    
}


int philosphers(){
    putNames();       
    printf("Problema de los filosofos: \n");
    printf("a: agregar filososfos\n");
    printf("r: remover filososfos\n");
    printf("p: ver los procesos \n");
    printf("/: salir\n");
    int retSemOpen;
    mutex = "mutex";
    semOpen(mutex, 1, &retSemOpen); // ver si el 1 esta bien
    if(retSemOpen < 0){
        printf("No se pudo abrir el semaforo\n");
        return -1;
    }
   semWait(mutex);
    for (int i = 0; i < 5; i++) {
        addPhiloinit(i);
    }
   semPost(mutex);
    printf("Filosofos filosofando...\n");

    int flag = 1;
    char bufferPS[1024] = {0};

    while (flag) {
        int k = getChar();

        switch (k) {
        case 'a':
            //printf("ADD recibido \n");
            addPhilo(cant);
            break;
        case 'r':
            printf("");
            if (cant > 0)
            {
                killPhil(cant - 1);  
            }
            if (cant == 0) flag = 0;
            break;
        case 'p':
            printf("\n");
            cleanBuffer(bufferPS, 100);
            ps(bufferPS);
            printf(bufferPS);
            printf("\n\n");
            break;
        case '/':
            //printf("EXIT recibido \n");
            exitPhilo();
            flag = 0;
            break;
        default:
            printf("No es una opcion valida");
            break;
        }
    }
    printf("Saliendo de los filosos \n");
    return 0;
}