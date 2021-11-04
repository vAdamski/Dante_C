#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#include "format_type.h"

int main() {
    int **table, error;
    struct statistic_t *stats;
    char *filename = malloc(40*sizeof(char));
    if(filename == NULL)
    {
        printf("Failed to allocate memory\n");
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    printf("Podaj nazwe pliku: ");
    scanf("%39s", filename);

    char *lastFourChar = filename + (int)strlen(filename) - 4;

    if (strcmp(lastFourChar, ".txt") == 0)
    {
        error = load(filename, &table, fmt_text);
    }
    else if (strcmp(lastFourChar, ".bin") == 0)
    {
        error = load(filename, &table, fmt_binary);
    }
    else
    {
        printf("Unsupported file format\n");
        free(filename);
        return UNSUPPORTED_FILE_TYPE;
    }
    //Check load error
    switch (error)
    {
        case 2:
            printf("Couldn't open file\n");
            free(filename);
            return COULDNT_OPEN_FILE;
        case 3:
            printf("File corrupted\n");
            free(filename);
            return FILE_CORRUPTED;
        case 4:
            printf("Failed to allocate memory\n");
            free(filename);
            return FAILED_TO_ALLOCATE_MEMORY;
        default:
            break;
    }

    int size = statistics_row(table, &stats);

    for (int i = 0; i < size; ++i)
    {
        printf("%d %d %d %.2f %.2f\n", (stats+i)->min, (stats+i)->max, (stats+i)->range, (stats+i)->avg, (stats+i)->standard_deviation);
    }

    free(filename);
    free(stats);
    destroy(&table);
    return 0;
}
