#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max numero de candidatos
#define MAX 9

// Los candidatos tienen nombre y conteo de votos
typedef struct
{
    string name;
    int votes;
}
candidate;

// Matriz de candidatos
candidate candidates[MAX];

// Numero de candidatos
int candidate_count;

// Prototipos de funciones
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
// Comprobar si hay un uso inválido
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

// Rellenar variedad de candidatos
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

// Bucle sobre todos los votantes
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Checkeo voto invalido
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // mostrar ganador
    print_winner();
}

// Actualizar los totales de votos dado un nuevo voto
bool vote(string name)
{   //damos una validacion for 
    for (int i = 0; i < candidate_count; i++)
    { //comparamos los dos string de candidatos y cada vez que haya un voto se sumara la variable
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Imprimir el ganador (o ganadores) de la elección
void print_winner(void)
{
    int votos_total = 0;
    //mayor numero sobre votos
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > votos_total)
        {
            votos_total = candidates[i].votes;
        }
    }

    // votaciones puras y transparentes daniel forever
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == votos_total)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}