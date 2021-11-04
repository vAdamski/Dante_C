//
// Created by Adam Ludwiczak on 27/05/2021.
//

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int matrix_create(struct matrix_t *m, int width, int height)
{
    if (m == NULL || height < 1 || width < 1)
        return 1;

    m->width = width;
    m->height = height;

    m->ptr = malloc(height * sizeof(int*));
    if (m->ptr == NULL)
    {
        return 2;
    }

    for (int i = 0; i < height; ++i)
    {
        *(m->ptr + i) = malloc(width * sizeof(int));
        if (*(m->ptr + i) == NULL)
        {
            for (int j = 0; j < i; ++j)
            {
                free(*(m->ptr + j));
            }
            free(m->ptr);
            return 2;
        }
    }

    return SUCCES;
}

int matrix_read(struct matrix_t *m)
{
    if (m == NULL || m->ptr == NULL || m->height < 1 || m->width < 1)
        return 1;

    int _width = m->width;
    int _height = m->height;

    for (int i = 0; i < _height; ++i)
    {
        for (int j = 0; j < _width; ++j)
        {
            int num;
            if(scanf("%d", &num) != 1)
            {
                return 2;
            }
            *(*(m->ptr + i) + j) = num;
        }
    }

    return SUCCES;
}
void matrix_display(const struct matrix_t *m)
{
    if (m == NULL || m->ptr == NULL || m->height < 1 || m->width < 1)
        return;

    int _width = m->width;
    int _height = m->height;

    for (int i = 0; i < _height; ++i)
    {
        for (int j = 0; j < _width; ++j)
        {
            printf("%d ", *(*(m->ptr + i) + j));
        }
        printf("\n");
    }
}
void matrix_destroy(struct matrix_t *m)
{
    if (m == NULL ||m->height < 1 || m->width < 1)
        return;

    for (int i = 0; i < m->height; i++)
    {
        free(*(m->ptr + i));
    }
    free(m->ptr);
}