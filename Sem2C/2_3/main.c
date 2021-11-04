#include <stdio.h>

struct point_t
{
    int x;
    int y;
};

int save_points_b(const char *filename, const struct point_t* p, unsigned int N);
struct point_t* read(struct point_t* p);

int main() {
    //Zmienne
    int numOfPoints;
    int x = 0;
    struct point_t punkt[100];
    char fileName[31];

    //Wczytanie ilosci liczb max 100
    printf("Podaj liczbe punktów do wczytania: ");
    if((scanf("%d", &numOfPoints) != 1))
    {
        printf("Incorrect input\n");
        return 1;
    }
    if(numOfPoints < 1)
    {
        printf("Incorrect input data\n");
        return 2;
    }
    if (numOfPoints  > 100) numOfPoints = 100;

    //Wczytanie danych
    printf("Podaj punkty:\n");
    do {
        if(read(punkt + x) ==  NULL)
        {
            printf("Incorrect input\n");
            return 1;
        }
        x++;
    }while (x < numOfPoints && x < 100);

    //Wczytanie nazwy pliku do zapisu
    printf("Podaj plik do zapisu: ");
    scanf("%30s", fileName);

    //Zapis danych do pliku
    int errorNum = save_points_b(fileName, punkt, numOfPoints);
    if(errorNum == 2 || errorNum == 3)
    {
        printf("Couldn't create file\n");
        return 5;
    }

    printf("File saved\n");
    return 0;
}

int save_points_b(const char *filename, const struct point_t* p, unsigned int N)
{
    FILE *file;
    int x = 0;
    int fileSaved = 0;

    //Sprawdzenie danych wejsciowych
    if(filename == NULL || p == NULL || N < 1)
    {
        return 1;
    }

    //Otworzenie pliku binarnego
    if((file = fopen(filename, "wb")) == NULL)
    {
        return 2;
    }

    //Pętla zapisująca dane do pliku
    do {
        size_t saveFile = fwrite(p+x, sizeof(struct point_t), 1, file);
        fileSaved += saveFile;
        x++;
    }while (x < (int)N);

    //Sprawdzenie ilości zapisnaych danych
    if(fileSaved != (int)N)
    {
        return 3;
    }

    //Zamknięcie pliku i koniec funkcji
    fclose(file);
    return 0;
}
struct point_t* read(struct point_t* p)
{
    //Sprawdzenie danych wejsciowych
    if(p == NULL)
    {
        return NULL;
    }

    //Wczytanie danych od uzytkownika
    if(scanf("%d %d", &p->x, &p->y) != 2)
    {
        return NULL;
    }
    //Zwrocenie wypełnionej struktury
    return p;
}