#include <stdio.h>
#include <stdlib.h>

float* create_array(int N)
{
    float *tabFloat = NULL;
    if(N < 1)
    {
        return NULL;
    }
    tabFloat = malloc(N * sizeof(float));
    if(tabFloat ==  NULL)
    {
        return NULL;
    }

    return tabFloat;
}

int main()
{
    int size;
    float *tabFloat = NULL;
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

    tabFloat = create_array(size);

    if(tabFloat == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    int x = 0;
    printf("Podaj liczby: ");
    while(x < size)
    {
        int error = scanf("%f", tabFloat + x);
        if(error != 1)
        {
            printf("incorrect input\n");
            free(tabFloat);
            return 1;
        }

        x++;
    }

    for (int i = 0; i < x; ++i)
    {
        printf("%f ", *(tabFloat + x - i - 1));
    }

    free(tabFloat);

    return 0;
}
