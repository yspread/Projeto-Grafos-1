#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    int option; //identifica qual caso teste será aplicado
    int N, x, y, w;//N é o número de vértices do grafo e x, y e w são os inputs que serão dados pelos usuários a depender da operação
    int res;
    int printmatriz = 0; //indica se a matriz de adjacencia será printada ou não
    int *osvizinhos = NULL; //vetor de vizinhos, será usado apenas no caso 3
    bool printstatus = 1; //indica se chamaremos a função print info e printaremos o grafo ou se apenas printaremos o status da operação feita
    GRAFO *G;
    scanf("%d", &option);
    while(option != -1)
    {
        switch(option)
        {
        case 0: //aqui criamos o grafo com n vértices
            scanf("%d", &N);
            G = criargrafo(N);
            break;
        case 1: //nesse caso criamos no grafo uma aresta entre x e y, de peso w
            scanf("%d %d %d", &x, &y, &w);
            addaresta(G, x, y, w);                
            break;
        case 2: //nesse caso verificamos se existe aresta entre x e y
            scanf("%d %d", &x, &y);
            res = existearesta(G, x, y);
            printstatus = 0; //iremos printar o status da operação (1 se existe e -1 se não)
            break;
        case 3: //nesse caso printamos o array de vizinhos do vértice x
            scanf("%d", &x);
            osvizinhos = vizinhos(G, x);
            break;
        case 4: //nesse caso apagamos a aresta entre x e y, se esta existir
            scanf("%d %d", &x, &y);
            res = apagaaresta(G, x, y);
            if (res == -1) //caso de erro na função apagaaresta, iremos printar o valor de res (-1), mas caso seja bem sucedido, printaremos o grafo completo, sem a aresta removida
            {
                printstatus = 0;
            }
            break;
        case 5: //caso para imprimir a matriz de adjacência
            printmatriz = 1;
            break;
        case 6: //caso para retornar o vértice com mais vizinhos
            res = maisvizinhos(G); //res vai armazenar o vértice com mais vizinhos
            printf("max vertex: ");
            printstatus = 0; //para printar o valor de res
            break;
        default:
            printf("unrecognized option %d!\n", option);
        }
        scanf("%d", &option);
    }
    if (option == -1)
    {
        if(printstatus)
        {
            if (printmatriz)
            {
                printf("Adjacency Matrix:\n"); //impressao da matriz de adjacência
                int valorprint; //valor que será printado por posição da matriz
                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        valorprint = getmatrizadj(G)[i][j];
                        if ((valorprint) == -1)
                            valorprint = 0; //se a posição da matriz valer -1, eu devo printar 0 no lugar
                        }
                        if (j == 0) //para consertar a formação e fazer de acordo com a saída esperada
                        {
                            printf("%3d", valorprint);
                        }
                        else{
                            printf("%4d", valorprint);
                        }
                    }
                    printf("\n");
                }
            }
            else
            {
                printinfo(G, osvizinhos); //printamos o estado do grafo, printamos os vizinhos de um vértice caso option = 3 tenha sido acionado
                if (osvizinhos != NULL)
                {
                    free(osvizinhos); //liberamos a memória se necessário
                    osvizinhos = NULL;
                }
            }
        }
        else //printamos o status da operação
        {
            printf("%d\n", res);
        }
    }
    apagargrafo(&G);
    return 0;
}