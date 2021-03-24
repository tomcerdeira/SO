// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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

// struct suma1
// {//int car1 = 0;
//     //int car2 = 0;
//     char * nameFile;
//     int valorSuma;
// } ;

// void *thread(void *arg);
// typedef struct suma1 suma_t;

// void suma(suma_t *s);

// int main(int argc, char *argv[])
// {
//     suma_t s1,s2;

//     s1.nameFile = argv[1];
//     s2.nameFile = argv[2];
  

//     pthread_t th1[2];
//    // pthread_create((&th1[0]), NULL, (void *)suma, (void *)&s1);
//     //sleep(1);
//     pthread_create((&th1[1]), NULL, (void *)suma, (void *)&s2);
    
//     int ret = 0;
//  //   ret =  pthread_join(th1[0],NULL);
//     if(ret!=0){
//         perror("ERROR PTHREAD_JOIN 1");
//     }
//      ret = pthread_join(th1[1],NULL);
//    if(ret!=0){
//           perror("ERROR PTHREAD_JOIN 2");
//       }

// //printf("%d \n", s1.valorSuma);
// printf("%d \n", s2.valorSuma);
// return 0;
   
// }


// void suma(suma_t * s){
//     int id;
    
//     id = open(s->nameFile,O_RDONLY);
//     if(id<0){
//         perror("ERROR EN OPEN: ");
//         abort();
//     }

//     s->valorSuma = 0;

//     dup2(id,STDIN_FILENO);
//     int c=0;
//     //int car1 = 0;
//     //int car2 = 0;
//     int flag = 0;

//     while((c = getchar())!=EOF){
//      if(c != '+'){
//         if (flag == 0){
//              s->valorSuma += (c - 48);
//         }
//         if (flag == 2){
//             s->valorSuma += (c - 48);
//         }
//      }
//         flag++;
//     }
//     close(id);
//     //s->valorSuma = car1+car2;
// }