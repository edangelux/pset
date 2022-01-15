# SPELLER

el código es un corrector de ortografía como tal fue hecho para su ejecución fuera rápida un reto al ser que funciona con un diccionario pesado 

1) escribiremos en `speller.c` comenzaremos comprobando si el argumento de entrada del usuario esta correcto, si es así tomaremos el texto a corregir 

2) luego de eso tendríamos de cargar el diccionario,  si por alguna razón el diccionario está demorando en cargar retornamos un error al usuario , y determinamos el tamaño del diccionario y cargar nuevamente todo

3) si el diccionario abre correctamente sería abrir el texto a corregir y revisar la ortografía de cada palabra,  permitiendo sólo caracteres y apóstrofes

4) cosas que el código haría es  ignorar las palabras con números como ms Word y al encontrar una palabra completa se revisa detenidamente si esta bien escrita y nuevamente se coloca un punto de referencia para seguir con la siguiente palabra,

5) si hubo una palabra corregida se sumara y se mandara luego qué termine el código los puntos de referencia de, faltas de ortografía, palabras,  tiempo de carga

