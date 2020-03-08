#include <stdio.h>

int main(int argc, char const *argv[])
{
    //****************supression des epsilons ****
    int i,j,k,h;
    FILE *fichier_pointeur2 = NULL; //CREATION DU FICHIER GRAPH2
    fichier_pointeur2 = fopen("graph2.dot", "w+");
    if (fichier_pointeur2 == NULL)
        printf("erreur");
    else
    {
        for (i = 1; i < n - 2; i++)
        {
            if (tabdetransition[i][2] == '0')
            {
                for (k = 1; k < n - 1; k++)
                {
                    if (tabdetransition[k][0] == tabdetransition[i][1])
                    {
                        if (tabdetransition[k][2] != '0')
                            tabdetransition[i][2] = tabdetransition[k][2];
                        else if (tabdetransition[k][2] == '0')
                        {
                            n++;
                            tabdetransition[n - 2][0] = tabdetransition[i][0];
                            tabdetransition[n - 2][1] = tabdetransition[k][1];
                            for (h = 1; h < n - 1; h++)
                            {
                                if (tabdetransition[h][0] == tabdetransition[k][1])
                                {
                                    if (tabdetransition[h][2] != '0')
                                        tabdetransition[n - 2][2] = tabdetransition[h][2];
                                    if (tabdetransition[h][2] == '0')
                                        tabdetransition[n - 2][2] = '0';
                                }
                                else
                                    tabdetransition[n - 2][2] = '0';
                            }
                        }
                    }
                }
            }
        }
        //affichage du tableau *********************
        printf("la table apres supression des epsilons est :\n");
        for (i = 1; i < n - 1; i++)
        {
            for (j = 0; j < 3; j++)
                printf("%c\t", tabdetransition[i][j]);
            printf("\n");
        }

        //
        for (i = 1; i < n - 1; i++)
        {
            // if(tabdetransition[i][2]=='0')
            while (tabdetransition[i][2] == '0')
            {

                tabdetransition[i][0] = tabdetransition[n - 2][0];
                tabdetransition[i][1] = tabdetransition[n - 2][1];
                tabdetransition[i][2] = tabdetransition[n - 2][2];
                tabdetransition[i][3] = tabdetransition[n - 2][3];
                n--;
            }
        }

        //affichage du tableau *********************
        printf("la table apres supression des epsilons est :\n");
        for (i = 1; i < n - 1; i++)
        {
            for (j = 0; j < 3; j++)
                printf("%c\t", tabdetransition[i][j]);
            printf("\n");
        }

        //ecriture dans graph2 *******************
        fprintf(fichier_pointeur2, "Digraph {");
        fprintf(fichier_pointeur2, "\n");
        for (i = 1; i < n - 1; i++)
        {
            fprintf(fichier_pointeur2, "%c->%c[label=\"%c\"];", tabdetransition[i][0], tabdetransition[i][1], tabdetransition[i][2]);
            fprintf(fichier_pointeur2, "\n");
        }
        fprintf(fichier_pointeur2, "}");
        //***************
        fclose(fichier_pointeur2);
        system("dot -Tpng graph2.dot -o test2.png");
        system("test2.png");
    }
return 0;
}