#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

int main() {
    struct doubly_linked_list_t *list = dll_create();
    if (list == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    while (1) {
        printf("Operacja: ");
        int i;
        if (scanf("%d", &i) != 1) {
            printf("Incorrect input");
            dll_clear(list);
            free(list);
            return 1;
        }
        int err, pos;
        switch (i) {
            case 0:
                dll_clear(list);
                free(list);
                return 0;
                break;
            case 1:
                printf("Podaj liczbe: ");
                if (scanf("%d", &i) != 1) {
                    printf("Incorrect input");
                    dll_clear(list);
                    free(list);
                    return 1;
                }
                err = dll_push_back(list, i);
                if (err != 0) {
                    printf("Failed to allocate memory");
                    dll_clear(list);
                    free(list);
                    return 8;
                }
                break;
            case 2:
                i = dll_pop_back(list, &err);
                if (err == 0) {
                    printf("%d\n", i);
                } else {
                    printf("List is empty\n");
                }
                break;
            case 3:
                printf("Podaj liczbe: ");
                if (scanf("%d", &i) != 1) {
                    printf("Incorrect input");
                    dll_clear(list);
                    free(list);
                    return 1;
                }
                err = dll_push_front(list, i);
                if (err != 0) {
                    printf("Failed to allocate memory");
                    dll_clear(list);
                    free(list);
                    return 8;
                }
                break;
            case 4:
                i = dll_pop_front(list, &err);
                if (err == 0) {
                    printf("%d\n", i);
                } else {
                    printf("List is empty\n");
                }
                break;
            case 5:
                printf("Podaj liczbe: ");
                if (scanf("%d", &i) != 1) {
                    printf("Incorrect input");
                    dll_clear(list);
                    free(list);
                    return 1;
                }
                printf("Podaj liczbe: ");
                if (scanf("%d", &pos) != 1) {
                    printf("Incorrect input");
                    dll_clear(list);
                    free(list);
                    return 1;
                }
                err = dll_insert(list, pos, i);
                if (err != 0) {
                    if (err == 2) {
                        dll_clear(list);
                        free(list);
                        printf("Failed to allocate memory");
                        return 8;
                    }
                    printf("Index out of range\n");
                }
                break;
            case 6:
                if (dll_is_empty(list)) {
                    printf("List is empty\n");
                    break;
                }
                printf("Podaj liczbe: ");
                if (scanf("%d", &i) != 1) {
                    printf("Incorrect input");
                    dll_clear(list);
                    free(list);
                    return 1;
                }
                i = dll_remove(list, i, &err);
                if (err == 0) {
                    printf("%d\n", i);
                } else {
                    printf("Index out of range\n");
                }
                break;
            case 7:
                if (dll_is_empty(list)) {
                    printf("List is empty\n");
                    break;
                }
                printf("%d\n", dll_back(list, NULL));
                break;
            case 8:
                if (dll_is_empty(list)) {
                    printf("List is empty\n");
                    break;
                }
                printf("%d\n", dll_front(list, NULL));
                break;
            case 9:
                if (dll_is_empty(list)) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
                break;
            case 10:
                printf("%d\n", dll_size(list));
                break;
            case 11:
                dll_clear(list);
                break;
            case 12:
                if (dll_is_empty(list)) {
                    printf("List is empty\n");
                    break;
                }
                printf("Podaj liczbe: ");
                if (scanf("%d", &i) != 1) {
                    printf("Incorrect input");
                    dll_clear(list);
                    free(list);
                    return 1;
                }
                i = dll_at(list, i, &err);
                if (err == 0) {
                    printf("%d\n", i);
                } else {
                    printf("Index out of range\n");
                }
                break;
            case 13:
                if (dll_is_empty(list)) {
                    printf("List is empty\n");
                    break;
                }
                dll_display(list);
                break;
            case 14:
                if (dll_is_empty(list)) {
                    printf("List is empty\n");
                    break;
                }
                dll_display_reverse(list);
                break;
            default:
                printf("Incorrect input data\n");
        }
    }
    return 0;
}
