#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *file1, *file2;
    char fileName[31];
    long index = 0;
    long numIndex = 0;
    long numArea = 0;
    int numLine = 0;
    char c;

    printf("Podaj nazwe pliku:\n");
    scanf("%30s", fileName);
    if((file1 = fopen(fileName, "rb")) == NULL)
    {
        printf("Couldn't open file\n");
        return 4;
    }
    if((file2 = fopen(fileName, "rb")) == NULL)
    {
        printf("Couldn't open file\n");
        fclose(file1);
        return 4;
    }

    //Sprawdzenie rozmiaru pliku
    fseek(file1, 0l, SEEK_END);
    long size = ftell(file1);
    fseek(file1, 0L, SEEK_SET);

    //Sprawdzenie ilosci lini w text
    while((c = fgetc(file1)) != EOF)
    {
        if(c == '\n')
            numLine++;
    }
    //printf("%d\n", numLine);
    if (numLine < 2)
    {
        printf("File corrupted\n");
        fclose(file1);
        fclose(file2);
        return 6;
    }

    //Spradzeni indeksu obszaru liczb
    fseek(file1, 0L, SEEK_SET);
    while(fgetc(file1) != '\n')
    {
        numArea++;
    }

    //Sprawdzenie czy w pierwszej lini są tylko cyfry
    fseek(file1, 0L, SEEK_SET);
    while((c = fgetc(file1)) != '\n')
    {
        if(isdigit(c) != 0 || isspace(c) != 0)
        {
            //printf("%c --> Jest cyfrą lub znakiem białym\n", c);
        }
        else
        {
            printf("File corrupted\n");
            fclose(file1);
            fclose(file2);
            return 6;
        }
    }

    //Sprawdzenie czy index nie jest po za obszarem tekstu
    fseek(file1, 0L, SEEK_SET);
    while(fscanf(file1, "%ld", &index) != 0)
    {
        if(index <= numArea || index >= size)
        {
            printf("File corrupted\n");
            fclose(file1);
            fclose(file2);
            return 6;
        }
        numIndex++;
    }

    //Sprawdzenie czy brak indexow
    if(numIndex == 0)
    {
        printf("File corrupted\n");
        fclose(file1);
        fclose(file2);
        return 6;
    }

    //Wczytywanie teksu
    fseek(file1, 0L, SEEK_SET);
    while(fscanf(file1, "%ld", &index) != 0)
    {
        fseek(file2,index,SEEK_SET);
        c = fgetc(file2);
        printf("%c", c);
        fseek(file2, 0L, SEEK_SET);
    }

    //Zamkniecie plikow i koniec programu
    fclose(file1);
    fclose(file2);
    return 0;
}
