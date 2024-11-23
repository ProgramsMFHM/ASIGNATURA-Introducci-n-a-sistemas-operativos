/**
 * @file philosopher.c
 * @author Milton Hernandez, Ayrton Morrison
 * @brief Implementación del problema de los filósofos
 */
// Definiciones iniciales

#define N 5 /* Número de filósofos */
#define LEFT ID!=0 ? (ID-1) : N-1 /* Vecino a la izquierda de i */
#define RIGHT (ID+1)%N /* Vecino a la derecha de i */
#define THINKING 0 /* Filosofando */
#define HUNGRY 1 /* Intentando comer */
#define EATING 2 /* Comiendo */

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

/** \struct _programInfo
 * @brief Informacion del programa, para trabajo con hebras
*/
struct _programInfo{
    sem_t mutex; /*< Mutex para proteger el acceso a la estructura*/
    sem_t s[N]; /*< Semáforos para proteger las operaciones*/
    int state[N]; /*< Estado de cada filósofo*/
};

struct _programInfo ProgramInfo;

void* philosopher(void* arg);
void think(int ID);
void eat(int ID);
void take_forks(int ID);
void test(int ID);
void put_forks(int ID);

int main(){
    // Inicializamos a todos los filosofos
    sem_init(&ProgramInfo.mutex, 0, 1);
    for(int i = 0; i < N; i++){
        sem_init(&ProgramInfo.s[i], 0, 0);
        ProgramInfo.state[i] = THINKING;
    }

    pthread_t threads[N];
    for(int i = 0; i < N; i++){
        int* id = (int*)malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, philosopher, (void*)(id));
    }

    srand(time(NULL));

    for(int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void* philosopher(void* arg){
    int* ID = ((int*)arg);
    // printf("Inicializando filosofo %d\n", *ID);

    while(1){
        think(*ID);
        take_forks(*ID);
        eat(*ID);
        put_forks(*ID);
    }

    free(ID);
    return NULL;
}

void eat(int ID){
    printf("Filosofo %d" ANSI_COLOR_GREEN " COMIENDO" ANSI_COLOR_RESET "\n", ID);
    sleep((rand()%9)+1);
}

void think(int ID){
    printf("Filosofo %d" ANSI_COLOR_YELLOW " PENSANDO" ANSI_COLOR_RESET "\n", ID);
    sleep((rand()%9)+1);
}

void take_forks(int ID){
    sem_wait(&ProgramInfo.mutex);       // Entro en la seccion crítica
    ProgramInfo.state[ID] = HUNGRY;     // Indico que tengo hambre
    test(ID);                           // Compruebo si puedo o no comer
    sem_post(&ProgramInfo.mutex);       // Salgo de la seccion crítica
    sem_wait(&ProgramInfo.s[ID]);       // Me bloqueo en caso que no haya podido tomar los tenedores
}

void put_forks (int ID){
    sem_wait(&ProgramInfo.mutex);       // Entro en la seccion crítica
    printf("Fin %d\n",ID);
    ProgramInfo.state[ID] = THINKING;   // Indicamos que el filosofo termino de comer
    printf("\tFilosofo %d prueba a %d\n", ID, LEFT);
    test(LEFT);                         // Probamos si el filosofo de la izquierda quiere comer y si puede hacerlo
    printf("\tFilosofo %d prueba a %d\n", ID, RIGHT);
    test(RIGHT);                        // Probamos si el filosofo de la derecha quiere comer y si puede hacerlo
    sem_post(&ProgramInfo.mutex);       // Salgo de la seccion crítica
}



void test(int ID){
    // En caso de que tenga hambre compruebo si puedo comer.
    if(ProgramInfo.state[ID] == HUNGRY){
        if(ProgramInfo.state[LEFT] != EATING &&
           ProgramInfo.state[RIGHT] != EATING
        ){
            // En caso de poder entonces indico que estoy comiendo
            ProgramInfo.state[ID] = EATING;
            // En caso de que estuviera bloqueado por esperar a que los demas terminen de comer entonces me desbloqueo
            // Si no estoy bloqueado esta senhal evita que me bloquee por accion de la función "take_forks()"
            sem_post(&ProgramInfo.s[ID]);
        }
        else{
            printf("Filosofo %d" ANSI_COLOR_RED " ESPERANDO" ANSI_COLOR_RESET "\n", ID);
        }
    }
}