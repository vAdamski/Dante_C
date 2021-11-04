#include "array.h"
#include <stdio.h>
#include <stdlib.h>

int array_create(struct array_t *a, int N)
{
    if(a == NULL || N < 1) return 1;

    a->ptr = malloc(N * sizeof(int));
    a->size = 0;
    a->capacity = N;

    if(a->ptr == NULL) return 2;

    return 0;
}

int array_push_back(struct array_t *a, int value)
{
    if(a == NULL || a->size < 0 || a->capacity < 1 || a->size > a->capacity) return 1;

    void *b;

    if(a->size == a->capacity)
    {
        b = realloc(a->ptr, a->capacity * 2 * sizeof(int));

        if(b == NULL) return 2;

        a->ptr = b;

        a->capacity *= 2;
    }

    *(a->ptr + a->size) = value;
    a->size += 1;

    return 0;
}

void array_display(const struct array_t *a)
{
    if(a == NULL || a->size > a->capacity || a->size < 1 || a->ptr == NULL) return;

    for (int i = 0; i < a->size; ++i)
    {
        printf("%d ", *(a->ptr + i));
    }
}

void array_destroy(struct array_t *a)
{
    if(a == NULL || a->ptr == NULL) return;

    free(a->ptr);
}

int array_create_struct(struct array_t **a, int N)
{
    if(a == NULL || N < 1) return 1;

    *a = malloc(sizeof(struct array_t));

    if(*a ==  NULL) return 2;

    int error = array_create(*a, N);

    if (error == 1 || error == 2)
    {
        free(*a);
        return 2;
    }

    return 0;
}

void array_destroy_struct(struct array_t **a)
{
    if(a == NULL) return;

    array_destroy(*a);
    free(*a);
}

int array_remove_item(struct array_t *a, int value)
{
    if(a == NULL || a->size < 0 || a->capacity < 1 || a->size > a->capacity || a->ptr == NULL) return -1;
    int x = 0;
    int deleteItems = 0;

    while(x < a->size)
    {
        if(*(a->ptr + x) == value)
        {
            deleteItems++;
            for (int i = x; i < a->size - 1; ++i)
            {
                *(a->ptr + i) = *(a->ptr + i + 1);
            }
            a->size = a->size - 1;
            x--;
        }
        x++;
    }

    if(((float)a->size / (float)a->capacity) < 0.25 && a->capacity >= 2)
    {
        void *b = realloc(a->ptr, a->capacity / 2 * sizeof(int));

        if(b == NULL) return -1;

        a->ptr = b;

        a->capacity /= 2;
    }

    return deleteItems;
}