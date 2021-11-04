#include <stdio.h>
#include <stdlib.h>
#include "image_utils.h"

enum errors {
    SUCCES = 0,
    INCORECT_INPUT = 1,
    INCORECT_INPUT_DATA = 2,
    COULDNT_OPEN_FILE = 4,
    COULDNT_CREATE_FILE = 5,
    FILE_CORRUPTED = 6,
    FAILED_TO_ALLOCATE_MEMORY = 8
};

int main()
{
    int x,y,color,height,width,error_code;
    struct image_t *image;
    char *filename = malloc(40 * sizeof(char));
    if(filename == NULL)
    {
        printf("Failed to allocate memory\n");
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    //Open file
    printf("Filename to open: ");
    scanf("%39s", filename);

    //Clear buff
    while(getchar()!='\n'){}

    image = load_image_t(filename, &error_code);
    if (error_code == 2)
    {
        free(filename);
        printf("Couldn't open file\n");
        return COULDNT_OPEN_FILE;
    }
    if (error_code == 3)
    {
        free(filename);
        printf("File corrupted\n");
        return FILE_CORRUPTED;
    }
    if (error_code == 4)
    {
        free(filename);
        printf("Failed to allocate memory\n");
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    //Take info about rect
    printf("Give (X Y WIDTH HEIGHT): ");
    if(scanf("%d %d %d %d", &x, &y, &width, &height) != 4)
    {
        free(filename);
        destroy_image(&image);
        printf("Incorrect input\n");
        return INCORECT_INPUT;
    }

    //Take color
    printf("Give color: ");
    if(scanf("%d", &color) != 1)
    {
        free(filename);
        destroy_image(&image);
        printf("Incorrect input\n");
        return INCORECT_INPUT;
    }

    if(color < 0 || color > 255 || x < 0 || y < 0 || width < 0 || height < 0)
    {
        free(filename);
        destroy_image(&image);
        printf("Incorrect input data\n");
        return INCORECT_INPUT_DATA;
    }

    error_code = image_draw_rectangle(image, &(struct rectangle_t){ .p = {x,y}, .width = width, .height = height}, color);
    if(error_code == 1)
    {
        free(filename);
        destroy_image(&image);
        printf("Incorrect input data\n");
        return INCORECT_INPUT_DATA;
    }

    error_code = save_image_t(filename, image);
    if(error_code == 0)
    {
        printf("File saved\n");
    }
    else
    {
        free(filename);
        destroy_image(&image);
        printf("Couldn't create file");
        return COULDNT_CREATE_FILE;
    }

    free(filename);
    destroy_image(&image);
    return SUCCES;
}
