#include <stdio.h>

void clean_stdin(void);

int main()
{
    FILE *f_in;
    FILE *f_out;
    char file_name[31];
    char c;
    int size;

    //Wczytanie pliku wejściowego
    printf("Podaj nazwe pliku wejsciowego:\n");
    scanf("%30s", file_name);
    if((f_in = fopen(file_name, "r")) == NULL)
    {
        printf("Couldn't open file\n");
        return 4;
    }

    //Sprawdzenie wielkości pliku wejściowego
    fseek(f_in, 0l, SEEK_END);
    size = ftell(f_in);
    fseek(f_in, 0l, SEEK_SET);

    //Wyczyszczenie bufforu
    clean_stdin();

    //Wczytanie pliku wyjściowego
    printf("Podaj nazwe pliku wyjsciowego:\n");
    scanf("%30s", file_name);
    if((f_out = fopen(file_name, "w")) == NULL)
    {
        printf("Couldn't create file\n");

        fclose(f_in);
        return 5;
    }

    //Nadpisywanie pliku
    for(int i = size - 1; i >= 0; i--)
    {
        fseek(f_in, i, SEEK_SET);
        c = getc(f_in);
        fputc(c, f_out);
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