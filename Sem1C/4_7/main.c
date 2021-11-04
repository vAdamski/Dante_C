#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_utils.h"

int main()
{
    char *filename = malloc(40 * sizeof(char));
    if(filename == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }
    struct image_t *image;
    struct image_t *image_v;
    struct image_t *image_h;
    struct image_t *image_n;
    int error_code;

    printf("Enter file name: ");
    scanf("%39s", filename);

    //Load image form file
    image = load_image_t(filename, &error_code);
    if(error_code == 2)
    {
        printf("Couldn't open file\n");
        free(filename);
        return 4;
    }
    if(error_code == 3)
    {
        printf("File corrupted\n");
        free(filename);
        return 6;
    }
    if(error_code == 4)
    {
        printf("Failed to allocate memory\n");
        free(filename);
        return 8;
    }

    //Generate image
    image_h = image_flip_horizontal(image);
    if(image_h == NULL)
    {
        printf("Failed to allocate memory\n");
        free(filename);
        destroy_image(&image);
        return 8;
    }

    image_v = image_flip_vertical(image);
    if(image_v == NULL)
    {
        printf("Failed to allocate memory\n");
        free(filename);
        destroy_image(&image_h);
        destroy_image(&image);
        return 8;
    }

    image_n = image_negate(image);
    if(image_n == NULL)
    {
        printf("Failed to allocate memory\n");
        free(filename);
        destroy_image(&image_h);
        destroy_image(&image_v);
        destroy_image(&image);
        return 8;
    }

    //Save file - allocate memory for file name
    char *filenameHorizontal = malloc((9 + 40) * sizeof(char)); // mirror_h_ (9) + filename
    if(filenameHorizontal == NULL)
    {
        printf("Failed to allocate memory\n");
        free(filename);
        destroy_image(&image_n);
        destroy_image(&image_h);
        destroy_image(&image_v);
        destroy_image(&image);
        return 8;
    }

    char *filenameVertical = malloc((9 + 40) * sizeof(char)); // mirror_v_ (9) + filename
    if(filenameVertical == NULL)
    {
        printf("Failed to allocate memory\n");
        free(filenameHorizontal);
        free(filename);
        destroy_image(&image_n);
        destroy_image(&image_h);
        destroy_image(&image_v);
        destroy_image(&image);
        return 8;
    }

    char *filenameNegate = malloc((7 + 40) * sizeof(char)); // invert_ (7) + filename
    if(filenameNegate == NULL)
    {
        printf("Failed to allocate memory\n");
        free(filenameVertical);
        free(filenameHorizontal);
        free(filename);
        destroy_image(&image_n);
        destroy_image(&image_h);
        destroy_image(&image_v);
        destroy_image(&image);
        return 8;
    }

    //Save file - create file name
    strcpy(filenameHorizontal, "mirror_h_");
    strcat(filenameHorizontal, filename);

    strcpy(filenameVertical, "mirror_v_");
    strcat(filenameVertical, filename);

    strcpy(filenameNegate, "invert_");
    strcat(filenameNegate, filename);

    //Save Horizontal file
    error_code = save_image_t(filenameHorizontal, image_h);
    if(error_code == 0)
    {
        printf("File saved\n");
    }
    if(error_code == 2)
    {
        printf("Couldn't create file\n");
        /*
        free(filenameNegate);
        free(filenameVertical);
        free(filenameHorizontal);
        free(filename);
        destroy_image(&image_n);
        destroy_image(&image_h);
        destroy_image(&image_v);
        destroy_image(&image);
        return 4;
         */
    }
    if(error_code == 3)
    {
        printf("File corrupted\n");
        free(filenameNegate);
        free(filenameVertical);
        free(filenameHorizontal);
        free(filename);
        destroy_image(&image_n);
        destroy_image(&image_h);
        destroy_image(&image_v);
        destroy_image(&image);
        return 6;
    }
    if(error_code == 4)
    {
        printf("Failed to allocate memory\n");
        free(filenameNegate);
        free(filenameVertical);
        free(filenameHorizontal);
        free(filename);
        destroy_image(&image_n);
        destroy_image(&image_h);
        destroy_image(&image_v);
        destroy_image(&image);
        return 8;
    }

    //Save Vertical file
    error_code = save_image_t(filenameVertical, image_v);
    if(error_code == 0)
    {
        printf("File saved\n");
    }
    if(error_code == 2)
    {
        printf("Couldn't create file\n");
        /*
        free(filenameNegate);
        free(filenameVertical);
        free(filenameHorizontal);
        free(filename);
        destroy_image(&image_n);
        destroy_image(&image_h);
        destroy_image(&image_v);
        destroy_image(&image);
        return 4;
         */
    }
    if(error_code == 3)
    {
        printf("File corrupted\n");
        free(filenameNegate);
        free(filenameVertical);
        free(filenameHorizontal);
        free(filename);
        destroy_image(&image_n);
        destroy_image(&image_h);
        destroy_image(&image_v);
        destroy_image(&image);
        return 6;
    }
    if(error_code == 4)
    {
        printf("Failed to allocate memory\n");
        free(filenameNegate);
        free(filenameVertical);
        free(filenameHorizontal);
        free(filename);
        destroy_image(&image_n);
        destroy_image(&image_h);
        destroy_image(&image_v);
        destroy_image(&image);
        return 8;
    }

    //Save Horizontal file
    error_code = save_image_t(filenameNegate, image_n);
    if(error_code == 0)
    {
        printf("File saved\n");
    }
    if(error_code == 2)
    {
        printf("Couldn't create file\n");
        /*
        free(filenameNegate);
        free(filenameVertical);
        free(filenameHorizontal);
        free(filename);
        destroy_image(&image_n);
        destroy_image(&image_h);
        destroy_image(&image_v);
        destroy_image(&image);
        return 4;
         */
    }
    if(error_code == 3)
    {
        printf("File corrupted\n");
        free(filenameNegate);
        free(filenameVertical);
        free(filenameHorizontal);
        free(filename);
        destroy_image(&image_n);
        destroy_image(&image_h);
        destroy_image(&image_v);
        destroy_image(&image);
        return 6;
    }
    if(error_code == 4)
    {
        printf("Failed to allocate memory\n");
        free(filenameNegate);
        free(filenameVertical);
        free(filenameHorizontal);
        free(filename);
        destroy_image(&image_n);
        destroy_image(&image_h);
        destroy_image(&image_v);
        destroy_image(&image);
        return 8;
    }


    //End program
    free(filenameNegate);
    free(filenameVertical);
    free(filenameHorizontal);
    free(filename);
    destroy_image(&image_n);
    destroy_image(&image_h);
    destroy_image(&image_v);
    destroy_image(&image);
    return 0;
}
