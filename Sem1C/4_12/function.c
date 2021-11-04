//
// Created by Adam Ludwiczak on 23/05/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "function.h"

int statistics(int **ptr, struct statistic_t **stats)
{
    if (ptr == NULL || stats == NULL)
        return 1;

    int sum = 0;
    int sum_numbers = 0;
    int x = 0;

    *stats = malloc(sizeof(struct statistic_t));
    if(*stats == NULL)
        return 2;

    while (*(ptr + x) != NULL)
    {
        int y = 0;
        while(*(*(ptr + x) + y) != -1)
        {
            //Add to sum
            sum += *(*(ptr + x) + y);
            //Add sum numbers to cal avg
            sum_numbers++;
            y++;
        }
        x++;
    }

    //If array empty return 3
    if(sum_numbers == 0)
    {
        free(*stats);
        return 3;
    }


    (*stats)->min = *(*(ptr + 0) + 0);
    (*stats)->max = *(*(ptr + 0) + 0);

    x = 0;
    while (*(ptr + x) != NULL)
    {
        int y = 0;
        while(*(*(ptr + x) + y) != -1)
        {
            //Set min
            if(*(*(ptr + x) + y) < (*stats)->min)
            {
                (*stats)->min = *(*(ptr + x) + y);
            }
            //Set max
            if(*(*(ptr + x) + y) > (*stats)->max)
            {
                (*stats)->max = *(*(ptr + x) + y);
            }
            y++;
        }
        x++;
    }

    (*stats)->range = (*stats)->max - (*stats)->min;
    (*stats)->avg = (float)sum / (float)sum_numbers;
    (*stats)->standard_deviation = stdDev(ptr);
    return 0;
}

void display(int **ptr)
{
    if(ptr == NULL) return;
    int x = 0;
    while (*(ptr + x) != NULL)
    {
        int y = 0;
        while(*(*(ptr + x) + y) != -1)
        {
            printf("%d ", *(*(ptr + x) + y));
            y++;
        }
        printf("\n");
        x++;
    }
}

int save(const char *filename, int **ptr, enum save_format_t format)
{
    if (filename == NULL || ptr == NULL)
        return 1;
    if (format != fmt_text && format != fmt_binary)
        return 1;

    FILE *file = NULL;
    int x = 0;
    switch (format)
    {
        case fmt_text:
            //Open file
            if((file = fopen(filename, "w")) == NULL)
            {
                return 2;
            }

            while (*(ptr + x) != NULL)
            {
                int y = 0;
                while(*(*(ptr + x) + y) != -1)
                {
                    fprintf(file, "%d ", *(*(ptr + x) + y));
                    y++;
                }
                fprintf(file, "-1");
                fprintf(file, "\n");
                x++;
            }

            fclose(file);
            break;
        case fmt_binary:
            //Open file binary
            if((file = fopen(filename, "wb")) == NULL)
            {
                return 2;
            }

            while (*(ptr + x) != NULL)
            {
                int y = 0;
                while(*(*(ptr + x) + y) != -1)
                {
                    fwrite(*(ptr + x) + y, sizeof(int), 1, file);
                    y++;
                }
                fwrite(*(ptr + x) + y, sizeof(int), 1, file);
                x++;
            }

            fclose(file);
            break;
        default:
            break;
    }

    return 0;
}

float stdDev(int **ptr)
{
    int sum = 0;
    int size = 0;
    int x = 0;
    while (*(ptr + x) != NULL)
    {
        int y = 0;
        while(*(*(ptr + x) + y) != -1)
        {
            //Add to sum
            sum += *(*(ptr + x) + y);
            //Add sum numbers to cal avg
            size++;
            y++;
        }
        x++;
    }
    float avg = (float)sum/(float)size;
    float licznik = 0;
    float mianownik = (float)size;

    x = 0;
    while (*(ptr + x) != NULL)
    {
        int y = 0;
        while(*(*(ptr + x) + y) != -1)
        {
            licznik += powf((float)(*(*(ptr + x) + y)) - avg, 2);
            y++;
        }
        x++;
    }
    return sqrtf(licznik/mianownik);
}

float stdDev_row(int **ptr)
{
    int sum = 0;
    int size = 0;
    int x = 0;
    while(*(*ptr + x) != -1)
    {
        //Add to sum
        sum += *(*ptr + x);
        //Add sum numbers to cal avg
        size++;
        x++;
    }
    float avg = (float)sum/(float)size;
    float licznik = 0;
    float mianownik = (float)size;

    x = 0;
    while(*(*ptr + x) != -1)
    {
        licznik += powf((float)*(*ptr + x) - avg, 2);
        x++;
    }
    return sqrtf(licznik/mianownik);
}

