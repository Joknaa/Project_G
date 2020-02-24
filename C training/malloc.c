#include <stdio.h>
#include <malloc.h>

int main(int argc, char const *argv[])
{
    int tab[50];
    float *tabMalloc;





    tabMalloc = malloc(10*sizeof(float));


    tabMalloc = realloc(tabMalloc,50*sizeof(float));

    free(tabMalloc);



    return 0;
}
