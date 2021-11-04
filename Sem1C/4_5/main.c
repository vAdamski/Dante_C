#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_utils.h"

int main()
{
    int height, width, error;
    char *filename;
    printf("Podaj szerokość i wysokość: ");
    if (scanf("%d %d", &width, &height) != 2)
    {
        printf("Incorrect input\n");
        return INCORECT_INPUT;
    }

    if (width < 1 || height < 1)
    {
        printf("Incorrect input data\n");
        return INCORECT_INPUT_DATA;
    }

    struct matrix_t *matrix = matrix_create_struct(width, height);
    if (matrix == NULL)
    {
        printf("Failed to allocate memory\n");
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    printf("Podaj liczby: ");
    error = matrix_read(matrix);
    if (error == 1 || error == 2)
    {
        matrix_destroy_struct(&matrix);
        printf("Incorrect input\n");
        return INCORECT_INPUT;
    }

    filename = malloc(40 * sizeof(char));
    if (filename == NULL)
    {
        matrix_destroy_struct(&matrix);
        printf("Failed to allocate memory\n");
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    printf("Podaj sciezke do pliku: ");
    scanf("%39s", filename);

    struct matrix_t *matrixTranspose = matrix_transpose(matrix);
    if (matrixTranspose == NULL)
    {
        matrix_destroy_struct(&matrix);
        free(filename);
        printf("Failed to allocate memory\n");
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    char *extension = filename + strlen(filename) - 4;

    if (strcmp(extension, ".txt") == 0)
    {
        error = matrix_save_t(matrixTranspose, filename);
    }
    else if (strcmp(extension, ".bin") == 0)
    {
        error = matrix_save_b(matrixTranspose, filename);
    }
    else
    {
        matrix_destroy_struct(&matrix);
        matrix_destroy_struct(&matrixTranspose);
        free(filename);
        printf("Unsupported file format\n");
        return UNSUPPORTED_FILE_TYPE;
    }

    //Check load error
    switch (error)
    {
        case 0:
            printf("File saved\n");
            break;
        case 2:
            matrix_destroy_struct(&matrix);
            matrix_destroy_struct(&matrixTranspose);
            free(filename);
            printf("Couldn't create file\n");
            return COULDNT_CREATE_FILE;
        default:
            break;
    }

    matrix_destroy_struct(&matrix);
    matrix_destroy_struct(&matrixTranspose);
    free(filename);
    return 0;
}
