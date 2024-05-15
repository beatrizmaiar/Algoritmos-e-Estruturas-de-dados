/*
Programa:fila de tarefas
Autor: Beatriz Rodrigues Maia
Versao: 1.0 - 16/11/2022
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct fila {
  int primeiro;
  int ultimo;
  int tamanhoFila;
  int elementos[MAX];
};
typedef struct fila tipoFC;

void inicializaFila(tipoFC *filaAux) {
  // inicializa a fila
  int i = 0;
  filaAux->primeiro = -1;
  filaAux->ultimo = -1;
  for (i = 0; i < MAX; i++) {
    filaAux->elementos[i] = 0;
  }
}
int filaVazia(tipoFC *filaAux) {
  if ((filaAux->primeiro == filaAux->ultimo) && (filaAux->ultimo == -1)) {
    // fila está vazia
    return 1;
  } else {
    // fila não está vazia
    return 0;
  }
}

int filaCheia(tipoFC *filaAux) {
  if (((filaAux->ultimo + 1) % MAX) == filaAux->primeiro) {
    // fila está cheia
    return 1;
  } else {
    // fila não está cheia
    return 0;
  }
}

void insereElemento(tipoFC *filaAux, int id) {
  if (filaCheia(filaAux) == 0) {
    if (filaVazia(filaAux) == 1) {
      filaAux->primeiro = 0;
      filaAux->ultimo = 0;
      filaAux->elementos[0] = id;
    } else {
      int posicao = ((filaAux->ultimo + 1) % MAX);
      filaAux->elementos[posicao] = id;
      filaAux->ultimo = posicao;
    }
  } else {
    printf("fila cheia");
  }
}

void excluiID(tipoFC *filaAux, int id) {
  int i;
  if (filaVazia(filaAux) == 1) {
    printf("vazia\n");
  } else if (filaAux->elementos[filaAux->primeiro] ==
             filaAux->elementos[filaAux->ultimo]) {
    filaAux->elementos[filaAux->primeiro] = -1;
    filaAux->elementos[filaAux->ultimo] = -1;
    filaAux->tamanhoFila--;
    filaAux->primeiro = -1;
    filaAux->ultimo = -1;

  } else {
    filaAux->elementos[filaAux->primeiro] = 0;
    filaAux->tamanhoFila--;
    for (i = filaAux->primeiro; i < filaAux->ultimo; i++) {
      filaAux->elementos[i] = filaAux->elementos[i + 1];
    }
    filaAux->elementos[filaAux->ultimo] = 0;
    filaAux->ultimo--;
  }
}

void primeiroviraultimo(tipoFC *filaAux) {
  int i;
  if (filaVazia(filaAux) == 1) {
    printf("vazia\n");
  } else {
    int aux = filaAux->elementos[filaAux->primeiro];
    filaAux->elementos[filaAux->primeiro] = 0;
    filaAux->primeiro = ((filaAux->primeiro + 1) % MAX);
    filaAux->ultimo = ((filaAux->ultimo + 1) % MAX);
    filaAux->elementos[filaAux->ultimo] = aux;
  }
}
void imprimeFila(tipoFC *filaAux) {
  int i;
  if (filaVazia(filaAux) == 1) {
    printf("vazia\n");
  } else {
    for (i = filaAux->ultimo; i != filaAux->primeiro; i--) {
      if (i < 0)
        i = MAX - i;
      if (filaAux->elementos[i] > -1)
        printf("%d ", filaAux->elementos[i]);
    }
    if (filaAux->elementos[filaAux->primeiro] > -1)
      printf("%d", filaAux->elementos[i]);
  }
}
// funcao principal
int main() {
  // op=operacao, o=opcao, id=id da tarefa, i=iterador
  int op, o, id, i;
  tipoFC *filatarefas = malloc(sizeof(tipoFC));
  inicializaFila(filatarefas);

  printf("digite quantas operacoes vc quer: ");
  scanf("%d", &op);
  for (i = 0; i < op; i++) {
    printf("digite a operacao: ");
    scanf("%d", &o);

    if (o == 1) {
      // printf("digite o id: ");
      scanf("%d", &id);
      insereElemento(filatarefas, id);
    } else if (o == 2) {
      excluiID(filatarefas, id);
    } else if (o == 3) {
      int pri;
      pri = filatarefas->elementos[filatarefas->primeiro];
      excluiID(filatarefas, pri);
      insereElemento(filatarefas, pri);
    }
  }
  imprimeFila(filatarefas);
  return 0;
}