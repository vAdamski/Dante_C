#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main()
{
    int height, width, error;
    struct matrix_t matrix;

    printf("Podaj szerokość i wysokość: ");
    if (scanf("%d %d", &width, &height) != 2)
    {
        printf("Incorrect input\n");
        return INCORECT_INPUT;
    }

    if (height < 1 || width < 1)
    {
        printf("Incorrect input data\n");
        return INCORECT_INPUT_DATA;
    }

    error = matrix_create(&matrix, width, height);
    switch (error)
    {
        case 1:
            printf("Incorrect input data\n");
            return INCORECT_INPUT_DATA;
        case 2:
            printf("Failed to allocate memory\n");
            return FAILED_TO_ALLOCATE_MEMORY;
        default:
            break;
    }

    printf("Podaj wartości: ");
    error = matrix_read(&matrix);
    switch (error)
    {
        case 1:
            matrix_destroy(&matrix);
            printf("Incorrect input data\n");
            return INCORECT_INPUT_DATA;
        case 2:
            matrix_destroy(&matrix);
            printf("Incorrect input\n");
            return INCORECT_INPUT;
        default:
            break;
    }

    matrix_display(&matrix);
    matrix_destroy(&matrix);
    return 0;
}
