
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//? -----------------------------------> Ideas :
//todo what about sorting the file before scaning the data, so that the nodes get sorted in the array  ???

//* -----------------------------------> Struct :
typedef struct Graph Graph;
struct Graph
{
    int **Nodes;
    char **Labels;
};

//* -----------------------------------> Globale Variables :
FILE *myFile;
Graph myGraph;
char *myFileName, CurrentChar;
int NumberOfLines = 0, CurrentLine = 1, Ni = 0, Nj = 0, Li = 0, Lj = 0;

//* -----------------------------------> Functions :
void StoreData();
void PrintData();
void ShowImage();
int FindEpsilons();
int GetIndexOfNode();

//* ----------------------------------------------------> Main :
int main()
{
    system("cls");
    myFileName = (char *)malloc(50 * sizeof(char));

    /*printf("Enter the file name : ");
    scanf("%s", myFileName);*/
    myFileName = "Labels.dot";
    if ((myFile = fopen(myFileName, "r")) == NULL)
    {
        printf("\nError! file doesn't exist x_x\n");
        return 0;
    }

    //* --------------->  Count the lines
    while ((CurrentChar = fgetc(myFile)) != '}')
    {
        if (CurrentChar == ']')
        {
            NumberOfLines++;
        }
    }

    //* --------------->  SetUp the tables ..
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

    //* --------------->  Storing the Data ..
    StoreData();
    PrintData();

    //* Working here ..
    int condition = 1;
    while (condition)
    {
        for (int i = 0; i < NumberOfLines; i++)
        {
            if (FindEpsilons(i) != 999)
            {
                printf("\n Node : %d \t Epsilon : %d.", myGraph.Nodes[i][0], FindEpsilons(i));
            }
        }
        condition = 0;
    }

    ShowImage();
    fclose(myFile);
    return 0;
}

//* -----------------------------------> FindEpsilons :
int FindEpsilons(int i)
{
    int NextNode;

    if (strcmp(myGraph.Labels[i], "0") == 0)
    {
        NextNode = GetIndexOfNode(i);
        printf("\n %d", NextNode == i);

        if (NextNode == i)
        {
            return i;
        }
        FindEpsilons(NextNode);
    }
    return 999;
}

//* -----------------------------------> GetIndexOfNode :
int GetIndexOfNode(int EpsilonIndex)
{
    int i;
    for (i = 0; i < NumberOfLines; i++)
    {
        if (myGraph.Nodes[i][0] == myGraph.Nodes[EpsilonIndex][1])
        {
            return i; //! Return an array of nodes !
        }
    }
    return EpsilonIndex;
}

//* -----------------------------------> StoreNodes :
void StoreData()
{
    int LSize;

    rewind(myFile);

    while (CurrentLine <= NumberOfLines)
    {
        //* Storing Nodes ..
        while ((CurrentChar = fgetc(myFile)) != '"')
        {
            printf("char:%c.\t isdigit:%d\n", CurrentChar, isdigit(CurrentChar));

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

        //* Storing Labels ..
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
        Li++;
        CurrentLine++;
    }
}

//* -----------------------------------> PrintData :
void PrintData()
{
    for (int i = 0; i < Ni; i++)
    {
        printf("\n(%d) ------[%s]------> (%d)",
               myGraph.Nodes[i][0],
               myGraph.Labels[i],
               myGraph.Nodes[i][1]);
    }
}

//* -----------------------------------> ShowImage :
void ShowImage()
{
    char myCommande[] = "dot -Tpng ";
    char pictureName[] = "ImageTest.png";
    strcat(myCommande, myFileName);
    strcat(myCommande, " -o ");
    strcat(myCommande, pictureName);
    system(myCommande);
}

int *etat(FILE *fichier_pointeur)
{
    int i = 0, k, j, compteur = 1;
    int *tab_etat;
    char char_actuel;
    tab_etat = (int *)malloc(sizeof(int) * compteur);
    while ((char_actuel = fgetc(fichier_pointeur)) != '}')
    {
        if (isdigit(char_actuel))
        {
            tab_etat = (int *)realloc(tab_etat, sizeof(int) * compteur);
            tab_etat[i] = char_actuel - '0';
            i++;
            compteur++;
        }

        for (i = 0; i < compteur - 1; i++)
        {
            for (j = i + 1; j < compteur - 1; j++)
            {
                if (tab_etat[j] == tab_etat[i])
                {
                    for (k = j; k < compteur - 1; k++)
                    {
                        tab_etat[k] = tab_etat[k + 1];
                    }
                    compteur--;
                }
            }
        }
    }
    for (i = 0; i < compteur - 1; i++)
    {
        printf("%d\n", tab_etat[i]);
    }
    return tab_etat;
}