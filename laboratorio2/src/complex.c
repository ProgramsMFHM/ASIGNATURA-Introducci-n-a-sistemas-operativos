#include "complex.h"

/// @brief Inicializa el numero complejo
/// @param real Parte real del numero complejo
/// @param imaginary Parte imaginaria del numero complejo
/// @return Numero complejo inicializado
/// @note Si algún parámetro no se ingresa, se asigna 0 a dicho parámetro
complex initComplex(float real, float imaginary)
{
    complex x;

    if(!real)
        x.real = 0;
    if(!imaginary)
        x.imaginary = 0;
    else{
        x.real = real;
        x.imaginary = imaginary;
    }

    return x;
}

/// @brief Calcula el conjugado de un numero complejo
/// @param x Numero complejo para calcular
/// @return Conjugado de @p x
complex conjugate(complex x)
{
    complex z;

    z.real = x.real;
    z.imaginary = -x.imaginary;

    return z;
}

/// @brief Calcula la suma de los numeros @p x e @p y
/// @param x Primer sumando
/// @param y Segundo sumando
/// @return Suma de los numeros @p x e @p y
complex sum(complex x, complex y)
{
    complex z;

    z.real = x.real + y.real;
    z.imaginary = x.imaginary + y.imaginary;

    return z;
}

/// @brief Calcula la resta de los numeros @p x e @p y
/// @param x Primer restando
/// @param y Segundo restando
/// @return Resta de los numeros @p x e @p y
complex dif(complex x, complex y)
{
    complex z;

    z.real = x.real - y.real;
    z.imaginary = x.imaginary - y.imaginary;

    return z;
}

/// @brief Calcula el producto de los numeros @p x e @p y
/// @param x Primer factor
/// @param y Segundo factor
/// @return Producto de los numeros @p x e @p y
complex mult(complex x, complex y)
{
    complex z;

    z.real = x.real*y.real - x.imaginary*y.imaginary;
    z.imaginary = x.real*y.imaginary + x.imaginary*y.real;

    return z;
}

/// @brief Calcula la division de los numeros @p x e @p y
/// @param x Dividendo
/// @param y Divisor
/// @return Division de los numeros @p x e @p y
complex divition(complex x, complex y)
{
    return mult(x, inverse(y));
}

complex inverse(complex x)
{
    complex z;

    if(mod(x)==0)
        return initComplex(0,0);

    z.real = x.real/(pow((double)mod(x),(double)2));
    z.imaginary = -x.imaginary/(pow((double)mod(x),(double)2));

    return z;
}

/// @brief Calcula el modulo del numero complejo @p x
/// @param x Numero a calcular el modulo
/// @return Modulo del numero complejo @p x
float mod(complex x)
{
    return sqrt(x.real*x.real + x.imaginary*x.imaginary);
}

void printComplex(FILE* stream, complex x)
{
    if(x.imaginary<0)
        fprintf(stream,"%.3f - %.3f i", x.real, -x.imaginary);
    else
        fprintf(stream,"%.3f + %.3f i", x.real, x.imaginary);
}