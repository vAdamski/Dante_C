#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    int error_code;
    int imgToLoad;
    char *mainImgFilename = malloc(40 * sizeof(char));
    if(mainImgFilename == NULL)
    {
        printf("Failed to allocate memory\n");
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    //Load main img
    printf("Enter destination image file name: ");
    scanf("%39s", mainImgFilename);

    //Clear buff
    while(getchar()!='\n'){}

    struct image_t *mainImg = load_image_t(mainImgFilename, &error_code);
    if (error_code == 2)
    {
        free(mainImgFilename);
        printf("Couldn't open file\n");
        return COULDNT_OPEN_FILE;
    }
    if (error_code == 3)
    {
        free(mainImgFilename);
        printf("File corrupted\n");
        return FILE_CORRUPTED;
    }
    if (error_code == 4)
    {
        free(mainImgFilename);
        printf("Failed to allocate memory\n");
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    //How many img to draw in img
    printf("How many subimages you want to draw: ");
    if (scanf("%d", &imgToLoad) != 1)
    {
        printf("Incorrect input\n");
        free(mainImgFilename);
        destroy_image(&mainImg);
        return INCORECT_INPUT;
    }

    //Less then 1 img to load
    if (imgToLoad < 1)
    {
        printf("Incorrect input data\n");
        free(mainImgFilename);
        destroy_image(&mainImg);
        return INCORECT_INPUT_DATA;
    }

    //Load img to draw in main img
    for (int i = 0; i < imgToLoad; ++i)
    {
        char *imgFilename = malloc(40 * sizeof(char));
        if(imgFilename == NULL)
        {
            printf("Failed to allocate memory\n");
            free(mainImgFilename);
            destroy_image(&mainImg);
            return FAILED_TO_ALLOCATE_MEMORY;
        }

        printf("Enter a name of a subimage: ");
        scanf("%39s", imgFilename);

        struct image_t *image = load_image_t(imgFilename, &error_code);
        if (error_code == 2)
        {
            free(imgFilename);
            printf("Couldn't open file\n");
            continue;
        }
        if (error_code == 3)
        {
            free(imgFilename);
            printf("File corrupted\n");
            continue;
        }
        if (error_code == 4)
        {
            free(mainImgFilename);
            free(imgFilename);
            destroy_image(&mainImg);
            printf("Failed to allocate memory\n");
            return FAILED_TO_ALLOCATE_MEMORY;
        }

        int x,y;
        printf("Enter coordinates (x, y): ");
        if(scanf("%d %d", &x, &y) != 2)
        {
            free(mainImgFilename);
            free(imgFilename);
            destroy_image(&image);
            destroy_image(&mainImg);
            printf("Incorrect input\n");
            return INCORECT_INPUT;
        }
        if(x < 0 || y < 0 || x + image->width - 1 > mainImg->width || y + image->height - 1 > mainImg->height)
        {
            printf("Incorrect input data\n");
            free(imgFilename);
            destroy_image(&image);
            continue;
        }

        draw_image(mainImg, image, x, y);
        free(imgFilename);
        destroy_image(&image);
    }
    char *newFilename = malloc(40 + 9/*_modified*/ * sizeof(char));

    int howMany = 0;
    for (int i = 0; i < (int)strlen(mainImgFilename); ++i)
    {
        if(*(mainImgFilename + i) == 46) howMany++;
    }

    char *schowek = strtok(mainImgFilename, ".");
    int flag = 0;
    while( schowek != NULL )
    {
        if(flag == 0)
        {
            strcpy(newFilename, schowek);
            flag++;
            schowek = strtok( NULL, ".");
            continue;
        }
        if(flag == howMany)
        {
            strcat(newFilename, "_modified");
            strcat(newFilename, ".");
            strcat(newFilename, schowek);
            schowek = strtok( NULL, ".");
            continue;
        }
        strcat(newFilename, ".");
        strcat(newFilename, schowek);
        schowek = strtok( NULL, ".");
        flag++;
    }

    error_code = save_image_t(newFilename, mainImg);
    if(error_code == 0)
    {
        free(mainImgFilename);
        free(newFilename);
        destroy_image(&mainImg);
        printf("File saved\n");
    }
    else
    {
        free(mainImgFilename);
        free(newFilename);
        destroy_image(&mainImg);
        printf("Couldn't create file");
        return COULDNT_CREATE_FILE;
    }
    return 0;
}
