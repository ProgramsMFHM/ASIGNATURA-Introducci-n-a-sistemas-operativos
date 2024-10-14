/// @author Milton Hernandez Morales
/// @brief Lectura y solucion de n ecuaciones cuadraticas en forma paralela con n hijos.
///
/// En este programa se crea un hijo mediante fork() para cada una de las ecuaciones cuadraticas.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "complex.h"
#include <unistd.h>
#include "sys/types.h"
#include "sys/wait.h"

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
    complex part1 = initComplex(0,0); // corresponde al -b
    complex part2 = initComplex(0,0); // corresponde a la raiz
    complex part3 = initComplex(0,0); // corresponde al denominador
    float discriminant;
    complex solution1, solution2; // Soluciones de la ecuacion
    clock_t start, end;
    double elapsedTime;
    FILE *resourcesF;
    long int MAXHIJOS = 0;

    if((resourcesF = fopen("./resources.txt", "rb")) == NULL){
        printf("No se pudo abrir el archivo de recursos\n");
        exit(-1);
    }

    part1 = initComplex(0,0); // corresponde al -b
    part2 = initComplex(0,0); // corresponde a la raiz
    part3 = initComplex(0,0); // corresponde al denominador

    // Calcular la cantidad de hijos maxima
    if((resourcesF = fopen("./resources.txt", "rb")) == NULL){
        printf("No se pudo abrir el archivo de recursos\n");
        exit(-1);
    }
    fseek(resourcesF, 0, SEEK_END);
    MAXHIJOS = ftell(resourcesF) / sizeof(float) / 3;
    fclose(resourcesF);

    printf("Hijos maximos: %ld\n", MAXHIJOS);

    start = clock();

    for(long int i = 1; i <= MAXHIJOS; i++){
        if(!fork()){ // Crear un hijo
            if((resourcesF = fopen("./resources.txt", "rb")) == NULL){
                printf("No se pudo abrir el archivo de recursos\n");
                exit(-1);
            }
            fseek(resourcesF, (i-1) * sizeof(float) * 3, SEEK_SET); // Ir a la linea
            if(fread(&coefficient, sizeof(float), 3, resourcesF)<3){ // Leer los coeficientes
                printf("No se pudo leer los coeficientes de la linea %ld\n", i);
                exit(-1);
            }
            fclose(resourcesF);

            if(coefficient[0] == 0){
                printf("La ecuacion no corresponde a una ecuacion cuadratica\n");
            }
            part1.real = -coefficient[1]; // -b

            discriminant = coefficient[1]*coefficient[1] - 4*coefficient[0]*coefficient[2]; // b^2 - 4ac

            if(discriminant >= 0){ // Caso real
                part2.real = sqrt(discriminant); // sqrt(b^2 - 4ac)
            }
            else{ // Caso imaginario
                part2.imaginary = -sqrt(-discriminant); // sqrt(-(b^2 - 4ac))i
            }

            part3.real = 2*coefficient[0]; // 2a

            solution1 = sum(divition(part1, part3), divition(part2,part3));
            solution2 = dif(divition(part1, part3), divition(part2,part3));

            // Imprimir soluciones por pantalla
            printf("%ld - Coef: %.2f, %.2f, %.2f\t\t ", i, coefficient[0], coefficient[1], coefficient[2]);
            printf("x_1 = "BLUE);
            printComplex(stdout, solution1);
            printf(RESET"   ;   x_2 = "GREEN);
            printComplex(stdout, solution2);
            printf(RESET"\n");
            exit(0);
        }
    }

    printf("For terminado\n");
    for(long int i = 0; i < MAXHIJOS; i++){ // Esperamos a todos los hijos
        wait(NULL);
    }
    end = clock();
    elapsedTime = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    printf("Tiempo de ejecucion %f\n", elapsedTime);

    return 0;
}