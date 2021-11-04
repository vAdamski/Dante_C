#include <stdio.h>
#include "int_operations.h"

int main()
{
    int a, b, option, res;
    printf("Enter numbers: ");
    if(scanf("%d %d", &a,&b) != 2)
    {
        printf("Incorrect input\n");
        return 1;
    }
    printf("Choose an operation: ");
    if(scanf("%d", &option) != 1)
    {
        printf("Incorrect input\n");
        return 1;
    }
    switch (option)
    {
        case 0:
            res = calculate(a,b,add_int);
            break;
        case 1:
            res = calculate(a,b,sub_int);
            break;
        case 2:
            res = calculate(a,b,div_int);
            break;
        case 3:
            res = calculate(a,b,mul_int);
            break;
        default:
            printf("Incorrect input data\n");
            return 2;
    }
    printf("Result: %d", res);
    return 0;
}