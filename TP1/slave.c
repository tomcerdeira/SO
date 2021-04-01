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
#include <string.h>
#include <strings.h>

#define MINISAT "minisat "
#define GREP_AND_FLAGS " | grep -o -e 'Number of.*[0-9]\\+' -e 'CPU time.*' -e '.*SATISFIABLE' | xargs | sed 's/ /\\t/g'"
#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
    size_t res;
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, 0, _IONBF, 0);
    char buffer[BUFFER_SIZE] = {'\0'};
    //printf("EL HIJO \n");

    while ((res = read(STDIN_FILENO, buffer, sizeof(buffer))) != 0) //EOF del read
    {
        char buffer_aux[BUFFER_SIZE] = {'\0'};
        int flag = 1;
        int t = 0;
        int i = 0;
        while (flag)
        {
            if (buffer[i] != '\n' && buffer[i] != '\0')
            {
                buffer_aux[t++] = buffer[i];
            }
            else if (buffer[i] == '\n')
            {
                buffer_aux[t + 1 ] = '\0';

                char cmd[BUFFER_SIZE];
                char par[BUFFER_SIZE] = {"\0"};
                strcpy(par, MINISAT);


                strcat(par, buffer_aux);
                strcat(par, GREP_AND_FLAGS);

                // printf("Al grep : %s \n", par);
                char *const params[] = {par, NULL};

                int len;
                len = sprintf(cmd, "%d\t%s\t", getpid(), buffer_aux); //check error sprint?

                FILE *stream = popen(*params, "r");
                fgets(&cmd[len], BUFFER_SIZE, stream);
                pclose(stream);
                printf("%s\n", cmd); //this write is atomic

                int h = 0;
                while (h < BUFFER_SIZE) //CAMBIAR!!!!!!!!
                {
                    cmd[h] = '\0';
                    par[h] = '\0';
                    buffer_aux[h++] = '\0';
                }
                t = 0;
            }
            else if (buffer[i] == '\0')
            {
                flag = 0;
            }
            i++;
        }
    }

    return 0;
}
