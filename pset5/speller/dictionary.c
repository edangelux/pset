
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// tamaño de la tabla hash = 2 ^ 16
const int HASHTABLE_SIZE = 26;

// definir el nodo de la lista vinculada
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// inicializar tabla hash
node *hash_table[HASHTABLE_SIZE];


int hash(const char *needs_hashing)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(needs_hashing); i < n; i++)
    {
        hash = (hash << 2) ^ needs_hashing[i];
    }

    return hash % HASHTABLE_SIZE;
}

// Devuelve verdadero si la palabra está en el diccionario; de lo contrario, es falso.
bool check(const char *word)
{

    // inicializar palabra en minúscula
    char lcword[LENGTH + 1];
    int tamaño = strlen(word);
    // convertir a minúsculas, ya que lo necesitamos para buscar
    for (int i = 0; i < tamaño; i++)
    {
        lcword[i] = tolower(word[i]);
    }

    lcword[tamaño] = '\0';

    // coloque el cursor al comienzo de la lista alineada apropiada
    node *cursor = hash_table[hash(lcword)];


    // lista transversal
    while (cursor != NULL)
    {
        // verifique la palabra del nodo para ver si es la palabra de destino, ignorando el caso
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}


// Carga el diccionario en la memoria. Devuelve verdadero si tiene éxito, de lo contrario es falso.

bool load(const char *dictionary)
{
    // inicializar palabra
    char word[LENGTH + 1];

    // diccionario abierto
    FILE *dicptr = fopen(dictionary, "r");

    // iterar a través de las palabras del diccionario
    while (fscanf(dicptr, "%s", word) != EOF)
    {
        // hacer una nueva palabra.
        node *new_node = malloc(sizeof(node));

        // compruebe si hay errores en la asignación de memoria
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        else
        {
            // copiar palabra en el nodo
            strcpy(new_node->word, word);

            // use la función hash para determinar en qué depósito (lista vinculada) insertar la palabra
            int n = hash(new_node->word);

            // insertar en la lista
            new_node->next = hash_table[n];
            hash_table[n] = new_node;
        }
    }
    // cerrar dictionario
    fclose(dicptr);

    return true;
}


// Devuelve el número de palabras en el diccionario si se cargó o 0 si aún no se cargó.

unsigned int size(void)
{
    // contador de tamaño de diccionario
    int counter = 0;

    // iterar a través de la tabla hash
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // establecer el puntero al encabezado de la lista
        node *cursor = hash_table[i];

        // traverse list
        while (cursor != NULL)
        {
            counter++;
            cursor = cursor->next;
        }
    }
    return counter;
}

//  Descarga el diccionario de la memoria. Devuelve cverdadero si tiene éxito, de lo contrario es falso.

bool unload(void)
{
    // iterar a través de la tabla hash
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // establecer el puntero al encabezado de la lista
        node *cursor = hash_table[i];

        // lista transversal
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

    }
    return true;
}