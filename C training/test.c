#include <stdio.h>

float PrintN(int n)
{
    n++;
    return n;
}

int main()
{
    int s =2;
    char c = '8';

    s = s*10 + (c - '0');
    printf("%d", s);

    return 0;
}
