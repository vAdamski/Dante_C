//
// Created by Adam Ludwiczak on 28/05/2021.
//

#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void clean_stdin(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
int power(int base, int a) {
    if (a != 0)
        return (base * power(base, a - 1));
    else
        return 1;
}
int decode(const char * filename, char *txt, int size)
{
    if(filename == NULL || txt == NULL || size < 1)
        return 1;

    FILE *file;
    int read_number;
    int x = 0;
    int number_ASCII = 0;
    int len_text = 0;

    //Otiwranie pliku
    if((file = fopen(filename, "r")) == NULL)
        return 2;

    while (1)
    {
        if (fscanf(file, "%d", &read_number) != 1)
        {
            fclose(file);
            return 3;
        }

        if (len_text >= size - 1)
            break;

        if (ferror(file) != 0)
        {
            fclose(file);
            return 3;
        }

        if(read_number % 2 == 1)
        {
            number_ASCII += power(2, 7 - x);
            x++;
        }
        else
        {
            x++;
        }

        if(x == 8)
        {
            *(txt+len_text) = (char)number_ASCII;
            number_ASCII= 0;
            x = 0;
            len_text++;
        }
    }
    *(txt + size - 1) = '\0';
    fclose(file);
    return 0;
}
int encode(const char *input, char *txt, const char *output)
{
    if (input == NULL || txt == NULL || output == NULL)
        return 1;

    FILE *file1, *file2;
    int error;
    int numsInFile = 0;

    if ((file1 = fopen(input, "r")) == NULL)
        return 2;

    if ((file2 = fopen(output, "w")) == NULL)
    {
        fclose(file1);
        return 4;
    }



    int readNumber = 0;
    int size = 0;

    while (fscanf(file1, "%d", &readNumber) == 1)
    {
        numsInFile++;
    }

    int txtSize = (int)strlen(txt);
    //printf("Wieklkosc textu do zapisu: %d\n", txtSize);
    //printf("Ilosc liczb w pliku: %d\n", numsInFile);
    //printf("Tyle znakow mozna zapisac: %d\n", numsInFile / 8);

    if(numsInFile / 8 <= txtSize)
    {
        fclose(file1);
        fclose(file2);
        return 3;
    }

    fseek(file1, 0L, SEEK_SET);
    char c;
    int width = 0;
    int height;
    while ((c = fgetc(file1)) != '\n')
    {
        if(c == ' ') width++;
    }
    //Bo jedna wiecej liczba
    //width++;
    //printf("Szerkokosc (ilosc liczb w lini): %d\n", width);
    height = numsInFile / width;
    //printf("Wysokosc: %d\n", height);

    fseek(file1, 0L, SEEK_SET);
    int heightFile = 0;
    while((error = fscanf(file1, "%d", &readNumber)) != EOF)
    {
        if (!error)
        {
            fclose(file1);
            fclose(file2);
            return 3;
        }
        if (size % width == 0 && heightFile < height && size > 0)
        {
            fprintf(file2,"%c",'\n');
            heightFile++;
        }
        if (size <= txtSize * 8)
        {
            readNumber = (readNumber & 0xFE) | ((*(txt + (size / 8)) & 1 << (7 - size % 8)) > 0);
        }
        else
        {
            if(readNumber % 2 == 1)
            {
                readNumber--;
            }
        }
        error = fprintf(file2, "%d ", readNumber);
        if (!error)
        {
            fclose(file1);
            fclose(file2);
            return 3;
        }
        size++;
    }

    fclose(file1);
    fclose(file2);
    return 0;
}