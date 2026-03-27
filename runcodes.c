//16863736 - Enzo Ferreira de Castro Lima
//17070779 - Eric Costa Lopes
//16990096 - Nicolas José Mota
//16898096 - Rafael Pavon Diesner

#include <stdio.h>
#include <stdbool.h>

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

int *vizinhos (GRAFO *grafo, int v)
{
    if (grafo != NULL)
    {
        int p = 0; //marca a posição do vetor que os vizinhos serão adicionados
        int *vizinhos = (int *)malloc(grafo->nVertices * sizeof(int)); //array de vizinhos, seu tamanho é a quantidade de vértices do grafo. Ele é alocado dinâmicamente para que eu possa utilizá-lo fora do escopo da função
        for (int i = 0; i < grafo->nVertices; i++) //percorro a linha da matriz correspondente ao vertice v
        {
            if (grafo->matrizAdjacencia[v-1][i] != -1) //caso o valor da matriz seja diferente de -1, existirá uma aresta entre o vértice v e o vértice correspondente a coluna
            {
                vizinhos[p] = i+1; //coloco o valor do vértice correspondente a coluna no array de vizinho, pois ele é vizinho de v
                p++;
            }
        }
        if(p == 0)
        {
            return NULL;
        }
        for (p; p < grafo->nVertices; p++)
        {
            vizinhos[p] = 0;
        }
        return vizinhos;
    }
}

int apagaaresta (GRAFO *grafo, int v1, int v2)
{
    if (grafo != NULL && v1 <= grafo->nVertices && v2 <= grafo->nVertices)
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
void printinfo (GRAFO *grafo, int *vetor)
{
    if (grafo != NULL && vetor == NULL)
    {
        int temaresta = 0; //marcador que vale 0 se o grafo não tiver arestas e vale 1 se o grafo tiver pelo menos 1 aresta
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
        printf ("E = [");
        //para imprimir as arestas, percorremos primeiro as colunas e depois as linhas
        for (int j = 1; j < grafo->nVertices; j++) //percorremos a matriz pra ver quais arestas existem e printamos elas
        {
            for (int i = 0; i < j; i++) //a restrição de i < j serve para percorrer na ordem correta de acordo com a formatação pedida
            {
                if (grafo->matrizAdjacencia[i][j] != -1) //se a aresta existe, imprimimos
                {
                    printf("(%d, %d), ", (i+1), (j+1));
                    temaresta = 1; //o grafo tem pelo menos uma aresta
                }
            }
        }
        if (temaresta == 1) //essa verificação serve para corrigir a formatação da saída
        {
            printf("\b\b]\n");
        }
        else{
            printf("]\n");
        }
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

int main()
{
    int option; //identifica qual caso teste será aplicado
    int N, x, y, w;//N é o número de vértices do grafo e x, y e w são os inputs que serão dados pelos usuários a depender da operação
    int res;
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
        default:
            printf("unrecognized option %d!\n", option);
        }
        scanf("%d", &option);
    }
    if (option == -1)
    {
        if(printstatus)
        {
            printinfo(G, osvizinhos); //printamos o estado do grafo, printamos os vizinhos de um vértice caso option = 3 tenha sido acionado
            if (osvizinhos != NULL)
            {
                free(osvizinhos); //liberamos a memória se necessário
                osvizinhos = NULL;
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
