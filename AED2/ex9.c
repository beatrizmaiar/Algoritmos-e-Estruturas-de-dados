/*Beatriz Rodrigues Maia
Tabela Hash com duplo mapeamento*/
#include <stdio.h>
#include <stdlib.h>

//estrutura do no da tabela hash
struct no {
    int num;
    int status;
};

//funcao para inserir um elemento na tabela, se a posicao estiver ocupada, usa a estrategia de duplo mapeamento 
void insere(struct no *tabela, int num, int m) {
    int i, j, h1, h2, h;
    h1 = num % m;
    h2 = 1 + (num % (m - 1));
    h = h1;
    for (i = 0; i < m; i++) {
        if (tabela[h].status == 0) {
            tabela[h].num = num;
            tabela[h].status = 1;
            return;
        }
        h = (h1 + i * h2) % m;
    }
}

//funcao para pesquisar um elemento na tabela, retorna 1 se encontrar e 0 caso contrario
int pesquisa(struct no *tabela, int chave, int m) {
    int i, j, h1, h2, h;
    h1 = chave % m;
    h2 = 1 + (chave % (m - 1));
    h = h1;
    for (i = 0; i < m; i++) {
        if (tabela[h].status == 0) {
            printf("Valor nao encontrado\n");
            return 0;
        }
        if (tabela[h].num == chave) {
            return 1;
        }
        h = (h1 + i * h2) % m;
    }
    printf("Valor nao encontrado\n");
    return 0;
}

//funcao para remover um elemento da tabela
void removechave(struct no *tabela, int chave, int m) {
    int i, j, h1, h2, h;
    h1 = chave % m;
    h2 = 1 + (chave % (m - 1));
    h = h1;
    int elementosRemovidos = 0; //contador de elementos removidos

    for (i = 0; i < m; i++) {
        if (tabela[h].status == 0) {
            return;
        }
        if (tabela[h].num == chave) {
            tabela[h].status = -1;
            elementosRemovidos++; //incrementa o contador
        }
        h = (h1 + i * h2) % m;
    }
}

//funcao para imprimir, posições nao utilizadas devem ser marcadas pelo caracter '\' e posições removidas pelo caracter 'D'
void imprime(struct no *tabela, int m) {
    int i;
    for (i = 0; i < m; i++) {
        if (tabela[i].status == 0) {
            printf("\\ ");
        } else if (tabela[i].status == -1) {
            printf("D ");
        } else {
            printf("%d ", tabela[i].num);
        }
    }
    printf("\n");
}

//funcao para liberar a memoria alocada para a tabela
void freetabela(struct no *tabela) {
    free(tabela);
}

int main() {
    int m, num, chave;

    struct no *tabela;

    //printf("digite um numero primo referente ao tamanho da tabela:");
    scanf("%d", &m);

    tabela = (struct no *)malloc(m * sizeof(struct no));
    if (tabela == NULL) {
        printf("Falha na alocação de memória.\n");
        return 1;
    }

    //printf("digite os numeros a serem inseridos na tabela com espaço e -1 para finalizar:");
    scanf("%d", &num);
    while (num != -1) {
        insere(tabela, num, m);
        scanf("%d", &num);
    }

    //printf("digite a chave a ser pesquisada:");
    scanf("%d", &chave);
    if(pesquisa(tabela, chave, m) == 1) {
        removechave(tabela, chave, m);
    }
    
    imprime(tabela, m);
    freetabela(tabela);

    return 0;
}
