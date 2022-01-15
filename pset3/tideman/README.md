# TIDEMAN :postbox:

tideman es posiblemente un sistema mejorado de runoff de la eleciones preferenciales que existe mas de 1 candidato preferencial, el sistema tideman funciona de manera mas perfecionista de errores que runoff, este sistema es mas tardio y su posicion es no tener un ciclo de votaciones sino el sistema de el es romper cualquier minimo de ciclo que se pueda hacer antes de la definicion del ganador

1) se usara 4 librerias `cs50.h` `stdio.h` `string.h` `stdlib.h`, comprobaremos que cada voto sea un voto transparente en elegir un candidato en cada rango, actualizaremos los rangos por cada nuevo voto, se estara actualizando al matriz de preferencia cuando se guarden los votos 

2) si existe la posibilidad que haya par de candidatos ganadores, aca tomaremos la tarea de romper el ciclo que se haria futuramente, nos daremos cuenta por `pairs` 

3) `comparar` que lo que hara es encontrar un ganador dependiendo de cuanto gente apoya a cierto candidato, me refiero cuantos votantes tienen como primer rango preferido a ese candidato si existe una mayoria

4) tenemo `ciclo` que nos hara confirmar o saber que existe un ciclo si existe esto pasara en `ciclo_ayuda` y con ayuda de `raiz` estara buscando una posible raiz y con `esraiz` sera al final encontrar la raiz de un posible candidato ganador  y asi es como se llegaria a no ser un sistema que pueda elegir a el candidato ganador

