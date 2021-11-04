//
// Created by Adam Ludwiczak on 27/05/2021.
//

#ifndef INC_4_4_MATRIX_H
#define INC_4_4_MATRIX_H

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

struct matrix_t{
    int **ptr;
    int width;
    int height;
};

int matrix_create(struct matrix_t *m, int width, int height);
int matrix_read(struct matrix_t *m);
void matrix_display(const struct matrix_t *m);
void matrix_destroy(struct matrix_t *m);
#endif //INC_4_4_MATRIX_H
