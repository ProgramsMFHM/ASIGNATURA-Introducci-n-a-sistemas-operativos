#ifndef DELAY
#define DELAY
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

double delay(int min, int max)
{
	clock_t tiempo_inicio, tiempo_final, tiempo_espera;
	if(max)
	{
		clock_t minclock = min*CLOCKS_PER_SEC;
		clock_t maxclock = max*CLOCKS_PER_SEC;

		tiempo_espera =(rand()%maxclock+1-minclock)+minclock;
	}
	else
		tiempo_espera = min * CLOCKS_PER_SEC;

	tiempo_inicio = clock();
	while (clock() < tiempo_inicio + tiempo_espera);

	tiempo_final = clock();
	tiempo_final -= tiempo_inicio;

	return (double) tiempo_final/CLOCKS_PER_SEC; // Retornamos el tiempo de delay
}

#endif