#include <cs50.h>
#include <stdio.h>


int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Pregunte cuántos centavos le deben al cliente
    int cents = get_cents();
    

    // Calcular el número de cuartos para dar al cliente
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calcular la cantidad de monedas de diez centavos para darle al cliente
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calcular el número de monedas de cinco centavos para dar al cliente
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calcular la cantidad de centavos para darle al cliente
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sumar monedas
    int coins = quarters + dimes + nickels + pennies;

    // Imprime el número total de monedas para darle al cliente
    printf("%i\n", coins);
}

int get_cents(void)
{
    int centavos = 0;
    do
    {
        centavos = get_int("centavos: ");
    }
    while (centavos < 0);
    return  centavos;
}


int calculate_quarters(int cents)
{
    int a = cents / 25;
    return a;
}

int calculate_dimes(int cents)
{
    int a = cents / 10;
    return a;
}

int calculate_nickels(int cents)
{
    int a = cents / 5;
    return a;
}

int calculate_pennies(int cents)
{
    int a = cents / 1;
    return a;
}
