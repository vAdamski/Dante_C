#ifndef DANTE_LINKED_LIST_H
#define DANTE_LINKED_LIST_H

struct node_t {
    int data;
    struct node_t *next;
    struct node_t *prev;
};

struct doubly_linked_list_t {
    struct node_t *head;
    struct node_t *tail;
};

struct doubly_linked_list_t *dll_create();

int dll_push_back(struct doubly_linked_list_t *ll, int value);

int dll_push_front(struct doubly_linked_list_t *ll, int value);

int dll_pop_front(struct doubly_linked_list_t *ll, int *err_code);

int dll_pop_back(struct doubly_linked_list_t *ll, int *err_code);

int dll_back(const struct doubly_linked_list_t *ll, int *err_code);

int dll_front(const struct doubly_linked_list_t *ll, int *err_code);

struct node_t *dll_begin(struct doubly_linked_list_t *ll);

struct node_t *dll_end(struct doubly_linked_list_t *ll);

int dll_size(const struct doubly_linked_list_t *ll);

int dll_is_empty(const struct doubly_linked_list_t *ll);

int dll_at(const struct doubly_linked_list_t *ll, unsigned int index, int *err_code);

int dll_insert(struct doubly_linked_list_t *ll, unsigned int index, int value);

int dll_remove(struct doubly_linked_list_t *ll, unsigned int index, int *err_code);

void dll_clear(struct doubly_linked_list_t *ll);

void dll_display(const struct doubly_linked_list_t *ll);


void dll_display_reverse(const struct doubly_linked_list_t *dll);

#endif //DANTE_LINKED_LIST_H
