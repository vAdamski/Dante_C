#include <stdio.h>

unsigned long long add(unsigned long long a, unsigned long long b);

int main()
{
    unsigned long long a,b;
    printf("Podaj dwie liczby: ");
    if(scanf("%llu %llu", &a, &b) != 2)
    {
        printf("Incorrect input\n");
        return 1;
    }

    printf("%llu", add(a, b));
    return 0;
}

unsigned long long add(unsigned long long a, unsigned long long b)
{
    if (b == 0)
        return a;
    else
        return add(a ^ b, (a & b) << 1);
}
