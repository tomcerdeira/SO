#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    int fd[2];
    if (pipe(fd) != 0)
    {
        perror("Pipe error");
        abort();
    }

   //int res = 0;
 
    //char *const params[] = {"minisat", argv[1], "|", "grep","-o -e \"Number of.*[0-9]\\+\"-e CPU time.* -e .*SATISFIABLE", NULL};
    char *const params[] = {"minisat ../CNF/hole8.cnf > grep -o -e \"Number of.*[0-9]\\+\"-e CPU time.* -e .*SATISFIABLE", NULL};
    FILE * fp = popen(*params, "w");

    pclose(fp);

    // if ((res = fork()) == 0) // el hijo que ejecuta minisat
    // {
    //     close(fd[0]);
    //     dup2(fd[1],STDOUT_FILENO);
    //     char *const params[] = {"minisat",argv[1], NULL};
    //     int res_execv = execvp(params[0], params);
    //     if (res_execv < 0)
    //     {
    //         perror("Execv error");
    //         abort();
    //     }

    // }else if(res<0){
        
    //     perror("Fork error");
    //     abort();

    // }else{ // el padre
    //     int res2;
    //     if ((res2 = fork()) == 0) // el hijo que ejecuta minisat
    //     {
    //         dup2(fd[0],STDIN_FILENO);
    //         popen()
    //         char *const params[] = {"grep","-o","-e","Number of.*[0-9]\\+","-e","CPU time.*" ,"-e", ".*SATISFIABLE",argv[1], NULL};
    //         int res_execv = execvp(params[0], params);
    //         if (res_execv < 0)
    //         {
    //             perror("Execv error");
    //             abort();
    //         }

    //     }else if(res2<0){
            
    //         perror("Fork error");
    //         abort();
    //     }
    // }
    
    return 0;
    
}

/////////////////////////////////////////////////////////////////



// int randInt(int a, int b);

// int main(int argc, char *argv[])
// {
//     //  setvbuf(stdout, NULL, _IONBF, 0);
//     // setvbuf(stdin, 0, _IONBF, 0);
//    // srand(time(NULL));
//     int rand1 = randInt(1, 10);
  
//     sleep((getpid() % 3)+2);
//     if (1)
//     {
//         // printf("Hijo %d espera %d\n", getpid(), rand1);
//         printf("Hijo %d recibe archivo %s\n", getpid(), argv[1]);
//     }
    
//     return 1;
// }

// int randInt(int a, int b)
// {
//     int randValue;
//     randValue = (rand() % (b - a + 1)) + a;
//     return randValue;
// }
