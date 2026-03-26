#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

typedef struct grafo_
{
    int nVertices;
    int **matrizAdjacencia;
}GRAFO;

GRAFO* criargrafo(int n)
{
    GRAFO *grafo = (GRAFO *)malloc(sizeof(GRAFO));
    if (grafo != NULL)
    {
        grafo->nVertices = n;
        grafo->matrizAdjacencia = (int **)malloc(n * sizeof(int *)); //alocando a matriz de adjacencia dinamicamente
        for (int i = 0; i < n; i++)
        {
            grafo->matrizAdjacencia[i] = (int*)malloc(n * sizeof(int));
            for (int j = 0; j < n; j++)
            {
                grafo->matrizAdjacencia[i][j] = -1; //-1 indica a ausência de aresta entre os vértices i e j
            }
        }
    }
    return grafo;
}

void addaresta(GRAFO *grafo, int v1, int v2, int peso)
{
    if (grafo != NULL || v1 > grafo->nVertices || v2 > grafo->nVertices)
    {
        grafo->matrizAdjacencia[v1-1][v2-1] = peso; //escrevo o peso na posição correta da matriz de adjacência;
        grafo->matrizAdjacencia[v2-1][v1-1] = peso; //adiciono no simétrico também, considerando arestas bidirecionais
    }
    else{
        printf("-1");
    }
}

int existearesta(GRAFO *grafo, int v1, int v2)
{
    if (grafo != NULL)
    {
        if (grafo->matrizAdjacencia[v1-1][v2-1] != -1) //-1 na matriz indica que a aresta não existe
        {
            return 0; //a aresta entre v1 e v2 não existe
        }
        else
        {
            return 1;//a aresta entre v1 e v2 existe
        }
    }
}
void vizinhos (GRAFO *grafo, int v)
{
    if (grafo != NULL)
    {
        printf("V = [");
        for (int i = 0; i < grafo->nVertices; i++) //percorro a linha da matriz correspondente ao vertice v
        {
            if (grafo->matrizAdjacencia[v-1][i] != -1) //caso o valor da matriz seja diferente de -1, existirá uma aresta entre o vértice v e o vértice correspondente a coluna
            {
                printf("%d, ", i); //imprimo o número do vértice (também é o número da coluna) que divide aresta com v
            }
        }
        printf("\b\b]");
    }
}

int apagaaresta (GRAFO *grafo, int v1, int v2)
{
    if (grafo != NULL)
    {
        if (grafo->matrizAdjacencia[v1-1][v2-1] == -1) //caso a aresta não exista, printa e retorna -1
        {
            printf("-1");
            return -1;
        }
        else //caso a aresta existe (seja diferente de -1), colocamos -1 nos espaços equivalentes a aresta a ser apagada
        {
            grafo->matrizAdjacencia[v1-1][v2-1] = -1;
            grafo->matrizAdjacencia[v2-1][v1-1] = -1;
            return 1;
        }
    }
}   
void printinfo (GRAFO *grafo)
{
    if (grafo != NULL)
    {
        printf("V = [");
        for(int i = 1; i <= grafo->nVertices; i++)
        {   
            if (i != grafo->nVertices)
            {
                printf("%d, ", i);
            }
            else{
                printf("%d]\n", i);
            }
        }
        printf ("E = [");
        for (int i = 0; i < grafo->nVertices; i++)
        {
            for (int j = i; j < grafo->nVertices; j++)
            {
                if (grafo->matrizAdjacencia[i][j] != -1)
                {
                    printf("(%d, %d),  ", (i+1), (j+1));
                }
            }
        }
        printf("\b\b]");
    }
}

void apagargrafo(GRAFO **grafo)
{
    if (*grafo != NULL)
    {
        //libero toda a memória alocada para a matriz de adjacencia
        for (int i = 0; i < (*grafo)->nVertices; i++)
        {
            free((*grafo)->matrizAdjacencia[i]);
            (*grafo)->matrizAdjacencia[i] = NULL;
        }
        free ((*grafo)->matrizAdjacencia);
        (*grafo)->matrizAdjacencia = NULL;
    }
    free(*grafo); //libero a memória alocada para o grafo
    *grafo = NULL;
}

int maisvizinhos(GRAFO *grafo)
{
    if (grafo != NULL)
    {
        int vertice, contador = 0, maior = 0; //vertice armazenará o vértice com mais vizinhos, contador conta quantos vizinhos cada vértice tem, maior guarda o n de vizinhos do vertice que mais tem ate então
        for (int i = 0; i < grafo->nVertices; i++) //percorro pela matriz
        {
            for (int j = 0; j < grafo->nVertices; j++)
            {
                if (grafo->matrizAdjacencia[i][j] != -1) //verifico quantas arestas cada vértice tem, vertice por vertice
                {
                    contador++;
                }
            }
            if (contador > maior) //se o contador for maior que o maior numero de vizinhos ate entao, esse valor será o novo maior numero de vizinhos
            {
                vertice = i; //o vertice atual é o novo vértice com mais vizinhos
                maior = contador;
            }
            contador = 0; //o contador reinicia para o próximo vertice
        }
        return (vertice+1); // a posição do vértice na matriz é sempre 1 a menos do que o numero do vértice, pois a matriz começa no 0 e não no 1
    }
    return 0;
}

int **getmatrizadj(GRAFO *grafo)
{
    if (grafo != NULL)
    {
        return (grafo->matrizAdjacencia); //função que retorna a matriz de adjacencia
    }
}
