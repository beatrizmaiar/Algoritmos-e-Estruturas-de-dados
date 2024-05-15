/*Nome: Beatriz Rodrigues Maia
Caminhos mínimos*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

//nó da lista
typedef struct Node {
    int destino;
    int peso;
    struct Node* prox;
} Node;

//lista de adjacência
typedef struct ListaAdj {
    Node* head;
} ListaAdj;

//inicializa a lista de adjacência
ListaAdj* inicializa(int numver) {
    ListaAdj* lista = (ListaAdj*)malloc(numver * sizeof(ListaAdj));
    for (int i = 0; i < numver; i++) {
        lista[i].head = NULL;
    }
    return lista;
}

// insere uma aresta na lista
void insere(ListaAdj* lista, int origem, int destino, int peso) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->destino = destino;
    novoNo->peso = peso;
    novoNo->prox = NULL;
    if (lista[origem].head == NULL) {
        lista[origem].head = novoNo;
    } else {
        Node* atual = lista[origem].head;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoNo;
    }
}

//encontra o vértice com a distância mínima
int mindist(int distancias[], bool visitados[], int numver) {
    int min = INT_MAX, minIndex;
    for (int v = 0; v < numver; v++) {
        if (visitados[v] == false && distancias[v] <= min) {
            min = distancias[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// imprime o caminho mínimo para todos os vértices a partir do vértice inicial
void imprime(int distancias[], int numver) {
    printf("%d", distancias[0]);
    for (int i = 1; i < numver; i++) {
        printf(" %d", distancias[i]);
    }
    printf("\n");
}

//algoritmo de dijkstra para encontrar o caminho mínimo com restrição
void dijkstra(ListaAdj* lista, int numver, int noInicial, int restricao) {
    int distancias[numver];
    bool visitados[numver];

    //todas as distâncias iniciam como infinito e marca todos os vértices como não visitados
    for (int i = 0; i < numver; i++) {
        distancias[i] = INT_MAX;
        visitados[i] = false;
    }

    // distância do nó inicial é sempre 0
    distancias[noInicial] = 0;
  
    // encontra o caminho mínimo
    for (int count = 0; count < numver - 1; count++) {
        // encontra o vértice com a menor distância entre os vértices não visitados
        int u = mindist(distancias, visitados, numver);
        visitados[u] = true;
        // atualiza as distâncias
        Node* atual = lista[u].head;
        while (atual != NULL) {
            int v = atual->destino;
            int peso = atual->peso;
            if (!visitados[v] && peso <= restricao && distancias[u] != INT_MAX &&
                distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
            }

            atual = atual->prox;
        }
    }
    // Imprime o caminho mínimo 
    imprime(distancias, numver);
}

int main() {
    int noInicial, restricao, numver, numArestas;

    //leitura do nó inicial, restrição, número de nós e número de arestas
    scanf("%d", &noInicial);
    scanf("%d", &restricao);
    scanf("%d", &numver);
    scanf("%d", &numArestas);

    //inicializa a lista de adjacência
    ListaAdj* lista = inicializa(numver);

    //leitura das arestas e pesos
    for (int i = 0; i < numArestas; i++) {
        int origem, destino, peso;
        scanf("%d %d %d", &origem, &destino, &peso);
        insere(lista, origem, destino, peso);
    }

    //chama a função para encontrar o caminho mínimo
    dijkstra(lista, numver, noInicial, restricao);

    return 0;
}
