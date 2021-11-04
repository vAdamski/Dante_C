#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int numbersToSave = 0;
    int numToEnd = 0;
    FILE *file;
    char fileName[10];
    time_t time_s;
    srand((unsigned) time(&time_s));

    printf("Ile liczb chcesz zapisać:\n");
    if(scanf("%d", &numbersToSave) != 1)
    {
        printf("Incorrect input");
        return 1;
    }

    numToEnd = numbersToSave;

    if(numbersToSave < 1 || numbersToSave > 1000)
    {
        printf("Incorrect input data\n");
        return 2;
    }

    for (int i = 0; i < (numbersToSave - 1) / 10 + 1; ++i)
    {
        sprintf(fileName, "%d.txt", i);
        if((file = fopen(fileName, "w")) == NULL)
        {
            printf("Couldn't create file\n");
            return 5;
        }

        for (int j = 0; j < 10; ++j)
        {
            if(numToEnd <= 0) break;
            fprintf(file, "%d\n", rand()%1000+1);
            numToEnd--;
        }
        printf("%s\n", fileName);
        fclose(file);
    }

    return 0;
}
