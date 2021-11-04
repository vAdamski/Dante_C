#include <stdio.h>
#include <stdlib.h>

int main()
{
    float *pi = NULL;
    pi = (float*)malloc(sizeof(float));
    if(pi == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }
    *(pi) = (float)3.141593;

    printf("%f %p", *pi, (void*)&pi);

    free(pi);

    return 0;
}
