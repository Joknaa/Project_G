#include <stdio.h>
#include <ctype.h>
#include <malloc.h>

/*  --------> To Do <--------
    * The nodes might be numbers composed of 2 or more digits .. [I got the idea !]
    * Write the 'CollectIntigers()' function ..

*/
/*  --------> Working On <--------

*/
/*  --------> DONE ! <--------
    * Referencing the .Dot File ..
    * Checking the stat of the pointer ..
    * 'CheckingForData' function ..
    * Optimazing the Collect Algorithm ..
    * 'GetNumberOfLines' function ..
    * Write the 'CreatTables()' function ..


*/

// ------------------ Global Variables ------------------
int GraphTitleSize = 0;
int NumberOfLines = 1;

// ---------------------------------------- CheckingForUsefulData ----------------------------------------
void CheckingForUsefulData(FILE *myFile, int NumberOfLines)
{
    char CurrentChar1;
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
            printf("%c", CurrentChar1);
        }
    } while ((CurrentChar1 = fgetc(myFile)) != '{');
    printf("\nTitle Size: %d", GraphTitleSize);

    // collect the usefull Data for each line .. '{' --> ';'  ..
    while (CurrentLine <= NumberOfLines)
    {
        // Last Wanted Character ..
        while ((CurrentChar1 = fgetc(myFile)) != '"')
        {
            // Nodes are intigers !
            if (isdigit(CurrentChar1))
            {
                printf("\nNode: %c", CurrentChar1);
            }
        }

        // the start of the Label
        if (CurrentChar1 == '"')
        {
            // while we are NOT at the end of the Label ..
            while ((CurrentChar1 = fgetc(myFile)) != '"')
            {
                printf("\nLabel : %c", CurrentChar1);
            }
        }
        CurrentLine++;
    }
}

// ----------------------------------------- GetNumberOfLines -----------------------------------------
int GetNumberOfLines(FILE *myFile)
{
    char CurrentChar = fgetc(myFile);
    while ((CurrentChar = fgetc(myFile)) != '}')
    {
        if (CurrentChar == ';')
        {
            NumberOfLines++;
        }
    }
    return NumberOfLines;
}

// --------------------------------------------- CreatTables ---------------------------------------------
int *CreatTables()
{
    int *StartingNodes, *FinishingNodes, *Labels, *GraphName;

    StartingNodes = malloc(NumberOfLines * sizeof(int));
    FinishingNodes = malloc(NumberOfLines * sizeof(int));
    Labels = malloc(NumberOfLines * sizeof(char));
    GraphName = malloc(GraphTitleSize * sizeof(char));

    return StartingNodes, FinishingNodes, Labels, GraphName;
}

// ------------------------------------------------ MAIN -------------------------------------------------
int main(int argc, char const *argv[])
{
    //--> Referencing the .Dot File ..
    FILE *myFile = fopen("Graphviz_files/Labels.dot", "r");

    //--> Checking the state of the pointer then for Data in the file ..
    if (myFile == NULL)
    {
        printf("Null");
    }
    else
    {
        NumberOfLines = GetNumberOfLines(myFile);
        CreatTables(NumberOfLines);
        CheckingForUsefulData(myFile, NumberOfLines);
    }
    fclose(myFile);
    return 0;
}