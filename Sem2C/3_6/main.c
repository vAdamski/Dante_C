#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int main()
{
    int size;
    int num;
    struct array_t array;

    printf("Podaj wielkosc tablicy: ");
    if(scanf("%d", &size) != 1)
    {
        printf("Incorrect input\n");
        return 1;
    }

    if(size < 1)
    {
        printf("Incorrect input data\n");
        return 2;
    }


    int error = array_create(&array, size);

    if (error == 2)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj liczby do tablicy: ");
    do {
        if(scanf("%d", &num) != 1)
        {
            printf("Incorrect input\n");
            array_destroy(&array);
            return 1;
        }

        if(num == 0) break;

        array_push_back(&array, num);
        if(array.size == array.capacity)
        {
            printf("Buffer is full\n");
            break;
        }
    }while(1);

    if(array.size == 0)
    {
        printf("Buffer is empty\n");
        array_destroy(&array);
        return 0;
    }

    array_display(&array);
    array_destroy(&array);
    return 0;
}

