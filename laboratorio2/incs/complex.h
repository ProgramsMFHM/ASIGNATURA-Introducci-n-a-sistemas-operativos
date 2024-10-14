#ifndef COMPLEX
#define COMPLEX
#include<stdio.h>
#include<math.h>

/// \struct complex
/// @brief Estructura para representar un numero complejo.
typedef struct complex{
    float real; ///< Parte real
    float imaginary; ///< Parte imaginaria
} complex;

complex initComplex(float real, float imaginary);
float mod(complex x);
complex conjugate(complex x);
complex sum(complex x, complex y);
complex dif(complex x, complex y);
complex mult(complex x, complex y);
complex divition(complex x, complex y);
complex inverse(complex x);
void printComplex(FILE* stream, complex x);
#endif