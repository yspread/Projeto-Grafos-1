#ifndef GRAPH_H
    #define GRAPH_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    
    typedef struct grafo_ GRAFO;
    GRAFO* criargrafo(int n); //função para alocar dinamicamente a matriz de adjacência, recebe número de vértices
    void addaresta(GRAFO *grafo, int v1, int v2, int peso); //função que adiciona aresta com seu peso entre v1 e v2
    int existearesta(GRAFO *grafo, int v1, int v2); //função para verificar se uma aresta existe ou não
    int* vizinhos (GRAFO *grafo, int v); //função que retorna os vizinhos do vértice v
    int apagaaresta (GRAFO *grafo, int v1, int v2); //função para apagar uma aresta que liga v1 e v2
    void printinfo (GRAFO *grafo, int *vetor); //função que imprime vértices e arestas, o array serve apenas pra imprimir na chamada da função "vizinhos"
    void apagargrafo(GRAFO **grafo); //apaga a memória reservada pro grafo
    int maisvizinhos(GRAFO *grafo); //função que retorna o vértice com mais vizinhos (em caso de empate, retorna o primeiro)
    int **getmatrizadj(GRAFO *grafo); //função que retorna a matriz de adjacência
#endif
