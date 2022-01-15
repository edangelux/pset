import csv
from sys import argv

def main():
    # verificamos el numero correcto de argumentos
    # si es correcto tenemos archivo csv y el archivo txt
    if len(argv) !=3:
        print("Usage: python dna.py data.csv sequence.txt")

    #abrimos archivos
    archivo = open("./"+ argv[1])
    dna = open("./" + argv[2])

    #obtener solo los str
    leer = csv.DictReader(archivo)
    strs = leer.fieldnames[1:]

    #copiamos conteido de dna a una cadena y cerramos archivo
    ADN = dna.read()
    dna.close()

    #contamos el numero de cada str en secuense y almacenamos el valor
    ADN_str = {}
    for str in strs:
        ADN_str[str] = repetidas(str, ADN)

    #encontrar coincidencia
    for row in leer:

        #si hay coincidencias imprimir resultado y acabar todo lptm
        if match(strs, ADN_str, row):
            print(f"{row['name']}")
            archivo.close()
            return

     # si no coincide decir eso y cerrar todo el asqueroso codigo
    print("No match")
    archivo.close()

    #repeticiones consecutivas de str
def repetidas(str, ADN):
    i = 0
    while str*(i+1) in ADN:
        i += 1
    return i

    #coincidencia de la base de datos de str
def match(strs, ADN_str, row):
    for str in strs:
        if ADN_str[str] != int(row[str]):
            return False
    return True


main()

