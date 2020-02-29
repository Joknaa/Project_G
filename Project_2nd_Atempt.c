#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Graph Graph;
struct Graph
{
    int **Nodes;
    char **Labels;
};

FILE *myFile;
int NumberOfLines = 1, CurrentLine = 1;
char CurrentChar;
Graph myGraph;

void CountLines();
void StoreNodes();
void StoreLabels();
void SetUpGraphVars();

//* --------------------------> Main :
int main(int argc, char const *argv[])
{

    if (myFile = fopen("Graphviz_files/Labels.dot", "r"))
    {
        CountLines();
        SetUpGraphVars();
        rewind(myFile);
        while (CurrentLine < NumberOfLines)
        {
            StoreNodes();
            StoreLabels();
            CurrentLine++;
        }
    }
    else
    {
        printf("Error! file doesn't exist ..");
    }
    fclose(myFile);
    return 0;
}

//* ------------> SetUpGraphVars :
void SetUpGraphVars()
{
    myGraph.Nodes = (int **)malloc(NumberOfLines * sizeof(int *));
    for (int i = 0; i < NumberOfLines; i++)
        myGraph.Nodes[i] = (int *)malloc(sizeof(int));

    myGraph.Labels = (char **)malloc(NumberOfLines * sizeof(char *));
    for (int i = 0; i < NumberOfLines; i++)
        myGraph.Labels[i] = (char *)malloc(2 * sizeof(char));
}

//* ------------> LinesCount :
void CountLines()
{
    rewind(myFile);
    while ((CurrentChar = fgetc(myFile)) != '}')
    {
        if (CurrentChar == ']')
        {
            NumberOfLines++;
        }
    }
    printf("\nLines : %d", NumberOfLines);
}

//* ------------> StoreNodes :
void StoreNodes()
{
    int Ni = 0, Nj = 0;

    while ((CurrentChar = fgetc(myFile)) != '"')
    {
        myGraph.Nodes[Ni][Nj] = 0;
        if (isdigit(CurrentChar))
        {
            do
            {
                myGraph.Nodes[Ni][Nj] = myGraph.Nodes[Ni][Nj] * 10 + (CurrentChar - '0');
            } while (isdigit(CurrentChar = fgetc(myFile)));
            printf("\nNode : %d", myGraph.Nodes[Ni][Nj]);
        }
        else if (CurrentChar == '>')
        {
            Nj++;
        }
    }
    Ni++;
}

//* ------------> StoreLabels :
void StoreLabels()
{
    int Li = 0, Lj = 0, LSize;

    if (CurrentChar == '"')
    {
        LSize = 0;
        while ((CurrentChar = fgetc(myFile)) != '"')
        {
            LSize++;
        }

        fseek(myFile, -LSize - 1, SEEK_CUR);
        CurrentChar = fgetc(myFile);
        myGraph.Labels[Li] = realloc(myGraph.Labels[Li], (LSize) * sizeof(char));
        for (Lj = 0; Lj < LSize; Lj++, CurrentChar = fgetc(myFile))
        {
            myGraph.Labels[Li][Lj] = CurrentChar;
        }
        myGraph.Labels[Li][Lj] = '\0';
    }
    printf("\nLabel : %s", myGraph.Labels[Li]);
    Li++;
}