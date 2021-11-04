#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"


int main() {
    struct doubly_linked_list_t *list = dll_create();
    if (list == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podawaj liczby");
    while (1) {
        int n;
        if (scanf("%d", &n) != 1) {
            printf("Incorrect input");
            dll_clear(list);
            free(list);
            return 1;
        }
        if (n == -1) {
            break;
        }
        if (dll_push_back(list, n)) {
            printf("Failed to allocate memory");
            dll_clear(list);
            free(list);
            return 8;
        }
    }
    if (list->head == NULL) {
        printf("Not enough data available");
        free(list);
        return 3;
    }
    int n;
    printf("a");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input");
        dll_clear(list);
        free(list);
        return 1;
    }
    if (n == 0) {
        dll_sort_asc(list);
    } else if (n == 1) {
        dll_sort_desc(list);
    } else {
        dll_clear(list);
        free(list);
        printf("Incorrect input data");
        return 2;
    }
    dll_display(list);
    dll_display_reverse(list);
    dll_clear(list);
    free(list);
    return 0;
}
