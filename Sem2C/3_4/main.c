#include <stdio.h>
#include <stdlib.h>

int create_array_int(int **ptr, int N);
void destroy_array_int(int **ptr);

int main()
{
    int size = 0, error;
    int *tab = NULL;
    printf("Podaj rozmiar tablicy: ");
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

    error = create_array_int(&tab, size);

    if(error == 2)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    int x = 0;
    printf("Podaj liczby: ");
    while(x < size)
    {
        error = scanf("%d", tab + x);
        if(error != 1)
        {
            printf("Incorrect input\n");
            destroy_array_int(&tab);
            return 1;
        }
        x++;
    }

    for (int i = 0; i < x; ++i)
    {
        printf("%d ", *(tab + x - i - 1));
    }

    destroy_array_int(&tab);

    return 0;
}

int create_array_int(int **ptr, int N)
{
    if(ptr == NULL || N < 1)
    {
        return 1;
    }

    *ptr = malloc(N * sizeof(int));

    if (*ptr == NULL)
    {
        return 2;
    }

    return 0;
}
void destroy_array_int(int **ptr)
{
    if(ptr == NULL) return;

    free(*ptr);
    *ptr = NULL;
}