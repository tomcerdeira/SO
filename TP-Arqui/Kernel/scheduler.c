#include "scheduler.h"

#define MATADO 0
#define ACTIVO 1
#define BLOQUEADO 2

#define CANT_PROCESS 10
#define STACK_SIZE 4096

extern uint64_t *initStack(int argc, char *argv[], uint64_t *rsp, void *main);

process processes[CANT_PROCESS] = {{0}};
uint64_t processMemory[CANT_PROCESS][STACK_SIZE] = {{0}};

int current_process_index = 0;
int cant_of_active_processes = 0;

// Creo y lleno el arreglo processes con todos los proceso que puedo tener
// Version 1.0 de manejo de procesos

//TODO crearlos de manera "dinamica" a medida que se necesiten
// hacer que el pid sea incremental
void createprocesses(process *processes)
{
    int p = 1;
    for (; p <= CANT_PROCESS; p++)
    {
        process proc;
        proc.pid = p;
        proc.memory = processMemory[p - 1];
        proc.state = MATADO;
        processes[p - 1] = proc;
    }
}

int getAvailableProcess(process *processes)
{
    int i = 0;
    for (; i < CANT_PROCESS; i++)
    {
        if (processes[i].state == MATADO)
        {
            return i;
        }
    }
    return -1;
}

void startProcess(char *name, void *func, int argc, char *argv[])
//se fija entre todos los procesos, agarra uno que esté muerto/disponible, le asigna la tarea, lo activa,
{
    int availableProcess = getAvailableProcess(processes);

    while (availableProcess < 0)
    {
        // No hay ningun proceso libre --> hlt y volver a buscar
        availableProcess = getAvailableProcess(processes);
    }

    processes[availableProcess].function = func;
    processes[availableProcess].state = ACTIVO;
    processes[availableProcess].name = name;
    processes[availableProcess].memory = processMemory[availableProcess];
    processes[availableProcess].stackPointer = initStack(argc, argv, processes[availableProcess].memory + STACK_SIZE, processes[availableProcess].function);
    cant_of_active_processes++;
}

void wrapper(void *func(int, char **), int argc, char *argv[], int pid)
{
    (*func)(argc, argv);
    kill(pid);
}

uint64_t *activeProcess(uint64_t *rsp)
{
    if (cant_of_active_processes == 0)
    {
        return rsp;
    }
    else
    {
        processes[current_process_index].stackPointer = rsp;
        int i = 0;
        for (; i < CANT_PROCESS; i++) //TODO esta implementación no usa prioridades, habría que chequear el más prioritario
        {
            if (processes[i].state == ACTIVO)
            {
                current_process_index = i;
                return processes[i].stackPointer; //TODO devolver el más prioritario
            }
        }
    }
}