#include <stdio.h>

int file_size_from_path(const char *path);
int file_size_from_file(FILE *f);

int main()
{
    FILE *file;
    char file_name[31];
    printf("Nazwa pliku: \n");
    scanf("%30s", file_name);

    int firstFun = file_size_from_path(file_name);
    file = fopen(file_name, "r");
    int secoundFun = file_size_from_file(file);

    if(firstFun == -1 || firstFun == -2)
    {
        printf("Couldn't open file");
        return 4;
    }
    if(secoundFun == -1 || secoundFun == -2)
    {
        printf("Couldn't open file");
        return 4;
    }
    if(firstFun == secoundFun)
    {
        printf("Rozmiar pliku wynosi %d bajtow\n", firstFun);
    }
    else
    {
        printf("Error\n");
    }
    
    fclose(file);
    return 0;
}

int file_size_from_path(const char *path)
{
    FILE *fileToFind;
    if(path == NULL)
        return -2;

    if ((fileToFind = fopen(path,"r")) == NULL)
        return -1;

    fseek(fileToFind,0L,SEEK_END);
    long size = ftell(fileToFind);
    fclose(fileToFind);
    return size;
}

int file_size_from_file(FILE *f)
{
    int size = 0;
    int position = 0;
    if(f == NULL)
        return -2;
    position = ftell(f);
    fseek(f, 0L, SEEK_SET);
    fseek(f, 0L, SEEK_END);
    size = ftell(f);
    fseek(f, position, SEEK_SET);
    return size;
}
