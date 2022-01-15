#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int grado(int letras, int palabras, int oraciones);

int main(void)
{
    string text = get_string("Text: ");
    int letra = count_letters(text);
    int palabra = count_words(text);
    int oracion = count_sentences(text);

    int Grado = grado(letra, palabra, oracion);
    //dar validacion de grado
    if (Grado >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (Grado < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", Grado);
    }
}

//contador de las letras
int count_letters(string text)
{
    int cuenta = 0;
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(text[i]))
        {
            continue;
        }
        else
        {
            cuenta++;
        }
    }
    return cuenta;
}
// contador de espacios, determinas el conteo de palabras
int count_words(string text)
{
    int conteo = 0;
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        if (isspace(text[i]))
        {
            conteo++;
        }
        else
        {
            continue;
        }
    }
    conteo += 1;
    return conteo;
}
//calculando las oraciones determinadas por los signos
int count_sentences(string text)
{
    int contador = 0;
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            contador++;
        }
    }
    return contador;
}
// formula del problem set
int grado(int letras, int palabras, int oraciones)
{
    float L = (letras / (float)palabras) * 100;
    float S = (oraciones / (float)palabras) * 100;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    int grado = round(index);
    return grado;
}