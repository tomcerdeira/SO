#include <scheduler2.h>

char *priorityProcessesNames[] = {"shell", "time", "printmem"};
int priorityProcessesValue[] = {1,2,2};
char memoryAUX[STACK_SIZE_PROCESS] = {0};

int init = 0;
int cantActiveProcesses = 0;
int lastAvailablePid = 1;

int currentIndex = 0;
int currentPriority = 0;
int firstTime = 1;
uint64_t * rspKernel = 0;

process processes[CANT_PRIO][MAX_PROCESSES_PER_PRIO];

void initScheduler(){
    int i =0;
    for(;i<CANT_PRIO;i++){
        int j=0;
        for(;j<MAX_PROCESSES_PER_PRIO;j++){
            process proc;
            proc.pid = 0;
            proc.memory =0; // No alocamos memoria aca para no malgastar memoria
            proc.state = KILLED;
            processes[i][j] = proc;
        }
    }
    init = 1;
}

int getProcessesIndex(int priority){
    int i=0;
    for(;i<MAX_PROCESSES_PER_PRIO;i++){
        if(processes[priority][i].state == KILLED){
            return i;
        }
    }
    return -1;
}

process * getNextActiveProcess(){
   int i=0;
   int indexPriority = currentPriority; //0
   int indexInPriority = currentIndex +1 ; //0+1


   for (; i  < CANT_PRIO; i++,indexPriority++){
       //current+1 -> fin nada
                 //i= current_prio --> j= current +1
       int j = 0;
       for (; j < MAX_PROCESSES_PER_PRIO; j++, indexInPriority++)
       {
           if (processes[i][j].state == ACTIVE)
           {
               currentIndex = indexInPriority % MAX_PROCESSES_PER_PRIO;
               currentPriority = indexPriority % CANT_PRIO;
               firstTime = 0;
               return &processes[i][j];
           }
      }
      
   }
   return (process *) -1;
}


uint64_t * changeProcess(uint64_t * sp){

   if (cantActiveProcesses == 0)
    {
        if (firstTime){
            rspKernel = sp;
        }
        print("___Adentro___",0x00,0xFF);
        return rspKernel;
    }
    else
    {
        if(!firstTime){
            char buf[21]={0};
            numToStr(buf,currentIndex);
            print(buf,0xFF,0xDA);
            print("currentIndex",0xFF,0xDA);

        processes[currentPriority][currentIndex].stackPointer = sp;
        }
        // Estamos seguros de q next_p es valido por q validamos q alla algun proceso
        _cli();
         uint64_t * toRet = getNextActiveProcess()->stackPointer;
         _sti();
         return toRet;
    }
}


int startProcess(char *name, void *func(int,char **), int argc, char *argv[])
{
    //_cli();
    int processPriority = getPriority(name); //1
    int indexProcesses = getProcessesIndex(processPriority); //primer lugar libre en esa prioridad (0)

    if(indexProcesses < 0)
    {
         return -1;
        // Q pasa si no hay lugar para el proceso? Como espera a ser insertado?
    }
    
    process newProcess;
    newProcess.name = name;
    newProcess.pid = lastAvailablePid++;
    // newProcess.memory = mallocNUESTRO(STACK_SIZE_PROCESS);
    newProcess.memory = memoryAUX;
    newProcess.priority= processPriority;
    newProcess.function = func;
    newProcess.stackPointer = ACTIVE;
    newProcess.stackPointer = initStack(newProcess.memory + STACK_SIZE_PROCESS, wrapper, newProcess.function, argc, argv, newProcess.pid);
    cantActiveProcesses++;
    //_sti();
    return newProcess.pid;
}

void wrapper(void *func(int, char **), int argc, char *argv[], int pid)
 {
    int retValue;
    retValue = (int)(*func)(argc, argv); // --> return --> wrapper -->  kill (libere todo) --> return a shell
                                         // exit -->kill (libere todo) --> return a padre
    // print("Salgo del proceso",0xFF,0x32);
    exit(retValue);
}

int getPriority(char * name)
{
    int i =0;
    for (;i< 3;i++){ //TODO mejorar la cantidad de elementos en el arreglo de procesos definidos
        if(strcompare(priorityProcessesNames[i],name)== 1){
            return priorityProcessesValue[i];
        }
    }
    // Si no esta en nuestro arreglo de procesos
    return CANT_PRIO -1;
}

void kill(int pid)
{
    process * p = getProcessIndexByPid(pid);
    p->state = KILLED;
    // Liberar memoria si no esta liberada
    freeMemory(p->memory);
    cantActiveProcesses--;
}

void killCurrent()
{
    processes[currentPriority][currentIndex].state = KILLED;
    freeMemory(processes[currentPriority][currentIndex].memory);
    cantActiveProcesses--;
}

process * getProcessIndexByPid(int pid)
{
    int i = 0;
    int j = 0;
    for(;i<CANT_PRIO;i++){
        for(;j<MAX_PROCESSES_PER_PRIO;j++){
            if(processes[i][j].pid == pid){
                return &processes[i][j];
            }
        }
    }
    return NULL;
}

void exit(int status)
{
    killCurrent();
    timerTickInterrupt();
}