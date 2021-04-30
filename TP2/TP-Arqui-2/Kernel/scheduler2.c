#include <scheduler2.h>

#define MAX_PROCESSES_PER_PRIO 10
#define STACK_SIZE_PROCESS 4096
#define CANT_PRIO 3

#define KILLED 0
#define ACTIVE 1
#define BLOCKED 2

int init = 0;
int cantActiveProcesses = 0;
int last_pid = 1;
int current_index = 0;
int current_priority = 0;
process processes[CANT_PRIO][MAX_PROCESSES_PER_PRIO];

void initScheduler(){
    int i =0;
    for(;i<CANT_PRIO;i++){
        int j=0;
        for(;j<MAX_PROCESSES_PER_PRIO;j++){
            process proc;
            proc.pid = last_pid++;
            proc.memory = mallocNUESTRO(STACK_SIZE_PROCESS); // si, malloc
            proc.state = KILLED;
            processes[i][j] = proc;
        }
    }
    init = 1;
}

process * getNextActiveProcess(){
   int i=current_priority;
   int index = i % CANT_PRIO;
   int j = current_index +1;


   for (; i < CANT_PRIO; i++)
   {
       //current+1 -> fin nada
                 //i= current_prio --> j= current +1
      for (; j < MAX_PROCESSES_PER_PRIO; j++)
      {
         if(processes[i][j].state == ACTIVE){
            current_index = j;
            return &processes[i][j];
         }
      }
      j=0;
      if (i == CANT_PRIO - 1) {
          current_priority = 0;
          current_index = 0;
      }
   }
   return getNextActiveProcess();
}

