El siguiente código es una recomendación del profesor para implementar la función delay().

```C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
double delay();

int main()
{
	int alt, N=0;
	clock_t tiempo_init, tiempo_end;
	double seg, dey;
	srand(time(0));

	printf("\n");
	while(N<=100)
	{
        tiempo_init=clock();

        alt=(rand()%101)-1;
        printf("\nNúmero aleatorio: [%d]", alt);

        tiempo_end=clock();
        seg= (double) (tiempo_end - tiempo_init)/CLOCKS_PER_SEC;
        printf("\nTIME--->[%f]", seg);

        N++;
        dey=delay();
        printf("\n\t\t\t\tDELAY:%.2f\n", dey);
	}
	return 0;
}
double delay()
{
	double miliseg=0, segs=0;
	clock_t tiempo_inicio, tiempo_final;

	srand(time(0));
	segs=(rand()%2000)+1000;

	miliseg = 1000 * segs;
	tiempo_inicio = clock();
	while (clock() < tiempo_inicio + miliseg);

    tiempo_final = clock();
    tiempo_final -= tiempo_inicio;

	return (double) tiempo_final/CLOCKS_PER_SEC;
}
```