#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Graph Graph;
struct Graph
{
    int **Node;
    char *Label;
};

//* ---------------------------> Globals :
Graph InitialGraph;

//sorting function
void sort(Graph *Graph, int count)
{
    int permu = 1;
    char tmp[2], tmpc;
    while (permu)
    {
        permu = 0;
        for (int i = 0; i < count - 1; i++)
        {
            if (Graph->Node[i][0] > Graph->Node[i + 1][0])
            {
                tmp[0] = Graph->Node[i][0];
                tmp[1] = Graph->Node[i][1];
                Graph->Node[i][0] = Graph->Node[i + 1][0];
                Graph->Node[i][1] = Graph->Node[i + 1][1];
                Graph->Node[i + 1][0] = tmp[0];
                Graph->Node[i + 1][1] = tmp[1];
                tmpc = Graph->Label[i];
                Graph->Label[i] = Graph->Label[i + 1];
                Graph->Label[i + 1] = tmpc;
                permu = 1;
            }
        }
    }
}

int main()
{
    Graph InitialGraph;
    FILE *Graphfile = NULL;
    FILE *epfile = NULL;
    FILE *opfile = NULL;
    int count = 0;
    char Graphfile_name[30], mycommand[100], c;

    // Selecting the Graph's file
    printf("Enter the file name : ");
    scanf("%s", Graphfile_name);

    // Customize the executed cmd in system()
    strcpy(mycommand, "dot -Tpng ");
    strcat(mycommand, Graphfile_name);
    strcat(mycommand, " -o Graph.png");

    Graphfile = fopen(Graphfile_name, "r");

    // Counting the instructions
    while ((c = fgetc(Graphfile)) != EOF)
    {
        if (c == '>')
            count++;
    }

    // Allocating the memory
    InitialGraph.Label = (char *)calloc(count, sizeof(char));
    InitialGraph.Node = (int **)calloc(count, sizeof(int *));
    for (int i = 0; i < count; i++)
        InitialGraph.Node[i] = (int *)calloc(2, sizeof(int));

    // Store the Node/Label values
    rewind(Graphfile);
    int Node_i = 0, Label_i = 0, j = 0;
    while ((c = fgetc(Graphfile)) != '}')
    {

        if (isdigit(c))
        {

            if (j == 2)
            {
                j = 0;
                Node_i++;
            }

            InitialGraph.Node[Node_i][j] = InitialGraph.Node[Node_i][j] * 10 + (c - '0');
        }
        else
        {
            if ((c == '>') || (c == '['))
                j++;
        }

        if (c == '"')
        {

            while ((c = fgetc(Graphfile)) != '"')
            {
                InitialGraph.Label[Label_i] = c;
                Label_i++;
            }
        }
    }

    // Sorting the Nodes
    sort(&InitialGraph, count);

    printf("\n---------------> Initial Graph : \n\n");
    // Print the stored values of the Nodes
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%d ", InitialGraph.Node[i][j]);
            if (!j)
                printf(" ->  ");
        }
        printf("  [ label = ' %c ' ]\n", InitialGraph.Label[i]);
    }

    system(mycommand);
    system("Graph.png");

    // New Graph (epsilon deleted)
    Graph ep;

    // Allocating the memory
    ep.Label = (char *)calloc(count, sizeof(char));
    ep.Node = (int **)calloc(count, sizeof(int *));
    for (int z = 0; z < count; z++)
        ep.Node[z] = (int *)calloc(2, sizeof(int));

    //deleting eps
    int l = 0, again = 1, check = 0;
    int tempo = count;

    while (again)
    {
        again = 0;
        for (int i = 0; i < count; i++)
        {
            if (InitialGraph.Label[i] != '0')
            {
                if (l >= count)
                {
                    ep.Label = (char *)realloc(ep.Label, (l + 1) * sizeof(char));
                    ep.Node = (int **)realloc(ep.Node, (l + 1) * sizeof(int *));
                    for (int z = l; z < l + 1; z++)
                        ep.Node[z] = (int *)realloc(ep.Node[z], 2 * sizeof(int));
                }

                ep.Node[l][0] = InitialGraph.Node[i][0];
                ep.Node[l][1] = InitialGraph.Node[i][1];
                ep.Label[l] = InitialGraph.Label[i];
                l++;
            }
            else
            {
                for (int j = 0; j < count; j++)
                {
                    if (InitialGraph.Node[i][1] == InitialGraph.Node[j][0])
                    {
                        if (l >= count)
                        {
                            ep.Label = (char *)realloc(ep.Label, (l + 1) * sizeof(char));
                            ep.Node = (int **)realloc(ep.Node, (l + 1) * sizeof(int *));
                            for (int z = l; z < l + 1; z++)
                                ep.Node[z] = (int *)realloc(ep.Node[z], 2 * sizeof(int));
                        }

                        ep.Node[l][0] = InitialGraph.Node[i][0];
                        ep.Node[l][1] = InitialGraph.Node[j][1];
                        ep.Label[l] = InitialGraph.Label[j];
                        l++;
                        check = 1;
                    }
                }
            }
        }

        if (l > count)
            count = l;
        InitialGraph.Label = (char *)calloc(count, sizeof(char));
        InitialGraph.Node = (int **)calloc(count, sizeof(int *));
        for (int z = 0; z < count; z++)
            InitialGraph.Node[z] = (int *)calloc(2, sizeof(int));

        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                InitialGraph.Node[i][j] = ep.Node[i][j];
            }
            if (ep.Label[i] == '0')
                again = 1;
            InitialGraph.Label[i] = ep.Label[i];
        }

        if (again)
        {
            ep.Label = (char *)calloc(count, sizeof(char));
            ep.Node = (int **)calloc(count, sizeof(int *));
            for (int i = 0; i < count; i++)
                ep.Node[i] = (int *)calloc(2, sizeof(int));
        }

        l = 0;
    }
    // sort(&ep,count);
    printf("\n---------------> Non-Epsilon Graph :\n\n");

    // printing the new Graph
    int salvation = 0;
    for (int i = 0; i < count; i++)
    {
        if ((ep.Label[i]) != 0)
        {
            salvation++;
            for (int j = 0; j < 2; j++)
            {
                printf("%d ", ep.Node[i][j]);
                if (!j)
                    printf(" ->  ");
            }
            printf("  [ label = ' %c ' ]\n", ep.Label[i]);
        }
    }

    // Part2 (creating and writing another file)
    epfile = fopen("deletedep.dot", "w+");
    fputs("diGraph new {\n\n", epfile);
    for (int i = 0; i < salvation; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            fprintf(epfile, "%d", ep.Node[i][j]);
            fputc(' ', epfile);
            if (!j)
                fputs("-> ", epfile);
        }
        fputs("[label=\"", epfile);
        fputc(ep.Label[i], epfile);
        fputs("\"]\n", epfile);
    }
    fputs("\n}", epfile);

    fclose(epfile);

    system("dot -Tpng deletedep.dot -o deletedepGraph.png");
    system("deletedepGraph.png");

    //nEntering the initial state Nodes
    printf("\n---------------> Optimizing the Graph :\n");
    again = 1;

    int *EI, size = 0, B;
    EI = (int *)malloc(size * sizeof(int));

    while (again)
    {

        printf("\nDo you want to add another initial state node ? (1=Yes | 0=No)");
        scanf("%d", &B);
        if (B)
        {
            EI = (int *)realloc(EI, (++size) * sizeof(int));
            printf("\nEntrer the initial state Node N %d :    ", size);
            scanf("%d", &EI[size - 1]);
        }
        else
            again = 0;
    }
    //for(int i=0;i<size;i++)printf("%d\n",EI[i]);

    Graph op;

    op.Label = (char *)calloc(salvation, sizeof(char));
    op.Node = (int **)calloc(salvation, sizeof(int *));
    for (int i = 0; i < salvation; i++)
        op.Node[i] = (int *)calloc(2, sizeof(int));

    int x = 0, y = 0, k = 0;

    for (int i = 0; i < salvation; i++)
    {

        for (int j = 0; j < size; j++)
            if (ep.Node[i][0] == EI[j])
                x = 1;
        for (int j = 0; j < salvation; j++)
            if (x || (!x && ep.Node[i][0] == ep.Node[j][1]))
                y = 1;
        if (y)
        {
            op.Node[k][0] = ep.Node[i][0];
            op.Node[k][1] = ep.Node[i][1];
            op.Label[k] = ep.Label[i];
            k++;
        }
        x = 0;
        y = 0;
    }
    printf("\n---------------> Non-Epsilon Optimized Graph :\n\n");
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%d ", op.Node[i][j]);
            if (!j)
                printf(" ->  ");
        }
        printf("  [ label = ' %c ' ]\n", op.Label[i]);
    }

    opfile = fopen("deletedop.dot", "w+");
    fputs("diGraph op {\n\n", opfile);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            fprintf(opfile, "%d", op.Node[i][j]);
            fputc(' ', opfile);
            if (!j)
                fputs("-> ", opfile);
        }
        fputs("[label=\"", opfile);
        fputc(op.Label[i], opfile);
        fputs("\"]\n", opfile);
    }

    fputs("\n}", opfile);
    fclose(opfile);

    system("dot -Tpng deletedop.dot -o deletedopGraph.png");
    system("deletedopGraph.png");

    return 0;
}