#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main() {
    struct linked_list_t *list = ll_create();
    if (list == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    while (1) {
        printf("Operacja: ");
        int i;
        if (scanf("%d", &i) != 1) {
            printf("Incorrect input");
            ll_clear(list);
            free(list);
            return 1;
        }
        int err, pos;
        switch (i) {
            case 0:
                ll_clear(list);
                free(list);
                return 0;
                break;
            case 1:
                printf("Podaj liczbe: ");
                if (scanf("%d", &i) != 1) {
                    printf("Incorrect input");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                err = ll_push_back(list, i);
                if (err != 0) {
                    printf("Failed to allocate memory");
                    ll_clear(list);
                    free(list);
                    return 8;
                }
                break;
            case 2:
                i = ll_pop_back(list, &err);
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
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                err = ll_push_front(list, i);
                if (err != 0) {
                    printf("Failed to allocate memory");
                    ll_clear(list);
                    free(list);
                    return 8;
                }
                break;
            case 4:
                i = ll_pop_front(list, &err);
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
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                printf("Podaj liczbe: ");
                if (scanf("%d", &pos) != 1) {
                    printf("Incorrect input");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                err = ll_insert(list, pos, i);
                if (err != 0) {
                    if (err == 2) {
                        ll_clear(list);
                        free(list);
                        printf("Failed to allocate memory");
                        return 8;
                    }
                    printf("Index out of range\n");
                }
                break;
            case 6:
                if (ll_is_empty(list)) {
                    printf("List is empty\n");
                    break;
                }
                printf("Podaj liczbe: ");
                if (scanf("%d", &i) != 1) {
                    printf("Incorrect input");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                i = ll_remove(list, i, &err);
                if (err == 0) {
                    printf("%d\n", i);
                } else {
                    printf("Index out of range\n");
                }
                break;
            case 7:
                if (ll_is_empty(list)) {
                    printf("List is empty\n");
                    break;
                }
                printf("%d\n", ll_back(list, NULL));
                break;
            case 8:
                if (ll_is_empty(list)) {
                    printf("List is empty\n");
                    break;
                }
                printf("%d\n", ll_front(list, NULL));
                break;
            case 9:
                if (ll_is_empty(list)) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
                break;
            case 10:
                printf("%d\n", ll_size(list));
                break;
            case 11:
                ll_clear(list);
                break;
            case 12:
                if (ll_is_empty(list)) {
                    printf("List is empty\n");
                    break;
                }
                printf("Podaj liczbe: ");
                if (scanf("%d", &i) != 1) {
                    printf("Incorrect input");
                    ll_clear(list);
                    free(list);
                    return 1;
                }
                i = ll_at(list, i, &err);
                if (err == 0) {
                    printf("%d\n", i);
                } else {
                    printf("Index out of range\n");
                }
                break;
            case 13:
                if (ll_is_empty(list)) {
                    printf("List is empty\n");
                    break;
                }
                ll_display(list);
                break;
            default:
                printf("Incorrect input data\n");
        }
    }
    return 0;
}
