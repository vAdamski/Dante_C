#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int concatenate(char *res, int s, int n, ...) {
    if (res == NULL || s <= 0 || n <= 0) {
        return 1;
    }
    unsigned int size = (unsigned int) s;
    va_list list;
            va_start(list, n);
    char *txt = va_arg(list, char*);
    if (strlen(txt) >= size) {
                va_end(list);
        return 2;
    }
    strcpy(res, txt);
    int i;
    for (i = 1; i < n; i++) {
        txt = va_arg(list, char*);
        if (strlen(res) + 1 >= size) {
                    va_end(list);
            return 2;
        }
        strcat(res, " ");
        if (strlen(res) + strlen(txt) >= size) {
                    va_end(list);
            return 2;
        }
        strcat(res, txt);

    }
            va_end (list);
    return 0;
}

void loadText(char *txt, int max) {
    int n = 0;
    while (1) {
        char c = getchar();
        if (c == '\n') {
            break;
        }
        if (n < max - 1) {
            *(txt + n) = c;
            n++;
        }
    }
    *(txt + n) = '\0';
}

int main() {
    char *target = malloc(4004);
    if (target == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    char **inputs = malloc(sizeof(char *) * 4);
    if (inputs == NULL) {
        free(target);
        printf("Failed to allocate memory");
        return 8;
    }
    *(inputs) = malloc(1001);
    if (*(inputs) == NULL) {
        free(target);
        free(inputs);
        printf("Failed to allocate memory");
        return 8;
    }
    *(inputs + 1) = malloc(1001);
    if (*(inputs + 1) == NULL) {
        free(*(inputs));
        free(target);
        free(inputs);
        printf("Failed to allocate memory");
        return 8;
    }
    *(inputs + 2) = malloc(1001);
    if (*(inputs + 2) == NULL) {
        free(*(inputs));
        free(*(inputs + 1));
        free(target);
        free(inputs);
        printf("Failed to allocate memory");
        return 8;
    }
    *(inputs + 3) = malloc(1001);
    if (*(inputs + 3) == NULL) {
        free(*(inputs));
        free(*(inputs + 1));
        free(*(inputs + 2));
        free(target);
        free(inputs);
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Ile: ");
    int ile;
    if (scanf("%d", &ile) != 1) {
        printf("Incorrect input");
        free(*(inputs));
        free(*(inputs + 1));
        free(*(inputs + 2));
        free(*(inputs + 3));

        free(target);
        free(inputs);
        return 1;
    }
    if (ile < 2 || ile > 4) {
        printf("Incorrect input data");
        free(*(inputs));
        free(*(inputs + 1));
        free(*(inputs + 2));
        free(*(inputs + 3));

        free(target);
        free(inputs);
        return 2;
    }
    getchar();
    printf("Podaj napisy: ");
    int i;
    for (i = 0; i < ile; i++) {
        loadText(*(inputs + i), 1001);
//        printf("'%s'\n", *(inputs + i));
    }
    if (ile == 2) {
        concatenate(target, 4005, 2, *(inputs), *(inputs + 1));
    }
    if (ile == 3) {
        concatenate(target, 4005, 3, *(inputs), *(inputs + 1), *(inputs + 2));
    }
    if (ile == 4) {
        concatenate(target, 4005, 4, *(inputs), *(inputs + 1), *(inputs + 2), *(inputs + 3));
    }

    printf("%s", target);
    free(*(inputs));
    free(*(inputs + 1));
    free(*(inputs + 2));
    free(*(inputs + 3));
    free(target);
    free(inputs);
    return 0;
}
