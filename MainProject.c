#include <stdio.h>
#include <ctype.h>
#include <malloc.h>

//?--------> // ToDo <--------
//FIXME //!The nodes might be numbers composed of 2 or more digits

//? ----------------  Working On  ------------------
//TODO Write the 'CollectData()' function ..

/*//? -------------------  DONE !! -------------------
    * Referencing the .Dot File ..
    * Checking the stat of the pointer ..
    * 'CheckingForData' function ..
    * Optimazing the Collect Algorithm ..
    * 'GetNumberOfLines' function ..
    * Write the 'CreatTables()' function ..
*/

//* ------------------ Global Variables ------------------
FILE *myFile;
int GraphTitleSize = 0;
int NumberOfLines = 1;

//* ---------------------------------------- CheckingForUsefulData ----------------------------------------
void CheckingForUsefulData()
{
    char CurrentChar;
    int CurrentLine = 1, CurrentPositionInTitle = 0, DigraphKeywordSize = 9;

    // Reseting the cursur position in the file ..
    rewind(myFile);

    // Collect all the string, for the graph's name .. Start --> '{' ..
    printf("Title:");
    do
    {
        CurrentPositionInTitle++;
        if (CurrentPositionInTitle >= DigraphKeywordSize)
        {
            GraphTitleSize++;
            printf("%c", CurrentChar);
        }
    } while ((CurrentChar = fgetc(myFile)) != '{');
    printf("\nTitle Size: %d", GraphTitleSize);

    // collect the usefull Data for each line .. '{' --> ';'  ..
    while (CurrentLine <= NumberOfLines)
    {
        // Last Wanted Character ..
        while ((CurrentChar = fgetc(myFile)) != '"')
        {
            // Nodes are intigers !
            if (isdigit(CurrentChar))
            {
                //printf("\nNode: %c", CurrentChar);
                CollectData(CurrentChar);
            }
        }

        // the start of the Label
        if (CurrentChar == '"')
        {
            // while we are NOT at the end of the Label ..
            while ((CurrentChar = fgetc(myFile)) != '"')
            {
                printf("\nLabel : %c", CurrentChar);
            }
        }
        CurrentLine++;
    }
}

//* ------------------------------------------- GetNumberOfLines -------------------------------------------
void GetNumberOfLines()
{
    char CurrentChar = fgetc(myFile);
    while ((CurrentChar = fgetc(myFile)) != '}')
    {
        if (CurrentChar == ';')
        {
            NumberOfLines++;
        }
    }
}

//* --------------------------------------------- CreatTables ----------------------------------------------
int *CreatTables()
{
    int *StartingNodes, *FinishingNodes, *Labels, *GraphName;

    StartingNodes = malloc(NumberOfLines * sizeof(int));
    FinishingNodes = malloc(NumberOfLines * sizeof(int));
    Labels = malloc(NumberOfLines * sizeof(char));
    GraphName = malloc(GraphTitleSize * sizeof(char));

    return StartingNodes, FinishingNodes, Labels, GraphName;
}

//* ---------------------------------------------- CollectData ---------------------------------------------
void CollectData(char CurrentChar)
{
    int Node = 0;
    char *Label;

    if (isdigit(CurrentChar))
    {
        // Collect this number ..
        do
        {
            Node = Node * 10 + (CurrentChar - '0');
        } while (isdigit(CurrentChar = fgetc(myFile)));
    }
    else
    {
        // Collect this string ..
    }
    printf("\n%d  ", Node);
}

//* ------------------------------------------------- MAIN -------------------------------------------------
int main(int argc, char const *argv[])
{
    //--> Referencing the .Dot File ..
    myFile = fopen("Graphviz_files/Labels.dot", "r");

    //--> Checking the state of the pointer then for Data in the file ..
    if (myFile == NULL)
    {
        printf("Null");
    }
    else
    {
        GetNumberOfLines();
        CreatTables();
        CheckingForUsefulData();
    }
    fclose(myFile);
    return 0;
}