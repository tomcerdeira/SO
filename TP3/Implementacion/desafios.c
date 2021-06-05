
#include "includes/desafios.h"

void desafio1()
{
    puts(DESAFIO);
    puts("Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\n\n\n\nDeberán estar atentos a los easter eggs.\n\n\n\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra 'entendido\\n'\n");
    puts(PREGUNTA);
    puts("¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?");
}

void desafio2()
{
    puts(DESAFIO);
    puts("The Wire S1E5\n5295 888 6288\n");
    puts(PREGUNTA);
    puts("¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?\n");
    /// respuesta : itba
}

void desafio3()
{
    puts(DESAFIO);
    puts("https://ibb.co/tc0Hb6w\n");
    puts(PREGUNTA);
    puts("¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?\n");
    // respuesta : M4GFKZ289aku
}

void desafio4()
{
    puts(DESAFIO);
    puts("EBADF...\nwrite: Bad file descriptor\n");
    write(WRITE_EBADF, ".................................................................La respuesta es: fk3wfLCm3QvS", strlen(".................................................................La respuesta es: fk3wfLCm3QvS"));
    puts(PREGUNTA);
    puts("¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?\n");
    // respuesta :fk3wfLCm3QvS
}
void desafio5()
{
    puts(DESAFIO);
    puts("respuesta = strings: 71\n");
    puts(PREGUNTA);
    puts("¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?\n");
    //respuesta :too_easy
}

void desafio6()
{
    puts(DESAFIO);
    puts(".data .bss .comment ? .shstrtab .symtab .strtab\n");
    pid_t pid = getpid();
    char buffer[100] = {0};
    sprintf(buffer, "cat /proc/%d/status | grep \"TracerPid\" > killP.txt ", pid);
    system(buffer);
    FILE *killFile;
    killFile = fopen("killP.txt", "r");

    if (killFile != NULL)
    {
        int pidTracer = -1;
        fscanf(killFile, "TracerPid:\t%d", &pidTracer);
        if (pidTracer >0)
        { // Si leyo un numero
            char bufferKill[30] = {0};
            sprintf(bufferKill, "kill %d", pidTracer);
            system(bufferKill);
            //kill(pidTracer, 0);
        }
    }
    system("rm -f killP.txt");
    //respuesta : .RUN_ME
    puts(PREGUNTA);
    puts("Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?\n");
}

void desafio7()
{
    puts(DESAFIO);
    puts("Filter error\n");
    int k = 0;
    int i = strlen("La respuesta es: K5n2UFfpFMUN");
    char *toPrint = "La respuesta es: K5n2UFfpFMUN";
    srand(time(NULL));
    int randNumber = 0;
    while (k < i)
    {
        randNumber = rand() % 7;
        if (randNumber == 0)
        {
            write(STDOUT_FILENO, toPrint + k++, 1);
        }
        else
        {
            char toP = (char)(rand() % CANT_CHARACTER_USED + ASCII_NO_REPRESENTABLES);
            write(STDERR_FILENO, &toP, 1);
        }
    }
    puts("\n\n");
    puts(PREGUNTA);
    puts("¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?\n");
    //respuesta :K5n2UFfpFMUN
}

// https://www.programmersought.com/article/2256659653/
void desafio8()
{
    puts(DESAFIO);
    puts("¿?\n");
    printf(BLACK_COLOR_PRINTF); // Seteado el color
    printf("La respuesta es: BUmyYq5XxXGt \n");
    printf(RESET_COLOR); // Se resetea al valor default
    puts(PREGUNTA);
    puts("¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?\n");
    //respuesta :BUmyYq5XxXGt
}

void desafio9()
{
    puts(DESAFIO);
    puts("Latexme\nSi\n\\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\\frac{u'}{u})\nentonces\n y=\n");
    puts(PREGUNTA);
    puts("sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?\n");
    // respuesta :u^v
}

