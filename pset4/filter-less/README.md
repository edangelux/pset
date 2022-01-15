# FILTER-LESS:camera:

Es un programa que aplica filtros a archivos BMP que se dedican a archivos de pixeles, la parte que implementaremos sera `helpers.c`

1) usaremos 3 librerias una que es la libreria local que es `helpers.h` otra es `math.h` `cs50.h`

2) comenzamos conviertiendo escala de grises que simplemente haremos es restablecer los colores, dividiendo un punto flotante y redondeando para que los valores de los colores se vuelvan en entero dando 255 para que sean grises

3) `sepia` es filtro de marron rojizo la documentacion da un algoritmo para poder lograr el filtro de esa manera y hacemos lo mismo pasamos los valores a redondeandolos y hacerlo flotante y ponerlo un maximo de 255

4) `reflex`  usaremos puntero de una manera muy logica tomaremos el color y lo pasaremos a un puntero y el puntero2 tomara el valor del primero puntero como tal cambiando solo el angulo dando vuelta como espejo}

5) `blur` haces que la imagen tengo un tono borroso recorremos las celdas que sale en documentacion esto lo hacemos en una variable aparte haremos que por pixel se desenfoque y luego colocarlo en la variable correspondiente para que tome su accion correcta
