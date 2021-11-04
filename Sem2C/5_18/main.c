#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int sort_sentences(char ***output);

int sort_words(char **words);

int split_sentences(const char *text, char ****output);

char **split_words(const char *text, unsigned len);

void destroy(char ***words);

void destroy2d(char **words);

int length_comparator(const void *a, const void *b);

int comparator(const void *a, const void *b);

int length_comparator(const void *a, const void *b) {
    const char **x1 = *(const char ***) a;
    const char **x2 = *(const char ***) b;

    size_t len1, len2;
    len1 = len2 = 0;

    for (size_t i = 0; *(x1 + i) != NULL; i++)
        len1++;

    for (size_t i = 0; *(x2 + i) != NULL; i++)
        len2++;

    if (len1 == len2)
        return 0;

    return len1 < len2 ? -1 : 1;
}

int comparator(const void *a, const void *b) {
    const char *x1 = *(const char **) a;
    const char *x2 = *(const char **) b;

    if (isupper(*x1) && !isupper(*x2))
        return -1;
    else if (!isupper(*x1) && isupper(*x2))
        return 1;

    return strcmp(x1, x2);
}

char **failed_to_allocate_memory(char **p, char *b, size_t size) {
    free(b);
    if (size)
        for (size_t i = 0; i < size; i++)
            free(*(p + i));
    free(p);
    return NULL;
}

int failed_to_allocate_sentence(char ***p, size_t size, char ****output) {
    if (p) {
        for (size_t k = 0; k < size; k++) {
            char **ptr = *(p + k);
            size_t i = 0;
            for (char *ptr2 = *ptr; ptr2 != NULL; ptr2 = *(ptr + (++i)))
                free(ptr2);

            free(ptr);
        }
    }

    free(p);
    *output = NULL;
    return 3;
}

char **split_words(const char *text, unsigned len) {
    if (text == NULL)
        return NULL;

    char *buffer = NULL;
    char **result = NULL;
    size_t result_size = 0;
    size_t buffer_size = 0;

    while (len--) {
        char c = *(text++);
        if (isalpha(c)) {
            if (!buffer_size) // edge-case
            {
                char *tmp = NULL;
                if ((tmp = realloc(buffer, sizeof(char) * 2)) == NULL)
                    return failed_to_allocate_memory(result, buffer, result_size);
                else buffer = tmp;

                buffer_size += 2;
            } else {
                char *tmp = NULL;
                if ((tmp = realloc(buffer, sizeof(char) * (++buffer_size))) == NULL)
                    return failed_to_allocate_memory(result, buffer, result_size);
                else buffer = tmp;
            }

            *(buffer + (buffer_size - 2)) = c;
            *(buffer + (buffer_size - 1)) = '\0';
        } else {
            if (!buffer_size)
                continue;

            char **tmp = NULL;
            if ((tmp = realloc(result, sizeof(char *) * (++result_size))) == NULL)
                return failed_to_allocate_memory(result, buffer, --result_size);
            else result = tmp;

            *(result + result_size - 1) = buffer;
            buffer = NULL;
            buffer_size = 0;
        }
    }

    if (result_size) {
        char **tmp = NULL;
        if ((tmp = realloc(result, sizeof(char *) * (++result_size))) == NULL)
            return failed_to_allocate_memory(result, buffer, --result_size);
        else result = tmp;

        *(result + result_size - 1) = NULL;
    }

    if (!result) {
        char **tmp = NULL;
        if ((tmp = malloc(sizeof(char *))) == NULL)
            return NULL;
        else result = tmp;
        *result = NULL;
    }
    return result;
}

int split_sentences(const char *text, char ****output) {
    if (output == NULL)
        return 1;

    if (!strchr(text, '.')) {
        *output = NULL;
        return 2;
    }

    char ***sentences = NULL;
    size_t sentences_size = 0;
    char *prev = (char *) text;

    for (char *pchr = strchr(text, '.'); pchr != NULL; pchr = strchr(pchr + 1, '.')) {
        char **words = NULL;
        if ((pchr - prev) > 1 || (prev == text && prev != pchr)) {
            words = split_words(prev, (pchr - prev) + 1);
            if (!words)
                return failed_to_allocate_sentence(sentences, sentences_size, output);
        } else {
            words = malloc(sizeof(char *));
            if (words)
                *words = NULL;
            else
                return failed_to_allocate_sentence(sentences, sentences_size, output);
        }
        char ***tmp = realloc(sentences, sizeof(char **) * (sentences_size + 1));

        if (!tmp) {
            destroy2d(words);
            return failed_to_allocate_sentence(sentences, sentences_size, output);
        } else sentences = tmp;

        *(sentences + (sentences_size++)) = words;
        prev = pchr;
    }

    if (sentences_size) {
        char ***tmp = realloc(sentences, sizeof(char **) * (sentences_size + 1));

        if (!tmp)
            return failed_to_allocate_sentence(sentences, sentences_size, output);
        else sentences = tmp;

        *(sentences + (sentences_size++)) = NULL;
    }

    *output = sentences;
    return 0;
}

int sort_sentences(char ***output) {
    if (output == NULL)
        return 1;

    size_t len = 0;
    char ***p = output;
    while (*(p++) != NULL)
        len++;

    if (len > 1) {
        qsort(output, len, sizeof(*output), length_comparator);
    }
    for (size_t i = 0; i < len; i++) {
        size_t words_num = 0;
        char **words = *(output + i);
        while (*(words++) != NULL)
            words_num++;

        qsort(*(output + i), words_num, sizeof(char *), comparator);
    }

    return 0;
}

int sort_words(char **words) {
    if (words == NULL)
        return 1;

    size_t len = 0;
    char **p = words;
    while (*(p++) != NULL)
        len++;

    if (len > 1)
        qsort(words, len, sizeof(*words), comparator);
    return 0;
}

void destroy2d(char **words) {
    char **p = words;

    while (*(p++) != NULL)
        free(*(p - 1));

    free(words);
}

void destroy(char ***words) {
    for (size_t i = 0; *(words + i) != NULL; i++)
        destroy2d(*(words + i));

    free(words);
}

int main() {
    char *buffer = malloc(1000);
    if (buffer == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Enter text:");
    scanf("%999[^\n]", buffer);

    char ***ret = NULL;
    int r = split_sentences(buffer, &ret);
    if (r == 3) {
        free(buffer);
        printf("Failed to allocate memory");
        return 8;
    } else if (r != 0) {
        printf("Nothing to show");
        free(buffer);
        return 0;
    }

    if (!ret) {
        free(buffer);
        return 0;
    }
    char ***w = ret;
    sort_sentences(w);
    int ok = 0;
    for (size_t i = 0; *(w + i) != NULL; i++) {
        if (*(*(w + i) + 0) != NULL)
            ok = 1;
    }
    if(ok==0){
        printf("Nothing to show\n");
    }else {
        for (size_t i = 0; *(w + i) != NULL; i++) {
            if (*(*(w + i) + 0) == NULL)
                printf("Nothing to show");
            for (size_t j = 0; *(*(w + i) + j) != NULL; j++) {
                printf("%s ", *(*(w + i) + j));
            }
            printf("\n");
        }
    }

    destroy(ret);
    free(buffer);
    return 0;
}