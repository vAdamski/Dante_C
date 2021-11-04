//
// Created by Adam Ludwiczak on 26/04/2021.
//
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

    if(a->size == a->capacity) return 2;

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