#include <stdio.h>
#include <string.h>

struct file_t
{
    FILE *f;
    int size;
};
int open_file(struct file_t* f, const char *filename);
struct file_t* find_min(const struct file_t* files, int size);
void close_file(struct file_t* f);
void clean_stdin(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main()
{
    struct file_t tab[5];
    int openedFile = 0;
    char fileName[1000];
    char text[1000];

    //Gets files name from user
    printf("Podaj nazwy plikow:\n");
    do
    {
        fgets(fileName, 1000, stdin);
        if(*(fileName+0) == '\n')
        {
            break;
        }
        int lenght = (int)strlen(fileName);
        *(fileName+lenght-1) = '\x0';
        int error = open_file(tab+openedFile, fileName);
        if(error == 0)
        {
            openedFile++;
        }
    }while(openedFile <= 5);

    //If zero file opened
    if(openedFile == 0)
    {
        printf("Couldn't open file\n");
        return 4;
    }

    //Read text from user
    printf("Podaj tekst do dopisania do pliku:\n");
    do {
        fgets(text, 1000, stdin);

        if(*(text+0) == '\n') break;

        struct file_t *minFile = find_min(tab, openedFile);
        fprintf(minFile->f, "%s", text);
        minFile->size = (int)ftell(minFile->f);
    }while (1);

    //Close all files
    for (int i = 0; i < openedFile; ++i)
    {
        close_file(tab+i);
    }

    printf("Files saved\n");
    return 0;
}

int open_file(struct file_t* f, const char *filename)
{
    if(f == NULL || filename == NULL)
    {
        return 1;
    }

    FILE *file;
    if((file = fopen(filename, "a")) == NULL) return 2;

    f->size = ftell(file);
    fclose(file);
    f->f = fopen(filename, "a");

    if(f->f == NULL) return 2;

    return 0;
}
struct file_t* find_min(const struct file_t* files, int size)
{
    if(files == NULL || size < 1) return NULL;

    int min_size = (files+0)->size;
    int lowest = 0;

    for(int i = 0; i < size; i++)
    {
        if((files+i)->size <= min_size)
        {
            lowest = i;
            min_size = (files+i)->size;
        }
    }

    return (struct file_t*)(files+lowest);
}
void close_file(struct file_t* f)
{
    if(f == NULL || f->f == NULL) return;

    fclose(f->f);
}
