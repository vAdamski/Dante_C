#include <stdio.h>

int main()
{
    FILE *file;
    char file_path[31];

    printf("Podaj nazwe pliku wyjsciowego:\n");
    scanf("%30s", file_path);
    if((file = fopen(file_path, "w")) == NULL)
    {
        printf("Couldn't create file\n");
        return 5;
    }

    for(int i = 0; i < 101; i++)
    {
        fprintf(file, "%d", i);
        fputc('\n', file);
    }


    printf("File saved\n");
    fclose(file);

    return 0;
}
