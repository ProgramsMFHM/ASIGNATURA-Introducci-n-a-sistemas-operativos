/// @author Milton Hernandez Morales
/// @brief Generacion de procesos Abuelo-Padre-Hijo con fork();
///
/// Ingresar por consola un valor entero, indicar al hijo que duplique esa informacion, al padre que eleve esa informacion a la potencia 3 y que el nieto obtenga la raiz de esa informacion.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

int main(int argc, char *argv[])
{
    int num;
    double resultado;
    if(argv[argc-1]){
        num = atoi(argv[argc-1]);
        printf("Numero pasado por parametro: %d\n\n", num);
    }
    else{
        printf("Numero no ingresado, se usara 2\n\n");
        num = 2;
    }

    if(!fork()){
        if(!fork()){ // Proceso nieto
            resultado = sqrt(num);
            printf("Soy el nieto; PID %d\nEl numero %d en raiz es: %f\n\n", getpid(), num, resultado);
        }
        else{ // Proceso Padre
            resultado = 2*num;
            printf("Soy el hijo; PID %d\nEl numero %d duplicado es: %f\n\n", getpid(), num, resultado);
        }
    }
    else{ // Proceso principal - Abuelo
        resultado = num*num;
        printf("Soy el padre; PID %d\nEl numero %d elevado es: %f\n\n", getpid(), num, resultado);
    }

    return 0;
}