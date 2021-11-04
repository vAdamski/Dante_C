#include <stdio.h>
#include <stdlib.h>

int **create_array_2d(int width, int height);
void display_array_2d(int **ptr, int width, int height);
void destroy_array_2d(int **ptr, int height);

int main()
{
    int width, height;
    int **tab = NULL;
    printf("Podaj szerokość i wysokość: ");
    if(scanf("%d %d", &width, &height) != 2)
    {
        printf("Incorrect input\n");
        return 1;
    }
    if(width < 1 || height < 1)
    {
        printf("Incorrect input data\n");
        return 2;
    }

    tab = create_array_2d(width, height);

    if(tab == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj tablice: ");
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if(scanf("%d", *(tab+i)+j) != 1)
            {
                printf("Incorrect input\n");
                destroy_array_2d(tab, height);
                return 1;
            }
        }
    }

    display_array_2d(tab, width, height);
    destroy_array_2d(tab, height);

    return 0;
}

int **create_array_2d(int width, int height)
{
    if(height < 1 || width < 1) return NULL;

    int **tab = malloc(height * sizeof(int*));
    if(tab == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < height; ++i)
    {
        *(tab + i) = malloc(width * sizeof(int));
        if(*(tab+i) == NULL)
        {
            for (int j = 0; j < i ; ++j)
            {
                free(*(tab + j));
            }
            free(tab);
            return NULL;
        }
    }

    return tab;
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
void destroy_array_2d(int **ptr, int height)
{
    if(ptr == NULL || height < 1) return;

    for (int i = 0; i < height; ++i) {
        free(*(ptr+i));
    }
    free(ptr);
}
