//
// Created by Adam Ludwiczak on 28/05/2021.
//

#ifndef INC_4_5_MATRIX_UTILS_H
#define INC_4_5_MATRIX_UTILS_H

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

//4.4
struct matrix_t{
    int **ptr;
    int width;
    int height;
};

int matrix_create(struct matrix_t *m, int width, int height);
int matrix_read(struct matrix_t *m);
void matrix_display(const struct matrix_t *m);
void matrix_destroy(struct matrix_t *m);

//4.5
struct matrix_t* matrix_create_struct(int width, int height);

void matrix_destroy_struct(struct matrix_t **m);

struct matrix_t* matrix_transpose(const struct matrix_t *m);

int matrix_save_b(const struct matrix_t *m, const char *filename);
int matrix_save_t(const struct matrix_t *m, const char *filename);

#endif //INC_4_5_MATRIX_UTILS_H
