//
// Created by Adam Ludwiczak on 23/05/2021.
//

#ifndef INC_4_12_FUNCTION_H
#define INC_4_12_FUNCTION_H

#include "format_type.h"

enum errors {
    SUCCES = 0,
    INCORECT_INPUT = 1,
    INCORECT_INPUT_DATA = 2,
    COULDNT_OPEN_FILE = 4,
    COULDNT_CREATE_FILE = 5,
    FILE_CORRUPTED = 6,
    UNSUPPORTED_FILE_TYPE = 7,
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

//4_11
float stdDev(int **ptr);
int statistics(int **ptr, struct statistic_t **stats);
void display(int **ptr);
int save(const char *filename, int **ptr, enum save_format_t format);

//4_12
int load(const char *filename, int ***ptr, enum save_format_t format);
int statistics_row(int **ptr, struct statistic_t **stats);
void destroy(int ***ptr);

#endif //INC_4_12_FUNCTION_H
