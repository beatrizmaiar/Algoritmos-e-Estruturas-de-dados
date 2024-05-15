/*Programa:gerenciamento de estoque de uma mercearia
Autor: Beatriz Rodrigues Maia
Versao: 1.0 - 31/10/2022
*/

#include <stdio.h>
#include <stdlib.h>
// struct contendo os valores que serao guardados em cada elemento
typedef struct lista {
  int valorid;
  float valorpr;
  int valorqu;
  float comprei;
  float valort;
  struct lista *prox;
} TLista;
typedef TLista *PLista;
// struct da lista dinamica
struct ListaDE {
  PLista inicio;
  PLista fim;
  float tamanho;
};
typedef struct ListaDE TListaDE;
typedef TListaDE *PListaDE;
// funcao para iniciarmos a lista
void inicializaLista(TListaDE *listaAux) {
  listaAux->inicio = NULL;
  listaAux->fim = NULL;
  listaAux->tamanho = 0;
}
// funcao para inserir os valores na lista
void insereLista(PListaDE lista, int id, int quantproduto, int preco,
                 float total) {
  PLista ant=NULL, aux = lista->inicio;
  // aloca dinamicamente a memoria para a lista
  PLista novo = (PLista)malloc(sizeof(TLista));
  novo->valorid = id;
  novo->valorqu = quantproduto;
  novo->valorpr = preco;
  novo->valort = total;
  novo->prox = NULL;
  // se a lista estiver vazia, coloca os valores no inicio da lista
  while(aux != NULL && aux->valorpr < novo->valorpr){
    ant = aux;
    aux = aux->prox;
  }
  if(ant != NULL){
    novo->prox = ant->prox;
     ant->prox = novo; 
  }
  else{
    novo->prox = aux;
    lista->inicio = novo;
  }
}
// funcao para remover um id
int removeId(PListaDE lista, int id) {
  PLista aux = lista->inicio;
  PLista ant = NULL;
  // enquanto nao acha o valor do id, vai para o proximo elemento da lista
  while (aux != NULL && aux->valorid != id) {
    ant = aux;
    aux = aux->prox;
  }
  // se a lista estiver vazia, retorna 1
  if (aux == NULL) {
    printf("nao existe\n");
    return 1;
  }
  if (ant == NULL) {
    lista->inicio = aux->prox;
    free(aux);
    lista->tamanho--;
    return 1;
  }
  ant->prox = aux->prox;
  free(aux);
  lista->tamanho--;
  return 0;
}

// funcao que verifica se o valor existe
int valoridExiste(PListaDE lista, int id) {
  PLista aux = lista->inicio;
  while (aux != NULL) {
    // se o id ja foi incluido na lista, retorna 1
    if (aux->valorid == id) {
      return 1;
    }
    // se nao, procura para encontrar
    aux = aux->prox;
  }
  return 0;
}
// funcao para retornar um ponteiro para um elemento
PLista retornaPonteiro(PListaDE lista, int id) {
  PLista aux = lista->inicio;
  while (aux != NULL) {
    // se achar um id, retorna o auxiliar
    if (aux->valorid == id) {
      return aux;
    }
    // se nao, procura na lista para achar
    aux = aux->prox;
  }
  return NULL;
}
// funcao que imprime o ganho de cada produto
void imprimeSoma(PListaDE lista, int id) {
  PLista aux = lista->inicio;
  while (aux != NULL) {
    printf("%d %f\n", aux->valorid, aux->valort);
    aux = aux->prox;
  }
}

// funcao principal
int main() {
  TListaDE listaMerc;
  // i=iterador, mov=quantidade de movimentacoes, op=opcao desejada, id=ID do
  // produto, quantproduto= quantidade do produto, compras=0: para mostrar as
  // somas
  int i, mov, op, id, quantproduto, quantprodutonovo;
  // preco= preco do produto, soma=soma dos ganhos por produto
  float preco, total;

  inicializaLista(&listaMerc);
  // le a quantidade de movimentacoes a serem realizadas
  scanf("%d", &mov);
  for (i = 0; i < mov; i++) {
    // le a opcao de acao desejada
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d %d %f", &id, &quantproduto, &preco);
      if (valoridExiste(&listaMerc, id)) {
        printf("ja existe\n");
      } else {
        // insere o id, quantidade do produto e preco na lista
        insereLista(&listaMerc, id, quantproduto, preco, total);
      }
    } else if (op == 2) {
      // le as informacoes da opcao 2
      scanf("%d %d", &id, &quantprodutonovo);
      PLista aux = retornaPonteiro((&listaMerc), id);
      if (aux != NULL) {
        aux->valorqu += quantprodutonovo;
      } else {
        printf("nao existe\n");
      }
    } else if (op == 3) {
      // le o id do produto que foi comprado
      scanf("%d", &id);
      PLista aux = retornaPonteiro(&listaMerc, id);
      if (aux != NULL) {
        if (aux->valorqu != 0) {
          // diminui em 1 a quantidade de produtos
          aux->valorqu -= 1;
          // guarda a quantidade que ja foi comprada
          aux->comprei++;
          aux->valort = (aux->comprei) * (aux->valorpr);
        //insereLista(&listaMerc, id, quantproduto, preco, total);
        } else {
          printf("nao existe\n");
        }
      } else {
        printf("nao existe\n");
      }
    } else if (op == 4) {
      // le o id do produto que deseja excluir
      scanf("%d", &id);
      if (valoridExiste(&listaMerc, id)) {
        removeId(&listaMerc, id);
      } else {
        printf("nao existe\n");
      }
    }
  }
  // printa o resultado dos ganhos de cada produto
  imprimeSoma(&listaMerc, id);
  // printf("%d %f",id, total);
  return 0;
}