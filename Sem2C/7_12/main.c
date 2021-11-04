#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateNumber(char *a) {
    if (*a == '-') {
        a++;
    }
    if (strlen(a) == 0) {
        return 0;
    }
    while (*a != '\0') {
        if (*a < '0' || *a > '9') {
            return 0;
        }
        a++;
    }
    return 1;
}

int main(int argc, char **argv) {
    int sum = 0;
    int i;
    if (argc < 2) {
        printf("Not enough arguments");
        return 9;
    }
    for (i = 1; i < argc; i++) {
        char *num = *(argv + i);
        if (!validateNumber(num)) {
            printf("Incorrect input");
            return 1;
        }
        sum += atoi(num);
    }
    printf("%d\n", sum);
    return 0;
}
