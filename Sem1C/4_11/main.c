#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "format_type.h"

enum errors {
    SUCCES = 0,
    INCORECT_INPUT = 1,
    INCORECT_INPUT_DATA = 2,
    COULDNT_OPEN_FILE = 4,
    COULDNT_CREATE_FILE = 5,
    FILE_CORRUPTED = 6,
    FAILED_TO_ALLOCATE_MEMORY = 8
};


struct statistic_t
{
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};

float stdDev(int **ptr);
int statistics(int **ptr, struct statistic_t **stats);
void display(int **ptr);
int save(const char *filename, int **ptr, enum save_format_t format);

int main()
{
    struct statistic_t *stats;

    int A[] = {10, 20, 30, 40, 50, 60, 70, -1};
    int B[] = {100, 200, 300, 400, 500, 600, 700, 800, -1};
    int C[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, -1};
    int* D[] = {A, B, C, NULL};

    display(D);
    //Get filename
    char *filename = malloc(40 * sizeof(char));
    if (filename == NULL)
    {
        printf("Failed to allocate memory\n");
        return FAILED_TO_ALLOCATE_MEMORY;
    }
    printf("File name: ");
    scanf("%39s", filename);

    //Clear buff
    while(getchar()!='\n'){}

    //Txt filename allocate and create
    char *filenameTxt = malloc((40 + 4) * sizeof(char));
    if (filenameTxt == NULL)
    {
        free(filename);
        printf("Failed to allocate memory\n");
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    strcpy(filenameTxt, filename);
    strcat(filenameTxt, ".txt");

    //Bin filename allocate and create
    char *filenameBin = malloc((40 + 4) * sizeof(char));
    if (filenameBin == NULL)
    {
        free(filename);
        free(filenameTxt);
        printf("Failed to allocate memory\n");
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    strcpy(filenameBin, filename);
    strcat(filenameBin, ".bin");

    //Save txt file
    if(save(filenameTxt, D, fmt_text) != 2)
        printf("File saved\n");
    else
        printf("Couldn't create file\n");

    //Save bin file
    if(save(filenameBin, D, fmt_binary) != 2)
        printf("File saved\n");
    else
        printf("Couldn't create file\n");

    //Print stats
    if(statistics(D,&stats) == 2)
    {
        free(filename);
        free(filenameTxt);
        free(filenameBin);
        printf("Failed to allocate memory\n");
    }
    printf("%d\n%d\n%d\n%f\n%f", stats->min, stats->max, stats->range, stats->avg, stats->standard_deviation);


    free(stats);
    free(filename);
    free(filenameTxt);
    free(filenameBin);
    return 0;
}

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

    //Debug
    //printf("Ile liczb: %d\n", sum_numbers);

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
