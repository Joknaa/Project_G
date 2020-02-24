#include <stdio.h>

int main(int argc, char const *argv[])
{
    system("cls");
    char CurrentChar;
    //--> Referencing the .Dot File ..
    FILE *myFile = fopen("Graphviz_files/Labels.dot", "r");

    //--> Checking the stat of the pointer ..
    if (myFile == NULL)
    {
        printf("Null");
    }
    else
    {
        //--> Loop the file and check for characters ..
        while ((CurrentChar = fgetc(myFile)) != EOF)
        {
            printf("%c", CurrentChar);
        }
    }

    //--> Close the file ..
    fclose(myFile);

    return 0;
}
