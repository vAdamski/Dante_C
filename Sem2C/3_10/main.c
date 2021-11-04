#include <stdio.h>
#include "circular_buffer.h"

void clean_stdin(void);

int main()
{
    int size;
    int error;
    struct circular_buffer_t *buffer;

    //Create buff
    printf("Size tab to allocate: ");
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

    error = circular_buffer_create_struct(&buffer, size);

    if(error == 2)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    //Main program
    while(1)
    {
        //Take option
        int option;
        clean_stdin();
        printf("What you want do: ");
        if(scanf("%d", &option) != 1)
        {
            printf("Incorrect input\n");
            circular_buffer_destroy_struct(&buffer);
            return 1;
        }

        //If 0 - End program
        if(option == 0)
        {
            circular_buffer_destroy_struct(&buffer);
            return 0;
        }

        //If 1 - Add num tu buffer
        else if(option == 1)
        {
            int num;
            clean_stdin();
            printf("Number to add: ");
            if(scanf("%d", &num) != 1)
            {
                printf("Incorrect input\n");
                circular_buffer_destroy_struct(&buffer);
                return 1;
            }

            circular_buffer_push_back(buffer, num);
        }

        //If 2 - Get last num from buff
        else if(option == 2)
        {
            int error_code;
            int num = circular_buffer_pop_back(buffer, &error_code);

            //If empty
            if (error_code == 2)
            {
                printf("Buffer is empty\n");
            }

            //If buff not empty
            if (error_code == 0)
            {
                printf("%d\n", num);
            }
        }

        //If 3 - Get first num from buff
        else if(option == 3)
        {
            int error_code;
            int num = circular_buffer_pop_front(buffer, &error_code);

            //If empty
            if (error_code == 2)
            {
                printf("Buffer is empty\n");
            }

            //If buff not empty
            if (error_code == 0)
            {
                printf("%d\n", num);
            }
        }

        //If 4 - Display buff
        else if(option == 4)
        {
            if(circular_buffer_empty(buffer) == 1)
            {
                printf("Buffer is empty\n");
            }
            else
            {
                circular_buffer_display(buffer);
                printf("\n");
            }
        }

        //If 5 - Is buff empty
        else if(option == 5)
        {
            if(circular_buffer_empty(buffer) == 1)
                printf("1\n");
            else
                printf("0\n");
        }

        //If 6 - Is buff empty
        else if(option == 6)
        {
            if(circular_buffer_full(buffer) == 1)
                printf("1\n");
            else
                printf("0\n");
        }

        //If option != {0,1,2,3,4,5,6}
        else
        {
            printf("Incorrect input data\n");
        }
    }
}

//Additional function
void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    }while(c != '\n' && c != EOF);
}
