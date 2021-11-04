#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *napis = malloc(1);
    if (napis == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    *napis = '\0';
    printf("Podaj tekst");
    while (1) {
        char c = getchar();
        if (c == '\n') {
            break;
        }
        char *n = realloc(napis, strlen(napis) + 2);
        if (n == NULL) {
            printf("%s", napis);
            free(napis);
            return 0;
        }
        napis = n;
        *(napis + strlen(napis) + 1) = '\0';
        *(napis + strlen(napis)) = c;
    }
    printf("%s", napis);
    free(napis);
    return 0;
}