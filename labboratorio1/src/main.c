#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "delay.h"

int main(int argc, char *argv[]){
    int tiempo_espera=0;
    if(argv[1])
        tiempo_espera = atoi(argv[1]);
    if(!tiempo_espera)
        tiempo_espera = 10;


    if(system("./build/proceso1.out &"))
        printf("Error al ejecutar proceso 1\n");
    if(system("./build/proceso2.out &"))
        printf("Error al ejecutar proceso 2\n");
    if(system("./build/proceso3.out &"))
        printf("Error al ejecutar proceso 3\n");

    delay(tiempo_espera,0);

    if(system("killall proceso1.out proceso2.out proceso3.out"))
        printf("NO SE PUDO MATAR A LOS PROCECSOS!\n");
    printf("Los procesos han terminado luego de %d segundos\n", tiempo_espera);

    return 0;
}