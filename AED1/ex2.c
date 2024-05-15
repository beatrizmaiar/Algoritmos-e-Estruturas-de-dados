/*Programa: Gerenciador de reservas de bibliotecas 
Autor: Beatriz Rodrigues Maia 
Versao: 1.0 - 11/10/2022
  */
//Bibliotecas externas
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

//Lista estática 
struct listaES {
int ultimo;
int tamanhoLista;
int livro;
int lista[MAX];
};
typedef struct listaES tipoListaES;

//Função para iniciar a lista
 void inicializaLista (tipoListaES *listaAux){
   int i;
   //Zera a lista
listaAux->tamanhoLista =0;
for (i=0; i<MAX; i++)
  //inicializa o ultimo 
listaAux->livro=0;
listaAux->ultimo = 0;
  }
//insere elementos no final da lista
  int insereElemento (tipoListaES *listaAux, int add){
// atualiza a lista
listaAux->tamanhoLista++;
    if(listaAux->tamanhoLista<=MAX){
      listaAux->livro++;
      listaAux->lista[listaAux->tamanhoLista-1] = add;
    
// atualiza o último
listaAux->ultimo = listaAux->tamanhoLista-1;
    //elemento foi inserido na lista
    printf("Sua reserva foi realizada\n");
      }else{
      //lista está cheia
      printf("Lista de reserva cheia\n");
      
    }
    }
//exclui um elemento da lista
int excluiElemento(tipoListaES *listaAux, int variavel2){
    if(listaAux== NULL){
        return 0;
      }
    if(listaAux->tamanhoLista == 0){

        return 0;
      
      }
    int k,i = 0;
    while(i<listaAux->tamanhoLista && listaAux->lista[i]!= variavel2) {
            
        i++;
      
      }
    if(i == listaAux->tamanhoLista && listaAux->lista[i]!= variavel2)//elemento nao encontrado  
      return 0;


for(k=i; k<listaAux->tamanhoLista-1; k++){
	listaAux->lista[k] = listaAux->lista[k+1];


} 
      listaAux->tamanhoLista--;
    return 1;
}

//função principal
int main() {
  tipoListaES livrosLista;
  int i, variavel, variavel1, variavel2, livro=0, retidas=0;
  //i:iterador, variavel1:reserva ou retirada, variavel2: numero do livro, variavel: quant de reservas
  
  inicializaLista(&livrosLista);
  //le a quantidade de movimentações que o usuário deseja
  scanf("%d",&variavel);
  
   for(i=0; i<variavel; i++){
 //le se o usuário quer retirar ou reservar e qual o livro
  scanf("%d %d",&variavel1,&variavel2);
      //se o usuário quer reservar
      if(variavel1==1){
      insereElemento(&livrosLista, variavel2);
        }
        //seo usuário quer retirar
      else{
        if(excluiElemento(&livrosLista, variavel2)){
          //livro foi retirado com sucesso da lista
        printf("O livro foi retirado com sucesso\n");
        retidas++;
         }else{
          //livro não estava na lista
        printf("Voce nao possui reserva desse livro\n");
      }
      }  
      }
  printf("Voce realizou %d reservas e %d retiradas\n",livrosLista.livro , retidas); 
  return 0;
  
  }

