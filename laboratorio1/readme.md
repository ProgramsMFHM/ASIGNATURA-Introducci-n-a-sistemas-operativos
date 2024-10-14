# Laboratorio 1: Repaso de herramientas de programación en C
El objetivo de este laboratorio es reforzar conceptos aprendidos anteriormente y/o adquirirlos en caso de no haberlos tenido.

Estos Conceptos son:
- Números Aleatorios
- Retardo de tiempo
- Cálculo de tiempo ejecución
- Números de procesos
- Eliminación de procesos
- Ejecución de procesos en forma desatendida

Según instrucciones del profesor se debe realizar lo siguiente:
1. Crear tres procesos generadores de palabras.
    - Primer proceso Genera (Números enteros aleatorios entre 0 y 100)
    - Segundo proceso Genera (Letras aleatorias de la A a la Z)
    - Tercer proceso Genera (Una letra acompañada de un numero entero)
2. Para cada generador se debe considerar que tras cada creación debe haber un tiempo de retardo delay() entre 0 y 3 seg
3. Determinar el tiempo de ejecución de cada generador de palabras.
4. Correr los tres generadores al mismo tiempo en forma desatendida, liberando así  la consola de comandos.
5. Guardar los datos generados en tiempo de ejecución de cada uno de los tres generadores.
6. Si el generador es infinito, ver; Número de proceso en ejecución y eliminación del proceso.

Ejecutando estas instrucciones se busca responder mediante un [Informe](docs/Latex/Informe%20de%20laboratorio.pdf) las siguientes preguntas:
1. De que manera se puede realizar verdadera aleatoriedad de un numero?
2. Si los tres generadores crean 10.000 palabras cada uno, demoran el mismo tiempo de ejecución?
3. Si se crean 50 generadores idénticos, el tiempo de ejecución es el mismo para todos?
4. De que manera se pueden eliminar todos los procesos en ejecución de una sola vez
5. Cuál es el comando que elimina procesos?
6. Si quitemos los delay de tiempos, la ejecución de los generadores será la misma?  si no es así, a que se debe?
7. Qué otros procesos ejecuta el Sistema Operativo mientras se ejecutan los que ud creó?

## Ejecución
Luego de ejecutar `make folders` y `make` se puede hacer lo siguiente.
- Ejecutar `main.out` de la carpeta `build/` con un número entero accionará los tres procesos durante ese número de segundos y posterior a eso los eliminará.
- Ejecutar el script [tables.py](docs/python/tables.py) habiendo ejecutado previamente el `main.out` generará tablas LaTex en el directorio [Latex](docs/Latex/src/tables/) que será compiladas si se compila el [main.tex](docs/Latex/main.tex).