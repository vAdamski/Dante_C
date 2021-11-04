#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

char *concatenate(int n, ...) {
    if (n <= 0) {
        return NULL;
    }
    char *res = NULL;
    va_list list;
            va_start(list, n);
    char *txt = va_arg(list, char*);
    res = malloc(strlen(txt) + 1);
    if (res == NULL) {
                va_end(list);
        return NULL;
    }
    strcpy(res, txt);
    int i;
    for (i = 1; i < n; i++) {
        txt = va_arg(list, char*);
        char *newPtr = realloc(res, strlen(res) + 2);
        if (newPtr == NULL) {
            free(res);
                    va_end(list);
            return NULL;
        }
        res = newPtr;
        strcat(res, " ");
        newPtr = realloc(res, strlen(res) + strlen(txt) + 1);
        if (newPtr == NULL) {
            free(res);
                    va_end(list);
            return NULL;
        }
        res = newPtr;
        strcat(res, txt);

    }
            va_end (list);
    return res;
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
    char *target;
    char **inputs = malloc(sizeof(char *) * 4);
    if (inputs == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    *(inputs) = malloc(1001);
    if (*(inputs) == NULL) {
        free(inputs);
        printf("Failed to allocate memory");
        return 8;
    }
    *(inputs + 1) = malloc(1001);
    if (*(inputs + 1) == NULL) {
        free(*(inputs));
        free(inputs);
        printf("Failed to allocate memory");
        return 8;
    }
    *(inputs + 2) = malloc(1001);
    if (*(inputs + 2) == NULL) {
        free(*(inputs));
        free(*(inputs + 1));
        free(inputs);
        printf("Failed to allocate memory");
        return 8;
    }
    *(inputs + 3) = malloc(1001);
    if (*(inputs + 3) == NULL) {
        free(*(inputs));
        free(*(inputs + 1));
        free(*(inputs + 2));
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
        free(inputs);
        return 1;
    }
    if (ile < 2 || ile > 4) {
        printf("Incorrect input data");
        free(*(inputs));
        free(*(inputs + 1));
        free(*(inputs + 2));
        free(*(inputs + 3));
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
        target = concatenate(2, *(inputs), *(inputs + 1));
    }
    if (ile == 3) {
        target = concatenate(3, *(inputs), *(inputs + 1), *(inputs + 2));
    }
    if (ile == 4) {
        target = concatenate(4, *(inputs), *(inputs + 1), *(inputs + 2), *(inputs + 3));
    }

    if (target != NULL) {
        printf("%s", target);
        free(target);
    } else {
        printf("Failed to allocate memory");
        free(*(inputs));
        free(*(inputs + 1));
        free(*(inputs + 2));
        free(*(inputs + 3));
        free(inputs);
        return 8;
    }
    free(*(inputs));
    free(*(inputs + 1));
    free(*(inputs + 2));
    free(*(inputs + 3));
    free(inputs);
    return 0;
}
