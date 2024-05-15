/*Programa: transforma numero decimal em binario
nome: Beatriz Rodrigues Maia
Versão: 1.0 22/11/22
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//estrutura para o elemento da pilha
struct numero {
  int info;
  int *prox;
};
typedef struct numero Numero;

//estrutura para a pilha
struct pilha {
  int tamanho;
  Numero *topo;
};
typedef struct pilha Pilha;

//funcao para iniciar a pilha
void inicializaPilha(Pilha *pilha) {
  pilha->tamanho = 0;
  pilha->topo = NULL;
}
//funcao para inserir o elemento na pilha
void inserePilha(Pilha *pilha, int n) {
  Numero *novo;
  novo = (Numero *)malloc(sizeof(Numero));
  novo->info = n;
  novo->prox = pilha->topo;
  pilha->topo = novo;
  pilha->tamanho++;
}
//funcao para mudar os numeros binarios(se 1, transforma em 0, se 0, transforma em 1)
void transformaPilha(Pilha *pilha) {
    Numero *aux;
    aux = pilha->topo;
    while (aux != NULL) {
        if (aux->info == 0) {
        aux->info = 1;
        }
        else{
            aux->info = 0;
        }
        aux = aux->prox;
    }
    }
//funcao para transformar o numero binario em decimal
void binariodecimal(Pilha *pilha){
    Numero *aux;
    int i, soma=0;
    aux = pilha->topo;
    for(i=pilha->tamanho-1; i>=0; i--){
        soma = soma + (aux->info * pow(2, i));
        aux = aux->prox;
    }
    printf("%d\n", soma);
}
//funcao para imprimir a pilha
void imprimePilha(Pilha *pilha) {
  Numero *aux = pilha->topo;
  while (aux != NULL) {
    printf("%d", aux->info);
    aux = aux->prox;
  }
}
//funcao que exclui todos os elementos da pilha
void excluiPilha(Pilha *pilha) {
  Numero *aux;
  aux = pilha->topo;
  while (aux != NULL) {
    pilha->topo = aux->prox;
    free(aux);
    aux = pilha->topo;
  }
  pilha->tamanho = 0;
}
// funcao principal
int main() {
  // op=quant de operacoes, n=numero decimal, i=iterador, resto=resto da divisao por 2
  int op, n, i, resto;
  Pilha pilhadec;
  //inicia a lista
  inicializaPilha(&pilhadec);
  //le a quantidade de operacoes
  scanf("%d", &op);
  for (i = 0; i < op; i++) {
    //le o numero que foi digitado
    scanf("%d", &n);
    printf("%d ",n);
    //pega o resto da divisao do numero por 2 e vai inserindo na pilha
    while (n>0) {
      resto = n % 2;
      n = n / 2;
      inserePilha(&pilhadec, resto);
      }
    //imprime o numero em sua forma binaria
    imprimePilha(&pilhadec);
    //inverte o 1 em 0 e 0 em 1
    transformaPilha(&pilhadec);
    printf(" ");
    //imprime a inversao
    imprimePilha(&pilhadec);
    printf(" ");
    //transforma o numero binario em decimal
    binariodecimal(&pilhadec);
    excluiPilha(&pilhadec);
    }
  return 0;
}