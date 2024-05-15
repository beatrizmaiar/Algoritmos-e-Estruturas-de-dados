/*Programa: Árvore geneologica familia real
Autor: Beatriz Rodrigues Maia
Versão: 1.0 30/11/2022 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura para o no da arvore
struct noArvoreBB {
char nome[20], sexo;
int ano;
struct noArvoreBB* esq;
struct noArvoreBB* dir;
};
typedef struct noArvoreBB tipoABB;

//inicializa a arvore binaria de busca
/*void inicializa (tipoABB *arvoreAux)
{
char nome[20], sexo;
int ano;

arvoreAux->nome = nome;
arvoreAux->ano = ano;
arvoreAux->sexo =sexo;
arvoreAux->esq = NULL;
arvoreAux->dir=NULL;
}*/

//funcao para buscar um no na arvore
tipoABB *busca(tipoABB *no, char nome[]){
  if(no==NULL){
    return no;
    if(strcmp(no->nome, nome)==0){
      return no;
      }
      tipoABB *aux = busca(no->esq, nome);
      if(aux!=NULL){
        return aux;
        }
      return busca(no->dir, nome);
    }
  }

//funcao para inserir um no na arvore
tipoABB *insere( tipoABB *raiz, char nome[], char sexo, int ano, char pai[]){
  if(raiz == NULL){
    raiz = (tipoABB*)malloc(sizeof(tipoABB));
    raiz->ano=ano;
    raiz->sexo = sexo;
    raiz->dir = NULL;
    raiz->esq = NULL;

    strcpy(raiz->nome, nome);
    return raiz;
  }
  tipoABB *papai = busca(raiz, pai);
  if(papai==NULL){
    printf("nao existe");
    return raiz;
  }
  tipoABB * novo = (tipoABB*)malloc(sizeof(tipoABB));
  novo->dir = NULL;
  novo->esq = NULL;
  novo->sexo=sexo;
  novo->ano=ano;
  strcpy(novo->nome, nome);
   if(papai->esq==NULL){
     papai->esq = novo;
   } else{
     if(papai->esq->ano >ano){
       papai->dir = papai->esq;
       papai->esq = novo;
     }
     else{
       papai->dir = novo;
     }
   }
  return raiz;
}

//funcao que busca um pai na arvore 
tipoABB *buscaPai(tipoABB *raiz, tipoABB *filho){
  if(raiz==NULL){
    return raiz;
  }
  if(raiz->esq==filho || raiz->dir==filho){
    return raiz;
  }
  tipoABB *aux = buscaPai(raiz->esq, filho);
      if(aux!=NULL){
        return aux;
        }
      return buscaPai(raiz->dir, filho);
    }

//funcao que remove um no e seus filhos
tipoABB *remover(tipoABB *raiz, char nome[]){
  if(raiz==NULL){
    return raiz;
  }
  //acha o nome de quem precisa ser retirado
  if(strcmp(raiz->nome, nome)==0){
    tipoABB *aux = raiz;
    raiz = NULL;
    return aux;
  }
  tipoABB *filho = busca(raiz, nome);
  if(filho == NULL){
    printf("nao existe");
    return NULL;
  }
  tipoABB *pai = buscaPai(raiz, filho);
  if(pai->esq==filho){
    pai->esq = pai->dir;
  }
  pai->dir=NULL;
  return filho;
}
//funcao para imprimir a arvore
void imprimeABB(tipoABB *raiz){
  if(raiz==NULL){
    return;
  }
  printf("%s" , raiz->nome);
  /*imprimeABB(raiz->esq);
  imprimeABB(raiz->dir);*/
}
//funcao principal
int main() {
//op=quantidade de operacoes, ano= ano de nascimento, i=iterador
int o, op, ano, i;
//mon=monarca
char mon[20], nome[20], sexo, pai[20];
  
  printf("digite o monarca no poder, sexo e o ano de nascimento: ");
  scanf("%s %c %d",mon,&sexo,&ano);
  
   tipoABB *raiz =NULL;
   raiz = insere(raiz, nome, sexo, ano, " " );
  
   printf("digite a quantidade de operações: ");
   scanf("%d", &o);
  
   for(i=0; i<o; i++){
    printf("digite a operacao:");
    scanf("%d",&op);
    if(op==1){
      printf("digite nome, sexo, ano de nascimento e pai:");
      scanf("%s %c %d %s",&op, nome, &sexo, &ano, pai);
      raiz = insere(raiz, nome, sexo, ano, pai);
    }
    else if(op==2){
      remover(raiz, nome);
    }
  }
  imprimeABB(nome);
  return 0;
}