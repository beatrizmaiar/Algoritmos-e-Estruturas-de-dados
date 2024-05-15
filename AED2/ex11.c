/*Beatriz Rodrigues Maia
busca em largura e busca em profundidade*/

#include <stdio.h>
#include <stdlib.h>

// estrutura para o no do grafo
typedef struct No {
    int num;
    struct No* prox;
} No;

// estrutura para o grafo
typedef struct Grafo {
    int numNos;
    No** listaadj;
} Grafo;

// funcao que cria um no
No* criarNo(int num) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->num = num;
    novoNo->prox = NULL;
    return novoNo;
}

// funcao para criar um novo grafo
Grafo* criargrafo(int numNos) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numNos = numNos;
    grafo->listaadj = (No**)malloc(numNos * sizeof(No*));
    for (int i = 0; i < numNos; i++) {
        grafo->listaadj[i] = NULL;
    }
    return grafo;
}

//Funcao para adicionar uma aresta
void adicionarAresta(Grafo* grafo, int origem, int destino) {
    No* novoNo = criarNo(destino);

    // Encontra a posição correta para inserir o novo nó
    No* atual = grafo->listaadj[origem];
    No* anterior = NULL;
    while (atual != NULL && atual->num < novoNo->num) {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL) {
        novoNo->prox = grafo->listaadj[origem];
        grafo->listaadj[origem] = novoNo;
    } else {
        anterior->prox = novoNo;
        novoNo->prox = atual;
    }
}

//funcao para realizar a busca em largura 
void bfs(Grafo* grafo, int noInicial) {
    int visitado[101] = {0}; 
    int fila[101];
    int inicio = 0, fim = 0; //indices para controle da fila
    visitado[noInicial] = 1; 
    fila[fim++] = noInicial;

    while (inicio != fim) {
        int noAtual = fila[inicio++]; //remove o nó da frente
        printf("%d ", noAtual);

        // Percorre os nós adjacentes ao nó atual
        No* temp = grafo->listaadj[noAtual];
        while (temp != NULL) {
            int noAdjacente = temp->num;
            if (!visitado[noAdjacente]) {
                visitado[noAdjacente] = 1; 
                fila[fim++] = noAdjacente;
            }
            temp = temp->prox;
        }
    }
    printf("\n");
}

// funcao auxiliar para a busca em profundidade
void dfsUtil(Grafo* grafo, int noAtual, int visitado[]) {
    visitado[noAtual] = 1; 
    printf("%d ", noAtual);
    //percorre os nós adjacentes ao nó atual
    No* temp = grafo->listaadj[noAtual];
    while (temp != NULL) {
        int noAdjacente = temp->num;
        if (!visitado[noAdjacente]) {
            dfsUtil(grafo, noAdjacente, visitado);
        }
        temp = temp->prox;
    }
}

// funcao para realizar a busca em profundidade
void dfs(Grafo* grafo, int noInicial) {
    int visitado[101] = {0};
    dfsUtil(grafo, noInicial, visitado);
}

// Função para liberar a memória alocada para o grafo
void freegrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->numNos; i++) {
        No* temp = grafo->listaadj[i];
        while (temp != NULL) {
            No* anterior = temp;
            temp = temp->prox;
            free(anterior);
        }
    }
    free(grafo->listaadj);
    free(grafo);
}

int main() {
    int noInicial, numNos, numArestas;
    
    scanf("%d", &noInicial);
    scanf("%d", &numNos);
    scanf("%d", &numArestas);

    Grafo* grafo = criargrafo(numNos);

    // Leitura das arestas
    for (int i = 0; i < numArestas; i++) {
        int origem, destino;
        scanf("%d %d", &origem, &destino);
        adicionarAresta(grafo, origem, destino);
    }

    bfs(grafo, noInicial);
    dfs(grafo, noInicial);

    freegrafo(grafo);

    return 0;
}
