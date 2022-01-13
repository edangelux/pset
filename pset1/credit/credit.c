#include <stdio.h>
#include <math.h>
#include <cs50.h>
//verificar que tipo de tarjeta de credito es
int main(void)
{
//long long para poner cifras grandes y aca tambien se comiezan a almacenar
    long long cc_number = get_long_long(" numero: ");
    int digit1 = 0, digit2 = 0, num_digits = 0, sum_double_odds = 0, sum_events  = 0;
//aqui para comprobar que ningun error entre
    while (cc_number > 0)
    {
        digit2 = digit1;
        digit1 = cc_number % 10;

        if (num_digits % 2 == 0)
        {
            sum_events += digit1;
        }
        else
        {
            int multiple = 2 * digit1;
            sum_double_odds += (multiple / 10) + (multiple % 10);
        }

        cc_number /= 10;
        num_digits++;
    }
//aca hacemos una variable logica con bool
    bool is_valid = (sum_events + sum_double_odds) % 10 == 0;
    int first_two_digits = (digit1 * 10) + digit2;

//aca comenzamos a usar las matematicas para descubrir que tarjeta es del numero que ingreso
    if (digit1 == 4 && num_digits >= 13 && num_digits <= 16 && is_valid)
    {
        printf("VISA\n");
    }

    else if (first_two_digits >= 51 && first_two_digits <= 55 && num_digits == 16 && is_valid)
    {
        printf(" MASTERCARD\n");
    }

    else if ((first_two_digits == 34 || first_two_digits == 37) && num_digits == 15 && is_valid)
    {
        printf("AMEX\n");
    }
    else
    {
        printf(" INVALID\n");
    }

    return 0;
}
