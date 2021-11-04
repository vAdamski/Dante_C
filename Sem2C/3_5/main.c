#include <stdio.h>
#include <stdlib.h>

int* create_array_int(int N);
int* copy_array_int(const int* ptr, int N);
void display_array_int(const int* ptr, int N);

int main()
{
    int *tab = NULL;
    int size;
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

    tab = create_array_int(size);

    if(tab == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    int x = 0;
    printf("Podaj liczby: ");
    while(x < size)
    {
        int error = scanf("%d", tab + x);
        if(error != 1)
        {
            printf("Incorrect input\n");
            free(tab);
            return 1;
        }
        x++;
    }

    int *newTab = copy_array_int(tab, size);

    if(newTab == NULL)
    {
        printf("Failed to allocate memory\n");
        free(tab);
        return 8;
    }

    display_array_int(tab, size);
    display_array_int(newTab, size);

    free(tab);
    free(newTab);

    return 0;
}

int* create_array_int(int N)
{
    if(N < 1) return NULL;

    int *tab = malloc(N * sizeof(int));

    if(tab == NULL) return NULL;

    return tab;
}
int* copy_array_int(const int* ptr, int N)
{
    if(ptr == NULL || N < 1) return NULL;

    int *newTab = malloc(N * sizeof(int));

    if(newTab == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < N; ++i)
    {
        *(newTab + i) = *(ptr + i);
    }

    return newTab;
}
void display_array_int(const int* ptr, int N)
{
    if(ptr == NULL || N < 1) return;

    for (int i = 0; i < N; ++i)
    {
        printf("%d ", *(ptr+i));
    }
    printf("\n");
}