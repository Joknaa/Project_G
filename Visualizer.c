#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Graph Graph;
struct Graph
{
    int **Nodes;
    char *Labels;
};

//* ---------------------------> Globals :
Graph InitialGraph;
FILE *InitialFile = NULL;
FILE *epfile = NULL;
FILE *opfile = NULL;
char mycommand[100], CurrentChar;
int NumberOfLines = 0, CurrentLine = 1, Ni = 0, Nj = 0, Li = 0;

//* -----------------------------------> Functions :
void StoreData();

//sorting function
void sort(Graph *Graph, int NumberOfLines)
{
    int permu = 1;
    char tmp[2], tmpc;
    while (permu)
    {
        permu = 0;
        for (int i = 0; i < NumberOfLines - 1; i++)
        {
            if (Graph->Nodes[i][0] > Graph->Nodes[i + 1][0])
            {
                tmp[0] = Graph->Nodes[i][0];
                tmp[1] = Graph->Nodes[i][1];
                Graph->Nodes[i][0] = Graph->Nodes[i + 1][0];
                Graph->Nodes[i][1] = Graph->Nodes[i + 1][1];
                Graph->Nodes[i + 1][0] = tmp[0];
                Graph->Nodes[i + 1][1] = tmp[1];
                tmpc = Graph->Labels[i];
                Graph->Labels[i] = Graph->Labels[i + 1];
                Graph->Labels[i + 1] = tmpc;
                permu = 1;
            }
        }
    }
}

