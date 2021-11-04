#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct point_t* set(struct point_t* p, int x, int y);
void show(const struct point_t* p);
int save_point_b(const char *filename, const struct point_t* p);
int load_point_b(const char *filename, struct point_t* p);
int save_point_t(const char *filename, const struct point_t* p);
int load_point_t(const char *filename, struct point_t* p);
void clean_stdin(void);

struct point_t {
    int x;
    int y;
};

int main()
{
    time_t time_s;
    srand(time(&time_s));
    struct point_t punkt;
    char fileName[31];
    char odp;
    char *fileExtension;

    //Generowanie struktury
    set(&punkt, rand()%100+1, rand()%100+1);
    show(&punkt);

    //Generownie zapytan o plik
    printf("Podaj nazwe pliku:\n");
    scanf("%30s", fileName);
    fileExtension = strpbrk(fileName, ".");
    if(fileExtension == NULL)
    {
        printf("Unsupported file format\n");
        return 7;
    }

    if(strcmp(fileExtension, ".txt") == 0)
    {
        int error = save_point_t(fileName, &punkt);
        if(error == 2)
        {
            printf("Couldn't create file\n");
            return 5;
        }
        else if(error == 0)
        {
            printf("File saved\n");
        }
    }
    else if (strcmp(fileExtension, ".bin") == 0)
    {
        int error = save_point_b(fileName, &punkt);
        if(error == 2)
        {
            printf("Couldn't create file\n");
            return 5;
        }
        else if(error == 0)
        {
            printf("File saved\n");
        }
    }
    else
    {
        printf("Unsupported file format\n");
        return 7;
    }

    //Odczytwanie danych z pliku
    printf("Do you want to read the file (Y/N)? ");
    clean_stdin();
    odp = getchar();
    clean_stdin();
    if(odp == 'y' || odp == 'Y')
    {
        if(strcmp(fileExtension, ".txt") == 0)
        {
            int error = load_point_t(fileName, &punkt);
            if(error == 2)
            {
                printf("Couldn't open file\n");
                return 4;
            } else if (error == 3)
            {
                printf("File corrupted\n");
                return 6;
            }
            show(&punkt);
        }
        else if (strcmp(fileExtension, ".bin") == 0)
        {
            int error = load_point_b(fileName, &punkt);
            if(error == 2)
            {
                printf("Couldn't open file\n");
                return 4;
            } else if (error == 3)
            {
                printf("File corrupted\n");
                return 6;
            }
            show(&punkt);
        }
    }
    else if(odp == 'n' || odp == 'N')
    {
        return 0;
    }
    else
    {
        printf("Incorrect input\n");
        return 1;
    }
}

struct point_t* set(struct point_t* p, int x, int y)
{
    if(p == NULL)
        return NULL;

    p->x = x;
    p->y = y;

    return p;
}
void show(const struct point_t* p)
{
    if(p == NULL)
        return;
    printf("x = %d; y = %d\n", p->x, p->y);
}
int save_point_b(const char *filename, const struct point_t* p)
{
    FILE *file;
    if(filename == NULL || p == NULL)
        return 1;
    if((file = fopen(filename, "wb")) == NULL)
        return 2;

    size_t fileSaved = fwrite(p, sizeof(struct point_t), 1, file);

    if(fileSaved == 0)
    {
        fclose(file);
        return 3;
    }
    fclose(file);
    return 0;
}
int load_point_b(const char *filename, struct point_t* p)
{
    FILE *file;
    if(filename == NULL || p == NULL)
        return 1;
    if((file = fopen(filename, "rb")) == NULL)
        return 2;

    size_t fileSaved = fread(p, sizeof(struct point_t), 1, file);
    if(fileSaved != 1)
    {
        fclose(file);
        return 3;
    }

    fclose(file);
    return 0;
}
int save_point_t(const char *filename, const struct point_t* p)
{
    FILE *file;
    if(filename == NULL || p == NULL)
        return 1;
    if((file = fopen(filename, "w")) == NULL)
        return 2;

    int fileSaved = fprintf(file,"%d %d", p->x, p->y);
    if(fileSaved < 0)
    {
        fclose(file);
        return 3;
    }

    fclose(file);
    return 0;
}
int load_point_t(const char *filename, struct point_t* p)
{
    FILE *file;
    if(filename == NULL || p == NULL)
        return 1;
    if((file = fopen(filename, "r")) == NULL)
        return 2;

    int fileSaved = fscanf(file, "%d %d", &p->x, &p->y);
    if(fileSaved != 2)
    {
        fclose(file);
        return 3;
    }

    fclose(file);
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
