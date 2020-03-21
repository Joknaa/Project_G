
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//* ---------------------------> Globals :
#define MAX_LEN 30 // Length of each line in input file.
FILE *SortedFile;
FILE *PreSortedFile;
char myFileName[50];
char GraphData[50][100];
int NumberOfLines = 0, CurrentLine = 0, i = 0, j = 0;
int **NodesOccurrences;

//* ---------------------------> Funcions :
void SortFile();

//* ---------------------------> Main :
int main(int argc, char const *argv[])
{
    int ThisNode = 0, IsStartingNode = 1;
    system("cls");
    if ((PreSortedFile = fopen("Labels.dot", "r")) == NULL)
    {
        printf("\nError! file doesn't exist x_x\n");
        return 0;
    }

    //* --------------->  Sort the file
    SortFile();

    //* --------------->  Store Data ..
    rewind(SortedFile);

    char CurrentChar;

    while (CurrentLine <= NumberOfLines)
    {
        printf("\nCursur Position : %d \t char : (%c)", ftell(SortedFile), CurrentChar);

        //* Storing Nodes ..
        while ((CurrentChar = fgetc(SortedFile)) != '"')
        {

            if (isdigit(CurrentChar))
            {

                do
                {
                    ThisNode = ThisNode * 10 + (CurrentChar - '0');
                } while (isdigit(CurrentChar = fgetc(SortedFile)));

                if (IsStartingNode == 1)
                {
                    if (ThisNode != GraphData[i][0])
                    {
                        j = 0;
                        GraphData[++i][0] = ThisNode;
                        ThisNode = 0;
                        printf("\n%d] ", GraphData[i][j]);
                        IsStartingNode = 0;
                    }
                    else
                    {
                        GraphData[i][j] = ThisNode;
                        ThisNode = 0;
                    }
                }
                else
                {
                    GraphData[i][j] = ThisNode;
                    ThisNode = 0;
                    printf("(%d,", GraphData[i][j]);
                }
            }
            else if (CurrentChar == '>')
            {
                j++;
            }
        }
        //printf("test\n");

        //* Storing Labels ..
        if (CurrentChar == '"')
        {
            CurrentChar = fgetc(SortedFile);
            GraphData[i][j] = CurrentChar;
            printf(" %c)", GraphData[i][j]);
            CurrentChar = fgetc(SortedFile);
            j++;
        }
        IsStartingNode = 1;
        CurrentLine++;
        //printf("Nonber of lines : %d", NumberOfLines);
    }
    printf("Nonber of lines : %d", NumberOfLines);
    for (int i = 1; i < NumberOfLines; i++)
    {
        printf("Nonber of lines : %d", NumberOfLines);

        printf("\n(%d)->", GraphData[i][0]);
        for (int j = 0; j < 2 * NumberOfLines; j++)
        {
            printf("(%d):%c  ",
                   GraphData[i][j],
                   GraphData[i][++j]);
        }
    }
    return 0;
}

//* --------------------------> PeekNextNode :
/*int PeekNextNode()
{
    int Ni = 0;

    NodesOccurrences = (int **)malloc(NumberOfLines * sizeof(int *));
    for (int i = 0; i < NumberOfLines; i++)
    {
        NodesOccurrences[i] = (int *)malloc(2 * sizeof(int));
        NodesOccurrences[i][0] = 0;
        NodesOccurrences[i][1] = 0;
    }

    for (int i = 0; i < NumberOfLines - 1; i++)
    {
        for (int j = i + 1; j < NumberOfLines - 1; j++)
        {
            if (GraphData[i] == GraphData[j])
            {
                NodesOccurrences[Ni][0] = GraphData[i];
                NodesOccurrences[Ni][1]++;
            }
        }
        Ni++;
    }
}*/

//* ---------------------------> SortFile :
void SortFile()
{
    char **StrData = NULL; // String List
    char StrDataTemp[MAX_LEN];

    if ((SortedFile = fopen("SortedFile.dot", "w+")) == NULL)
    {
        printf("Error: Could not open SortedFile.dot\n");
        return;
    }

    // Read and store in a string list.
    while (fgets(StrDataTemp, MAX_LEN, PreSortedFile) != NULL)
    {
        // Remove the trailing newline character
        if (strchr(StrDataTemp, '\n'))
            StrDataTemp[strlen(StrDataTemp) - 1] = '\0';
        StrData = (char **)realloc(StrData, sizeof(char **) * (NumberOfLines + 1));
        StrData[NumberOfLines] = (char *)calloc(MAX_LEN, sizeof(char));
        strcpy(StrData[NumberOfLines], StrDataTemp);
        NumberOfLines++;
    }
    // Sort the array.
    for (int i = 0; i < (NumberOfLines - 1); ++i)
    {
        for (int j = 0; j < (NumberOfLines - i - 1); ++j)
        {
            if (strcmp(StrData[j], StrData[j + 1]) > 0)
            {
                strcpy(StrDataTemp, StrData[j]);
                strcpy(StrData[j], StrData[j + 1]);
                strcpy(StrData[j + 1], StrDataTemp);
            }
        }
    }
    // Write it to outfile. file.
    for (int i = 0; i < NumberOfLines - 2; i++)
        fprintf(SortedFile, "%s\n", StrData[i]);

    free(PreSortedFile);
}
