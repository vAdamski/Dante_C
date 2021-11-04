#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int is_sparse(uint64_t value) {
    unsigned int was_1 = 0;
    for (unsigned int i = 0; i < sizeof(uint64_t) * 8; i++) {
        if ((value >> i) % 2 == 1) {
            if (was_1) {
                return 0;
            }
            was_1 = 1;
        } else {
            was_1 = 0;
        }
    }
    return 1;
}

int main() {
    printf("Podaj wartosc: ");
    unsigned long long ull = 386169261305549739;
    if (scanf("%llu", &ull) != 1) {
        printf("Incorrect input");
        return 1;
    }
    printf("Liczba: %.16llx, Wynik: %d", ull, is_sparse(ull));
    return 0;
}