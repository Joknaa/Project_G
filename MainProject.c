#include <stdio.h>
#include <ctype.h>
#include <malloc.h>

//? ----------------------- FixMe -----------------------
//! //FIXME : The nodes might be numbers composed of 2 or more digits
//! //FIXME : If the node is repeated each line, the size of tables would be more than needed ..

//? ----------------------- ToDo -----------------------
//* -------->  Phase I :
//TODO : Constract the Data Matrix ..

//* -------->  Phase II :
//TODO : Scan the Matrix ..
//TODO : Creat a new .Dot file ..
//TODO : Show the new graph ..

//? -------------------  Working On  -------------------
//TODO : Write the 'CollectData()' function ..
//todo:     >>> Creat structers to hold data ..
//todo:         >>> Get the number of nodes and labels to creat the tables in the structers ..

/*//? --------------------  DONE !! --------------------
    * Referencing the .Dot File ..
    * Checking the stat of the pointer ..
    * 'CheckingForData' function ..
    * Optimazing the Collect Algorithm ..
    * 'GetNumberOfLines' function ..
    * Write the 'CreatTables()' function ..
*/

//* ----------------------- Defines-----------------------

//* ------------------ Global Variables ------------------
FILE *myFile;
int GraphTitleSize = 0;
int NumberOfLines = 1;
int NumberOfNodes = 0;
int *StartingNodes;
int *FinishingNodes;
char *Labels;
char *TableName;

//* -------------------------------------------- CollectData -------------------------------------------
void CollectData(char CurrentChar)
{
    int NodeID = 0;
    char *Label;

    do
    {
        NodeID = NodeID * 10 + (CurrentChar - '0');
    } while (isdigit(CurrentChar = fgetc(myFile)));
    printf("\nNode: %d", NodeID);
}

//* -------------------------------------- CheckingForUsefulData ----------------------------------------
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

    // collect the usefull Data for each line .. '{' --> '"'  ..
    while (CurrentLine <= NumberOfLines)
    {
        // Last Wanted Character ..
        while (CurrentChar != '"')
        {
            while ((CurrentChar = fgetc(myFile)) != '>')
            {
                // Nodes are intigers !
                if (isdigit(CurrentChar))
                {
                    CollectData(CurrentChar);
                }
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

//* ----------------------------------------- GetNumberOfLines -----------------------------------------
void GetNumberOfLines()
{
    char CurrentChar = fgetc(myFile);
    while ((CurrentChar = fgetc(myFile)) != '}')
    {
        if (CurrentChar == '\n')
        {
            NumberOfLines++;
        }
    }
}

//* ------------------------------------------- CreatTables --------------------------------------------
int *CreatTemporarilyTables()
{
    char GraphName = malloc(GraphTitleSize * sizeof(char));

    return GraphName;
}

//* ----------------------------------------- GetNumberOfNodes -----------------------------------------
void etat(FILE *fichier_pointeur)
{
    int i = 0, k, j, compteur = 1;
    char char_actuel;

    StartingNodes = (int *)malloc(sizeof(int) * compteur);

    while ((char_actuel = fgetc(fichier_pointeur)) != '}')
    {
        if (isdigit(char_actuel))
        {
            StartingNodes = (int *)realloc(StartingNodes, sizeof(int) * compteur);
            StartingNodes[i] = char_actuel - '0';
            i++;
            compteur++;
        }

        for (i = 0; i < compteur - 1; i++)
        {
            for (j = i + 1; j < compteur - 1; j++)
            {
                if (StartingNodes[j] == StartingNodes[i])
                {
                    for (k = j; k < compteur - 1; k++)
                    {
                        StartingNodes[k] = StartingNodes[k + 1];
                    }
                    compteur--;
                }
            }
        }
    }
    for (i = 0; i < compteur - 1; i++)
    {
        printf("%d\n", StartingNodes[i]);
    }
}

//* ----------------------------------------------- MAIN -----------------------------------------------
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
        CreatTemporarilyTables();
        CheckingForUsefulData();
    }
    fclose(myFile);
    return 0;
}