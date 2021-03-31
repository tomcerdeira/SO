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

#define MINISAT "minisat "
#define GREP_AND_FLAGS " | grep -o -e 'Number of.*[0-9]\\+' -e 'CPU time.*' -e '.*SATISFIABLE' | grep -o -e '[0-9|.]*' -o -e '.*SATISFIABLE' | xargs | sed 's/ /\\t/g'"
#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
    size_t res;
    char buffer[BUFFER_SIZE] = {'\0'};
    // printf("ESTOY EN EL HIJO\n");
    // while ((res = read(STDIN_FILENO, buffer, sizeof(buffer))) != EOF) // NO SERIA EOF??
    // {
    res = read(STDIN_FILENO, buffer, sizeof(buffer));
    if (res < 0)
    {
        perror("Slave READ error");
        abort();
    }

    char cmd[BUFFER_SIZE];
    char par[BUFFER_SIZE] = {"\0"};
    strcat(par, MINISAT);
    //Sacamos el \n
    buffer[res - 1] = '\0';

    strcat(par, buffer);
    strcat(par, GREP_AND_FLAGS);

    char *const params[] = {par, NULL};

    int len;
    len = sprintf(cmd, "%d\t%s\t", getpid(), buffer);

    FILE *stream = popen(*params, "r");
    fgets(&cmd[len], BUFFER_SIZE, stream);
    pclose(stream);
    printf("%s\n", cmd); //this write is atomic
    int i = 0;
    while (buffer[i] != '\0')
    {
        buffer[i] = '\0';
    }

    close(STDOUT_FILENO);
    //}
    return 0;
}
