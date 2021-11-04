//
// Created by Adam Ludwiczak on 28/05/2021.
//

#include "matrix_utils.h"
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
    if (m == NULL || m->ptr == NULL || m->height < 1 || m->width < 1) return;

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
    if (m == NULL ||m->height < 1 || m->width < 1) return;

    for (int i = 0; i < m->height; i++)
    {
        free(*(m->ptr + i));
    }
    free(m->ptr);
}

struct matrix_t* matrix_create_struct(int width, int height)
{
    if (width < 1 || height < 1) return NULL;

    struct matrix_t *matrix = malloc(sizeof(struct matrix_t));
    if (matrix == NULL) return NULL;

    int error = matrix_create(matrix, width, height);
    if (error == 1 || error == 2)
    {
        free(matrix);
        return NULL;
    }

    return matrix;
}
void matrix_destroy_struct(struct matrix_t **m)
{
    if (*m == NULL) return;

    matrix_destroy(*m);
    free(*m);
    *m = NULL;
}
struct matrix_t* matrix_transpose(const struct matrix_t *m)
{
    if (m == NULL || m->ptr == NULL || m->height < 1 || m->width < 1) return NULL;


    struct matrix_t *matrixTranspose = matrix_create_struct(m->height, m->width);
    if (matrixTranspose == NULL)
        return NULL;

    for (int i = 0; i < matrixTranspose->height; ++i)
    {
        for (int j = 0; j < matrixTranspose->width; ++j)
        {
            int num = *(*(m->ptr + j) + i);
            *(*(matrixTranspose->ptr + i) + j) = num;
        }
    }

    return matrixTranspose;
}
int matrix_save_b(const struct matrix_t *m, const char *filename)
{
    if (m == NULL || m->ptr == NULL || filename == NULL || m->width < 1 || m->height < 1) return 1;

    FILE *file = NULL;
    int _width = m->width;
    int _height = m->height;

    if ((file = fopen(filename, "wb")) == NULL) return 2;

    //Save width and height
    fwrite(&_width, sizeof(int), 1, file);
    if(ferror(file) != 0)
    {
        fclose(file);
        return 3;
    }
    fwrite(&_height, sizeof(int), 1, file);
    if(ferror(file) != 0)
    {
        fclose(file);
        return 3;
    }

    for (int i = 0; i < _height; ++i)
    {
        for (int j = 0; j < _width; ++j)
        {
            int num = *(*(m->ptr + i) + j);
            fwrite(&num, sizeof(int), 1, file);
            if(ferror(file) != 0)
            {
                fclose(file);
                return 3;
            }
        }
    }

    fclose(file);
    return 0;
}
int matrix_save_t(const struct matrix_t *m, const char *filename)
{
    if (m == NULL || m->ptr == NULL || filename == NULL || m->width < 1 || m->height < 1) return 1;

    FILE *file = NULL;
    int _width = m->width;
    int _height = m->height;

    if ((file = fopen(filename, "w")) == NULL) return 2;

    //Save width and height
    if (fprintf(file, "%d %d\n", _width, _height) < 0)
    {
        fclose(file);
        return 3;
    }

    for (int i = 0; i < _height; ++i)
    {
        for (int j = 0; j < _width; ++j)
        {
            int num = *(*(m->ptr + i) + j);
            if (fprintf(file, "%d ", num) < 0)
            {
                fclose(file);
                return 3;
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}
