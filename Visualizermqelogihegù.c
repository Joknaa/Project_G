#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct graph graph;
    struct graph {
    int** node;
    char* weight;
    };

//sorting function
void sort(graph *graph, int count){
    int permu=1;
    char tmp[2], tmpc;
        while(permu){
        permu=0;
        for(int i=0;i<count-1;i++){
            if(graph->node[i][0]>graph->node[i+1][0]){
            tmp[0]=graph->node[i][0]; tmp[1]=graph->node[i][1];
            graph->node[i][0]=graph->node[i+1][0]; graph->node[i][1]=graph->node[i+1][1];
            graph->node[i+1][0]=tmp[0]; graph->node[i+1][1]=tmp[1];
            tmpc=graph->weight[i];
            graph->weight[i]=graph->weight[i+1];
            graph->weight[i+1]=tmpc;
            permu=1;
            }

        }

        }
}


int main()
{
    graph basic;
    FILE *graphfile = NULL;
    FILE *epfile=NULL;
    FILE *opfile=NULL;
    int count=0;
    char graphfile_name[30],mycommand[100], c;
    



    // Selecting the graph's file
    printf("Enter the name of the file (max lenght is 30):  ");
    scanf("%s",graphfile_name);


    // Customize the executed cmd in system()
    strcpy(mycommand,"dot -Tpng ");
    strcat(mycommand,graphfile_name);
    strcat(mycommand," -o graph.png");

    graphfile = fopen(graphfile_name,"r");

    // Counting the instructions
    while((c=fgetc(graphfile))!=EOF){
        if(c == '>') count++;
    }


    // Allocating the memory
    basic.weight=(char*)calloc(count,sizeof(char));
    basic.node=(int**)calloc(count,sizeof(int*));
    for(int i=0; i<count;i++) basic.node[i]=(int*)calloc(2,sizeof(int)); 

    // Store the node/weight values
    rewind(graphfile);
    int node_i=0,weight_i=0, j=0;
    while((c=fgetc(graphfile))!='}'){
    
                if(isdigit(c)){

                    if(j==2){
                        j=0; node_i++;
                    }

                    basic.node[node_i][j]=basic.node[node_i][j]*10+(c-'0');
                    


                }else {if((c=='>') || (c=='[')) j++;}

                if(c == '"'){

                    while((c=fgetc(graphfile))!='"'){
                        basic.weight[weight_i]=c; 
                        weight_i++; 
                    }
                    
                } 
    
    }

    // Sorting the nodes
    sort(&basic, count);

    printf("\n-------------Visualizing the basic graph-------------\n\n");
    // Print the stored values of the nodes
    for(int i=0;i<count;i++){
        for(int j=0;j<2;j++){
            printf("%d ", basic.node[i][j]);
            if(!j) printf(" ->  ");
        }
        printf("  [ label = ' %c ' ]\n",basic.weight[i]);
    }

    system(mycommand);
    system("graph.png");

 
    // New graph (epsilon deleted)
    graph ep;

    // Allocating the memory
    ep.weight=(char*)calloc(count,sizeof(char));
    ep.node=(int**)calloc(count,sizeof(int*));
    for(int z=0;z<count;z++) ep.node[z]=(int*)calloc(2,sizeof(int)); 


    //deleting eps
    int l=0, again=1,check=0;
    int tempo=count;

while(again){                                                                   
    again=0;
    for(int i=0;i<count;i++){
            if(basic.weight[i]!='0'){ 
                if(l>=count){
                    ep.weight=(char*)realloc(ep.weight,(l+1)*sizeof(char));
                    ep.node=(int**)realloc(ep.node,(l+1)*sizeof(int*));
                    for(int z=l; z<l+1;z++) ep.node[z]=(int*)realloc(ep.node[z],2*sizeof(int));}


                ep.node[l][0]=basic.node[i][0]; 
                ep.node[l][1]=basic.node[i][1]; 
                ep.weight[l]=basic.weight[i];
                l++;

            }else{
                for(int j=0;j<count;j++){
                    if(basic.node[i][1]==basic.node[j][0]){
                        if(l>=count){
                        ep.weight=(char*)realloc(ep.weight,(l+1)*sizeof(char));
                        ep.node=(int**)realloc(ep.node,(l+1)*sizeof(int*));
                        for(int z=l; z<l+1;z++) ep.node[z]=(int*)realloc(ep.node[z],2*sizeof(int));}

                            ep.node[l][0]=basic.node[i][0];
                            ep.node[l][1]=basic.node[j][1]; 
                            ep.weight[l]=basic.weight[j];
                            l++;
                            check=1;         
                            
                    }
                    
                }
              /*  if(!check){
                    basic.node
                }
                */
            }
        //if(l>count) count=l;
    }

 if(l>count) count=l;
        basic.weight=(char*)calloc(count,sizeof(char));
        basic.node=(int**)calloc(count,sizeof(int*));
        for(int z=0; z<count;z++) basic.node[z]=(int*)calloc(2,sizeof(int));

  /* for(int i=0;i<count;i++){
        for(int j=0;j<2;j++){
            printf("%d ", basic.node[i][j]);
            if(!j) printf(" ->  ");
        }
        printf("  [ label = ' %c ' ]\n",basic.weight[i]);
    } */

  for(int i=0;i<count;i++){
      for(int j=0;j<2;j++){
          //  printf("%d ",i);
           basic.node[i][j]=ep.node[i][j];
        }
        if(ep.weight[i]=='0') again=1;
        basic.weight[i]=ep.weight[i];
    }

       if(again){
        ep.weight=(char*)calloc(count,sizeof(char));
        ep.node=(int**)calloc(count,sizeof(int*));
        for(int i=0; i<count;i++) ep.node[i]=(int*)calloc(2,sizeof(int));
       }

        

    l=0;
}
    //storing the values of the new graph
     /*   for(int i=0;i<count;i++){
            for(int j=0;j<2;j++){
                ep.node[i][j]=basic.node[i][j];
            }
            ep.weight[i]=basic.weight[i];
        }*/

   // sort(&ep,count);
       printf("\n-----Visualizing the new graph (epsilon deleted)-----\n\n");

    // printing the new graph
    int salvation=0;
    for(int i=0;i<count;i++){ 
      if((ep.weight[i]) != 0)  { salvation++;
      for(int j=0;j<2;j++){
            printf("%d ", ep.node[i][j]);
            if(!j) printf(" ->  ");
        }
        printf("  [ label = ' %c ' ]\n",ep.weight[i]);}
    }

   // Part2 (creating and writing another file)    
    epfile= fopen("deletedep.dot","w+");
    fputs("digraph new {\n\n",epfile);
        for(int i=0;i<salvation;i++){
        for(int j=0;j<2;j++){
            fprintf(epfile,"%d",ep.node[i][j]);
            fputc(' ',epfile);
            if(!j) fputs("-> ",epfile);
        }
        fputs("[label=\"",epfile);
        fputc(ep.weight[i],epfile);
        fputs("\"]\n",epfile);
    }
    fputs("\n}",epfile);

   fclose(epfile);


/*   // re-storing the node/weight values TO BASIC
    rewind(graphfile);
    node_i=0;weight_i=0; j=0;
    while((c=fgetc(graphfile))!='}'){
    
                if(isdigit(c)){
                    basic.node[node_i][j]=(c-'0');
                    j++;

                    if(j==2){
                        j=0; node_i++;
                    }

                }

                if(c == '"'){

                    while((c=fgetc(graphfile))!='"'){
                        basic.weight[weight_i]=c; 
                        weight_i++; 
                    }
                    
                } 
                  
    }
        fclose(graphfile);
    // Sorting the nodes
        sort(&basic, count);
         fclose(graphfile);
*/




   system("dot -Tpng deletedep.dot -o deletedepgraph.png");
   system("deletedepgraph.png");

    printf("\n-----------------------------------------------------\n\n");

    //nEntering the initial state nodes
    printf("\nEntering the initial state nodes\n");
    again=1;

    int *EI,size=0,B;
    EI=(int*)malloc(size*sizeof(int));

    while(again){

        printf("\nWould you like to add an initial state node?(type 1 for YES and 0 for No): ");
        scanf("%d",&B);
        if(B){
                EI=(int*)realloc(EI,(++size)*sizeof(int));
                printf("\nEntrer the initial state node N %d :    ", size);
                scanf("%d",&EI[size-1]);
        }else again=0;

    }
    //for(int i=0;i<size;i++)printf("%d\n",EI[i]);


    graph op;

    op.weight=(char*)calloc(salvation,sizeof(char));
    op.node=(int**)calloc(salvation,sizeof(int*));
    for(int i=0; i<salvation;i++) op.node[i]=(int*)calloc(2,sizeof(int)); 

    int x=0,y=0,k=0;

    for(int i=0;i<salvation;i++){

        for(int j=0;j<size;j++) if(ep.node[i][0]==EI[j]) x=1;
        for(int j=0;j<salvation;j++) if(x || (!x && ep.node[i][0]==ep.node[j][1])) y=1;
        if(y){
            op.node[k][0]=ep.node[i][0];
            op.node[k][1]=ep.node[i][1];
            op.weight[k]=ep.weight[i];
            k++;
        }
        x=0; y=0;
    }
    printf("\n---Visualizing the optimized graph-EI (epsilon deleted)---\n\n");
    for(int i=0;i<k;i++){
        for(int j=0;j<2;j++){
            printf("%d ", op.node[i][j]);
            if(!j) printf(" ->  ");
        }
        printf("  [ label = ' %c ' ]\n",op.weight[i]);

    }


    opfile= fopen("deletedop.dot","w+");
    fputs("digraph op {\n\n",opfile);
        for(int i=0;i<k;i++){
        for(int j=0;j<2;j++){
            fprintf(opfile,"%d",op.node[i][j]);
            fputc(' ',opfile);
            if(!j) fputs("-> ",opfile);
        }
        fputs("[label=\"",opfile);
        fputc(op.weight[i],opfile);
        fputs("\"]\n",opfile);
    }

    fputs("\n}",opfile);
    fclose(opfile);

    system("dot -Tpng deletedop.dot -o deletedopgraph.png");
    system("deletedopgraph.png");

    return 0;
    
}