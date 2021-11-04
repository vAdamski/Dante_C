#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

struct dictionary_t *create_dictionary(int N, int *err_code) {
    if (N <= 0) {
        if (err_code)*err_code = 1;
        return NULL;
    }
    if (err_code)*err_code = 0;
    struct dictionary_t *dict = malloc(sizeof(struct dictionary_t));
    if (dict == NULL) {
        if (err_code)*err_code = 2;
        return NULL;
    }
    dict->capacity = N;
    dict->size = 0;
    dict->wc = malloc(N * sizeof(struct word_count_t));
    if (dict->wc == NULL) {
        free(dict);
        if (err_code)*err_code = 2;
        return NULL;
    }
    return dict;
}

void destroy_dictionary(struct dictionary_t **d) {
    if (d == NULL) {
        return;
    }
    if (*d == NULL) {
        return;
    }
    if ((*d)->wc != NULL) {
        for(int i =0; i < (*d)->size;i++){
            free(((*d)->wc+i)->word);
        }
        free((*d)->wc);
    }
    free(*d);
}

struct word_count_t *dictionary_find_word(const struct dictionary_t *d, const char *word) {
    if (d == NULL || word == NULL || d->wc == NULL || d->size < 0 || d->capacity <= 0 || d->size > d->capacity) {
        return NULL;
    }
    for (int i = 0; i < d->size; i++) {
        if (strcmp((d->wc + i)->word, word) == 0) {
            return d->wc + i;
        }
    }
    return NULL;
}

int dictionary_add_word(struct dictionary_t *d, const char *word) {
    if (d == NULL || word == NULL || d->wc == NULL || d->size < 0 || d->capacity <= 0 || d->size > d->capacity) {
        return 1;
    }
    struct word_count_t *wc = dictionary_find_word(d, word);
    if (wc) {
        wc->counter++;
        return 0;
    }
    if (d->size == d->capacity) {
        struct word_count_t *newwc = realloc(d->wc, sizeof(struct word_count_t) * d->capacity * 2);
        if (newwc == NULL) {
            return 2;
        }
        d->wc = newwc;
        d->capacity *= 2;
    }
    wc = d->wc + d->size;
    wc->word = strdup(word);
    if (wc->word == NULL) {
        return 2;
    }
    wc->counter = 1;
    d->size++;
    return 0;
}

void dictionary_display(const struct dictionary_t *d) {
    if (d == NULL || d->wc == NULL || d->size < 0 || d->capacity <= 0 || d->size > d->capacity) {
        return;
    }
    for (int i = 0; i < d->size; i++) {
        struct word_count_t *wc = d->wc + i;
        printf("%s %d\n", wc->word, wc->counter);
    }
}
