# FILTER-MORE:camara_with_flash:

filter-more tendra las mismas funciones que filter-less pero tendra unas agradas como veran ahorita

1) hacemos todos lo pasos anteriores en `helpers.c` y colocamos todo 

2) la deteccion de los bordes es tomando cada pixel y modificando la cuadricula 3x3 que rodea el pixel, entonces eso haremos iterar por medios de los pixeles, sacaremos lo valores de celdas de dj y di correspondiento a las columnas, y hacer los calculos de raiz cuadra necesarios para crear los bordes

3) al tener todos esos datos lo unico que hariamos seria colocar los datos en la variable accionar de `edges`