int load(const char *filename, int ***ptr, enum save_format_t format)
{
    if (filename == NULL || ptr == NULL)
        return 1;
    if (format != fmt_text && format != fmt_binary)
        return 1;

    FILE *file = NULL;
    int **tab = NULL;
    int num;
    int height = 0;
    char c;
    switch (format)
    {
        //Text file
        case fmt_text:
            //Open file
            if((file = fopen(filename, "r")) == NULL)
            {
                return 2;
            }

            int ile_liczb = 0;
            //Scan numbers in file
            while(fscanf(file, "%d", &num) == 1)
            {
                ile_liczb++;
            }
            //printf("%d\n", ile_liczb);
            if (ile_liczb == 0)
            {
                fclose(file);
                return 3;
            }

            fseek(file, 0L, SEEK_SET);
            while((c = fgetc(file)) != EOF)
            {
                if(isdigit(c) != 0 || isspace(c) != 0 || c == 45)
                {
                    //printf("%c --> Jest cyfrą lub znakiem białym lub -\n", c);
                }
                else
                {
                    fclose(file);
                    return 3;
                }
            }
            fseek(file, 0L, SEEK_SET);

            //Scan height in file
            while(fscanf(file, "%d", &num) == 1)
            {
                if(num == -1)
                    height++;
            }

            if (height == 0)
            {
                fclose(file);
                return 3;
            }


            tab = malloc((height + 1) * sizeof(int*));
            if (tab == NULL)
            {
                fclose(file);
                return 4;
            }

            *(tab + height) = NULL;

            //Scan size for each height in file
            fseek(file, 0L, SEEK_SET);

            for (int i = 0; i < height; ++i)
            {
                int size = 0;
                do {
                    fscanf(file, "%d", &num);
                    size++;
                }while (num != -1);
                *(tab + i) = malloc(size * sizeof(int));
                if(*(tab + i) == NULL)
                {
                    for (int j = 0; j < i; ++j)
                    {
                        free(*(tab + j));
                    }
                    free(tab);
                    fclose(file);
                    return 4;
                }
            }


            //Load data to allocate memory
            fseek(file, 0L, SEEK_SET);

            for (int i = 0; i < height; ++i)
            {
                int size = 0;
                do {
                    fscanf(file, "%d", &num);
                    *(*(tab + i) + size) = num;
                    size++;
                }while (num != -1);
            }

            *ptr = tab;
            fclose(file);
            break;
        //Bin file
        case fmt_binary:
            //Open file binary
            if((file = fopen(filename, "rb")) == NULL)
            {
                return 2;
            }
            fseek(file, 0L, SEEK_SET);
            while(fread(&num, sizeof(int), 1, file) > 0)
            {
                if(ferror(file))
                {
                    fclose(file);
                    return 3;
                }
            }

            fseek(file, 0L, SEEK_SET);

            //Scan height in file
            while(fread(&num,sizeof(int), 1, file) == 1)
            {
                if(num == -1)
                    height++;
            }

            if (height == 0)
            {
                fclose(file);
                return 3;
            }


            tab = malloc((height + 1) * sizeof(int*));
            if (tab == NULL)
            {
                fclose(file);
                return 4;
            }

            *(tab + height) = NULL;

            //Scan size for each height in file
            fseek(file, 0L, SEEK_SET);

            for (int i = 0; i < height; ++i)
            {
                int size = 0;
                do {
                    fread(&num,sizeof(int), 1, file);
                    size++;
                }while (num != -1);
                *(tab + i) = malloc(size * sizeof(int));
                if(*(tab + i) == NULL)
                {
                    for (int j = 0; j < i; ++j)
                    {
                        free(*(tab + j));
                    }
                    free(tab);
                    fclose(file);
                    return 4;
                }
            }


            //Load data to allocate memory
            fseek(file, 0L, SEEK_SET);

            for (int i = 0; i < height; ++i)
            {
                int size = 0;
                do {
                    fread(&num,sizeof(int), 1, file);
                    *(*(tab + i) + size) = num;
                    size++;
                }while (num != -1);
            }

            *ptr = tab;
            fclose(file);
            break;
        default:
            break;
    }

    return 0;
}

int statistics_row(int **ptr, struct statistic_t **stats)
{
    if (ptr == NULL || stats == NULL)
        return -1;

    int height = 0;
    while (*(ptr + height) != NULL)
    {
        height++;
    }

    *stats = (struct statistic_t*)malloc(height * sizeof(struct statistic_t));
    if(*stats == NULL)
        return -2;

    for (int i = 0; i < height; ++i)
    {
        int sum = 0;
        int sum_numbers = 0;
        int x = 0;

        while(*(*(ptr + i) + x) != -1)
        {
            //Add to sum
            sum += *(*(ptr + i) + x);
            //Add sum numbers to cal avg
            sum_numbers++;
            x++;
        }

        if(sum_numbers == 0)
        {
            (*stats + i)->min = -1;
            (*stats + i)->max = -1;
            (*stats + i)->avg = -1.0;
            (*stats + i)->standard_deviation = -1.0;
            (*stats + i)->range = -1;
            continue;
        }


        (*stats + i)->min = *(*(ptr + i) + 0);
        (*stats + i)->max = *(*(ptr + i) + 0);

        x = 0;
        while(*(*(ptr + i) + x) != -1)
        {
            //Set min
            if(*(*(ptr + i) + x) < (*stats + i)->min)
            {
                (*stats + i)->min = *(*(ptr + i) + x);
            }
            //Set max
            if(*(*(ptr + i) + x) > (*stats + i)->max)
            {
                (*stats + i)->max = *(*(ptr + i) + x);
            }
            x++;
        }

        (*stats + i)->range = (*stats + i)->max - (*stats + i)->min;
        (*stats + i)->avg = (float)sum / (float)sum_numbers;
        (*stats + i)->standard_deviation = stdDev_row(ptr + i);
    }

    return height;
}

void destroy(int ***ptr)
{
    if(ptr == NULL)
        return;

    int x = 0;
    while(*(*ptr + x) != NULL)
    {
        free(*(*ptr + x));
        x++;
    }
    free(*ptr);
    *ptr = NULL;
}