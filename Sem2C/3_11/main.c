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
    int error;

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

    error = array_create_struct(&array, size);
    if(error == 2)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    do{
        int option;
        clean_stdin();
        printf("Co chcesz zrobić: ");
        if(scanf("%d", &option) != 1)
        {
            printf("Incorrect input\n");
            array_destroy_struct(&array);
            return 1;
        }

        //End program
        if(option == 0)
        {
            array_destroy_struct(&array);
            return 0;
        }
        //Dodaj liczby
        if(option == 1)
        {
            printf("Podaj liczby do dodania do tablicy: ");
            int x;
            while((x = scanf("%d", &num)) == 1 && num != 0)
            {
                error = array_push_back(array, num);

                if(error == 2)
                {
                    printf("Failed to allocate memory\n");
                    break;
                }
            }

            if(x != 1)
            {
                printf("Incorrect input\n");
                array_destroy_struct(&array);
                return 1;
            }

            if(array->size != 0)
            {
                array_display(array);
                printf("\n");
            }
        }
        //Usun liczby
        if(option == 2)
        {
            printf("Podaj liczby do usuniecia z tablicy: ");
            int x;
            while((x = scanf("%d", &num)) == 1 && num != 0)
            {
                array_remove_item(array, num);

                if(array->size == 0)
                {
                    break;
                }
            }

            if(x != 1)
            {
                printf("Incorrect input\n");
                array_destroy_struct(&array);
                return 1;
            }
            if(array->size == 0)
            {
                printf("Buffer is empty\n");
            }
            if(array->size != 0)
            {
                array_display(array);
                printf("\n");
            }
        }

        //Option < 0 || option > 2
        if(option < 0 || option > 2)
        {
            printf("Incorrect input data\n");
        }

    }while(1);
    return 0;
}







/*
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
        clean_stdin();
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

                    int error = array_push_back(array, num);

                    if(error == 2)
                    {
                        printf("Failed to allocate memory\n");
                        clean_stdin();
                        break;
                    }

                }while(1);

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
 */
