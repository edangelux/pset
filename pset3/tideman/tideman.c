#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}
// validaciones para iterar sobre el candidato retorna a boll vote
int get_transparente(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if(strcmp(candidates[i], name)== 0)
            return i;
    }
    return -1;
}
// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int candidate_transparente = get_transparente(name);
    if (candidate_transparente != -1)
    {   //el rangos de rango es igual a transparente
        ranks[rank] = candidate_transparente;
        return true;
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{   
    for(int i = 0; i < candidate_count; i++)
    {   //actualizar la matriz preference
        for(int j = i + 1; j < candidate_count; j++)
            preferences[ranks[i]][ranks[j]]++;
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        { //cuandos votantes prefieren el i candidato sobre
          //el j candidato y lo comparamos con el numero de votantes
          //
            if (preferences[i][j] > preferences[j][i])
            {   //definimos correctamente los pares
                pair total;
                total.winner = i;
                total.loser = j;
                pairs[pair_count++] = total;

            }
        }
    }
}
//realizar ordenamiento decreciente pero primero comparando 2 objetos
int comparar(const void * objeto1, const void * objeto2)
{
    pair p = *((pair*) objeto1);
    pair s = *((pair*) objeto2);
    //comparar cuantas personas apoyan usamos la idea de [i][j]
    //en este caso haremos encontrar el ganador de cuantas gente apoya el ganador sobre el
    //perdedor y luego restamos, cuantas personas apoyan al perdedor? encontrar margen de victoria
    int primero = preferences[p.winner][p.loser] - preferences[p.loser][p.winner];
    int segundo = preferences[s.winner][s.loser] - preferences[s.loser][s.winner];
    //ordenadr de forma descendente devolviendo el segundo margen menos el primer margen
    return segundo - primero;
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    qsort(pairs, pair_count, sizeof(pair), comparar);
}

bool ciclo_ayuda(int comenzar, bool grafica[])
{   //validaciones para salir del ciclo 
    if (grafica[comenzar])
        return true;
    grafica[comenzar] = true;
    for (int i = 0; i < candidate_count; i++)
    { //iterar y ver todos los vecinos de la grafica
    //si llegamos aca es por que hay un ciclo completo y ahora
        if (locked[comenzar][i] && ciclo_ayuda(i, grafica))
            return true;
    }
    return false;
}

bool ciclo(int comienzo)
{   //visitar cada candidato si se repite sabre que estoy en ciclo
    bool grafica[candidate_count];
    for (int i = 0; i < candidate_count; i++)
        grafica[i] = false;
    return ciclo_ayuda(comienzo, grafica);
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i = 0; i < pair_count; i++)
    {   //margen mas alto de victoria
        locked[pairs[i].winner][pairs[i].loser] = true;
        //comprobar ciclo
        if(ciclo(pairs[i].winner))
            locked[pairs[i].winner][pairs[i].loser] = false;
    }
}
bool esraiz (int inicio)
{// la raiz como tal del grafico
    for(int i = 0; i < candidate_count; i++)
        if (locked[i][inicio])
            return false;
    return true;
}
int raiz()
{//encontrar ka raiz del grafico
    for (int i = 0; i < candidate_count; i++)
        if(esraiz(i))
            return i;
    return -1;
}
// Print the winner of the election
void print_winner(void)
{
    //definir el HP GANADOR DESPUES DE TANTA MIERDA VIVA DANIEL
    int inicio = raiz();
    if (inicio != -1)
        printf("%s\n", candidates[inicio]);
}