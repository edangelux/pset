#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int a = 0;
    do
    {
        a = get_int("altura: ");
    }
    while (a <= 0 || a > 8);

    for(int i = 1; i <= a; i++)
    {
        for (int e = 0; e < a - i; e++)
        {
            printf(" ");
        }
        for (int c = 0; c < i; c++)
        {
            printf("#");
        }
        printf("  ");
        for (int b = 0; b < i; b++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}