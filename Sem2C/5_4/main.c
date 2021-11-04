#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR(msg, num) { printf("%s\n", msg); return num; }
#define MAX(x, y) (x > y ? x : y)


int validate(const char* number);
int compare(const char* number1, const char* number2);
void reverse(char* str);
void shift_right(char* str);
char take_from_end(const char* string, int n);
int to_int(char c);
int add(const char* number1, const char* number2, char** result);
int subtract(const char* number1, const char* number2, char** result);


int validate(const char* number) {
    if (number == NULL) return -1;

    int n = (int) strlen(number);
    if (n == 0) return 2;
    if (*number == '0' && n > 1) return 2;
    if (*number == '-' && n == 1) return 2;

    for (int i = 0; i < n; i++) {
        char current = *(number + i);

        if (current == '-' && i == 0) continue;
        if (current < '0' || current > '9') return 2;
    }

    return 0;
}


int compare(const char* number1, const char* number2) {
    if (number1 == NULL || number2 == NULL) return 2;
    if (validate(number1) == 2 || validate(number2) == 2) return 3;

    if (*number1 != '-' && *number2 == '-') return  1;
    if (*number1 == '-' && *number2 != '-') return -1;

    int len1 = (int) strlen(number1);
    int len2 = (int) strlen(number2);

    int negative = 0;
    if (*number1 == '-' && *number2 == '-') negative = 1;

    if (len1 > len2) return negative ? -1 :  1;
    if (len1 < len2) return negative ?  1 : -1;

    int equal = 1;
    for (int i = 0; i < (int) strlen(number1); i++) {
        if (*(number1 + i) != *(number2 + i)) {
            equal = 0;
            break;
        }
    }
    if (equal) return 0;

    int len = MAX(len1, len2);
    for (int i = 0; i < len; i++) {
        if (*(number1 + i) > *(number2 + i)) return negative ? -1 :  1;
        if (*(number1 + i) < *(number2 + i)) return negative ?  1 : -1;
    }

    return 0;
}


void reverse(char* str) {
    if (str == NULL) return;

    char* end = str + strlen(str) - 1;

    while (end > str) {
        char tmp = *str;
        *str = *end;
        *end = tmp;

        end--;
        str++;
    }
}


void shift_right(char* str) {
    if (str == NULL) return;

    char* end = str + strlen(str);

    while (end >= str) {
        *(end + 1) = *end;
        end--;
    }
}


char take_from_end(const char* string, int n) {
    if (n > (int) strlen(string)) return '0';

    return *(string + strlen(string) - n - 1);
}


int to_int(char c) {
    if (c < '0' || c > '9') return 0;

    return (int) (c - '0');
}


int add(const char* number1, const char* number2, char** result) {
    if (number1 == NULL || number2 == NULL || result == NULL) return 1;
    if (validate(number1) == 2 || validate(number2) == 2) return 2;

    int negative = 0;
    if        (*number1 == '-' && *number2 == '-') {  // (-) + (-)
        negative = 1;
        number1++;
        number2++;
    } else if (*number1 != '-' && *number2 == '-') {  // (+) + (-)
        return subtract(number1, number2 + 1, result);
    } else if (*number1 == '-' && *number2 != '-') {  // (-) + (+)
        return subtract(number2, number1 + 1, result);
    }

    int len = (int) MAX(strlen(number1), strlen(number2));
    *result = calloc(len + (negative ? 3 : 2), 1);
    if (*result == NULL) return 3;
    if (negative) (*result)++;

    int i = 0, carry = 0;
    for (; i < len; i++) {
        int n1 = to_int(take_from_end(number1, i));
        int n2 = to_int(take_from_end(number2, i));
        int sum = n1 + n2 + carry;

        *(*result + i) = (char) (sum % 10 + '0');
        carry = sum / 10;
    }

    if (carry) {
        *(*result + i) = (char) (carry + '0');
        i++;
    }
    *(*result + i) = '\0';

    reverse(*result);
    if (negative) {
        (*result)--;
        **result = '-';
    }

    return 0;
}


int subtract(const char* number1, const char* number2, char** result) {
    if (number1 == NULL || number2 == NULL || result == NULL) return 1;
    if (validate(number1) == 2 || validate(number2) == 2) return 2;

    int negative = 0;
    if (
              (*number1 == '-' && *number2 == '-') ||  // (-) - (-)
              (*number1 != '-' && *number2 != '-')) {  // (+) - (+)
        if (compare(number1, number2) == -1) negative = 1;
    } else if (*number1 != '-' && *number2 == '-') {   // (+) - (-)
        return add(number1, number2 + 1, result);
    } else if (*number1 == '-' && *number2 != '-') {   // (-) - (+)
        int ret = add(number1 + 1, number2, result);
        if (ret != 0) return ret;
        *result = realloc(*result, (int) strlen(*result) + 2);
        shift_right(*result);
        **result = '-';
        return ret;
    }

    if (*number1 == '-') number1++;
    if (*number2 == '-') number2++;

    if (compare(number1, number2) == -1) {
        const char* tmp = number1;
        number1 = number2;
        number2 = tmp;
    }


    int len = (int) MAX(strlen(number1), strlen(number2));
    *result = calloc(len + 2, 1);
    if (*result == NULL) return 3;
    if (negative) (*result)++;

    int i = 0, carry = 0;
    for (; i < len; i++) {
        int n1 = to_int(take_from_end(number1, i));
        int n2 = to_int(take_from_end(number2, i));
        int sub = n1 - n2 - carry;

        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        *(*result + i) = (char) (sub + '0');
    }

    if (carry) {
        *(*result + i) = (char) (carry + '0');
        i++;
    }
    *(*result + i) = '\0';

    char* end = *result + strlen(*result) + 1;
    while (end > *result) {
        if (*end > '0' && *end <= '9') break;
        if (*end == '0') *end = '\0';

        end--;
    }

    reverse(*result);
    if (negative) {
        (*result)--;
        **result = '-';
    }

    return 0;
}


int main() {
    char* num1 = calloc(201, 1);
    char* num2 = calloc(201, 1);
    if (num1 == NULL) ERR("Failed to allocate memory", 8)
    if (num2 == NULL) {
        free(num1);
        ERR("Failed to allocate memory", 8)
    }

    printf("Podaj pierwsza liczbe: ");
    fgets(num1, 201, stdin);
    char* num1_end = num1;
    while (*num1_end != '\0' && *num1_end != '\n') num1_end++;
    *num1_end = '\0';

    if (*(num1 + 199) != '\0') while (getchar() != '\n');

    printf("Podaj druga liczbe: ");
    fgets(num2, 201, stdin);
    char* num2_end = num2;
    while (*num2_end != '\0' && *num2_end != '\n') num2_end++;
    *num2_end = '\0';

    char* res;
    int add_err = add(num1, num2, &res);
    if (add_err == 3) {
        free(num1);
        free(num2);
        ERR("Failed to allocate memory", 8)
    } else if (add_err == 2) {
        free(num1);
        free(num2);
        ERR("Incorrect input", 1)
    }
    printf("%s\n", res);
    free(res);

    int sub_err = subtract(num1, num2, &res);
    if (sub_err == 3) {
        free(num1);
        free(num2);
        ERR("Failed to allocate memory", 8)
    } else if (sub_err == 2) {
        free(num1);
        free(num2);
        ERR("Incorrect input", 1)
    }
    printf("%s\n", res);
    free(res);

    free(num1);
    free(num2);

    return 0;
}
