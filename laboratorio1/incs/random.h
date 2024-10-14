#ifndef RANDOM
#define RANDOM
#include <stdlib.h>
#include <time.h>

int randomInt(int min, int max){
    return (rand()%(max+1-min))+min;
}

char randomLetter(){
    int min = 65; // A en ASCII
    int max = 122; // z en ASCII
    char letter;

    do
    {
        letter = (rand()%(max+1-min))+min;
    }while(letter>90 && letter<97); // Entre 91 y 96 no son letras

    return letter;
}

#endif