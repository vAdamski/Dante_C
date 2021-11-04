//
// Created by Adam Ludwiczak on 08/05/2021.
//

#ifndef INC_4_7_IMAGE_UTILS_H
#define INC_4_7_IMAGE_UTILS_H

struct image_t {
    char type[3];
    int **ptr;
    int width;
    int height;
};

struct image_t* load_image_t(const char *filename, int *err_code);
int save_image_t(const char * filename, const struct image_t *m1);

void destroy_image(struct image_t **m);
struct image_t* image_flip_horizontal(const struct image_t *m1);
struct image_t* image_flip_vertical(const struct image_t *m1);
struct image_t* image_negate(const struct image_t *m1);

#endif //INC_4_7_IMAGE_UTILS_H
