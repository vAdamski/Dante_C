#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "data_type.h"

#define OPERATE(TYPE, SCANFSYMBOL, PRINTFSYMBOL) {\
            TYPE **arr = malloc(ilosc_tablic * sizeof(TYPE *));\
if (arr == NULL) {\
    printf("Failed to allocate memory");\
    return 8;\
}\
for (int i = 0; i < ilosc_tablic; i++) {\
    printf("Podaj liczb eelementow ");\
    int n;\
    if (scanf("%d", &n) != 1) {\
        printf("Incorrect input");\
        for (int j = 0; j <= i; j++) {\
            free(*(arr + j));\
        }\
        free(arr);\
        return 1;\
    }                                             \
    if(n<1){                                      \
        printf("Incorrect input data");\
        for (int j = 0; j <= i; j++) {\
            free(*(arr + j));\
        }\
        free(arr);\
        return 2;\
    }\
    *(arr + i) = malloc((1 + n) * sizeof(TYPE));\
    if (*(arr + i) == NULL) {\
        printf("Failed to allocate memory");\
        for (int j = 0; j <= i; j++) {\
            free(*(arr + j));\
        }\
        free(arr);\
        return 8;\
    }\
\
    printf("Liczby :");\
    for (int j = 0; j < n; j++) {\
    if (scanf(SCANFSYMBOL, (*(arr + i) + j)) != 1) {\
            printf("Incorrect input");\
            for (j = 0; j <= i; j++) {\
                free(*(arr + j));\
            }\
            free(arr);\
            return 1;\
        }\
    }\
    *(*(arr + i) + n) = -1;                       \
}                                                 \
TYPE *a = connect(type, ilosc_tablic, *(arr + 0), *(arr + 1), *(arr + 2), *(arr + 3));\
free_array((void **) arr, ilosc_tablic);\
if (a == NULL) {\
    printf("Failed to allocate memory");\
    return 8;\
}\
for (int i = 0;; i++) {\
    TYPE n = *(a + i);\
    if (n == -1) {\
        break;\
    }\
    printf(PRINTFSYMBOL, n);\
}\
free(a);\
break;\
}

#define CONNECT(TYPE) void *connect_##TYPE(int count, va_list list){ \
    TYPE *array=malloc(1*sizeof(TYPE));                              \
    if(array==NULL){                                                 \
        return NULL;                                                     \
    }                                    \
    *array=-1;                                                       \
    int len=0;\
    for (int i=0;i<count;i++){                                       \
        TYPE *next= va_arg(list,TYPE*);                              \
        for(int i=0;*(next+i)!=-1;i++){                              \
            TYPE *new_array = realloc(array,sizeof(*array)*(len+2));                  \
            if(new_array==NULL){                                     \
                free(array);                                         \
                return NULL;\
            }                                                        \
            array=new_array;                                         \
            *(array+len)=*(next+i);                                  \
            len++;                                                   \
            *(array+len)=-1;                                         \
        }\
    }                                                                     \
    return array;                                                                     \
}

CONNECT(short)

CONNECT(int)

CONNECT(float)

CONNECT(double)

CONNECT(long)

void *connect(data_type_t type, int count, ...) {
    if (count < 1 || type > data_type_long || type < data_type_short)
        return NULL;
    va_list list;
            va_start(list, count);
    void *ret;
    switch (type) {
        case data_type_short:
            ret = connect_short(count, list);
            break;
        case data_type_int:
            ret = connect_int(count, list);
            break;
        case data_type_float:
            ret = connect_float(count, list);
            break;
        case data_type_double:
            ret = connect_double(count, list);
            break;
        case data_type_long:
            ret = connect_long(count, list);
            break;
    }
            va_end(list);
    return ret;
}

void free_array(void **ptr, int size) {
    for (int i = 0; i < size; i++)
        free(*(ptr + i));

    free(ptr);
}

int main() {
    data_type_t type;
    printf("Podaj typ danych do wprowadzenia: ");
    if (scanf("%u", &type) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (type > data_type_long || type < data_type_short) {
        printf("Incorrect input data");
        return 2;
    }
    printf("\nPodaj liczbe tablic do wprowadzenia: ");
    int ilosc_tablic = 0;
    if (scanf("%d", &ilosc_tablic) != 1) {
        printf("Incorrect Input");
        return 1;
    }
    if (ilosc_tablic < 2 || ilosc_tablic > 4) {
        printf("Incorrect input data");
        return 2;
    }

    switch (type) {
        case data_type_short: OPERATE(short, "%hd", "%hd ")
        case data_type_int: OPERATE(int, "%d", "%d ")
        case data_type_long: OPERATE(long, "%ld", "%ld ")
        case data_type_float: OPERATE(float, "%f", "%f ")
        case data_type_double: OPERATE(double, "%lf", "%lf ")

    }
    return 0;
}