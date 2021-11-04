#include <stdio.h>

void clean_stdin(void);

int main()
{
    FILE *f_in;
    FILE *f_out;
    char file_name[31];
    char c;
    printf("Podaj nazwe pliku wejsciowego:\n");
    scanf("%30s", file_name);
    if((f_in = fopen(file_name, "r")) == NULL)
    {
        printf("Couldn't open file\n");
        return 4;
    }

    clean_stdin();

    printf("Podaj nazwe pliku wyjsciowego:\n");
    scanf("%30s", file_name);
    if((f_out = fopen(file_name, "w")) == NULL)
    {
        printf("Couldn't create file\n");

        fclose(f_in);
        return 5;
    }

    c = fgetc(f_in);
    while(c != EOF)
    {
        putc(c,f_out);
        c = fgetc(f_in);
    }

    printf("File copied\n");
    fclose(f_in);
    fclose(f_out);

    return 0;
}

void clean_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    }while(c != '\n' && c != EOF);
}