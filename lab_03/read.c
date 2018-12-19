#include "define.h"

int read_key(char *text)
{
    int key = 0;
    char c;
    printf("%s", text);

    do
    {
        fflush(stdin);
        printf("(y/n): ");
        scanf("%c", &c);

        if (c == 'y' || c == 'Y')
            key = 2;
        else if (c == 'n' || c == 'N')
            key = 1;
    }
    while (!key);

    return (key - 1);
}

void read_size(char *text, int *m, int *n)
{
    printf("%s", text);
    fflush(stdin);

    while (scanf("%d %d", m, n) != 2)
    {
        printf("Wrong size input!\nTry again: ");
        fflush(stdin);
    }
}
