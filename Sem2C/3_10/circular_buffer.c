//
// Created by Adam Ludwiczak on 28/04/2021.
//

#include "circular_buffer.h"
#include <stdio.h>
#include <stdlib.h>

int circular_buffer_create(struct circular_buffer_t *a, int N)
{
    if(a == NULL || N < 1) return 1;

    a->ptr = malloc(N * sizeof(int));
    if (a->ptr == NULL) return 2;

    a->begin = 0;
    a->end = 0;
    a->capacity = N;
    a->full = 0;

    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N)
{
    if(cb == NULL || N < 1) return 1;

    *cb = malloc(sizeof(struct circular_buffer_t));
    if(cb == NULL) return 2;

    int error = circular_buffer_create(*cb, N);
    if(error == 1 || error == 2)
    {
        free(*cb);
        return 2;
    }

    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a)
{
    if(a == NULL || a->ptr == NULL) return;

    free(a->ptr);
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a)
{
    if(a == NULL) return;

    circular_buffer_destroy(*a);
    free(*a);
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value)
{
    if( cb == NULL || cb->ptr == NULL || cb->begin < 0 || cb->capacity < 1 || cb->begin > cb->capacity || cb->end < 0 || cb->end > cb->capacity) return 1;

    *(cb->ptr + cb->end) = value;

    cb->end ++;
    if (cb->end >= cb->capacity) cb->end = 0;

    if(cb->begin == cb->end)
    {
        cb->full = 1;
    }

    if(cb->full == 1)
    {
        cb->begin = cb->end;
    }

    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code)
{
    if(a == NULL || a->ptr == NULL || a->begin < 0 || a->begin > a->capacity || a->capacity < 1 || a->end < 0 || a->end > a->capacity)
    {
        if(err_code != NULL) *err_code = 1;
        return 1;
    }
    if(circular_buffer_empty(a) == 1)
    {
        if(err_code != NULL) *err_code = 2;
        return 2;
    }
    if(err_code != 0)
    {
        if(err_code != NULL) *err_code = 0;
    }

    int ret = *(a->ptr + a->begin);

    a->begin ++;
    if(a->begin >= a->capacity) a->begin = 0;

    if(a->begin != a->end) a->full = 0;

    if(err_code != NULL) *err_code = 0;

    return ret;
}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code)
{
    if(a == NULL || a->ptr == NULL || a->begin < 0 || a->begin > a->capacity || a->capacity < 1 || a->end < 0 || a->end > a->capacity)
    {
        if(err_code != NULL) *err_code = 1;
        return 1;
    }
    if(circular_buffer_empty(a) == 1)
    {
        if(err_code != NULL) *err_code = 2;
        return 2;
    }
    if(err_code != 0)
    {
        if(err_code != NULL) *err_code = 0;
    }

    a->end--;
    if(a->end < 0) a->end = a->capacity - 1;

    int ret = *(a->ptr + a->end);

    if(a->begin != a->end) a->full = 0;

    if(err_code != NULL) *err_code = 0;

    return ret;
}

int circular_buffer_empty(const struct circular_buffer_t *a)
{
    if(a == NULL || a->ptr == NULL || a->begin < 0 || a->begin > a->capacity || a->capacity < 1 || a->end < 0 || a->end > a->capacity)
        return -1;

    if(a->begin == a->end && a->full == 0) return 1;

    return 0;
}

int circular_buffer_full(const struct circular_buffer_t *a)
{
    if(a == NULL || a->ptr == NULL || a->begin < 0 || a->begin > a->capacity || a->capacity < 1 || a->end < 0 || a->end > a->capacity)
        return -1;

    if(a->end == a->begin && a->full == 1) return 1;

    return 0;
}

void circular_buffer_display(const struct circular_buffer_t *a)
{
    if(a == NULL || a->ptr == NULL || a->begin < 0 || a->begin > a->capacity || a->capacity < 1 || a->end < 0 || a->end > a->capacity)
        return;

    if(a->begin == a->end && a->full == 0) return;

    int x = a->begin;

    do
    {
        printf("%d ", *(a->ptr + x));
        x++;
        if(x == a->capacity) x = 0;
    }while (x != a->end);
}
