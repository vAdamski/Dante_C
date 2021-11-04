#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

int validate(const struct doubly_linked_list_t *ll) {
    if (ll == NULL) {
        return 0;
    }
    return 1;
}

struct doubly_linked_list_t *dll_create() {
    struct doubly_linked_list_t *ll = malloc(sizeof(struct doubly_linked_list_t));
    if (ll == NULL) {
        return NULL;
    }
    ll->head = NULL;
    ll->tail = NULL;
    return ll;
}

int dll_push_back(struct doubly_linked_list_t *ll, int value) {
    if (!validate(ll)) {
        return 1;
    }
    struct node_t *node = malloc(sizeof(struct node_t));
    if (node == NULL) {
        return 2;
    }
    node->data = value;
    node->next = NULL;
    node->prev = ll->tail;
    if (ll->tail) {
        ll->tail->next = node;
    } else {
        ll->head = node;
    }
    ll->tail = node;
    return 0;
}

int dll_push_front(struct doubly_linked_list_t *ll, int value) {
    if (!validate(ll)) {
        return 1;
    }
    struct node_t *node = malloc(sizeof(struct node_t));
    if (node == NULL) {
        return 2;
    }
    node->data = value;
    node->next = ll->head;
    if (ll->head)
        ll->head->prev = node;
    node->prev = NULL;
    if (ll->tail == NULL) {
        ll->tail = node;
    }
    ll->head = node;
    return 0;
}

int dll_pop_front(struct doubly_linked_list_t *ll, int *err_code) {
    if (!validate(ll) || dll_is_empty(ll)) {
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
    if (ll->head)
        ll->head->prev = NULL;
    free(node);
    return val;
}

int dll_pop_back(struct doubly_linked_list_t *ll, int *err_code) {
    if (!validate(ll) || dll_is_empty(ll)) {
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

int dll_back(const struct doubly_linked_list_t *ll, int *err_code) {
    if (!validate(ll) || dll_is_empty(ll)) {
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

int dll_front(const struct doubly_linked_list_t *ll, int *err_code) {
    if (!validate(ll) || dll_is_empty(ll)) {
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

struct node_t *dll_begin(struct doubly_linked_list_t *ll) {
    if (!validate(ll) || dll_is_empty(ll)) {
        return NULL;
    }
    return ll->head;
}

struct node_t *dll_end(struct doubly_linked_list_t *ll) {
    if (!validate(ll) || dll_is_empty(ll)) {
        return NULL;
    }
    return ll->tail;
}

int dll_size(const struct doubly_linked_list_t *ll) {
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

int dll_is_empty(const struct doubly_linked_list_t *ll) {
    if (!validate(ll)) {
        return -1;
    }
    if (ll->head == NULL) {
        return 1;
    }
    return 0;
}

int dll_at(const struct doubly_linked_list_t *ll, unsigned int index, int *err_code) {
    if (!validate(ll) || dll_is_empty(ll) || (unsigned int) dll_size(ll) <= index) {
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

int dll_insert(struct doubly_linked_list_t *ll, unsigned int index, int value) {
    if (!validate(ll) || (index != 0 && (unsigned int) dll_size(ll) < index)) {
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
        n->prev = NULL;
        if (ll->head)
            ll->head->prev = n;
        ll->head = n;
        return 0;
    }
    if (idx == (unsigned int) dll_size(ll)) {
        n->prev = ll->tail;
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
    n->prev = node;
    node->next->prev = n;
    node->next = n;

    return 0;
}

int dll_remove(struct doubly_linked_list_t *ll, unsigned int index, int *err_code) {
    if (!validate(ll) || dll_is_empty(ll) || (unsigned int) dll_size(ll) <= index) {
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
        if (node->next)
            node->next->prev = NULL;
        if (ll->tail == node) {
            ll->tail = NULL;
        }
        free(node);
        return data;
    }
    for (i = 1; i < index; i++) {
        prev = prev->next;
    }
    node = prev->next;
    int data = node->data;
    prev->next = node->next;
    if (node->next)
        node->next->prev = prev;
    if (ll->tail == node) {
        ll->tail = prev;
    }
    free(node);
    return data;
}

void dll_clear(struct doubly_linked_list_t *ll) {
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

void dll_display(const struct doubly_linked_list_t *ll) {
    if (!validate(ll) || dll_is_empty(ll)) {
        return;
    }
    struct node_t *node = ll->head;
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void dll_display_reverse(const struct doubly_linked_list_t *dll) {
    if (!validate(dll) || dll_is_empty(dll)) {
        return;
    }
    struct node_t *node = dll->tail;
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->prev;
    }
    printf("\n");
}

int dll_concat_zip(struct doubly_linked_list_t *dll1, struct doubly_linked_list_t *dll2) {
    if (!validate(dll1) || !validate(dll2)) {
        return 1;
    }
    if (dll1->head == NULL) {
        dll1->head = dll2->head;
        dll1->tail = dll2->tail;
        dll2->head = NULL;
        dll2->tail = NULL;
        return 0;
    }
    if (dll2->head == NULL) {
        return 0;
    }
    int i;
    struct doubly_linked_list_t templist = {dll1->head, dll1->head};
    struct node_t *node1 = dll1->head->next;
    struct node_t *node2 = dll2->head;
    templist.head->prev = NULL;
    templist.head->next = NULL;
    for (i = 0; !(node1 == NULL && node2 == NULL); i++) {
        struct node_t *node;
        if (i % 2) {
            node = node1;
            if (node1 != NULL)
                node1 = node1->next;
        } else {
            node = node2;
            if (node2 != NULL)
                node2 = node2->next;
        }
        if (node != NULL) {
            templist.tail->next = node;
            node->prev = templist.tail;
            templist.tail = node;
            templist.tail->next = NULL;
        }
    }
    dll2->head = NULL;
    dll2->tail = NULL;
    dll1->head = templist.head;
    dll1->tail = templist.tail;
    return 0;
}

int dll_concat_begin(struct doubly_linked_list_t *dll1, struct doubly_linked_list_t *dll2) {
    if (!validate(dll1) || !validate(dll2)) {
        return 1;
    }
    if (dll1->head == NULL) {
        dll1->head = dll2->head;
        dll2->head = NULL;
        dll1->tail = dll2->tail;
        dll2->tail = NULL;
        return 0;
    }
    if (dll2->head == NULL) {
        return 0;
    }
    dll2->tail->next = dll1->head;
    dll1->head->prev = dll2->tail;
    dll1->head = dll2->head;
    dll2->head = NULL;
    dll2->tail = NULL;
    return 0;
}

int dll_concat_end(struct doubly_linked_list_t *dll1, struct doubly_linked_list_t *dll2) {
    if (!validate(dll1) || !validate(dll2)) {
        return 1;
    }
    if (dll1->head == NULL) {
        dll1->head = dll2->head;
        dll2->head = NULL;
        dll1->tail = dll2->tail;
        dll2->tail = NULL;
        return 0;
    }
    if (dll2->head == NULL) {
        return 0;
    }
    dll2->head->prev = dll1->tail;
    dll1->tail->next = dll2->head;
    dll1->tail = dll2->tail;
    dll2->head = NULL;
    dll2->tail = NULL;
    return 0;
}