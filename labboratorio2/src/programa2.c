/// @author Milton Hernández Morales
/// @brief Generación de procesos Abuelo-Padre-Hijo con fork();
///
/// Ingresar por consola un valor entero, indicar al hijo que duplique esa información, al padre que eleve esa información a la potencia 3 y que el nieto obtenga la raíz de esa información.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

int main(int argc, char *argv[])
{
    int num;
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
            printf("Soy el nieto; PID %d\nEl numero %d en raíz es: %f\n\n", getpid(), num, sqrt(num));
        }
        else{ // Proceso Padre
            printf("Soy el hijo; PID %d\nEl numero %d duplicado es: %d\n\n", getpid(), num, 2*num);
        }
    }
    else{ // Proceso principal - Abuelo
        printf("Soy el padre; PID %d\nEl numero %d elevado es: %d\n\n", getpid(), num, num*num);
    }

    return 0;
}