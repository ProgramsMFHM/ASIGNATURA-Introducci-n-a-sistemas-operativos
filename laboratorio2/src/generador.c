#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int main(int argc, char* argv[]){
    srand(time(NULL));

    int triadas;
    float coeficientes[3];
    if(argc < 2){
        triadas = 10;
    }
    else{
        triadas = atoi(argv[1]);
    }
    printf("Se generaran %d triadas de numeros aleatorios:\n", triadas);

    FILE *res = fopen("./resources.txt", "wb");
    for(int i = 0; i < triadas; i++){
        for(int j = 0; j < 3; j++){
            coeficientes[j] = (float)((rand()%11)+1);
        }
        printf("%d %.2f %.2f %.2f\n", i+1, coeficientes[0], coeficientes[1], coeficientes[2]);
        fwrite(coeficientes, sizeof(float), 3, res);
    }
    fclose(res);
    return 0;
}
