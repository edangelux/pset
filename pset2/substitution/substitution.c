#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>
//#include <stdlib.h>
bool mayor(string key);
bool duplicado(string key);

int main(int argc, string argv[])
{
    if(argc != 2 || !mayor(argv[1]))
    {   //validaciones de la entrada del usuario
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else if (strlen(argv[1]) < 26)
    { //validacion de que la key tiene que ser de 26 caracteres
        printf("la key debe tener 26 caracteres\n");
        return 1;
    }
    else if (duplicado(argv[1]))
    { //validar que no haya letra repeditda en la key
        printf("la key no tiene que tener letras duplicadas\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        printf("%s \n", key);
        //entrada del texto del usuario
        string plaintext = get_string("Plaintext: ");
        printf("ciphertext: ");
        for (int i = 0, len = strlen(plaintext); i < len; i++)
        {
            if (isalpha(plaintext[i]))
            { //hacer y notar las letras de mayusculas y minusculas
                if (isupper(plaintext[i]))
                {
                    char letra = key[ ((plaintext)[i] - 65) % 26];
                    if(islower(letra))
                    {
                        printf("%c", letra - 32);
                    }
                    else
                    {
                        printf("%c", letra);
                    }
                }
                else
                {
                    char letra = key[((plaintext[i] - 97) % 26)];
                    if (isupper(letra))
                    {
                        printf("%c", (int)letra + 32);
                    }else
                    {
                        printf("%c", letra);
                    }
                }
            }
            else
            {
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");
        return 0;
    }
}

bool mayor(string key) //validaciones de bool mayor
{
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
    }
    return true;
}
bool duplicado(string key) // validaciones de bool duplicado
{
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        for (int a = 0; a < len; a++)
        {
            if (key[i] == key[a] && i != a)
            {
                return true;
            }
        }
    }
    return false;
}