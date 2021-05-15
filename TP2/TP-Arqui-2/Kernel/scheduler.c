#include <scheduler.h>

#define MATADO 0
#define ACTIVO 1
#define BLOQUEADO 2
#define CANT_PROCESS 10
#define STACK_SIZE 4096
#define MAX_PROCESSES_PER_PRIO 10
//#define CANT_PRIO 3
#define DEATH_INNER_P -1
#define TIME_SLOT 5

process processes[CANT_PROCESS] = {{0}};
//process processes[CANT_PRIO][CANT_PROCESS] = {{0}};

// uint64_t processMemory[CANT_PRIO][CANT_PROCESS][STACK_SIZE] = {{0}};

char *priorityProcessesNames[] = {"shell", "time", "printmem", "loop"};
int priorityProcessesValue[] = {2, 1, 2, 1};

int current_process_index = 0;
int current_prio_index = 0;
int cant_of_active_processes = 0;
int first_time_entering = 1;
int rsp_kernel = 0;
int last_pid = 5;

// Creo y lleno el arreglo processes con todos los proceso que puedo tener
// Version 1.0 de manejo de procesos

//TODO crearlos de manera "dinamica" a medida que se necesiten
// hacer que el pid sea incremental
void createprocesses()
{
    //Todo HALTER
    int p = 0;
        for (; p < CANT_PROCESS; p++)
        {
            process proc;
            proc.pid = 0;
            //proc.memory = processMemory[prio][p];
            proc.memory = 0;
            proc.state = MATADO;
            proc.timeRunnig = 0;
            proc.timeSlot = 0;
            processes[p] = proc;
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
    processes[availableProcess].pid = last_pid++;
    processes[availableProcess].timeSlot = TIME_SLOT;
    
    //processes[prio_name][availableProcess].memory = processMemory[prio_name][availableProcess]; // Habria que liberarla una vez matado el proceso
    processes[availableProcess].memory = mallocNUESTRO(STACK_SIZE);

    processes[availableProcess].stackPointer = initStack(processes[availableProcess].memory + STACK_SIZE,
                                                                    wrapper, processes[availableProcess].function, argc, argv, processes[availableProcess].pid);
    // setProcessPriority(&processes[availableProcess]); //?/

    cant_of_active_processes++;
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
    if (cant_of_active_processes == 0)
    {
        
        if (first_time_entering)
        {
            rsp_kernel = rsp;
        }
        return rsp_kernel;
    }
    else
    {
        if (!first_time_entering) // Esto es para que un proceso se actualice el SP.
        {
            processes[current_process_index].stackPointer = rsp;
        }
        first_time_entering = 0;
        if(processes[current_process_index].timeSlot > processes[current_process_index].timeRunnig && processes[current_process_index].state == ACTIVO){
            processes[current_process_index].timeRunnig++;
            return processes[current_process_index].stackPointer;
        }

        int auxIndex = current_process_index + 1;
        int j = 0;
        for(; j<=CANT_PROCESS; j++, auxIndex++){
            if (processes[auxIndex % CANT_PROCESS].state == ACTIVO)
            {
                processes[current_process_index].timeRunnig = 0;
                current_process_index = auxIndex % CANT_PROCESS;
                return processes[current_process_index].stackPointer;
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

        int pos = 0;
        for (; pos < CANT_PROCESS; pos++)
        {
            if (processes[pos].pid == pid)
            {
                processes[pos].state = MATADO;
                freeMemory(processes[pos].memory);
                cant_of_active_processes--;
            }
        }
}

void exit(int status)
{
    kill(processes[current_process_index].pid);
    timerTickInterrupt();
}

int getPid()
{
    return processes[current_process_index].pid;
}
