# READABILITY:black_nib:	

el codigo ayuda a decifrar si un texto tinene una complejidad y calcula que tipo de grado de complejidad llega a hacerlo

1)usamos 5 librerias `stdio.h` `cs50.h` `string.h` `ctype.h` `math.h` creamos 4 variables que seran las principales para hacer todo el codigo que serian `count_letters` `count_words` `count_sentences` `grado`

2) tomaremos el texto que el usuario ingrese y comenzamos a hacer la magia, iremos a el contador de letras y cada letra que se dectecte se ira sumando hasta tener el valor concreto de todo, en el contador de palabras como tal contamos que cada espacio seria la division de una palabra y asi sacamos la sumatoria de las palabras, cuando calculemos las oraciones sera que terminen con `?` `.` `!` cuando dectete uno de eso se tomara como una oracion 

3) al tener el conteo de todo usaremos la formula que dara entendimiento alcodigo que es `index = 0.0588 * L - 0.296 * S - 15.8` esa formulara hara saber el tipo de grado que el texto esta colocado

4) al tener el dato del grado solo falta determinar el `printf` determinado por cada grado que el check te pide
