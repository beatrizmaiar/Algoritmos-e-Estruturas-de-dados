/*Nome:Beatriz Rodrigues Maia
Arvores do tipo AVL*/
#include <stdio.h>
#include <stdlib.h>

//ARVORE DO TIPO AVL

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


//ARVORE RUBRO NEGRA

// Estrutura de um nó da árvore
typedef struct No {
    int chave;
    int cor; // 0 para preto, 1 para vermelho
    struct No* esquerda;
    struct No* direita;
    struct No* pai;
} No;

// Estrutura da árvore rubro-negra
typedef struct Arvore {
    No* raiz;
    No* nulo; // Nó nulo para folhas
} Arvore;

// Função auxiliar para criar um novo nó
No* criarNoAVP(int chave) {
    No* novo = (No*)malloc(sizeof(No));
    novo->chave = chave;
    novo->cor = 1; // Inicialmente, o nó é sempre vermelho
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->pai = NULL;
    return novo;
}

// Função auxiliar para inicializar a árvore rubro-negra
Arvore* inicializarArvoreAVP() {
    Arvore* arvore = (Arvore*)malloc(sizeof(Arvore));
    arvore->nulo = criarNoAVP(0);
    arvore->nulo->cor = 0; // O nó nulo é sempre preto
    arvore->raiz = arvore->nulo;
    return arvore;
}

// Função auxiliar para realizar uma rotação à esquerda
void rotacaoEsquerdaAVP(Arvore* arvore, No* x) {
    No* y = x->direita;
    x->direita = y->esquerda;

    if (y->esquerda != arvore->nulo)
        y->esquerda->pai = x;

    y->pai = x->pai;

    if (x->pai == arvore->nulo)
        arvore->raiz = y;
    else if (x == x->pai->esquerda)
        x->pai->esquerda = y;
    else
        x->pai->direita = y;

    y->esquerda = x;
    x->pai = y;
}

// Função auxiliar para realizar uma rotação à direita
void rotacaoDireitaAVP(Arvore* arvore, No* x) {
    No* y = x->esquerda;
    x->esquerda = y->direita;

    if (y->direita != arvore->nulo)
        y->direita->pai = x;

    y->pai = x->pai;

    if (x->pai == arvore->nulo)
        arvore->raiz = y;
    else if (x == x->pai->direita)
        x->pai->direita = y;
    else
        x->pai->esquerda = y;

    y->direita = x;
    x->pai = y;
}

// Função auxiliar para corrigir a árvore após a inserção de um nó
void correcaoInsercaoAVP(Arvore* arvore, No* novo) {
    No* pai = NULL;
    No* avo = NULL;

    while ((novo != arvore->raiz) && (novo->cor != 0) && (novo->pai->cor == 1)) {
        pai = novo->pai;
        avo = novo->pai->pai;

        // Caso 1: O pai do nó inserido é filho esquerdo do avô
        if (pai == avo->esquerda) {
            No* tio = avo->direita;

            // Caso 1.1: O tio é vermelho, então recolorimos
            if (tio != NULL && tio->cor == 1) {
                avo->cor = 1;
                pai->cor = 0;
                tio->cor = 0;
                novo = avo;
            }
            else {
                // Caso 1.2: O tio é preto ou nulo, realizamos as rotações
                if (novo == pai->direita) {
                    rotacaoEsquerdaAVP(arvore, pai);
                    novo = pai;
                    pai = novo->pai;
                }

                rotacaoDireitaAVP(arvore, avo);
                int cor_pai = pai->cor;
                pai->cor = avo->cor;
                avo->cor = cor_pai;
                novo = pai;
            }
        }
        // Caso 2: O pai do nó inserido é filho direito do avô
        else {
            No* tio = avo->esquerda;

            // Caso 2.1: O tio é vermelho, então recolorimos
            if (tio != NULL && tio->cor == 1) {
                avo->cor = 1;
                pai->cor = 0;
                tio->cor = 0;
                novo = avo;
            }
            else {
                // Caso 2.2: O tio é preto ou nulo, realizamos as rotações
                if (novo == pai->esquerda) {
                    rotacaoDireitaAVP(arvore, pai);
                    novo = pai;
                    pai = novo->pai;
                }

                rotacaoEsquerdaAVP(arvore, avo);
                int cor_pai = pai->cor;
                pai->cor = avo->cor;
                avo->cor = cor_pai;
                novo = pai;
            }
        }
    }

    // Garantir que a raiz seja sempre preta
    arvore->raiz->cor = 0;
}

// Função para inserir um novo nó na árvore rubro-negra
void inserirAVP(Arvore* arvore, int chave) {
    No* novo = criarNoAVP(chave);
    No* atual = arvore->raiz;
    No* pai = NULL;

    // Percorre a árvore até encontrar a posição correta para inserção
    while (atual != arvore->nulo) {
        pai = atual;

        if (chave < atual->chave)
            atual = atual->esquerda;
        else if (chave > atual->chave)
            atual = atual->direita;
        else {
            printf("Chave já existe na árvore.\n");
            return;
        }
    }
    novo->pai = pai;
    if (pai == NULL)
        arvore->raiz = novo;
    else if (chave < pai->chave)
        pai->esquerda = novo;
    else
        pai->direita = novo;
    novo->esquerda = arvore->nulo;
    novo->direita = arvore->nulo;
    novo->cor = 1; // Novo nó é sempre vermelho

    // Corrige a árvore após a inserção do novo nó
    correcaoInsercaoAVP(arvore, novo);
}

// Função auxiliar para pesquisar um valor na árvore rubro-negra
No* pesquisarAVP(No* raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave)
        return raiz;

    if (chave < raiz->chave)
        return pesquisarAVP(raiz->esquerda, chave);
    else
        return pesquisarAVP(raiz->direita, chave);
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