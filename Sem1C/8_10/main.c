#include <stdio.h>

int longest_series(unsigned int x);

int main()
{
    unsigned int num;
    printf("Podaj liczbe: ");
    if (scanf("%u", &num) != 1)
    {
        printf("Incorrect input\n");
        return 1;
    }

    printf("Wynik: %d", longest_series(num));
    return 0;
}

int longest_series(unsigned int x)
{
    int howMany = 0;

    while (x != 0)
    {
        x = (x & (x << 1));
        howMany++;
    }

    return howMany;
}