#include <stdio.h>

int main(int argc, char const *argv[])
{
    // referencing the File ..
    FILE *myFile = fopen("myFile.txt", "w");

    // Checking for NULLs ..
    if (myFile == NULL)
    {
        printf("ERROR");
    }
    else
    {
        fprintf(myFile, "teffffffffffffffffffst");
    }

    return 0;
}
