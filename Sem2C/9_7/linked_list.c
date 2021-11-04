#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

int validate(const struct linked_list_t *ll) {
    if (ll == NULL) {
        return 0;
    }
    return 1;
}

struct linked_list_t *ll_create() {
    struct linked_list_t *ll = malloc(sizeof(struct linked_list_t));
    if (ll == NULL) {
        return NULL;
    }
    ll->head = NULL;
    ll->tail = NULL;
    return ll;
}

int ll_push_back(struct linked_list_t *ll, int value) {
    if (!validate(ll)) {
        return 1;
    }
    struct node_t *node = malloc(sizeof(struct node_t));
    if (node == NULL) {
        return 2;
    }
    node->data = value;
    node->next = NULL;
    if (ll->tail) {
        ll->tail->next = node;
    } else {
        ll->head = node;
    }
    ll->tail = node;
    return 0;
}

int ll_push_front(struct linked_list_t *ll, int value) {
    if (!validate(ll)) {
        return 1;
    }
    struct node_t *node = malloc(sizeof(struct node_t));
    if (node == NULL) {
        return 2;
    }
    node->data = value;
    node->next = ll->head;
    if (ll->tail == NULL) {
        ll->tail = node;
    }
    ll->head = node;
    return 0;
}

int ll_pop_front(struct linked_list_t *ll, int *err_code) {
    if (!validate(ll) || ll_is_empty(ll)) {
        if (err_code) {
            *err_code = 1;
        }
        return 0;
    }
    if (err_code) {
        *err_code = 0;
    }
    int val = ll->head->data;
    struct node_t *node = ll->head;
    if (ll->head == ll->tail) {
        ll->tail = NULL;
    }
    ll->head = ll->head->next;
    free(node);
    return val;
}

int ll_pop_back(struct linked_list_t *ll, int *err_code) {
    if (!validate(ll) || ll_is_empty(ll)) {
        if (err_code) {
            *err_code = 1;
        }
        return 0;
    }
    if (err_code) {
        *err_code = 0;
    }
    int val = ll->tail->data;
    struct node_t *node = ll->tail;
    if (ll->head == ll->tail) {
        ll->head = NULL;
        ll->tail = NULL;
        free(node);
        return val;
    }
    struct node_t *prev = ll->head;
    while (prev->next != node) {
        prev = prev->next;
    }
    ll->tail = prev;
    prev->next = NULL;
    free(node);
    return val;
}

int ll_back(const struct linked_list_t *ll, int *err_code) {
    if (!validate(ll) || ll_is_empty(ll)) {
        if (err_code) {
            *err_code = 1;
        }
        return 0;
    }
    if (err_code) {
        *err_code = 0;
    }
    return ll->tail->data;
}

int ll_front(const struct linked_list_t *ll, int *err_code) {
    if (!validate(ll) || ll_is_empty(ll)) {
        if (err_code) {
            *err_code = 1;
        }
        return 0;
    }
    if (err_code) {
        *err_code = 0;
    }
    return ll->head->data;
}

struct node_t *ll_begin(struct linked_list_t *ll) {
    if (!validate(ll) || ll_is_empty(ll)) {
        return NULL;
    }
    return ll->head;
}

struct node_t *ll_end(struct linked_list_t *ll) {
    if (!validate(ll) || ll_is_empty(ll)) {
        return NULL;
    }
    return ll->tail;
}

int ll_size(const struct linked_list_t *ll) {
    if (!validate(ll)) {
        return -1;
    }
    struct node_t *node = ll->head;
    int size = 0;
    while (node != NULL) {
        node = node->next;
        size++;
    }
    return size;
}

int ll_is_empty(const struct linked_list_t *ll) {
    if (!validate(ll)) {
        return -1;
    }
    if (ll->head == NULL) {
        return 1;
    }
    return 0;
}

int ll_at(const struct linked_list_t *ll, unsigned int index, int *err_code) {
    if (!validate(ll) || ll_is_empty(ll) || (unsigned int) ll_size(ll) <= index) {
        if (err_code) {
            *err_code = 1;
        }
        return 0;
    }
    if (err_code) {
        *err_code = 0;
    }
    unsigned int i;
    struct node_t *node = ll->head;
    for (i = 0; i < index; i++) {
        node = node->next;
    }
    return node->data;
}

int ll_insert(struct linked_list_t *ll, unsigned int index, int value) {
    if (!validate(ll) || (index != 0 && (unsigned int) ll_size(ll) < index)) {
        return 1;
    }
    unsigned int idx = index;
    struct node_t *n = malloc(sizeof(struct node_t));
    if (n == NULL) {
        return 2;
    }
    n->data = value;
    if (index == 0) {
        if (ll->tail == NULL) {
            ll->tail = n;
        }
        n->next = ll->head;
        ll->head = n;
        return 0;
    }
    if (idx == (unsigned int) ll_size(ll)) {
        ll->tail->next = n;
        ll->tail = n;
        n->next = NULL;
        return 0;
    }
    unsigned int i;
    struct node_t *node = ll->head;
    for (i = 1; i < index; i++) {
        node = node->next;
    }
    n->next = node->next;
    node->next = n;

    return 0;
}

int ll_remove(struct linked_list_t *ll, unsigned int index, int *err_code) {
    if (!validate(ll) || ll_is_empty(ll) || (unsigned int) ll_size(ll) <= index) {
        if (err_code) {
            *err_code = 1;
        }
        return 0;
    }
    if (err_code) {
        *err_code = 0;
    }
    struct node_t *node;
    struct node_t *prev = ll->head;
    unsigned int i;
    if (index == 0) {
        if (ll->head == ll->tail) {
            ll->tail = NULL;
        }
        node = ll->head;
        int data = ll->head->data;
        ll->head = node->next;
        free(node);
        return data;
    }
    for (i = 1; i < index; i++) {
        prev = prev->next;
    }
    node = prev->next;
    int data = node->data;
    prev->next = node->next;
    free(node);
    return data;
}

void ll_clear(struct linked_list_t *ll) {
    if (!validate(ll)) {
        return;
    }
    struct node_t *node = ll->head;
    struct node_t *prev;
    while (node != NULL) {
        prev = node;
        node = node->next;
        free(prev);
    }
    ll->head = NULL;
    ll->tail = NULL;
}

void ll_display(const struct linked_list_t *ll) {
    if (!validate(ll) || ll_is_empty(ll)) {
        return;
    }
    struct node_t *node = ll->head;
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}