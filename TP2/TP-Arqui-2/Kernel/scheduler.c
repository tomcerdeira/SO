#include <scheduler.h>

#define MATADO 0
#define ACTIVO 1
#define BLOQUEADO 2
#define CANT_PROCESS 10
#define STACK_SIZE 4096
#define DEATH_INNER_P -1
#define TIME_SLOT 1
              

process processes[CANT_PROCESS] = {{0}};
process halter;

int currentProcessIndex = 0;

int cantOfActiveProcesses = 0;
int firstTimeEntering = 1;
int rspKernel = 0;
int globalPid = 0;

// Creo y lleno el arreglo processes con todos los proceso que puedo tener
// Version 1.0 de manejo de procesos


// hacer que el pid sea incremental

void halterProcess(){
    _hlt();
    block(1); 
    timerTickInterrupt();
}

void createprocesses()
{
    //Todo HALTER

       
        halter.function = &halterProcess;
        halter.name = "Halter";
        halter.pid = globalPid++;
        halter.state = ACTIVO;
        halter.timeSlot = TIME_SLOT;
        halter.timeRunnig = 0;
        halter.stackPointer = initStack(halter.memory + STACK_SIZE,wrapper, halter.function, NULL, NULL, halter.pid);
        
                
        int p = 0;
        for (; p < CANT_PROCESS; p++)
        {
            process proc;
            proc.pid = -1;
            //proc.memory = processMemory[prio][p];
            proc.memory = 0;
            proc.state = MATADO;
            proc.timeRunnig = 0;
            proc.timeSlot = 0;
            processes[p] = proc;
        }

}
void nice(int pid,int newTimeSlot){
    int i =0;
    for(;i<CANT_PROCESS;i++){
        if(processes[i].pid == pid){
            processes[i].timeSlot = newTimeSlot;
            return;
        }
    }
}

void block(int pid){
    int i =0;
    for(;i<CANT_PROCESS;i++){
        if(processes[i].pid == pid){
            if (processes[i].state == BLOQUEADO)
            {
                processes[i].state = ACTIVO;
                cantOfActiveProcesses++;
                return;
            }
            processes[i].state = BLOQUEADO;
            cantOfActiveProcesses--;
            return;
        }
    }
}

int getAvailableProcess(){
    int i=0;
    for(;i<CANT_PROCESS;i++){
        if(processes[i].state == MATADO){
            return i;
        }
    }
    return -1;
}

int startProcess(char *name, void *func(int, char **), int argc, char *argv[])
//se fija entre todos los procesos, agarra uno que esté muerto/disponible, le asigna la tarea, lo activa,
{
                               //2
    int availableProcess = getAvailableProcess(); //0

    if (availableProcess < 0)
    {
        // ERROR --> No hay un lugar para el proceso nuevo
        return;
    }

    processes[availableProcess].function = func;
    processes[availableProcess].state = ACTIVO;
    processes[availableProcess].name = name;
    processes[availableProcess].pid = globalPid++;
    processes[availableProcess].timeSlot = TIME_SLOT - 4;
    
    //processes[prio_name][availableProcess].memory = processMemory[prio_name][availableProcess]; // Habria que liberarla una vez matado el proceso
    processes[availableProcess].memory = mallocNUESTRO(STACK_SIZE);

    processes[availableProcess].stackPointer = initStack(processes[availableProcess].memory + STACK_SIZE,
                                                                    wrapper, processes[availableProcess].function, argc, argv, processes[availableProcess].pid);
    // setProcessPriority(&processes[availableProcess]); //?/

    cantOfActiveProcesses++;
    // char buf[12] = {0};
    // numToStr(buf, processes[prio_name][availableProcess].pid);
    // print(buf, 0xFF, 0x32);
    return processes[availableProcess].pid;
}

void wrapper(void *func(int, char **), int argc, char *argv[], int pid)
{
    int retValue;
    retValue = (int)(*func)(argc, argv); // --> return --> wrapper -->  kill (libere todo) --> return a shell
                                         // exit -->kill (libere todo) --> return a padre
    // print("Salgo del proceso",0xFF,0x32);
    exit(retValue);
}

