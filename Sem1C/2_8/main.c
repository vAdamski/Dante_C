#include <stdio.h>
#include <string.h>

struct entry_t {
    char name[20];
    char last_name[40];
    int number;
};
void display(const struct entry_t* p);
int load_phonebook_t(const char *filename, struct entry_t* p, int size);
const struct entry_t* find_by_last_name(const struct entry_t* p, int size, const char *last_name);
void clean_stdin(void);

int main()
{
    char fileName[100];
    char lastName[40];
    struct entry_t kontakt[10];
    printf("Wprowadz nazwe ksiażki:\n");
    scanf("%100s", fileName);

    int error = load_phonebook_t(fileName, kontakt, 10);
    switch (error) {
        case -2:
            printf("Couldn't open file\n");
            return 4;
        case 0:
            printf("File corrupted\n");
            return 6;
        default:
            break;
    }

    clean_stdin();
    printf("Wprowadz nazwisko:\n");
    scanf("%40s", lastName);

    const struct entry_t *person = find_by_last_name(kontakt, 10, lastName);
    if (person == NULL)
    {
        printf("Couldn't find name\n");
    }
    else
    {
        display(person);
    }
    return 0;
}

void display(const struct entry_t* p)
{
    if(p == NULL) return;
    printf("Name: %s\nLast name: %s\nPhone number: %d",p->name,p->last_name,p->number);
}

int load_phonebook_t(const char *filename, struct entry_t* p, int size)
{
    int goodLoad = 0;
    FILE *fp;
    if(filename == NULL || p == NULL || size < 1)
    {
        return -1;
    }
    if((fp = fopen(filename, "r")) == NULL)
    {
        return -2;
    }
    for (int i = 0; i < size; ++i)
    {
        if(fscanf(fp, "%20s | %40[^|] | %d", (p+i)->name, (p+i)->last_name, &(p+i)->number) == 3)
        {
            int size = strlen((p+i)->last_name);
            printf("%d\n%s|", size, (p+i)->last_name);
            while(getc((p+i)->last_name))
            goodLoad++;
        }
    }
    fclose(fp);
    return goodLoad;
}

const struct entry_t* find_by_last_name(const struct entry_t* p, int size, const char *last_name)
{
    if(p == NULL || size < 1 || last_name == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < size; ++i)
    {
        if(strcmp((p+i)->last_name, last_name) == 0)
        {
            return p+i;
        }
    }
    return NULL;
}

void clean_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    }while(c != '\n' && c != EOF);
}