int main()
{
    char *InitialFileName;

    system("cls");
    InitialFileName = (char *)malloc(50 * sizeof(char));

    printf("Enter the file name : ");
    scanf("%s", InitialFileName);

    if ((InitialFile = fopen(InitialFileName, "r")) == NULL)
    {
        printf("\nError! file doesn't exist x_x\n");
        return 0;
    }

    //* --------------->  Number of lines
    while ((CurrentChar = fgetc(InitialFile)) != '}')
    {
        if (CurrentChar == ']')
        {
            NumberOfLines++;
        }
    }

    //* --------------->  SetUp the tables ..
    InitialGraph.Labels = (char *)calloc(NumberOfLines, sizeof(char));
    InitialGraph.Nodes = (int **)calloc(NumberOfLines, sizeof(int *));
    for (int i = 0; i < NumberOfLines; i++)
        InitialGraph.Nodes[i] = (int *)calloc(2, sizeof(int));

    // Store the Nodes/Labels values
    StoreData();

    // Sorting the Nodess
    sort(&InitialGraph, NumberOfLines);

    printf("\n-------------Visualizing the InitialGraph Graph-------------\n\n");
    // Print the stored values of the Nodess
    for (int i = 0; i < NumberOfLines; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%d ", InitialGraph.Nodes[i][j]);
            if (!j)
                printf(" ->  ");
        }
        printf("  [ labels = ' %c ' ]\n", InitialGraph.Labels[i]);
    }

    system(mycommand);
    system("Graph.png");

    // New Graph (epsilon deleted)
    Graph ep;

    // Allocating the memory
    ep.Labels = (char *)calloc(NumberOfLines, sizeof(char));
    ep.Nodes = (int **)calloc(NumberOfLines, sizeof(int *));
    for (int z = 0; z < NumberOfLines; z++)
        ep.Nodes[z] = (int *)calloc(2, sizeof(int));

    //deleting eps
    int l = 0, again = 1, check = 0;
    int tempo = NumberOfLines;

    while (again)
    {
        again = 0;
        for (int i = 0; i < NumberOfLines; i++)
        {
            if (InitialGraph.Labels[i] != '0')
            {
                if (l >= NumberOfLines)
                {
                    ep.Labels = (char *)realloc(ep.Labels, (l + 1) * sizeof(char));
                    ep.Nodes = (int **)realloc(ep.Nodes, (l + 1) * sizeof(int *));
                    for (int z = l; z < l + 1; z++)
                        ep.Nodes[z] = (int *)realloc(ep.Nodes[z], 2 * sizeof(int));
                }

                ep.Nodes[l][0] = InitialGraph.Nodes[i][0];
                ep.Nodes[l][1] = InitialGraph.Nodes[i][1];
                ep.Labels[l] = InitialGraph.Labels[i];
                l++;
            }
            else
            {
                for (int j = 0; j < NumberOfLines; j++)
                {
                    if (InitialGraph.Nodes[i][1] == InitialGraph.Nodes[j][0])
                    {
                        if (l >= NumberOfLines)
                        {
                            ep.Labels = (char *)realloc(ep.Labels, (l + 1) * sizeof(char));
                            ep.Nodes = (int **)realloc(ep.Nodes, (l + 1) * sizeof(int *));
                            for (int z = l; z < l + 1; z++)
                                ep.Nodes[z] = (int *)realloc(ep.Nodes[z], 2 * sizeof(int));
                        }

                        ep.Nodes[l][0] = InitialGraph.Nodes[i][0];
                        ep.Nodes[l][1] = InitialGraph.Nodes[j][1];
                        ep.Labels[l] = InitialGraph.Labels[j];
                        l++;
                        check = 1;
                    }
                }
            }
        }

        if (l > NumberOfLines)
            NumberOfLines = l;
        InitialGraph.Labels = (char *)calloc(NumberOfLines, sizeof(char));
        InitialGraph.Nodes = (int **)calloc(NumberOfLines, sizeof(int *));
        for (int z = 0; z < NumberOfLines; z++)
            InitialGraph.Nodes[z] = (int *)calloc(2, sizeof(int));

        for (int i = 0; i < NumberOfLines; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                InitialGraph.Nodes[i][j] = ep.Nodes[i][j];
            }
            if (ep.Labels[i] == '0')
                again = 1;
            InitialGraph.Labels[i] = ep.Labels[i];
        }

        if (again)
        {
            ep.Labels = (char *)calloc(NumberOfLines, sizeof(char));
            ep.Nodes = (int **)calloc(NumberOfLines, sizeof(int *));
            for (int i = 0; i < NumberOfLines; i++)
                ep.Nodes[i] = (int *)calloc(2, sizeof(int));
        }

        l = 0;
    }
    // sort(&ep,NumberOfLines);
    printf("\n-----Visualizing the new Graph (epsilon deleted)-----\n\n");

    // printing the new Graph
    int salvation = 0;
    for (int i = 0; i < NumberOfLines; i++)
    {
        if ((ep.Labels[i]) != 0)
        {
            salvation++;
            for (int j = 0; j < 2; j++)
            {
                printf("%d ", ep.Nodes[i][j]);
                if (!j)
                    printf(" ->  ");
            }
            printf("  [ labels = ' %c ' ]\n", ep.Labels[i]);
        }
    }

    // Part2 (creating and writing another file)
    epfile = fopen("deletedep.dot", "w+");
    fputs("diGraph new {\n\n", epfile);
    for (int i = 0; i < salvation; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            fprintf(epfile, "%d", ep.Nodes[i][j]);
            fputc(' ', epfile);
            if (!j)
                fputs("-> ", epfile);
        }
        fputs("[labels=\"", epfile);
        fputc(ep.Labels[i], epfile);
        fputs("\"]\n", epfile);
    }
    fputs("\n}", epfile);

    fclose(epfile);

    system("dot -Tpng deletedep.dot -o deletedepGraph.png");
    system("deletedepGraph.png");

    printf("\n-----------------------------------------------------\n\n");

    //nEntering the initial state Nodess
    printf("\nEntering the initial state Nodess\n");
    again = 1;

    int *EI, size = 0, B;
    EI = (int *)malloc(size * sizeof(int));

    while (again)
    {

        printf("\nWould you like to add an initial state Nodes?(type 1 for YES and 0 for No): ");
        scanf("%d", &B);
        if (B)
        {
            EI = (int *)realloc(EI, (++size) * sizeof(int));
            printf("\nEntrer the initial state Nodes N %d :    ", size);
            scanf("%d", &EI[size - 1]);
        }
        else
            again = 0;
    }
    //for(int i=0;i<size;i++)printf("%d\n",EI[i]);

    Graph op;

    op.Labels = (char *)calloc(salvation, sizeof(char));
    op.Nodes = (int **)calloc(salvation, sizeof(int *));
    for (int i = 0; i < salvation; i++)
        op.Nodes[i] = (int *)calloc(2, sizeof(int));

    int x = 0, y = 0, k = 0;

    for (int i = 0; i < salvation; i++)
    {

        for (int j = 0; j < size; j++)
            if (ep.Nodes[i][0] == EI[j])
                x = 1;
        for (int j = 0; j < salvation; j++)
            if (x || (!x && ep.Nodes[i][0] == ep.Nodes[j][1]))
                y = 1;
        if (y)
        {
            op.Nodes[k][0] = ep.Nodes[i][0];
            op.Nodes[k][1] = ep.Nodes[i][1];
            op.Labels[k] = ep.Labels[i];
            k++;
        }
        x = 0;
        y = 0;
    }
    printf("\n---Visualizing the optimized Graph-EI (epsilon deleted)---\n\n");
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%d ", op.Nodes[i][j]);
            if (!j)
                printf(" ->  ");
        }
        printf("  [ labels = ' %c ' ]\n", op.Labels[i]);
    }

    opfile = fopen("deletedop.dot", "w+");
    fputs("diGraph op {\n\n", opfile);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            fprintf(opfile, "%d", op.Nodes[i][j]);
            fputc(' ', opfile);
            if (!j)
                fputs("-> ", opfile);
        }
        fputs("[labels=\"", opfile);
        fputc(op.Labels[i], opfile);
        fputs("\"]\n", opfile);
    }

    fputs("\n}", opfile);
    fclose(opfile);

    system("dot -Tpng deletedop.dot -o deletedopGraph.png");
    system("deletedopGraph.png");

    return 0;
}
//* -----------------------------------> StoreNodess :
void StoreData()
{
rewind(InitialFile);
    int Nodes_i = 0, Labels_i = 0, j = 0;
    while ((CurrentChar = fgetc(InitialFile)) != '}')
    {

        if (isdigit(CurrentChar))
        {

            if (j == 2)
            {
                j = 0;
                Nodes_i++;
            }

            InitialGraph.Nodes[Nodes_i][j] = InitialGraph.Nodes[Nodes_i][j] * 10 + (CurrentChar - '0');
        }
        else
        {
            if ((CurrentChar == '>') || (CurrentChar == '['))
                j++;
        }

        if (CurrentChar == '"')
        {

            while ((CurrentChar = fgetc(InitialFile)) != '"')
            {
                InitialGraph.Labels[Labels_i] = CurrentChar;
                Labels_i++;
            }
        }
    }
}