
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//* ---------------------------> Structs :
typedef struct Graph
{
    char **GraphData;
} Graph;

//* ---------------------------> Globals :
#define MAX_LEN 30 // Length of each line in input file.
FILE *SortedFile;
FILE *PreSortedFile;
Graph myGraph;
char *myFileName;
int NumberOfLines = 0, CurrentLine = 0, i = 0, j = 0;
int **NodesOccurrences;

//* ---------------------------> Funcions :
void SortFile();

//* ---------------------------> Main :
int main(int argc, char const *argv[])
{
    int ThisNode = 0, IsStartingNode = 1;
    system("cls");
    myFileName = (char *)malloc(50 * sizeof(char));

    if ((PreSortedFile = fopen("Labels.dot", "r")) == NULL)
    {
        printf("\nError! file doesn't exist x_x\n");
        return 0;
    }

    //* --------------->  Sort the file
    //SortFile();
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
    for (int i = 1; i < NumberOfLines - 2; i++)
        fprintf(SortedFile, "%s\n", StrData[i]);

    free(PreSortedFile);

    //* --------------->  SetUp the tables ..
    myGraph.GraphData = (char **)malloc(NumberOfLines * sizeof(char *));
    for (int i = 0; i < NumberOfLines; i++)
    {
        myGraph.GraphData[i] = (char *)calloc(2 * NumberOfLines, sizeof(char));
    }
    printf("%d\n", SortedFile);

    //* --------------->  Store Data ..n
    rewind(SortedFile);
    printf("Position after rewind : %d\n", ftell(SortedFile));

    char CurrentChar = 'e';

    for (CurrentLine = 0; CurrentLine < 8; CurrentLine++)
    {
        //printf("Cursur Position : %d \t char : (%c)\n", ftell(SortedFile), CurrentChar);

        //* Storing Nodes ..
        while ((CurrentChar = fgetc(SortedFile)) != '"')
        {
            printf("char:%c.\t isdigit:%d\n", CurrentChar, isdigit(CurrentChar));
            if (isdigit(CurrentChar))
            {
                do
                {
                    ThisNode = ThisNode * 10 + (CurrentChar - '0');
                } while (isdigit(CurrentChar = fgetc(SortedFile)));
                if (IsStartingNode == 1)
                {
                    if (ThisNode != myGraph.GraphData[i][0])
                    {
                        j = 0;
                        myGraph.GraphData[++i][0] = ThisNode;
                        IsStartingNode = 0;
                    }
                    else
                    {
                        myGraph.GraphData[i][j] = ThisNode;
                    }
                }
                else
                {
                    myGraph.GraphData[i][j] = ThisNode;
                }
            }
            else if (CurrentChar == '>')
            {
                j++;
            }
        }

        //* Storing Labels ..
        if (CurrentChar == '"')
        {
            CurrentChar = fgetc(SortedFile);
            myGraph.GraphData[i][j] = CurrentChar;
            j++;
        }
        IsStartingNode = 1;
    }
    for (int i = 1; i < NumberOfLines; i++)
    {
        printf("\n(%d)->", myGraph.GraphData[i][0]);
        for (int j = 0; j < 2 * NumberOfLines; j++)
        {
            printf("(%d):%s  ",
                   myGraph.GraphData[i][j],
                   myGraph.GraphData[i][++j]);
        }
        printf("\n");
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
            if (myGraph.GraphData[i] == myGraph.GraphData[j])
            {
                NodesOccurrences[Ni][0] = myGraph.GraphData[i];
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

    if ((SortedFile = fopen("SortedFile.dot", "w")) == NULL)
    {
        if ((SortedFile = fopen("SortedFile.dot", "a")) == NULL)
        {
            printf("Error: Could not open SortedFile.dot\n");
            return;
        }
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
    for (int i = 0; i < NumberOfLines; i++)
        fprintf(SortedFile, "%s\n", StrData[i]);

    free(PreSortedFile);
}
