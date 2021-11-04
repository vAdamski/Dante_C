#include <stdio.h>
#include <stdlib.h>
int main()
{
    int *tabInt =  NULL;
    tabInt = (int*)malloc(100 * sizeof(int));
    if(tabInt == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    for (int i = 0; i < 100; ++i)
    {
        *(tabInt + i) = i;
    }
    for (int i = 0; i < 100; ++i)
    {
        printf("%d ", *tabInt+i);
    }

    free(tabInt);

    return 0;
}
