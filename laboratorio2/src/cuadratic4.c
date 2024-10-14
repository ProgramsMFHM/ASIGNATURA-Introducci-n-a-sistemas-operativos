/// @author Milton Hernandez Morales
/// @brief Lectura y solucion de n ecuaciones cuadraticas en forma paralela con memoria compartida.
///
/// Dado un conjunto de valores del tipo {a,b,c} obtener las raices de una ecuacion cuadratica cuyos factores son a,b,c usando fork(), se usa <sys/shm.h> y <sys/ipc.h> para memoria compartida.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include "complex.h"

/// Colores para mejor apreciacion de los resultados
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define RESET "\x1b[0m"

int main()
{
    float coefficient[3];
    FILE *resourcesF;
    int cont = 0;
    int maxCont;
    clock_t start, end;
    double elapsedTime;

    // Crear un segmento de memoria compartida
    int shmid;
    complex *parts;
    complex solution1, solution2;
    key_t key = 1234; // Llave unica para la memoria compartida

    // Crear un segmento de memoria compartida de tamanio para 2 enteros
    if ((shmid = shmget(key, 3 * sizeof(complex), IPC_CREAT | 0666)) < 0)
    {
        perror("Error al crear la memoria compartida");
        exit(1);
    }

    // Adjuntar la memoria compartida
    if ((parts = (complex *)shmat(shmid, NULL, 0)) == (complex *)-1)
    {
        perror("Error al adjuntar la memoria compartida");
        exit(1);
    }

    // Inicializamos memoria compartida
    parts[0] = initComplex(0,0);
    parts[1] = initComplex(0,0);
    parts[2] = initComplex(0,0);

    if((resourcesF = fopen("./resources.txt", "rb")) == NULL){
        printf("No se pudo abrir el archivo de recursos\n");
        exit(-1);
    }

    fseek(resourcesF, 0, SEEK_END);
    maxCont = ftell(resourcesF) / sizeof(float) / 3;
    fseek(resourcesF, 0, SEEK_SET);
    printf("Cantidad de numeros: %d\n\n", maxCont);

    start = clock();

    for(cont = 1; cont <= maxCont; cont++)
    {
        if(fread(&coefficient, sizeof(float), 3, resourcesF)<3){ // Leer los coeficientes
            printf("No se pudo leer los coeficientes de la ecuacion %d\n", cont);
            exit(-1);
        }
        printf("%d - Los coeficientes ingresados son: %.2f, %.2f, %.2f\n",cont , coefficient[0], coefficient[1], coefficient[2]);

        if(!fork()){ // Primer hijo, encargado de -b
            parts[0].real = -coefficient[1]; // -b
            exit(0);
        }

        if(!fork()){ // Segundo hijo, encargado de \sqrt{b^2-4ac}
            float discriminant = coefficient[1]*coefficient[1] - 4*coefficient[0]*coefficient[2]; // b^2 - 4ac
            if(discriminant >= 0){ // Caso real
                parts[1].real = sqrt(discriminant); // sqrt(b^2 - 4ac)
            }
            else{ // Caso imaginario
                parts[1].imaginary = -sqrt(-discriminant); // sqrt(-(b^2 - 4ac))i
            }
            exit(0);
        }

        if(!fork()){ // Tercer hijo, encargado de 2a
            parts[2].real = 2*coefficient[0]; // 2a
            exit(0);
        }

        wait(NULL); // Espera al primer hijo
        wait(NULL); // Espera al segundo hijo
        wait(NULL); // Espera al tercer hijo

        solution1 = sum(divition(parts[0], parts[2]), divition(parts[1],parts[2]));
        solution2 = dif(divition(parts[0], parts[2]), divition(parts[1],parts[2]));

        // Imprimir por pantalla
        printf("x_1 = "BLUE);
        printComplex(stdout, solution1);
        printf(RESET"   ;   x_2 = "GREEN);
        printComplex(stdout, solution2);
        printf(RESET"\n");
    }

    shmdt(parts); // Desconectar la memoria compartida
    shmctl(shmid, IPC_RMID, NULL); // Eliminar la memoria compartida

    end = clock();
    elapsedTime = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    printf("Tiempo de ejecucion %f\n", elapsedTime);
    fclose(resourcesF);

    return 0;
}