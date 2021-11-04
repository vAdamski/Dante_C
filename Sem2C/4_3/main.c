#include <stdio.h>
#include <stdlib.h>

int create_array_2d_2(int ***ptr, int width, int height);
void destroy_array_2d(int ***ptr, int height);
void display_array_2d(int **ptr, int width, int height);
int sum_array_2d(int **ptr, int width, int height);
int sum_row(int *ptr, int width);

int main()
{
    int **tab = NULL;
    int width, height, error;
    printf("Podaj szerokość i wysokość: ");
    if(scanf("%d %d", &width, &height) != 2)
    {
        printf("Incorrect input\n");
        return 1;
    }
    if(height < 1 || width < 1)
    {
        printf("Incorrect input data\n");
        return 2;
    }

    error = create_array_2d_2(&tab, width, height);
    if(error == 2)
    {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj liczby: ");
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if(scanf("%d", *(tab + i) + j) != 1)
            {
                destroy_array_2d(&tab, height);
                printf("Incorrect input\n");
                return 1;
            }
        }
    }

    display_array_2d(tab, width, height);

    for (int i = 0; i < height; ++i)
    {
        printf("%d\n", sum_row(*(tab + i), width));
    }

    printf("%d\n", sum_array_2d(tab, width, height));

    destroy_array_2d(&tab,height);
    return 0;
}

int create_array_2d_2(int ***ptr, int width, int height)
{
    if(height < 1 || width < 1 || ptr == NULL) return 1;

    *ptr = malloc(height * sizeof(int*));
    if(*ptr == NULL)
    {
        return 2;
    }

    for (int i = 0; i < height; ++i)
    {
        *(*ptr + i) = malloc(width * sizeof(int));
        if(*(*ptr+i) == NULL)
        {
            for (int j = 0; j < i ; ++j)
            {
                free(*(*ptr + j));
            }
            free(*ptr);
            *ptr=NULL;
            return 2;
        }
    }

    return 0;
}

void destroy_array_2d(int ***ptr, int height)
{
    if(ptr == NULL || height < 1) return;

    for (int i = 0; i < height; ++i) {
        free(*(*ptr+i));
    }
    free(*ptr);
    *ptr = NULL;
}

void display_array_2d(int **ptr, int width, int height)
{
    if(ptr == NULL || height < 1 || width < 1) return;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            printf("%3d ", *(*(ptr + i) + j));
        }
        printf("\n");
    }
}

int sum_array_2d(int **ptr, int width, int height)
{
    if(ptr == NULL || height < 1 || width < 1) return -1;

    int sum = 0;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            sum += *(*(ptr + i) + j);
        }
    }

    return sum;
}

int sum_row(int *ptr, int width)
{
    if(ptr == NULL || width < 1) return -1;

    int sum = 0;
    for (int i = 0; i < width; ++i)
    {
        sum += *(ptr + i);
    }

    return sum;
}