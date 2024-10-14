/// @author Milton Hernandez Morales
/// @brief Lectura y solucion de ecuaciones cuadraticas en forma secuencial.
///
/// Dado un conjunto de valores del tipo {a,b,c} obtener las raices de una ecuacion cuadratica cuyos factores son a,b,c.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    complex part1 = initComplex(0,0); // corresponde al -b
    complex part2 = initComplex(0,0); // corresponde a la raiz
    complex part3 = initComplex(0,0); // corresponde al denominador
    float discriminant;
    complex solution1, solution2; // Soluciones de la ecuacion
    clock_t start, end;
    double elapsedTime;
    FILE *resourcesF;
    unsigned int cont = 0;
    unsigned int maxCont;

    if((resourcesF = fopen("./resources.txt", "r")) == NULL){
        printf("No se pudo abrir el archivo de recursos\n");
        exit(-1);
    }
    fseek(resourcesF, 0, SEEK_END);
    maxCont = ftell(resourcesF) / sizeof(float) / 3;
    fseek(resourcesF, 0, SEEK_SET);

    start = clock();
    for(cont=1; cont<=maxCont; cont++){
        coefficient[0]=0;
        coefficient[1]=0;
        coefficient[2]=0;
        part1 = initComplex(0,0); // corresponde al -b
        part2 = initComplex(0,0); // corresponde a la raiz
        part3 = initComplex(0,0); // corresponde al denominador


        if(fread(&coefficient, sizeof(float), 3, resourcesF) < 3){
            printf("No se pudo leer el archivo de recursos\n");
            exit(-1);
        }

        printf("%d - Los coeficientes ingresados son: %.2f, %.2f, %.2f\n", cont, coefficient[0], coefficient[1], coefficient[2]);

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


        printf("x_1 = "BLUE);
        printComplex(stdout, solution1);
        printf(RESET"   ;   x_2 = "GREEN);
        printComplex(stdout, solution2);
        printf(RESET"\n");
    }

    end = clock();
    elapsedTime = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    printf("Tiempo de ejecucion %f\n", elapsedTime);
    fclose(resourcesF);
    return 0;
}