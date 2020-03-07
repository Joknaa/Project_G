#include <stdio.h>
#include <stdlib.h>

int main()
{
    system("cls");
    char *mytable;

    mytable = (char *)malloc(sizeof(char));

    mytable[0] = '0';

    printf("mytable[0] = %d", mytable[0] - '0');
}