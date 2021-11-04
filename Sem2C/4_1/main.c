#include <stdio.h>
#include <stdlib.h>

int main() {
    int **tab = NULL;
    tab = malloc(10 * sizeof(int*));

    if(tab == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    //Init tab
    for (int i = 0; i < 10; ++i)
    {
        *(tab + i) = malloc(10 * sizeof(int));
        if(*(tab + i) == NULL)
        {
            printf("Failed to allocate memory\n");
            for (int j = 0; j < i; ++j)
            {
                free(*(tab+j));
            }
            free(tab);
            return 8;
        }
    }

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            *(*(tab + i) + j) = (i+1) * (j+1);
        }
    }

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            printf("%3d ", *(*(tab + i) + j));
        }
        printf("\n");
    }

    for (int i = 0; i < 10; ++i) {
        free(*(tab+i));
    }
    free(tab);
    return 0;
}
