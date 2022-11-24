GRAFICADOR DE FUNCIONES     
                                 
Salma Patricia Gutiérrez Rivera 
Maestría en Computación         
salma.gutierrez@cimat.mx        
agosto 2022                     


Programa que grafica funciones de una variable
utilizando las librerías Cairo y fparser.

El código se encuentra en el archivo graficador.cpp.
El resto de archivos pertenecen a la librería fparser
y deben incluirse en la misma carpeta que el programa
principal para que éste funcione.

*******************
COMPILAR:
*******************
g++ graficador.cpp -o graficador -std=c++0x $(pkg-config --cflags --libs cairo) fpoptimizer.cc fparser.cc

Nota: El programa fue compilado en Ubuntu. Otras distribuciones
podrían requerir comillas invertidas `` en lugar de $() para
usar el pkg-config.

La compilación demora unos ocho segundos.

******************** 
CORRER Y USAR:
********************
./graficador

Ingresar una función con sintaxis válida para fparser
(consultar documentación) y verificar que el inicio del
dominio de la función sea un número menor al final.

La gráfica se guarda en el archivo grafica.png