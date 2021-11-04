#include <stdio.h>
#include "int_operations.h"

int main()
{
    int a;
    int b;
    int operation;

    printf("Enter numbers: ");
    if(scanf("%d %d", &a, &b) != 2)
    {
        printf("Incorrect input\n");
        return 1;
    }

    printf("Enter operation: ");
    if(scanf("%d", &operation) != 1)
    {
        printf("Incorrect input\n");
        return 1;
    }

    if (operation < 0 || operation > 3)
    {
        printf("Incorrect input data\n");
        return 2;
    }

    int res = get_function(operation)(a, b);

    printf("%d\n", res);


    return 0;
}
