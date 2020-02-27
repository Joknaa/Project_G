#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a = 2, b = 10;

    printf("a++ *b = %d || a = %d || b = %d\n", a++ * b, a, b);

    a = 2;
    b = 10;
    printf("++a *b = %d || a = %d || b = %d\n\n", ++a * b, a, b);

    printf("a++ = %d || ++a = %d", a++, ++a);


    return 0;
}
