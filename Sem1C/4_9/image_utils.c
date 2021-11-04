//
// Created by Adam Ludwiczak on 18/05/2021.
//

#include "image_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum error {
    SUCCES = 0,
    IN_ERROR = 1,
    FILE_OPEN_ERROR = 2,
    FILE_CORRUPTED = 3,
    MEMORY_ERROR = 4
};

struct image_t* load_image_t(const char *filename, int *err_code)
{
    if(filename == NULL)
    {
        if(err_code != NULL) *err_code = IN_ERROR;
        return NULL;
    }

    //FILES
    FILE *file;
    struct image_t *image = malloc(sizeof(struct image_t));
    if(image == NULL)
    {
        if (err_code != NULL) *err_code = MEMORY_ERROR;
        return NULL;
    }
    //Open file
    if((file = fopen(filename, "r")) == NULL)
    {
        free(image);
        if (err_code != NULL) *err_code = FILE_OPEN_ERROR;
        return NULL;
    }
    //Type of doc
    char *code = malloc(3 * sizeof(char));
    //Scan type doc
    fscanf(file, "%2s", code);

    if (strcmp(code, "P2") != 0)
    {
        if (err_code != NULL) *err_code = FILE_CORRUPTED;
        free(image);
        free(code);
        fclose(file);
        return NULL;
    }

    strcpy(image->type, code);
    free(code);
    //Scan h & w
    if (fscanf(file, "%d %d", &image->width, &image->height) != 2)
    {
        if (err_code != NULL) *err_code = FILE_CORRUPTED;
        free(image);
        fclose(file);
        return NULL;
    }

    if(image->width < 1 || image->height < 1)
    {
        if (err_code != NULL) *err_code = FILE_CORRUPTED;
        free(image);
        fclose(file);
        return NULL;
    }

    //Scan max
    int max;

    if (fscanf(file, "%d", &max) != 1)
    {
        if (err_code != NULL) *err_code = FILE_CORRUPTED;
        free(image);
        fclose(file);
        return NULL;
    }

    if(max > 255)
    {
        if (err_code != NULL) *err_code = FILE_CORRUPTED;
        free(image);
        fclose(file);
        return NULL;
    }

    //Allocate memory
    image->ptr = malloc(image->height * sizeof(int*));
    if(image->ptr == NULL)
    {
        if (err_code != NULL) *err_code = MEMORY_ERROR;
        free(image);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < image->height; ++i)
    {
        *(image->ptr + i) = malloc(image->width * sizeof(int));
        if(*(image->ptr + i) == NULL)
        {
            for (int j = 0; j < i ; ++j)
            {
                free(*(image->ptr + j));
            }
            if (err_code != NULL) *err_code = MEMORY_ERROR;
            free(image->ptr);
            free(image);
            fclose(file);
            return NULL;
        }
    }

    for (int i = 0; i < image->height; ++i)
    {
        for (int j = 0; j < image->width; ++j)
        {
            if(fscanf(file, "%d", *(image->ptr + i) +j) != 1)
            {
                if (err_code != NULL) *err_code = FILE_CORRUPTED;
                for (int k = 0; k < image->height; ++k)
                {
                    free(*(image->ptr + k));
                }
                free(image->ptr);
                free(image);
                fclose(file);
                return NULL;
            }
            if(*(*(image->ptr + i) +j) < 0)
            {
                if (err_code != NULL) *err_code = FILE_CORRUPTED;
                for (int k = 0; k < image->height; ++k)
                {
                    free(*(image->ptr + k));
                }
                free(image->ptr);
                free(image);
                fclose(file);
                return NULL;
            }
        }
    }

    fclose(file);
    if (err_code != NULL) *err_code = SUCCES;
    return image;
}

