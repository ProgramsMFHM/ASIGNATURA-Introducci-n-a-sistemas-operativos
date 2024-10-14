#include <stdio.h>
#include "random.h"
#include "delay.h"

int main(){
    int i=0;
    char element;
    double execTime=0;
    double itemTime;

    FILE *data, *info;
    if((data= fopen("./build/dataproceso2.txt","w")) == NULL)
    {
        printf("No se pudo abrir el archivo ./build/dataproceso2.txt\n");
        exit(-1);
    }
    if((info= fopen("./build/infoproceso2.csv","w")) == NULL)
    {
        printf("No se pudo abrir el archivo ./build/infoproceso2.csv\n");
        exit(-1);
    }

    srand(time(0));
    delay(1,2);
    srand(rand());
    fprintf(info,"Item,Value,Partial,Total\n");
    while(1)
    {
        element = randomLetter();
        //printf("%c\n", element);
        fprintf(data,"%c\n", element);
        fflush(data);
        itemTime = delay(0,3);
        execTime += itemTime;

        //printf("Proceso 2 - Item %d demoro: %.3lf segundos\n",i,  execTime);
        fprintf(info,"%d,%c,%.3lf,%.3lf\n",i,element,itemTime,execTime);
        fflush(info);
        i++;
    }

    fclose(data);
    fclose(info);
}