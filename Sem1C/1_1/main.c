#include <stdio.h>
#include <stdlib.h>

int main()
{
    char file_name[31];
    char c;
    int charsInText = 0;
    FILE *file;

    printf("Nazwa pliku: \n");
    scanf("%30s", file_name);

    if ((file = fopen(file_name,"r")) == NULL){
        printf("Couldn't open file");
        return 4;
    }

    while((c = fgetc(file)) != EOF)
    {
        charsInText++;
        printf("%c", c);
    }
    if(charsInText == 0)
    {
        printf("Nothing to show");
    }

    fclose(file);

    return 0;
}