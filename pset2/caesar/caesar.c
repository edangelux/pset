
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

// aca determino las letra con lenguaje ascci
#define letras_mayusculas 65
#define letras_minusculas 97
#define conteo_letras 26


int main(int argc, string args[])
{
    if (argc != 2)
        //aca si el usuario solo pone ./caesar le saltara que ponga ese comando junto con numero
    {
        printf("Use: ./caesar n");
        return 1;
    }
    string x = args[1];
    int q = strlen(x);

    for( int i = 0; i < q; i++ )
    {

         if (!isdigit(x[i]))
        {

           printf("solo numeros puto!!");

           return 1;

        }
    }
    int n = atoi(args[1]) % conteo_letras;
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (!isalpha(plaintext[i]))
        {
            printf("%c", plaintext[i]);
            continue;
        }

// aca ocupo operador ? es un operador logico que es que funciona
// como verdadero y falso
        int ascii = isupper(plaintext[i]) ? letras_mayusculas : letras_minusculas;

        int pi = plaintext[i] - ascii;
        int ci = (pi + n) % conteo_letras;

        printf("%c", ci + ascii);
    }

    printf("\n");
    return 0;
}
