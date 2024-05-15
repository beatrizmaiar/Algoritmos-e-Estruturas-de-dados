#include <stdio.h>
#include <stdlib.h>

//estrutura para um nó da lista
struct no{
    int info;
    struct no *prox;
};

//funcao que insere os elementos em uma lista simplesmente encadeada sem ordenacao
int inserelista(struct no **lista, int x){
    struct no *novo;
    //alocando memoria para o novo no
    novo = (struct no*) malloc(sizeof(struct no));
    //inserindo o elemento no novo no
    novo->info = x;
    //inserindo o novo no no inicio da lista
    novo->prox = *lista;
    *lista = novo;
    struct no *atual = *lista;
    return 0;
}
// Função para dividir a lista encadeada em duas partes
// Retorna um ponteiro para o início da segunda metade
struct no* dividirLista(struct no *lista) {
    struct no *metade = lista, *fim = lista, *anterior = NULL;
    while(fim != NULL && fim->prox != NULL) {
        anterior = metade;
        metade = metade->prox;
        fim = fim->prox->prox;
    }
    if(anterior != NULL) {
        anterior->prox = NULL;
    }
    return metade;
}

// Função para juntar duas listas encadeadas ordenadas em ordem crescente
struct no* merge(struct no *esquerda, struct no *direita) {
    struct no *novaLista = NULL, *atual = NULL;
    if(esquerda == NULL) {
        return direita;
    } else if(direita == NULL) {
        return esquerda;
    }
    if(esquerda->info <= direita->info) {
        novaLista = esquerda;
        esquerda = esquerda->prox;
    } else {
        novaLista = direita;
        direita = direita->prox;
    }
    atual = novaLista;
    while(esquerda != NULL && direita != NULL) {
        if(esquerda->info <= direita->info) {
            atual->prox = esquerda;
            esquerda = esquerda->prox;
        } else {
            atual->prox = direita;
            direita = direita->prox;
        }
        atual = atual->prox;
    }
    if(esquerda != NULL) {
        atual->prox = esquerda;
    } else if(direita != NULL) {
        atual->prox = direita;
    }
    return novaLista;
}

// Função para ordenar a lista encadeada usando o Merge Sort com recursão
struct no* mergeSort(struct no *lista, int *r) {
    if(lista == NULL || lista->prox == NULL) {
        return lista;
    }
    struct no *metade = dividirLista(lista);
    struct no *esquerda = mergeSort(lista, r);
    struct no *direita = mergeSort(metade, r);
    (*r)++;
    return merge(esquerda, direita);
       
}

int imprime(struct no *lista){
    struct no *atual = lista;
    while(atual != NULL){
        printf("%d ", atual->info);
        atual = atual->prox;
    }
}

int main(){
    int n, x, i , r=0;
    struct no *lista = NULL;

    printf("Digite o numero de elementos: ");
    scanf("%d", &n);

    //alocando memória dinamicamente para o array lista
    int *vetor = (int*) malloc(n * sizeof(int));

    //lendo os elementos da lista
    printf("Digite os elementos da lista: ");
    for(i = 0; i < n; i++){
        scanf("%d", &x);
        vetor[i] = x;
        inserelista(&lista, x);
    }

  //ordenando o vetor com merge sort
  lista = mergeSort(lista, &r);
  //imprime a lista ordenada
    imprime(lista);
  //imprime a quantidade de recursao
    printf("\n%d", r);
    //liberando a memória alocada para o array lista
    free(vetor);

    return 0;
}