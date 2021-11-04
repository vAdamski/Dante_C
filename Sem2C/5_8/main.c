#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

int main() {
    char *buffer = malloc(50);
    if (buffer == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    int err;
    printf("Podaj nazwe pliku: ");
    scanf("%49[^\n]", buffer);
    FILE *file = fopen(buffer, "rt");
    if (file == NULL) {
        free(buffer);
        printf("Couldn't open file");
        return 4;
    }
    struct dictionary_t *dict = create_dictionary(10, &err);
    if (err != 0) {
        printf("Failed to allocate memory");
        free(buffer);
        fclose(file);
        return 8;
    }
    int len = 0;
    while (1) {
        char c = fgetc(file);
//        printf("%c", c);
        if (feof(file)) {
            if (len != 0) {
                *(buffer + len) = '\0';
                if (dictionary_add_word(dict, buffer)) {
                    printf("Failed to allocate memory");
                    destroy_dictionary(&dict);
                    free(buffer);
                    fclose(file);
                    return 8;
                }
            }
            break;
        }
        if (isalpha(c) && len < 50) {
            *(buffer + len) = c;
            len++;
        } else if (len > 0) {
            *(buffer + len) = '\0';
            if (dictionary_add_word(dict, buffer)) {
                printf("Failed to allocate memory");
                destroy_dictionary(&dict);
                free(buffer);
                fclose(file);
                return 8;
            }
            len = 0;
        }
    }
    if (dict->size == 0) {
        printf("Nothing to show\n");
    } else
        dictionary_display(dict);
    fclose(file);
    destroy_dictionary(&dict);
    free(buffer);
    return 0;
}