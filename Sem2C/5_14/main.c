#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int number_2_words(char **text, unsigned long long number);

char *my_strcat(char **dest, const char *src);

char *ltoa(unsigned long long number);

void reverse(char *);

int main() {
    unsigned long long number;
    printf("Enter a number:");
    int r = scanf("%llu", &number);
    if (r != 1) {
        printf("Incorrect input");
        return 1;
    }
    char *text;
    r = number_2_words(&text, number);
    if (r == 2) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("%s", text);
    free(text);
    return 0;
}

void reverse(char *txt) {
    for (int i = 0; i < (int) strlen(txt) / 2; i++) {
        char t = *(txt + i);
        *(txt + i) = *(txt + strlen(txt) - 1 - i);
        *(txt + strlen(txt) - 1 - i) = t;
    }
}

char *concat(char **text, const char *src) {
    if (*text == NULL) {
        return my_strcat(text, src);
    }
    char *r = my_strcat(text, " ");
    if (r == NULL) {
        return NULL;
    }
    return my_strcat(text, src);
}

char *numbers(char **text, int n) {
//    printf("%d\n", n);
    if (n >= 20) {
        const char *textadd = NULL;
        switch (n / 10) {
            case 9:
                textadd = "Ninety";
                break;
            case 8:
                textadd = "Eighty";
                break;
            case 7:
                textadd = "Seventy";
                break;
            case 6:
                textadd = "Sixty";
                break;
            case 5:
                textadd = "Fifty";
                break;
            case 4:
                textadd = "Forty";
                break;
            case 3:
                textadd = "Thirty";
                break;
            case 2:
                textadd = "Twenty";
                break;
            case 1:
                textadd = "Ten";
                break;
        }
        if (textadd != NULL) {
            char *r = concat(text, textadd);
            if (r == NULL) {
                return NULL;
            }
        }
        n %= 10;
    }
    const char *textadd = NULL;
    switch (n) {
        case 19:
            textadd = "Nineteen";
            break;
        case 18:
            textadd = "Eighteen";
            break;
        case 17:
            textadd = "Seventeen";
            break;
        case 16:
            textadd = "Sixteen";
            break;
        case 15:
            textadd = "Fifteen";
            break;
        case 14:
            textadd = "Fourteen";
            break;
        case 13:
            textadd = "Thirteen";
            break;
        case 12:
            textadd = "Twelve";
            break;
        case 11:
            textadd = "Eleven";
            break;
        case 10:
            textadd = "Ten";
            break;
        case 9:
            textadd = "Nine";
            break;
        case 8:
            textadd = "Eight";
            break;
        case 7:
            textadd = "Seven";
            break;
        case 6:
            textadd = "Six";
            break;
        case 5:
            textadd = "Five";
            break;
        case 4:
            textadd = "Four";
            break;
        case 3:
            textadd = "Three";
            break;
        case 2:
            textadd = "Two";
            break;
        case 1:
            textadd = "One";
            break;
    }
    if (textadd != NULL) {
        char *r = concat(text, textadd);
        if (r == NULL)
            return NULL;
    }
    return *text;
}

