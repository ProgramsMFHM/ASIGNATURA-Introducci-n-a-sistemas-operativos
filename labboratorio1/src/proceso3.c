#include <stdio.h>
#include "random.h"
#include "delay.h"

int main(){
    int number;
    int i = 0;
    char letter;
    double execTime=0;
    double itemTime;

    FILE *data, *info;
    if((data= fopen("./build/dataproceso3.txt","w")) == NULL)
    {
        printf("No se pudo abrir el archivo ./build/dataproceso3.txt\n");
        exit(-1);
    }
    if((info= fopen("./build/infoproceso3.csv","w")) == NULL)
    {
        printf("No se pudo abrir el archivo ./build/infoproceso3.csv\n");
        exit(-1);
    }

    srand(time(0));
    delay(1,2);
    srand(rand());
    fprintf(info,"Item,Value,Partial,Total\n");
    while (1)
    {
        number = randomInt(0,100);
        letter = randomLetter();
        //printf("%c%d\n", letter,number);
        fprintf(data,"%c%d\n",letter,number);
        fflush(data);
        itemTime = delay(0,3);
        execTime += itemTime;

        //printf("Proceso 3 - Item %d demoro: %.3lf segundos\n",i,  execTime);
        fprintf(info,"%d,%c%d,%.3lf,%.3lf\n",i,letter,number,itemTime,execTime);
        fflush(info);
        i+=1;
    }

    fclose(data);
    fclose(info);
}