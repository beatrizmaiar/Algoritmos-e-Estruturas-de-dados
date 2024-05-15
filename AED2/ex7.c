#include <stdio.h>
#include <stdlib.h>

//estrutura de um nó da árvore
struct no {
    int num;
    struct no* esq;
    struct no* dir;
    int altura;
};

// Função para criar um novo nó da árvore
struct no* novono(int num) {
    struct no* no = (struct no*)malloc(sizeof(struct no));
    no->num = num;
    no->esq = NULL;
    no->dir = NULL;
    no->altura = 1;
    return no;
}

// Função para obter a altura de um nó
int altura(struct no* no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

// Função para calcular o fator de balanceamento de um nó
int balanceamento(struct no* no) {
    if (no == NULL)
        return 0;
    return altura(no->esq) - altura(no->dir);
}

// Função para atualizar a altura de um nó
void atualizaalt(struct no* no) {
    int alturaesq = altura(no->esq);
    int alturadir = altura(no->dir);
    no->altura = (alturaesq > alturadir ? alturaesq : alturadir) + 1;
}

// Função para realizar uma rotação simples à direita
struct no* rotacaoLL(struct no* y) {
    struct no* x = y->esq;
    struct no* T2 = x->dir;
    // Realiza a rotação
    x->dir = y;
    y->esq = T2;
    // Atualiza as alturas
    atualizaalt(y);
    atualizaalt(x);
    return x;
}

// Função para realizar uma rotação simples à esquerda
struct no* rotacaoRR(struct no* x) {
    struct no* y = x->dir;
    struct no* T2 = y->esq;
    // Realiza a rotação
    y->esq = x;
    x->dir = T2;
    // Atualiza as alturas
    atualizaalt(x);
    atualizaalt(y);
    return y;
}

// Função para inserir um nó em uma árvore AVL
struct no* insere(struct no* no, int num) {
    // Realiza a inserção como em uma árvore de busca binária
    if (no == NULL)
        return novono(num);
    if (num < no->num)
        no->esq = insere(no->esq, num);
    else if (num > no->num)
        no->dir = insere(no->dir, num);
    else // Ignora chaves duplicadas
        return no;
    // Atualiza a altura do nó atual
    atualizaalt(no);
    // Verifica o fator de balanceamento e realiza as rotações necessárias
    int balanceFactor = balanceamento(no);
    // Rotação simples à direita
    if (balanceFactor > 1 && num < no->esq->num)
        return rotacaoLL(no);
    // Rotação simples à esquerda
    if (balanceFactor < -1 && num > no->dir->num)
        return rotacaoRR(no);
    // Rotação dupla à esquerda-direita
    if (balanceFactor > 1 && num > no->esq->num) {
        no->esq = rotacaoRR(no->esq);
        return rotacaoLL(no);
    }
    // Rotação dupla à direita-esquerda
    if (balanceFactor < -1 && num < no->dir->num) {
        no->dir = rotacaoLL(no->dir);
        return rotacaoRR(no);
    }
    // Caso em que a árvore já está balanceada
    return no;
}

int buscarElemento(struct no* no, int num) {
    if (no == NULL)
        return 0; // Elemento não encontrado
    if (num == no->num)
        return 1; // Elemento encontrado
    if (num < no->num)
        return buscarElemento(no->esq, num);
    else
        return buscarElemento(no->dir, num);
}

//
struct no* retorneno(struct no* no, int num) {
    if (no == NULL || no->num == num)
        return no;
    if (num < no->num)
        return retorneno(no->esq, num);
    return retorneno(no->dir, num);
}

void alturano(struct no* raiz, int num) {
    struct no* no = retorneno(raiz, num);
    if (no == NULL) {
        printf("Valor nao encontrado");
        return;
    }

    int alturaNo = altura(no);
    int alturaEsquerda = altura(no->esq);
    int alturaDireita = altura(no->dir);

    printf("%d, ",alturaNo-1);
    printf("%d, ",alturaEsquerda);
    printf("%d",alturaDireita);
}

// Função para encontrar o nó com o valor mínimo em uma árvore
struct no* nominimo(struct no* no) {
    struct no* atual = no;
    while (atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

// Função para remover um nó de uma árvore AVL
struct no* removeno(struct no* no, int num) {
    // Realiza a remoção como em uma árvore de busca binária
    if (no == NULL)
        return no;
    if (num < no->num)
        no->esq = removeno(no->esq, num);
    else if (num > no->num)
        no->dir = removeno(no->dir, num);
    else {
        // Verifica se o nó tem um filho ou nenhum filho
        if (no->esq == NULL || no->dir == NULL) {
            struct no* temp = no->esq ? no->esq : no->dir;
            // Caso de nenhum filho
            if (temp == NULL) {
                temp = no;
                no = NULL;
            } else // Caso de um filho
                *no = *temp; // Copia os valores do filho para o nó a ser removido
            free(temp);
        } else {
            // O nó a ser removido tem dois filhos
            struct no* temp = nominimo(no->dir); // Encontra o sucessor
            no->num = temp->num; // Copia o valor do sucessor para o nó atual
            no->dir = removeno(no->dir, temp->num); // Remove o sucessor da subárvore direita
        }
    }
    // Se a árvore tinha apenas um nó, retorna
    if (no == NULL)
        return no;
    // Atualiza a altura do nó atual
    atualizaalt(no);
    // Verifica o fator de balanceamento e realiza as rotações necessárias
    int fatorbalanco = balanceamento(no);
    // Rotação simples à direita
    if (fatorbalanco > 1 && balanceamento(no->esq) >= 0)
        return rotacaoLL(no);
    // Rotação dupla à esquerda-direita
    if (fatorbalanco > 1 && balanceamento(no->esq) < 0) {
        no->esq = rotacaoRR(no->esq);
        return rotacaoLL(no);
    }
    // Rotação simples à esquerda
    if (fatorbalanco < -1 && balanceamento(no->dir) <= 0)
        return rotacaoRR(no);
    // Rotação dupla à direita-esquerda
    if (fatorbalanco < -1 && balanceamento(no->dir) > 0) {
        no->dir = rotacaoLL(no->dir);
        return rotacaoRR(no);
    }
    // Caso em que a árvore já está balanceada
    return no;
}

// Função para liberar a memória ocupada pela árvore
void freeTree(struct no* no) {
    if (no != NULL) {
        freeTree(no->esq);
        freeTree(no->dir);
        free(no);
    }
}

//funcao para imprimir altura da arvore
void imprimealt(struct no* raiz) {
    int alturaMaxima = altura(raiz);
    int alturaEsquerda = altura(raiz->esq);
    int alturaDireita = altura(raiz->dir);

    printf("%d, ", alturaMaxima-1);
    printf("%d, ", alturaEsquerda);
    printf("%d\n", alturaDireita);
}

int main() {
    struct no* raiz = NULL;
    int num, chave, procura;

//printf("digite os numeros da arvore: ");
  scanf("%d", &num);
  while(num != -1){
    raiz = insere(raiz, num);
    scanf("%d", &num);
  }
    imprimealt(raiz);

  //printf("digite as chaves separadas por espaco que serao procuradas na arvore: ");
  scanf("%d", &chave);
    while(chave != -1){
    int busca = buscarElemento(raiz, chave);
    if(busca == 1){
     raiz = removeno(raiz, chave);
    }else{
       raiz = insere(raiz, chave);
    }
    scanf("%d", &chave);
    }
    
    //printf("Digite um elemento a ser procurado: ");
    scanf("%d", &procura);
    alturano(raiz, procura);
 
    // Liberação da memória ocupada pela árvore
    freeTree(raiz);

    return 0;
}

