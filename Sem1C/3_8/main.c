#include <stdio.h>
#include "array.h"

void clean_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    }while(c != '\n' && c != EOF);
}

int main()
{
    struct array_t *array;
    int num;
    int size;

    printf("Podaj wielkosc tablicy: ");

    if(scanf("%d", &size) != 1)
    {
        printf("Incorrect input\n");
        return 1;
    }
    if(size < 1)
    {
        printf("Incorrect input data\n");
        return 2;
    }

    int error = array_create_struct(&array, size);
    if(error == 2)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    while(1)
    {
        int option;
        printf("Co chcesz zrobić: ");

        if(scanf("%d", &option) != 1)
        {
            printf("Incorrect input\n");
            array_destroy_struct(&array);
            return 1;
        }

        clean_stdin();

        switch (option)
        {
            case 0:
                //End program
                array_destroy_struct(&array);
                return 0;
            case 1:
                //Add items to array

                printf("Podaj liczby do tablicy: ");

                do {
                    if(scanf("%d", &num) != 1)
                    {
                        printf("Incorrect input\n");
                        array_destroy_struct(&array);
                        return 1;
                    }

                    if(num == 0) break;

                    array_push_back(array, num);
                    if(array->size == array->capacity)
                    {
                        break;
                    }

                }while(1);

                if(array->size == array->capacity)
                {
                    printf("Buffer is full\n");
                    clean_stdin();
                }

                if(array->size != 0)
                {
                    array_display(array);
                    printf("\n");
                }


                break;
            case 2:
                //Delete items from array

                printf("Podaj liczby do usuniecia z tablicy: ");

                do {
                    if(scanf("%d", &num) != 1)
                    {
                        printf("Incorrect input\n");
                        array_destroy_struct(&array);
                        return 1;
                    }

                    if(num == 0) break;

                    array_remove_item(array, num);
                    if(array->size == 0)
                    {
                        break;
                    }

                }while(1);

                if(array->size == 0)
                {
                    printf("Buffer is empty\n");
                    clean_stdin();
                }

                if(array->size != 0)
                {
                    array_display(array);
                    printf("\n");
                }

                break;
            default:
                printf("Incorrect input data\n");
                break;
        }
    }
}
