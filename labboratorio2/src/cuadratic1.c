/// @author Milton Hernández Morales
/// @brief Lectura y solucion de ecuaciones cuadraticas en forma secuencial.
///
/// Dado un conjunto de valores del tipo {a,b,c} obtener las raices de una ecuacion cuadratica cuyos factores son a,b,c.

#include<stdio.h>
#include<stdlib.h>
#include"complex.h"

/// Colores para mejor apreciacion de los resultados
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define RESET "\x1b[0m"

int main(int argc, char *argv[])
{
    float coefficient[3];
    complex part1 = initComplex(0,0); // corresponde al -b
    complex part2 = initComplex(0,0); // corresponde a la raíz
    complex part3 = initComplex(0,0); // corresponde al denominador
    float discriminant;
    complex solution1, solution2; // Soluciones de la ecuacion

    if(argc<4){
        printf("No se ingresaron 3 coeficientes\n");
        exit(-1);
    }

    coefficient[0] = atof(argv[1]);
    coefficient[1] = atof(argv[2]);
    coefficient[2] = atof(argv[3]);

    printf("Los coeficientes ingresados son: %.2f, %.2f, %.2f\n", coefficient[0], coefficient[1], coefficient[2]);

    if(coefficient[0] == 0)
        printf("La ecuacion no corresponde a una ecuacion cuadratica\n");
    else{
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
        printComplex(solution1);
        printf(RESET"   ;   x_2 = "GREEN);
        printComplex(solution2);
        printf(RESET"\n");
    }

    return 0;
}