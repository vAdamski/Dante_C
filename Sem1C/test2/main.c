#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int calculate(int a, int b, int(*function)(int, int))
{
    return function(a, b);
}

int main()
{
    int res = calculate(5,5,add);
    printf("%d", res);
    return 0;
}
