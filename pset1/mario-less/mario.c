#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int altura = 0;
    do
    {
        altura = get_int("altura: ");
    }
    while (altura <= 0 || altura > 8);

    for (int i = 1; i <= altura; i++)
    {
        for (int spaces = 0; spaces < altura - i; spaces++)
        {
            printf(" ");
        }
        for (int hash = 0; hash < i; hash++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}