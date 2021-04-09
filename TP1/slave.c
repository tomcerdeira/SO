// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "includes.h"

#define MINISAT "minisat "
#define GREP_AND_FLAGS " | grep -o -e 'Number of.*[0-9]\\+' -e 'CPU time.*' -e '.*SATISFIABLE' | xargs | tr -s [:space:]"
#define BUFFER_SIZE 256
void cleanBuffer(char *buffer);

int main(int argc, char *argv[])
{
    //size_t res;
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, 0, _IONBF, 0);
    char buffer[BUFFER_SIZE] = {'\0'};

    while (read(STDIN_FILENO, buffer, sizeof(buffer)) != 0) //EOF del read
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
                buffer_aux[t + 1] = '\0';

                char cmd[BUFFER_SIZE] = {'\0'};
                char par[BUFFER_SIZE] = {"\0"};
                strcpy(par, MINISAT);

                strcat(par, buffer_aux);
                strcat(par, GREP_AND_FLAGS);

                char *const params[] = {par, NULL};

                int len;
                len = sprintf(cmd, "PID: %d | Solucion de: %s | ", getpid(), buffer_aux);
                if (len < 0)
                {
                    printf("PID: %d | ", getpid());
                    printf("ERROR en Slave - sprintf\n");
                    abort();
                }

                FILE *stream = popen(*params, "r");
                if (stream == NULL)
                {
                    printf("PID: %d | ", getpid());
                    perror("ERROR en Slave - popen");
                    abort();
                }
                fgets(&cmd[len], BUFFER_SIZE, stream);
                int retValue = pclose(stream);
                if (retValue < 0)
                {
                    printf("PID: %d | ", getpid());
                    perror("ERROR en Slave - pclose");
                    abort();
                }
                printf("%s \n", cmd); //this write is atomic
                cleanBuffer(cmd);
                cleanBuffer(par);
                cleanBuffer(buffer_aux);
                t = 0;
            }
            else if (buffer[i] == '\0')
            {
                flag = 0;
            }
            i++;
        }
        cleanBuffer(buffer);
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////FUNCIONES////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cleanBuffer(char *buffer)
{
    int j = 0;
    while (buffer[j] != '\0')
    {
        buffer[j++] = '\0';
    }
}