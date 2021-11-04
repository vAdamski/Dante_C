#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>



int main()
{
    char *filename = malloc(40*sizeof(char));
    char *newFilename = malloc(49*sizeof(char));
    scanf("%39s", filename);
    int howMany = 0;
    for (int i = 0; i < strlen(filename); ++i)
    {
        if(*(filename + i) == 46) howMany++;
    }

    printf("%d\n", howMany);

    char *schowek = strtok(filename, ".");
    int flag = 0;
    while( schowek != NULL )
    {
        if(flag == 0)
        {
            strcpy(newFilename, schowek);
            printf("%s\n", newFilename);
            flag++;
            schowek = strtok( NULL, ".");
            continue;
        }
        if(flag == howMany)
        {
            strcat(newFilename, "_modified");
            printf("%s\n", newFilename);
            strcat(newFilename, ".");
            strcat(newFilename, schowek);
            schowek = strtok( NULL, ".");
            continue;
        }
        strcat(newFilename, ".");
        strcat(newFilename, schowek);
        printf("%s\n", newFilename);
        schowek = strtok( NULL, ".");
        flag++;
    }
    printf("\n\n%s\n", newFilename);


    return 0;
}