int save_image_t(const char * filename, const struct image_t *m1)
{
    if(filename == NULL || m1 == NULL || m1->width < 1 || m1->height < 1 || m1->ptr == NULL) return IN_ERROR;

    FILE *file;
    int _height;
    int _width;

    if((file = fopen(filename, "w")) == NULL) return FILE_OPEN_ERROR;

    _height = m1->height;
    _width = m1->width;

    fprintf(file, "%s\n", m1->type);
    fprintf(file, "%d %d\n", m1->width, m1->height);
    fprintf(file, "255\n");

    for (int i = 0; i < _height; ++i)
    {
        for (int j = 0; j < _width; ++j)
        {
            if(fprintf(file, "%d ", *(*(m1->ptr+i)+j)) < 0)
            {
                fclose(file);
                return FILE_CORRUPTED;
            }
        }
        if(fprintf(file, "\n") < 0)
        {
            fclose(file);
            return FILE_CORRUPTED;
        }
    }

    fclose(file);
    return SUCCES;
}

void destroy_image(struct image_t **m)
{
    if(*m == NULL || (*m)->ptr == NULL || (*m)->height < 1) return;

    for (int i = 0; i < (*m)->height; ++i)
    {
        free(*((*m)->ptr + i));
    }
    free((*m)->ptr);
    free(*m);
    *m = NULL;
}

struct image_t* image_flip_horizontal(const struct image_t *m1)
{
    if(m1 == NULL || m1->ptr == NULL || m1->width < 1|| m1->height < 1) return NULL;

    struct image_t *image = malloc(sizeof(struct image_t));

    if(image == NULL)
    {
        return NULL;
    }

    image->height = m1->height;
    image->width = m1->width;
    strcpy(image->type, m1->type);

    //Allocate memory on image
    image->ptr = malloc(image->height * sizeof(int*));
    if(image->ptr == NULL)
    {
        free(image);
        return NULL;
    }

    for (int i = 0; i < image->height; ++i)
    {
        *(image->ptr + i) = malloc(image->width * sizeof(int));
        if(*(image->ptr + i) == NULL)
        {
            for (int j = 0; j < i ; ++j)
            {
                free(*(image->ptr + j));
            }
            free(image->ptr);
            free(image);
            return NULL;
        }
    }

    //Flip horizontal
    for (int i = 0; i < m1->height; ++i)
    {
        for (int j = 0; j < m1->width; ++j)
        {
            *(*(image->ptr + i) + j) = *(*(m1->ptr + m1->height - i - 1) + j);
        }
    }

    return image;
}

struct image_t* image_flip_vertical(const struct image_t *m1)
{
    if(m1 == NULL || m1->ptr == NULL || m1->width < 1|| m1->height < 1) return NULL;

    struct image_t *image = malloc(sizeof(struct image_t));

    if(image == NULL)
    {
        return NULL;
    }

    image->height = m1->height;
    image->width = m1->width;
    strcpy(image->type, m1->type);

    //Allocate memory on image
    image->ptr = malloc(image->height * sizeof(int*));
    if(image->ptr == NULL)
    {
        free(image);
        return NULL;
    }

    for (int i = 0; i < image->height; ++i)
    {
        *(image->ptr + i) = malloc(image->width * sizeof(int));
        if(*(image->ptr + i) == NULL)
        {
            for (int j = 0; j < i ; ++j)
            {
                free(*(image->ptr + j));
            }
            free(image->ptr);
            free(image);
            return NULL;
        }
    }

    //Flip vertical
    for (int i = 0; i < m1->height; ++i)
    {
        for (int j = 0; j < m1->width; ++j)
        {
            *(*(image->ptr + i) + j) = *(*(m1->ptr + i) + m1->width - j - 1);
        }
    }

    return image;
}

struct image_t* image_negate(const struct image_t *m1)
{
    if(m1 == NULL || m1->ptr == NULL || m1->width < 1|| m1->height < 1) return NULL;

    struct image_t *image = malloc(sizeof(struct image_t));

    if(image == NULL)
    {
        return NULL;
    }

    image->height = m1->height;
    image->width = m1->width;
    strcpy(image->type, m1->type);

    //Allocate memory on image
    image->ptr = malloc(image->height * sizeof(int*));
    if(image->ptr == NULL)
    {
        free(image);
        return NULL;
    }

