#include <stdio.h>
#include "random.h"
#include "delay.h"

int main(){
    int element;
    int i=0;
    double execTime=0;
    double itemTime;

    FILE *data, *info;
    if((data= fopen("./build/dataproceso1.txt","w")) == NULL)
    {
        printf("No se pudo abrir el archivo ./build/dataproceso1.txt\n");
        exit(-1);
    }
    if((info= fopen("./build/infoproceso1.csv","w")) == NULL)
    {
        printf("No se pudo abrir el archivo ./build/infoproceso1.csv\n");
        exit(-1);
    }

    srand(time(0));
    delay(1,2);
    srand(rand());
    fprintf(info,"Item,Value,Partial,Total\n");
    while(1)
    {
        element = randomInt(0,100);
        //printf("%d\n", element);
        fprintf(data,"%d\n", element);
        fflush(data);
        itemTime = delay(0,3);
        execTime += itemTime;

        //printf("Proceso 1 - Item %d demoro: %.3lf segundos\n",i,  execTime);
        fprintf(info,"%d,%d,%.3lf,%.3lf\n",i,element,itemTime,execTime);
        fflush(info);
        i++;
    }

    fclose(data);
    fclose(info);
}