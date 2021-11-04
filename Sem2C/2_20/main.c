#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"

int main()
{
    char text[1000];
    char filename[31];
    char out_filename[31];
    int error;

    printf("Do you want to encode (E/e) or decode (D/d) a message? ");
    int ans = getchar();

    if(ans == 68 || ans == 100) //d D
    {
        clean_stdin();
        printf("Enter input file name: ");
        scanf("%30s", filename);

        error = decode(filename, text, 1000);
        switch (error)
        {
            case 2:
                printf("Couldn't open file\n");
                return 4;
            case 3:
                printf("File corrupted\n");
                return 6;
        }
        printf("%s", text);
    }
    else if (ans == 69 || ans == 101) //e E
    {
        clean_stdin();
        printf("Enter a message to be encoded:: ");
        scanf("%1000[^\n]s", text);
        printf("Enter input file name: ");
        scanf("%30s", filename);
        printf("Enter output file name: ");
        scanf("%30s", out_filename);

        error = encode(filename, text, out_filename);
        switch (error)
        {
            case 0:
                printf("File saved\n");
                return 0;
            case 2:
                printf("Couldn't open file\n");
                return 4;
            case 4:
                printf("Couldn't create file\n");
                return 5;
            case 3:
                printf("File corrupted\n");
                return 6;
        }
    }
    else
    {
        printf("Incorrect input data\n");
        return 1;
    }

    return 0;
}