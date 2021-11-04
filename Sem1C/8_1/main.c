#include <stdio.h>

int is_equal(int a, int b);
int is_negative(int value);

int main()
{
    int a;
    int b;
    printf("Podaj liczby: ");
    if(scanf("%d %d", &a, &b) ^ 2)
    {
        printf("Incorrect input\n");
        return 1;
    }
    //printf("a: %d b: %d", a, b);

    if (is_equal(a, b) ^ 0)
        printf("rowne\n");
    else
        printf("nierowne\n");

    if(is_negative(a) & 1)
        printf("ujemna ");
    else
        printf("nieujemna ");

    if(is_negative(b) & 1)
        printf("ujemna ");
    else
        printf("nieujemna ");



    return 0;
}

int is_equal(int a, int b)
{
    if(a ^ b)
        return 0;
    else
        return 1;
}
int is_negative(int value)
{
    if (!(value ^ 0))
        return 0;
    else if ((!( value & (1 << (31)) | (!value))) ^ 0)
        return 0;
    else
        return 1;
}
