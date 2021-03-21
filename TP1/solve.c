#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct sumapar
{
    int n, m, r;
};

typedef struct sumapar sumapar_t;

void suma(sumapar_t *par);
void sumaPosta(sumapar_t *par);

int main(int argc, char *argv[])
{

    pthread_t th1, th2;
    sumapar_t s1 = {1, 50, 0};
    sumapar_t s2 = {51, 100, 0};

    // pthread_create(&th1, NULL, (void *)suma, (void *)&s1);
    // pthread_create(&th2, NULL, (void *)suma, (void *)&s2);

    pthread_create(&th1, NULL, (void *)sumaPosta, (void *)&s1);
    pthread_create(&th2, NULL, (void *)sumaPosta, (void *)&s2);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("Suma=%d\n", s1.r + s2.r);

    return 0;
}

void suma(sumapar_t *par)
{
    int i;
    int suma = 0;
    for (i = 0; i <= 2; i++)
    {
        suma += i;
    }
    par->r = suma;
}

void sumaPosta(sumapar_t *par)
{
    par->r = par->m + par->n;
}