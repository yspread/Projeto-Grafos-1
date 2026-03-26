#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

int main()
{
    int option;
    int N, x, y, w;
    int res;
    bool printstatus = 1;
    GRAFO *G;
    scanf("%d", &option);
    while(option != -1)
    {
        switch(option)
        {
        case 0:
            scanf("%d", &N);
            G = criargrafo(N);
            break;
        case 1:
            scanf("%d %d %d", &x, &y, &w);
            addaresta(G, x, y, w);                
            break;
        case 2:
            scanf("%d %d", &x, &y);
            res = existearesta(G, x, y);
            printstatus = 0;
            break;
        default:
            printf("unrecognized option %d!\n", option);
        }
        scanf("%d\n", &option);
    }
    if (option == -1)
    {
        if(printstatus)
        {
            printinfo(G);
        }
        else{
            printf("%d\n", res);
        }
    }
    apagargrafo(&G);
    return 0;
}
