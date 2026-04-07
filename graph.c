#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

typedef struct grafo_
{
    int nVertices;
    int **matrizAdjacencia;
}GRAFO;

//função para alocar memmória para a matriz de adjacência
GRAFO* criargrafo(int n)
{
    GRAFO *grafo = (GRAFO *)malloc(sizeof(GRAFO));
    if (grafo != NULL)
    {
        grafo->nVertices = n;
        grafo->matrizAdjacencia = (int **)malloc(n * sizeof(int *)); //matriz de adjacência alocada dinamicamente
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

//função para se adicionar uma aresta no grafo, marcando na matriz de adjacência
//como os vértices são indexados de 1 a N, mas as linhas e colunas vão do indice 0 ao indice N-1
//sempre marcaremos que uma aresta entre v1 e v2 estará no espaço [v1-1][v2-2] da matriz
void addaresta(GRAFO *grafo, int v1, int v2, int peso)
{
    if (grafo != NULL && v1 <= grafo->nVertices && v2 <= grafo->nVertices) //os vértices devem ser válidos para ser possível adicionar uma aresta
    {
        grafo->matrizAdjacencia[v1-1][v2-1] = peso; //escrevo o peso na posição correta da matriz de adjacência;
        grafo->matrizAdjacencia[v2-1][v1-1] = peso; //adiciono no simétrico também, considerando arestas bidirecionais
    }
    else
    {
        printf("-1"); //não foi possível criar a aresta
    }
}

//função para verificar se uma aresta entre 2 vértices existe
int existearesta(GRAFO *grafo, int v1, int v2)
{
    if (grafo != NULL)
    {
        if (grafo->matrizAdjacencia[v1-1][v2-1] != -1) //-1 na matriz indica que a aresta não existe
        {
            return 1; //a aresta entre v1 e v2 existe
        }
        else
        {
            return 0;//a aresta entre v1 e v2 não existe
        }
    }
}

//retorna um vetor contendo os vértices adjacentes a v
int *vizinhos (GRAFO *grafo, int v)
{
    if (grafo != NULL)
    {
        int *vizinhos = (int *)malloc((grafo->nVertices + 1)* sizeof(int)); //array de vizinhos, seu tamanho é a quantidade de vértices do grafo. Ele é alocado dinâmicamente para que eu possa utilizá-lo fora do escopo da função
        int p = 0; //marca a posição do vetor que os vizinhos serão adicionados
        for (int i = 0; i < grafo->nVertices; i++) //percorro a linha da matriz correspondente ao vertice v
        {
            if (grafo->matrizAdjacencia[v-1][i] != -1) //caso o valor da matriz seja diferente de -1, existirá uma aresta entre o vértice v e o vértice correspondente a coluna
            {
                vizinhos[p] = i+1; //coloco o valor do vértice correspondente a coluna no array de vizinhos, pois ele é adjacente a v
                p++;//passo pra próxima posição do vetor
            }
        }
        if(p == 0)
        {
            return NULL;
        }
        for (p; p <= grafo->nVertices; p++) //foi alocado anteriormente nVertices + 1 espaços de memória para se ter certeza de que terá pelo menos 1 '0' no vetor
        {
            vizinhos[p] = 0; //prenche o resto do vetor com zeros 
        }
        return vizinhos;
    }
}

//deleta uma aresta entre v1 e v2, se essa existir
int apagaaresta (GRAFO *grafo, int v1, int v2)
{
    if (grafo != NULL && v1 <= grafo->nVertices && v2 <= grafo->nVertices) //verifica se os vértices são validos
    {
        if (grafo->matrizAdjacencia[v1-1][v2-1] == -1) //caso a aresta não exista retorna -1
        {
            return -1;
        }
        else //caso a aresta existe (seja diferente de -1), colocamos -1 nos espaços equivalentes a aresta a ser apagada
        {
            grafo->matrizAdjacencia[v1-1][v2-1] = -1;
            grafo->matrizAdjacencia[v2-1][v1-1] = -1;
            return 1;
        }
    }
    return -1; //se o usuário forneceu vértices inválidos também retornamos erro
}  

//essa função pode imprimir 2 coisas
//caso int *vetor seja NULL, imprimimos o conjunto de vértices e arestas do grafo
//caso vetor seja != de NULL, imprimimos o vetor, esse vetor corresponde ao vetor de vertices adjacentes a um vertice informado na main
void printinfo (GRAFO *grafo, int *vetor)
{
    if (grafo != NULL && vetor == NULL) //nesse caso, imprimimo vertices e arestas do grafo
    {
        int primeiro = 1; //marcador serve para identificar a primeira aresta (apenas para fazer a formatação correta), ele será mudado para 0 depois que a primeira aresta tiver sido imprimida
        printf("V = [");
        for(int i = 1; i <= grafo->nVertices; i++) //imprimo todos os vértices (vão de 1 a nVertices)
        {   
            if (i != grafo->nVertices) //verifica se é o último vértice pra corrigir a formatação da saída
            {
                printf("%d, ", i);
            }
            else{
                printf("%d]\n", i);
            }
        }
        printf("E = [");
        //para imprimir as arestas, percorremos primeiro as colunas e depois as linhas
        for (int j = 1; j < grafo->nVertices; j++) //percorremos a matriz pra ver quais arestas existem e printamos elas
        {
            for (int i = 0; i < j; i++) //a restrição de i < j serve para percorrer na ordem correta de acordo com a formatação pedida
            {
                if (grafo->matrizAdjacencia[i][j] != -1) //se a aresta existe, imprimimos
                {
                    if (primeiro == 0)
                    {
                        printf(", (%d, %d)", (i+1), (j+1));
                    }
                    else{ //se for a primeira aresta a ser imprimida, imprimo sem virgula
                        printf("(%d, %d)", (i+1), (j+1));
                        primeiro = 0; //atualizamos o valor de primeiro
                    }
                }
            }
        }
        printf("]\n");
    }
    if (grafo != NULL && vetor != NULL) //caso o vetor de vizinhos não seja nulo, significa que eu quero printar apenas esse vetor e não o grafo inteiro
    {
        int i = 0;
        while (vetor[i] != 0)
        {
            printf("%d ", vetor[i]);
            i++;
        }
    }
}

//função para se liberar a memória alocada para o grafo
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

//função que retorna o vértice com mais vértices adjacentes do grafo
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

//função para se acessar a matriz de adjacência de um grafo
int **getmatrizadj(GRAFO *grafo)
{
    if (grafo != NULL)
    {
        return (grafo->matrizAdjacencia); //função que retorna a matriz de adjacencia
    }
}