void desafio10()
{
    puts(DESAFIO);
    puts("quine\n\n");

    //Compilar el quine.c
    system("gcc -Wall -o quine quine.c");
    // Busco en el PWD si esta el archivo
    DIR *dp;
    int pid = -1;
    int fd[2] = {-1, -1};
    struct dirent *entry;
    struct stat statbuf;
    if ((dp = opendir(".")) == NULL)
    {
        printf("Cannot open directory\n");
        return;
    }
    int found = 0;
    while ((entry = readdir(dp)) != NULL)
    {
        lstat(entry->d_name, &statbuf);
        if (S_ISREG(statbuf.st_mode))
        {
            if (strcmp("quine.c", entry->d_name) == 0)
            {
                found = 1;
            }
        }
    }
    closedir(dp);

    // Si el archivo NO esta, imprimo y corto
    if (!found)
    {
        puts("\n");
        puts("Introduzca cualquier tecla y ENTER para reintentar\n");
    }
    else
    {
        // Si el archivo esta, tengo que ver si hace lo que tiene que hacer
        puts("¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde.\n");

        if (pipe(fd) < 0)
        {
            perror("ERROR al crear pipe (desafio10)");
            return;
        }

        if ((pid = fork()) == 0)
        {
            close(fd[0]);                       // el hijo solo escribe
            if (dup2(fd[1], STDOUT_FILENO) < 0) //redirecciono la salida del STDOUT al pipe (eso intento)
            {
                perror("Error al supear la salida");
            }
            char *quine[] = {"./quine", NULL}; //antes del exec hay que forkear si no te pisa la imagen del server
            int resExec = execvp(quine[0], quine);
            if (resExec < 0)
            {
                perror("ERROR en Execv (desafio10)");
                return;
            }
        }

        close(fd[1]); // el padre solo lee
        char buffer[1024] = {0};
        read(fd[0], buffer, 1024);

        //Ahora deberia ver si lo que se escribio en el fd es igual al programa en si
        char chSalida;
        int bufferIndex = 0;
        FILE *fp;

        int different = 0;

        fp = fopen("quine.c", "r");

        while ((chSalida = (char)fgetc(fp)) != EOF && (buffer[bufferIndex]) != EOF && bufferIndex < 1024)
        {
            if (chSalida != buffer[bufferIndex++])
            {
                different = 1;
            }
        }
        fclose(fp);

        if (!different)
        {
            puts("La respuesta es chin_chu_lan_cha\n");
        }
        else
        {
            puts("-- Codigo del programa --\n"); //Codigo de quine
            char chAux;
            FILE *fpAux;
            fpAux = fopen("quine.c", "r");
            while ((chAux = fgetc(fpAux)) != EOF)
            {
                printf("%c", chAux);
            }

            puts("-- Salida del programa --\n"); //Salida de quine
            bufferIndex = 0;
            while ((buffer[bufferIndex]) != EOF && bufferIndex < 1024)
            {
                printf("%c", buffer[bufferIndex++]);
            }
            printf("\ndiff encontró diferencias.\n");
            printf("\n");
        }
        if (pid > 0)
        {
            waitpid(pid, NULL, 0);
        }
    }

    puts(PREGUNTA);
    puts("¿Cuáles son las características del protocolo SCTP?\n");
    if (fd[0] != -1)
    {
        close(fd[0]);
    }

    // hacer programa quine.c
    // respuesta :chin_chu_lan_cha
}

int gdbme()
{
    return 0;
}

void desafio11()
{
    puts(DESAFIO);
    puts("b gdbme y encontrá el valor mágico\n");

    if (gdbme() != 0x12345678) // Deberia cambiarse el valor de retorno usando el gdb!
    {
        puts("Introduzca cualquier tecla y ENTER para reintentar\n");
    }
    else
    {
        puts("La respuesta es gdb_rules\n");
    }

    puts(PREGUNTA);
    puts("¿Qué es un RFC?\n");
    //respuesta :gdb_rules
}

double drand() /* uniform distribution, (0..1] */
{
    return (rand() + 1.0) / (RAND_MAX + 1.0);
}

double randomNormal()
/* normal distribution, centered on 0, std dev 1 */
{
    return sqrt(-2 * log(drand())) * cos(2 * PI * drand());
}

void desafio12()
{
    puts(DESAFIO);
    puts("Me conoces\n");
    double rands[1000];
    int i = 0;
    for (i = 0; i < 1000; i++)
    {
        rands[i] = 1.0 + 0.5 * randomNormal();
        printf("%g ", rands[i]);
    }
    puts("\n");
    puts(PREGUNTA);
    puts("¿Fue divertido?\n");
    //respuesta :normal
}

void finDesafios()
{
    puts("Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto\n\n");
    // Easter egg
    puts("Lo dejaremos salir en cuanto responda a una pregunta acerca de el Japon\n");
}


