#include <stdio.h>
#include <string.h>

int read_file(const char *filename);

int main() {
    char fileName[31];
    int size;
    printf("Podaj nazwe pliku:\n");
    scanf("%30s", fileName);

    size = read_file(fileName);

    if(size == -1 || size == 0)
    {
        printf("Couldn't open file\n");
        return 4;
    }
    printf("%d\n", size);
    return 0;
}

int read_file(const char *filename)
{
    FILE *file;
    FILE *readedFile;
    char fileNameToOpen[31];
    int completeLoadFile = 0;

    if(filename == (void *)0)
        return -1;

    if((file = fopen(filename, "rb")) == NULL)
        return completeLoadFile;

    completeLoadFile++;

    while(fgets(fileNameToOpen,31,file) != NULL)
    {
        strtok(fileNameToOpen, "\n");

        if((readedFile = fopen(fileNameToOpen, "rb")) != NULL)
        {
            fclose(readedFile);
            printf("%s\n", fileNameToOpen);
            completeLoadFile += read_file(fileNameToOpen);
        }
        else
        {
            printf("%s\n", fileNameToOpen);
        }
    }


    fclose(file);
    return completeLoadFile;
}