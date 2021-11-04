#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


int main()
{
    int size;
    printf("Podaj wielkosc tablicy: ");
    if(scanf("%d", &size) != 1)
    {
        printf("Incorrect input\n");
        return 1;
    }
    if (size < 1)
    {
        printf("Incorrect input data\n");
        return 2;
    }

    void (**tab)(void) = easter(size, print_chicken, print_egg, print_rabbit);
    if(tab == NULL)
    {
        printf("Failed to allocate memory\n");
        free(tab);
        return 8;
    }

    for (int i = 0; i < size; ++i)
    {
        (*(tab + i))();
    }

    free(tab);
    return 0;
}
