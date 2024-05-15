/*Programa:lista de reserva de livros da biblioteca por RA
Autor:Beatriz Rodrigues Maia
Versão: 1.0 5/12/2022
*/
 
#include <stdio.h>
#include <stdlib.h>
#define N 10
 
//estrutura da lista estatica encadeada
typedef struct {
  int valores[N];
  int anos[8];
    int tam;
} Valores;
 
//funcao que inicia a lista
void inicia(Valores *aux) {
  for (int i = 0; i < N; i++)
    aux->valores[i] = -1;
    aux->tam = 0;
    //inicia um contador para a quantidade de reservas por ano
  for (int a = 0; a < 8; a++)
    aux->anos[a] = 0;
}
 
//funcao que insere os elementos na lista
void insere(Valores *aux, int novo) {
    //se a lista esta cheia
    if(aux->tam==N){
        printf("lista cheia\n");
        return;
    }
  int pos = 0;
  for (pos; pos<aux->tam; pos++)
    if (aux->valores[pos] == -1 || aux->valores[pos] > novo)
      break;
      aux->tam++;
  for (int i = aux->tam-1; i > pos; i--)
  //abre espaco para que o novo elemento seja inserido
    aux->valores[i] = aux->valores[i-1];
  aux->valores[pos] = novo;
  //o contador verifica o ano do ra inserido
  int va = novo/10000 - 6;
  aux->anos[va]++;
}
 
//funcao que remove um elemento da lista
void remover(Valores *aux, int ra) {
    if(aux->tam==0){
        printf("nao existe\n");
        return;
    }
  int pos = -1;
  for (int i = 0; i < aux->tam; i++) {
    if (aux->valores[i] == ra) {
      pos = i;
      break;
    }
  }
  if (pos == -1) {
    printf("nao existe\n");
    return;
  }
  aux->tam--;
  //altera o espaco da lista
  for (int i = pos; i < aux->tam; i++)
    aux->valores[i] = aux->valores[i+1];
}
 
//funcao que imprime a lista conforme a insercao
void imprimeLista(Valores *aux) {
  for (int i = 0; i < aux->tam; i++) {
    printf("%d ", aux->valores[i]);
  }
  printf("\n");
}
 
//funcao que imprime a quantidade de reservas por ano
void imprimeAno(Valores *aux) {
  for (int a = 0; a < 8; a++) {
    printf("%d: %d\n", a+2011, aux->anos[a]);
  }
}
 
//funcao principal
int main(){
    
  Valores listaBiblio;
  
    //i=iterador, ra=RA, op=operacao, mov=quantidade de movimentacoes, contador=conta a quantidade de ras registrados em cada ano
  int i, ra, op, mov, contador;
  
  //i=iterador, ra=numero do ra, re: retirada ou reserva, li=numero do livro, mov=quantidade de movimentacoes
  inicia(&listaBiblio);
  //le a quantidade de movimetacoes
  scanf("%d",&mov);
  
  for(i=0; i<mov; i++){
    //le a operacao desejada e o ra
    scanf("%d %d",&op, &ra);
  if(op==1){
    insere(&listaBiblio,ra);
    imprimeLista(&listaBiblio);
  }
  else if(op==2){
    remover(&listaBiblio, ra);
    imprimeLista(&listaBiblio);
  }
  }
  imprimeAno(&listaBiblio);
  return 0;
  }
 