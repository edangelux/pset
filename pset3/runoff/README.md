# RUNOFF :envelope_with_arrow:


tenemos una serie de candidatos el votante rankea por mayor favoritismo si un candidato tiene mas de la mitad de votaciones o sino se hara una ronda de eliminacion y se eliminaria el que tenga votos mas bajos y se vuelve a evaluar hasta que haya un ganador
1) usamos 3 librerias `cs50.h` `stdio.h` `string.h` definimos como maximo 100 votantes y 9 candidatos

2) verificamos que exista el candidato que votaria el votante si el voto es valido iremos actualizando la matriz

3) si a la primera un candidato no tiene mas de la mitad de los votos se haria la ronda de eliminacion, cuando surga la ronda de eliminacion actualizariamos los votos a el candidato de mayor rank de el votante y que no hayan sido eliminado

4) para descubrir el candidato minimo de votos existe `find_min` se repetira la funciones de eliminacion y colocacion de votos de mayor populariodad del votante hasta que se consiga un ganador
