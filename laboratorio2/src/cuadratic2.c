/// @author Milton Hernandez Morales
/// @brief Lectura y solucion de ecuaciones cuadraticas en forma paralela.
///
/// Dado un conjunto de valores del tipo {a,b,c} obtener las raices de una ecuacion cuadratica cuyos factores son a,b,c usando fork().

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
    complex solution1, solution2; // Soluciones de la ecuacion
    clock_t start, end;
    double elapsedTime;
    FILE *resourcesF, *part1F, *part2F, *part3F;
    pid_t child1, child2, child3;
    int cont = 0;
    int maxCont = 0;

    if((resourcesF = fopen("./resources.txt", "rb")) == NULL){
        printf("No se pudo abrir el archivo de recursos\n");
        exit(-1);
    }
    fseek(resourcesF, 0, SEEK_END);
    maxCont = ftell(resourcesF) / sizeof(float) / 3;
    rewind(resourcesF);

    start = clock();
    for(cont = 1; cont <= maxCont; cont++){
        part1 = initComplex(0,0); // corresponde al -b
        part2 = initComplex(0,0); // corresponde a la raiz
        part3 = initComplex(0,0); // corresponde al denominador

        if(fread(&coefficient, sizeof(float), 3, resourcesF) < 3){
            printf("No se pudo leer el archivo de recursos\n");
            exit(-1);
        }

        printf("%d - Los coeficientes ingresados son: %.2f, %.2f, %.2f\n",cont , coefficient[0], coefficient[1], coefficient[2]);

        if(!coefficient[0]){
            printf("La ecuacion no corresponde a una ecuacion cuadratica\n");
        }

        // Primer Fork, para el -b
        child1 = fork();
        if(!child1){ // Es el hijo porque fork devuelve 0
            part1.real = -coefficient[1]; // -b
            if((part1F = fopen("./part1", "wb")) == NULL){
                printf("No se pudo abrir el archivo auxiliar1\n");
                exit(-1);
            }
            fwrite(&part1.real, sizeof(float), 1, part1F);
            fwrite(&part1.imaginary, sizeof(float), 1, part1F);
            fclose(part1F);
            return 0;
        }

        // segundo fork, para el \sqrt{b^2-4ac}
        child2 = fork();
        if(!child2){ // Es el hijo porque fork devuelve 0
            float discriminant = coefficient[1]*coefficient[1] - 4*coefficient[0]*coefficient[2]; // b^2 - 4ac
            if(discriminant >= 0){ // Caso real
                part2.real = sqrt(discriminant); // sqrt(b^2 - 4ac)
            }
            else{ // Caso imaginario
                part2.imaginary = -sqrt(-discriminant); // sqrt(-(b^2 - 4ac))i
            }

            if((part2F = fopen("./part2", "wb")) == NULL){
                printf("No se pudo abrir el archivo auxiliar2\n");
                exit(-1);
            }

            fwrite(&part2.real, sizeof(float), 1, part2F);
            fwrite(&part2.imaginary, sizeof(float), 1, part2F);
            fclose(part2F);
            return 0;
        }

        // tercer fork, para el 2a
        child3 = fork();
        if(!child3){ // Es el hijo porque fork devuelve 0
            if((part3F = fopen("./part3", "wb")) == NULL){
                printf("No se pudo abrir el archivo auxiliar3\n");
                exit(-1);
            }

            part3.real = 2*coefficient[0]; // 2a

            fwrite(&part3.real, sizeof(float), 1, part3F);
            fwrite(&part3.imaginary, sizeof(float), 1, part3F);
            fclose(part3F);
            return 0;
        }

        // Padre
        wait(NULL); // Espera al primer hijo
        wait(NULL); // Espera al segundo hijo
        wait(NULL); // Espera al tercer hijo

        // Leemos las partes
        if((part1F = fopen("./part1", "rb")) == NULL){
            printf("No se pudo abrir el archivo auxiliar1\n");
            exit(-1);
        }
        if((part2F = fopen("./part2", "rb")) == NULL){
            printf("No se pudo abrir el archivo auxiliar2\n");
            exit(-1);
        }
        if((part3F = fopen("./part3", "rb")) == NULL){
            printf("No se pudo abrir el archivo auxiliar3\n");
            exit(-1);
        }

        if(fread(&part1.real, sizeof(float), 1, part1F) != 1){
            printf("No se pudo leer el archivo auxiliar1\n");
            exit(-1);
        }
        if(fread(&part1.imaginary, sizeof(float), 1, part1F) != 1){
            printf("No se pudo leer el archivo auxiliar1\n");
            exit(-1);
        }
        fclose(part1F);

        if(fread(&part2.real, sizeof(float), 1, part2F) != 1){
            printf("No se pudo leer el archivo auxiliar2\n");
            exit(-1);
        }
        if(fread(&part2.imaginary, sizeof(float), 1, part2F) != 1){
            printf("No se pudo leer el archivo auxiliar2\n");
            exit(-1);
        }
        fclose(part2F);

        if(fread(&part3.real, sizeof(float), 1, part3F) != 1){
            printf("No se pudo leer el archivo auxiliar3\n");
            exit(-1);
        }
        if(fread(&part3.imaginary, sizeof(float), 1, part3F) != 1){
            printf("No se pudo leer el archivo auxiliar3\n");
            exit(-1);
        }
        fclose(part3F);

        solution1 = sum(divition(part1, part3), divition(part2,part3));
        solution2 = dif(divition(part1, part3), divition(part2,part3));

        // Imprimir por pantalla
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