int number_2_words(char **text, unsigned long long number) {
    if (text == NULL) {
        return 1;
    }
    *text = NULL;
    if (number == 0) {
        *text = strdup("Zero");
        if (*text == NULL) {
            return 2;
        }
        return 0;
    }
    char *num = ltoa(number);
    if (num == NULL) {
        return 2;
    }
    char *nums = num;
    int ok = 0;
//    printf("%s\n", num);
    reverse(num);
    int n = 0;
    if (strlen(num) >= 20) {
        n += *(num + 19) - '0';
        n *= 10;
//        printf("%d\n",n);
    }
    if (strlen(num) >= 19) {
        n += *(num + 18) - '0';
//        printf("%d\n",n);
    }
    if (n != 0) {
        if (numbers(text, n) == NULL || concat(text, "Quintillion") == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    n = 0;
    if (strlen(num) >= 18) {
        n += *(num + 17) - '0';
//        printf("%d\n",n);
    }
    if (n != 0) {
        ok = 1;
        if (numbers(text, n) == NULL || concat(text, "Hundred") == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    n = 0;
    if (strlen(num) >= 17) {
        n += *(num + 16) - '0';
        n *= 10;
//        printf("%d\n",n);
    }
    if (strlen(num) >= 16) {
        n += *(num + 15) - '0';
//        printf("%d\n",n);
    }
    if (n != 0) {
        ok = 1;
        if (numbers(text, n) == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    if (ok) {
        if (concat(text, "Quadrillion") == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    ok = 0;
    n = 0;
    if (strlen(num) >= 15) {
        n += *(num + 14) - '0';
//        printf("%d\n",n);
    }
    if (n != 0) {
        ok = 1;
        if (numbers(text, n) == NULL || concat(text, "Hundred") == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    n = 0;
    if (strlen(num) >= 14) {
        n += *(num + 13) - '0';
        n *= 10;
//        printf("%d\n",n);
    }
    if (strlen(num) >= 13) {
        n += *(num + 12) - '0';
//        printf("%d\n",n);
    }
    if (n != 0) {
        ok = 1;
        if (numbers(text, n) == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    if (ok) {
        if (concat(text, "Trillion") == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    ok = 0;
    n = 0;
    if (strlen(num) >= 12) {
        n += *(num + 11) - '0';
//        printf("%d\n",n);
    }
    if (n != 0) {
        ok = 1;
        if (numbers(text, n) == NULL || concat(text, "Hundred") == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    n = 0;
    if (strlen(num) >= 11) {
        n += *(num + 10) - '0';
        n *= 10;
//        printf("%d\n",n);
    }
    if (strlen(num) >= 10) {
        n += *(num + 9) - '0';
//        printf("%d\n",n);
    }
    if (n != 0) {
        ok = 1;
        if (numbers(text, n) == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    if (ok) {
        if (concat(text, "Billion") == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    ok = 0;
    n = 0;
    if (strlen(num) >= 9) {
        n += *(num + 8) - '0';
//        printf("%d\n",n);
    }
    if (n != 0) {
        ok = 1;
        if (numbers(text, n) == NULL || concat(text, "Hundred") == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    n = 0;
    if (strlen(num) >= 8) {
        n += *(num + 7) - '0';
        n *= 10;
//        printf("%d\n",n);
    }
    if (strlen(num) >= 7) {
        n += *(num + 6) - '0';
//        printf("%d\n",n);
    }
    if (n != 0) {
        ok = 1;
        if (numbers(text, n) == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    if (ok) {
        if (concat(text, "Million") == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    ok = 0;
    n = 0;
    if (strlen(num) >= 6) {
        n += *(num + 5) - '0';
//        printf("%d\n",n);
    }
    if (n != 0) {
        ok = 1;
        if (numbers(text, n) == NULL || concat(text, "Hundred") == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    n = 0;
    if (strlen(num) >= 5) {
        n += *(num + 4) - '0';
        n *= 10;
//        printf("%d\n",n);
    }
    if (strlen(num) >= 4) {
        n += *(num + 3) - '0';
//        printf("%d\n",n);
    }
    if (n != 0) {
        ok = 1;
        if (numbers(text, n) == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    if (ok) {
        if (concat(text, "Thousand") == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    ok = 0;
    n = 0;
    if (strlen(num) >= 3) {
        n += *(num + 2) - '0';
//        printf("%d\n",n);
    }
    if (n != 0) {
        ok = 1;
        if (numbers(text, n) == NULL || concat(text, "Hundred") == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    n = 0;
    if (strlen(num) >= 2) {
        n += *(num + 1) - '0';
        n *= 10;
//        printf("%d\n",n);
    }
    if (strlen(num) >= 1) {
        n += *(num + 0) - '0';
//        printf("%d\n",n);
    }
    if (n != 0) {
        ok = 1;
        if (numbers(text, n) == NULL) {
            free(*text);
            *text = NULL;
            free(nums);
            return 2;
        }
    }
    ok = 0;
    n = 0;
    free(nums);
    return 0;
}

char *my_strcat(char **dest, const char *src) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }
    if (*dest == NULL) {
        *dest = strdup(src);
        return *dest;
    }
    char *d = realloc(*dest, strlen(*dest) + strlen(src) + 1);
    if (d == NULL) {
        return NULL;
    }
    strcat(d, src);
    *dest = d;
    return d;
}

char *ltoa_(unsigned long long number) {
    if (number == 0) {
        return strdup("");
    }
    unsigned long long num = number % 10;
    char *txt = ltoa_(number / 10);
    if (txt == NULL) {
        return NULL;
    }
    char *txt2 = realloc(txt, strlen(txt) + 2);
    if (txt2 == NULL) {
        free(txt);
        return NULL;
    }
    *(txt2 + strlen(txt2) + 1) = '\0';
    *(txt2 + strlen(txt2)) = '0' + num;
    return txt2;
}

char *ltoa(unsigned long long number) {
    if (number == 0) {
        return strdup("0");
    }
    return ltoa_(number);
}