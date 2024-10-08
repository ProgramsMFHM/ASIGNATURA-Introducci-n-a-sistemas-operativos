/// @author Milton Hernández Morales
/// @brief Generación de procesos Padre-Hijo-Nieto con fork();
///
/// Realizar un programa [padre, hijo, nieto] que muestre a través de sus ID la creación de ellos.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    if(!fork()){
        if(!fork()){ // Proceso Nieto
            printf("Soy el nieto; PID %d; PID padre %d\n", getpid(), getppid());
        }
        else{ // Proceso Hijo
            printf("Soy el hijo; PID %d; PID padre %d\n", getpid(), getppid());
        }
    }
    else{ // Proceso principal - Padre
        printf("Soy el padre; PID %d; PID padre %d\n", getpid(), getppid());
    }

    return 0;
}
