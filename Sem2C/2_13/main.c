#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "function.h"

int main(){
    struct message_t t[100];
    const char txt[3000];
    char filename[31];
    FILE *file;


    printf("Enter file name: ");
    scanf("%30s", filename);

    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Couldn't open file\n");
        return 4;
    }
    fclose(file);

    int error = load_data(t, 100, filename);
    if (error == -3)
    {
        printf("File corrupted\n");
        return 6;
    }

    decode_message(t, 100, (char*)txt, sizeof(txt));
    printf("%s", txt);

    return 0;
}
