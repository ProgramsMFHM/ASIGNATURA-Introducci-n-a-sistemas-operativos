# Laboratorio 2: Duplicación de procesos
Este segundo laboratorio se centra en la creación de procesos que se relacionan entre sí mediante la duplicación de un proceso.

Se busca comprender el la lógica detrás de la duplicación de procesos así como sus implicaciones tanto para el sistema operativo como para los propios procesos.

## Tareas del presente laboratorios
- un programa [hijo_padre_abuelo] que muestre a través de sus ID la creación de ellos.
- Ingresar por paso de parámetros tres valores enteros, indicar al padre que duplique el primer valor, al abuelo que eleve  a la potencia 3 el segundo valor y que el hijo obtenga la raíz del tercer valor.
- Dado un conjunto de valores del tipo `{a,b,c}` obtener las raíces de una ecuación cuadrática cuyos factores son a,b,c.  Resolver utilizando hilos (`fork()`)

## Ejecución del programa
Luego de ejecutar `make folders` y `make` se puede hacer lo siguiente.
- Se puede comprobar el programa $1$ ejecutando dentro de la carpeta `build/` el los ejecutables `programa1.out` y `programa2.out` para los dos primeros programas.
- Para los programas relacionados con la función cuadrática es necesario ejecutar primero el programa `generador.out` con un entero como parámetro para que se genere un conjunto de valores de la ecuación cuadrática.
    - Ejecutar `ccuadratic1.out` resolverá las ecuaciones de manera secuencial.
    - Ejecutar `ccuadratic2.out` resolverá las ecuaciones de manera paralela con un proceso para $-b$, uno para $\sqrt{b^2-4ac}$ y otro para $2a$.
    - Ejecutar `ccuadratic3.out` resolverá las ecuaciones generando un proceso por cada una de ellas.
    - Ejecutar `cuadratic4.out` resolverá las ecuaciones compartiendo memoria.

## Creación del informe
El presente programa se trabajó en colaboración con [Ayrton Morrison](https://github.com/ayrtonmo), el cuál tiene sus códigos dentro del (siguiene repositorio)[https://github.com/ayrtonmo/intro-so-2024].