    for (int i = 0; i < image->height; ++i)
    {
        *(image->ptr + i) = malloc(image->width * sizeof(int));
        if(*(image->ptr + i) == NULL)
        {
            for (int j = 0; j < i ; ++j)
            {
                free(*(image->ptr + j));
            }
            free(image->ptr);
            free(image);
            return NULL;
        }
    }

    //Negate 255 - x
    for (int i = 0; i < m1->height; ++i)
    {
        for (int j = 0; j < m1->width; ++j)
        {
            *(*(image->ptr + i) + j) = 255 - *(*(m1->ptr + i) + j);
        }
    }

    return image;
}

const int* image_get_pixel(const struct image_t *img, int x, int y)
{
    if (img == NULL ||
        img->ptr == NULL ||
        img->width < 1 ||
        img->height < 1 ||
        x < 0 ||
        y < 0 ||
        x > img->width - 1 ||
        y > img->height - 1)
        return NULL;

    return *(img->ptr + y) + x;
}

int* image_set_pixel(struct image_t *img, int x, int y)
{
    if (img == NULL ||
        img->ptr == NULL ||
        img->width < 1 ||
        img->height < 1 ||
        x < 0 ||
        y < 0 ||
        x > img->width - 1 ||
        y > img->height - 1)
        return NULL;

    return *(img->ptr + y) + x;
}

int image_draw_rectangle(struct image_t *img, const struct rectangle_t *rect, int value)
{
    //Sprawdzenie rect i img
    if (img == NULL ||
        img->ptr == NULL ||
        img->height < 1 ||
        img->width < 1 ||
        rect == NULL ||
        rect->width < 1 ||
        rect->height < 1 ||
        value < 0 ||
        value > 255)
        return 1;

    //Sprawdzenie czy kwadrat nie wcyhodzi po za obraz
    if (rect->p.x + rect->width> img->width ||
        rect->p.y + rect->height > img->height ||
        rect->p.x >= img->width ||
        rect->p.x < 0 ||
        rect->p.y >= img->height ||
        rect->p.y < 0)
        return 1;

    //Draw top line
    for (int i = 0; i < rect->width; ++i)
    {
        int *pixel = image_set_pixel(img, rect->p.x + i, rect->p.y);

        if(pixel != NULL)
            *pixel = value;
    }

    //Draw bottom line
    for (int i = 0; i < rect->width; ++i)
    {
        int *pixel = image_set_pixel(img, rect->p.x + i, rect->p.y + rect->height - 1);

        if(pixel != NULL)
            *pixel = value;
    }

    //Draw left line
    for (int i = 0; i < rect->height; ++i)
    {
        int *pixel = image_set_pixel(img, rect->p.x, rect->p.y + i);

        if(pixel != NULL)
            *pixel = value;
    }

    //Draw right line
    for (int i = 0; i < rect->height; ++i)
    {
        int *pixel = image_set_pixel(img, rect->p.x + rect->width - 1, rect->p.y + i);

        if(pixel != NULL)
            *pixel = value;
    }

    return 0;
}

int draw_image(struct image_t *img, const struct image_t *src, int destx, int desty)
{
    //Sprawdzenie poprawności danych
    if (img == NULL || img->ptr == NULL || src == NULL || src->ptr == NULL || destx < 0 || desty < 0 ||
        img->width < 1 || img->height < 1 || src->width < 1 || src->height < 1)
        return 1;
    //Sprawdzenie czy obraz nie wychodzi po za obraz podstawowy
    if (destx + src->width > img->width || desty + src->height > img->height)
        return 1;

    for (int i = 0; i < src->height; ++i)
    {
        for (int j = 0; j < src->width; ++j)
        {
            int *pixel = image_set_pixel(img, destx + j, desty + i);

            if(pixel != NULL)
            {
                const int *pixelFromNew = image_get_pixel(src, j, i);

                if(*pixelFromNew < 0)
                    return 1;

                *pixel = *pixelFromNew;
            }
        }
    }

    return 0;
}