uint64_t *sched(uint64_t *rsp) //TODO cambiar nombre a sched
{
    if (cantOfActiveProcesses == 0)
    {
        if (firstTimeEntering)
        {
            rspKernel = rsp;  
        } else {
            print("RETURN HALTER",0x32,0xFE);
            return halter.stackPointer;
        }
        return rspKernel;
    }
    else
    {
        if (!firstTimeEntering) // Esto es para que un proceso se actualice el SP.
        {
            processes[currentProcessIndex].stackPointer = rsp;
        }
        firstTimeEntering = 0;
        if(processes[currentProcessIndex].timeSlot > processes[currentProcessIndex].timeRunnig && processes[currentProcessIndex].state == ACTIVO){
            processes[currentProcessIndex].timeRunnig++;
            return processes[currentProcessIndex].stackPointer;
        }

        int auxIndex = currentProcessIndex + 1;
        int j = 0;
        for(; j<=CANT_PROCESS; j++, auxIndex++){
            if (processes[auxIndex % CANT_PROCESS].state == ACTIVO)
            {
                processes[currentProcessIndex].timeRunnig = 0;
                currentProcessIndex = auxIndex % CANT_PROCESS;
                return processes[currentProcessIndex].stackPointer;
                /* code */
            }
            
        }
    }
    print("_______ACA NO DEBERIA ESTAR________", 0x32, 0xFF);
    return (uint64_t *)-1;
    // Tira warning pero nunca llega aca (al menos no deberia)
}

void kill(int pid)
{       
        char buffer[1024] = {0};
        //ps(buffer);
        print(buffer,0x32,0xFE);
        int pos = 0;
        for (; pos < CANT_PROCESS; pos++)
        {
            if (processes[pos].pid == pid)
            {
                processes[pos].state = MATADO;
                freeMemory(processes[pos].memory);
                cantOfActiveProcesses--;
            }
        }
}

void exit(int status)
{
    kill(processes[currentProcessIndex].pid);
    timerTickInterrupt();
}

int getPid()
{
    return processes[currentProcessIndex].pid;
}


void ps(char * buffer){
    int i = 0;
    int j=0;

    char *header = "PID\tPRIO\tNAME\t\tSTACK\t\tSTATE\n";

    memcpy(buffer, header, strlen(header));
    j =strlen(header);


    for(;i<CANT_PROCESS;i++){
        if(processes[i].state != MATADO){
            //PID
            char auxPID[5];
            numToStr(auxPID,processes[i].pid);
            memcpy(buffer+j,auxPID,strlen(auxPID));
            j+=strlen(auxPID);
            memcpy(buffer+j,"\t",strlen("\t"));
            j+=strlen("\t");

            //Prioridad
            char auxPrio[5];
            numToStr(auxPrio,processes[i].timeSlot);
            memcpy(buffer+j,auxPrio,strlen(auxPrio));
            j+=strlen(auxPrio);
            memcpy(buffer+j,"\t",strlen("\t"));
            j+=strlen("\t");
            
        
            //Name
            memcpy(buffer+j,processes[i].name,strlen(processes[i].name));
            j+=strlen(processes[i].name);
            memcpy(buffer+j,"\t",strlen("\t"));
            j+=strlen("\t");

            memcpy(buffer+j,"\t",strlen("\t"));
            j+=strlen("\t");

            //Stack
            char auxStack[10];
            numToStr(auxStack,processes[i].stackPointer);
            memcpy(buffer+j,auxStack,strlen(auxStack));
            j+=strlen(auxStack);
            
            memcpy(buffer+j,"\t",strlen("\t"));
            j+=strlen("\t");

            //Estado
            if(processes[i].state == ACTIVO){
                 memcpy(buffer+j,"A\n",strlen("A\n"));
            }else{
                 memcpy(buffer+j,"B\n",strlen("A\n"));
            }
            j+=strlen("A\n");
        }
    }

}

void yield(){
    // print("_______Llega al yield________", 0x32, 0xFF);
    processes[currentProcessIndex].timeRunnig = processes[currentProcessIndex].timeSlot;
    timerTickInterrupt();
}