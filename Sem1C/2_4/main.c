#include <stdio.h>
#include <math.h>
#include <ctype.h>

struct point_t{
    int x;
    int y;
};

float distance(const struct point_t* p1, const struct point_t* p2, int *err_code);

int main()
{
    FILE *file1, *file2;
    struct point_t p1;
    struct point_t p2;
    struct point_t best_p1;
    struct point_t best_p2;
    char filename[100];
    float distance_p1p2 = 2000000.0;
    int error_code;
    char c;



    printf("Podaj plik do odczytu punktow:\n");
    scanf("%99s", filename);

    //Otwieranie pliku
    if((file1 = fopen(filename, "r")) == NULL)
    {
        printf("Couldn't open file\n");
        return 4;
    }

    if((file2 = fopen(filename, "r")) == NULL)
    {
        printf("Couldn't open file\n");
        fclose(file1);
        return 4;
    }

    while((c = fgetc(file1)) != EOF)
    {
        if(isalpha(c) != 0)
        {
            printf("File corrupted\n");
            fclose(file1);
            fclose(file2);
            return 6;
        }
    }

    fseek(file1, 0, SEEK_SET);

    int count = 0;
    while (fscanf(file1, "%d %d", &p1.x, &p1.y) == 2 && !ferror(file2))
    {
        count++;
        fseek(file2, ftell(file1), SEEK_SET);

        while (fscanf(file2, "%d %d", &p2.x, &p2.y) == 2 && !ferror(file1))
        {

            float dist = distance(&p1, &p2, &error_code);

            if(dist < distance_p1p2)
            {
                distance_p1p2 = dist;
                best_p1.x = p1.x;
                best_p1.y = p1.y;
                best_p2.x = p2.x;
                best_p2.y = p2.y;
            }
            if (dist == distance_p1p2)
            {
                int current_x = p1.x < p2.x ? p1.x : p2.x;
                int best_x = best_p1.x < best_p2.x ? best_p1.x : best_p2.x;
                if (current_x < best_x) {
                    distance_p1p2 = dist;
                    best_p1.x = p1.x;
                    best_p1.y = p1.y;
                    best_p2.x = p2.x;
                    best_p2.y = p2.y;
                }
            }
        }
    }

    if (count < 2) {
        fclose(file1);
        fclose(file2);
        printf("File corrupted\n");
        return 6;
    }

    if (ferror(file1) || ferror(file2)) {
        fclose(file1);
        fclose(file2);
        printf("File corrupted\n");
        return 6;
    }

    printf("%d %d %d %d\n", best_p2.x, best_p2.y, best_p1.x, best_p1.y);

    fclose(file1);
    fclose(file2);

    return 0;
}

float distance(const struct point_t* p1, const struct point_t* p2, int *err_code)
{
    if(p1 == NULL || p2 == NULL)
    {
        if(err_code == NULL)
            return -1;
        else
        {
            *err_code = 1;
            return -1;
        }
    }

    float dist = sqrtf(powf((float)p2->x - (float)p1->x, 2) + powf((float)p2->y - (float)p1->y, 2));

    if(err_code != NULL)
    {
        if(dist >= 0)
        {
            *err_code = 0;
        }
        else
        {
            *err_code = 1;
        }
    }

    return dist;
}