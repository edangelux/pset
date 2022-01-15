#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}
// verificacion si existe negativo osea no existe ese nombre
// leer documentacion docs para entender
int get_transparente(string name)
{
    for (int i = 0; i < candidate_count; i++)
        if (strcmp (candidates[i].name, name) == 0)
            return i;
    return -1;
}
// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    int transparente = get_transparente(name);

    // validaciones actualizar matriz
    if (transparente != -1)
    {
        preferences[voter][rank] = transparente;
        return true;
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //iterar sobre la matriz preferences y actualizar los 
    // vtos de candidatos no eliminados 
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_transparente = preferences[i][j];
            if (!candidates[candidate_transparente].eliminated)
            { //una vez que actualizamos los votos
              // iremos de acuerdo de el rango de votacion 
              // iterando en todos los rangos para ver cual esta eliminado
                candidates[candidate_transparente].votes++;
                break; 
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for(int i = 0; i < candidate_count; i++)
    {   //si un candidato tiene mas de de la mitad de votos
        // en teoria gano
        if(candidates[i].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
   //encontrar el minimo
    int minimo = 0;
    //encontrar el primer candidato
    bool primero = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        { 
            if (!primero)
            { //si no hemos encontrado el primer candidato actualizar el minimo
                minimo = candidates[i].votes;
                primero = true;
            }
            //si no ha sido eliminado
          //calcular el voto de los candidatos es menor al minimo
            else if (candidates[i].votes < minimo)
            {
                //actualizar el minimo
                minimo = candidates[i].votes;
            }
        }
    }
    return minimo;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
            if (candidates[i].votes != min)
                return false;
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if(!candidates[i].eliminated)
        {
            if (candidates[i].votes == min)
                candidates[i].eliminated = true;
        }
    }
    return;
}