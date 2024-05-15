/*Programa: Jogo de triplas com Lista Dinamica Duplamente Encadeada
Autor: Beatriz Rodrigues Maia
Versao: 1.0 - 08/11/2022
*/

#include <stdio.h>
#include <stdlib.h>

struct numero {
    int num;
    struct numero *prox;
    struct numero *ant;
};

typedef struct numero strnumero;

struct estruturaLDDE {
    strnumero *primeiro;
    strnumero *ultimo;
    int tamanhoLista;
};

typedef struct estruturaLDDE tipoLDDE;

void inicializaLista(tipoLDDE *listaAux) {
    listaAux->primeiro = NULL;
    listaAux->ultimo = NULL;
    listaAux->tamanhoLista = 0;
}

void insereLista(tipoLDDE *listaAux, int num) {
    strnumero *novo;
    novo = (strnumero *)malloc(sizeof(strnumero));
    novo->num = num;
    novo->prox = NULL;
    novo->ant = NULL;

    if (listaAux->primeiro == NULL) {
        listaAux->primeiro = novo;
        listaAux->ultimo = novo;
    } else {
        listaAux->ultimo->prox = novo;
        novo->ant = listaAux->ultimo;
        listaAux->ultimo = novo;
    }

    listaAux->tamanhoLista++;
}

void insereListaMeio(tipoLDDE *listaAux, int num, int pos) {
    strnumero *aux = listaAux->primeiro;
    strnumero *novo;
    int i = 0;

    novo = (strnumero *)malloc(sizeof(strnumero));
    novo->num = num;

    while (aux != NULL && i != pos) {
        i++;
        aux = aux->prox;
    }

    if (i == pos) {
        novo->ant = aux->ant;
        novo->prox = aux;

        if (aux->ant != NULL) {
            aux->ant->prox = novo;
        } else {
            listaAux->primeiro = novo;
        }

        aux->ant = novo;
        listaAux->tamanhoLista++;
    }
}

void excluinum(tipoLDDE *listaAux, int num) {
    strnumero *aux = listaAux->primeiro;
    strnumero *aux2 = NULL;
    strnumero *aux3 = NULL;

    while (aux != NULL) {
        if (aux->num == num) {
            if (aux->ant == NULL) {
                listaAux->primeiro = aux->prox;
                if (aux->prox != NULL) {
                    aux->prox->ant = NULL;
                }
                free(aux);
            } else if (aux->prox == NULL) {
                listaAux->ultimo = aux->ant;
                if (aux->ant != NULL) {
                    aux->ant->prox = NULL;
                }
                free(aux);
            } else {
                aux2 = aux->ant;
                aux3 = aux->prox;
                aux2->prox = aux3;
                aux3->ant = aux2;
                free(aux);
            }
            listaAux->tamanhoLista--;
            break;
        }
        aux = aux->prox;
    }
}

void excluiTripla(tipoLDDE *listaAux) {
    strnumero *aux = listaAux->primeiro;
    strnumero *aux2 = NULL;
    strnumero *aux3 = NULL;

    while (aux != NULL) {
        if (aux->prox != NULL && aux->prox->prox != NULL && aux->prox->prox->prox != NULL) {
            if (aux->num + aux->prox->num + aux->prox->prox->num == 10) {
                if (aux->ant == NULL) {
                    listaAux->primeiro = aux->prox->prox->prox->prox;
                    if (aux->prox->prox->prox->prox != NULL) {
                        aux->prox->prox->prox->prox->ant = NULL;
                    }
                    free(aux);
                    free(aux->prox);
                    free(aux->prox->prox);
                } else if (aux->prox->prox->prox->prox == NULL) {
                    listaAux->ultimo = aux->ant;
                    if (aux->ant != NULL) {
                        aux->ant->prox = NULL;
                    }
                    free(aux);
                    free(aux->prox);
                    free(aux->prox->prox);
                } else {
                    aux2 = aux->ant;
                    aux3 = aux->prox->prox->prox->prox;
                    aux2->prox = aux3;
                    aux3->ant = aux2;
                    free(aux);
                    free(aux->prox);
                    free(aux->prox->prox);
                }
                listaAux->tamanhoLista -= 3;
                break;
            }
        }
        aux = aux->prox;
    }
}

void imprimeLista(tipoLDDE *listaAux) {
    strnumero *aux = listaAux->primeiro;
    while (aux != NULL) {
        printf("%d ", aux->num);
        aux = aux->prox;
    }
}

int main() {
    int i, num, novonum, pos;
    tipoLDDE listaJogo;
    inicializaLista(&listaJogo);

    for (i = 0; i < 10; i++) {
        scanf("%d", &num);
        insereLista(&listaJogo, num);
    }

    imprimeLista(&listaJogo);

    for (i = 0; i < 5; i++) {
        if (listaJogo.primeiro != NULL) {
            printf("\ndigite o numero a ser inserido e sua posicao: ");
            scanf("%d %d", &novonum, &pos);
            insereListaMeio(&listaJogo, novonum, pos);
            excluiTripla(&listaJogo);
            imprimeLista(&listaJogo);
        } else {
            printf("ganhou");
            break;
        }
    }

    if (listaJogo.primeiro == NULL) {
        printf("perdeu");
    }

    return 0;
}
