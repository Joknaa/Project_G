#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//* -----------------------------------> Struct :
typedef struct Graph Graph;
struct Graph
{
    int **Nodes;
    char **Labels;
};

//* -----------------------------------> Globale Variables :
FILE *myFile;
int NumberOfLines = 1, Ni = 0, Nj = 0, Li = 0, Lj = 0;
char CurrentChar;
Graph myGraph;

//* -----------------------------------> Functions :
void CountLines();
void StoreNodes();
void StoreLabels();
void SetUpGraphVars();
void PrintData();
void ShowImage();

//* ----------------------------------------------------> Main :
int main()
{
    system("cls");
    int CurrentLine = 1;
    char *myFileName, *myFileRoot = malloc((strlen("Graphviz_files/ ")) * sizeof(char));

    /*printf("Enter the file name : ");
    scanf("%s", myFileName);*/
    myFileName = "Labels.dot";

    if (myFile = fopen(myFileName, "r"))
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
        PrintData();
        ShowImage(myFileName);
    }
    else
    {
        printf("\nError! file doesn't exist x_x\n");
    }
    fclose(myFile);
    return 0;
}

//* -----------------------------------> ShowImage :
void ShowImage(char *myFileName)
{
    char myCommande[] = "dot -Tpng ";
    char pictureName[] = "ImageTest.png";
    strcat(myCommande, myFileName);
    strcat(myCommande, " -o ");
    strcat(myCommande, pictureName);
    system(myCommande);
}

//* -----------------------------------> PrintData :
void PrintData()
{
    for (int i = 0; i < Ni; i++)
    {
        printf("\n(%d) ------[%s]------> (%d)", myGraph.Nodes[i][0], myGraph.Labels[i], myGraph.Nodes[i][1]);
    }
}

//* -----------------------------------> SetUpGraphVars :
void SetUpGraphVars()
{
    myGraph.Nodes = (int **)malloc(NumberOfLines * sizeof(int *));
    for (int i = 0; i < NumberOfLines; i++)
    {
        myGraph.Nodes[i] = (int *)malloc(sizeof(int));
        myGraph.Nodes[i][0] = 0;
        myGraph.Nodes[i][1] = 0;
    }

    myGraph.Labels = (char **)malloc(NumberOfLines * sizeof(char *));
    for (int i = 0; i < NumberOfLines; i++)
        myGraph.Labels[i] = (char *)malloc(2 * sizeof(char));
}

//* -----------------------------------> CountLines :
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
}

//* -----------------------------------> StoreNodes :
void StoreNodes()
{
    while ((CurrentChar = fgetc(myFile)) != '"')
    {
        if (isdigit(CurrentChar))
        {
            do
            {
                myGraph.Nodes[Ni][Nj] = myGraph.Nodes[Ni][Nj] * 10 + (CurrentChar - '0');
            } while (isdigit(CurrentChar = fgetc(myFile)));
        }
        else if (CurrentChar == '>')
        {
            Nj++;
        }
    }
    Ni++;
    Nj = 0;
}

//* -----------------------------------> StoreLabels :
void StoreLabels()
{
    int LSize;

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
    //printf("\nLabel : %s", myGraph.Labels[Li]);
    Li++;
}
