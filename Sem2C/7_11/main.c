#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Not enough arguments");
        return 9;
    }
    FILE *in = fopen(*(argv + 1), "rb");
    if (in == NULL) {
        printf("Couldn't open file");
        return 4;
    }
    FILE *out = fopen(*(argv + 2), "wb");
    if (out == NULL) {
        fclose(in);
        printf("Couldn't create file");
        return 5;
    }
    char elem;
    while (1) {
        fread(&elem, 1, 1, in);
        if (feof(in)) {
            break;
        }
        fwrite(&elem, 1, 1, out);
    }
    fclose(in);
    fclose(out);
    printf("File copied");
    return 0;
}
