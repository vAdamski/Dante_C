#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

int main() {
    struct doubly_linked_list_t *dll1 = dll_create();
    if (dll1 == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    struct doubly_linked_list_t *dll2 = dll_create();
    if (dll2 == NULL) {
        printf("Failed to allocate memory");
        free(dll1);
        return 8;
    }
    printf("Podawaj liczby ");
    while (1) {
        int n;
        if (scanf("%d", &n) != 1) {
            printf("Incorrect input");
            dll_clear(dll1);
            free(dll1);
            free(dll2);
            return 1;
        }
        if (n == -1) {
            break;
        }
        if (dll_push_back(dll1, n) != 0) {
            printf("Failed to allocate memory");
            dll_clear(dll1);
            free(dll1);
            free(dll2);
            return 8;
        }
    }
    printf("Podawaj liczby ");
    while (1) {
        int n;
        if (scanf("%d", &n) != 1) {
            printf("Incorrect input");
            dll_clear(dll1);
            dll_clear(dll2);
            free(dll1);
            free(dll2);
            return 1;
        }
        if (n == -1) {
            break;
        }
        if (dll_push_back(dll2, n) != 0) {
            printf("Failed to allocate memory");
            dll_clear(dll1);
            dll_clear(dll2);
            free(dll1);
            free(dll2);
            return 8;
        }
    }

    if (dll_is_empty(dll1) && dll_is_empty(dll2)) {
        printf("Not enough data available");
        dll_clear(dll1);
        dll_clear(dll2);
        free(dll1);
        free(dll2);
        return 3;
    }

    int n;
    printf("jak?");
    if (scanf("%d", &n) != 1) {
        dll_clear(dll1);
        dll_clear(dll2);
        free(dll1);
        free(dll2);
        printf("Incorrect input");
        return 1;
    }

    if (n < 0 || n > 2) {
        dll_clear(dll1);
        dll_clear(dll2);
        free(dll1);
        free(dll2);
        printf("Incorrect input data");
        return 2;
    }

    if (n == 0) {
        dll_concat_zip(dll1, dll2);
    }
    if (n == 1) {
        dll_concat_begin(dll1, dll2);
    }
    if (n == 2) {
        dll_concat_end(dll1, dll2);
    }

    dll_display(dll1);
    dll_display_reverse(dll1);

    dll_clear(dll1);
    dll_clear(dll2);
    free(dll1);
    free(dll2);
    return 0;
}
