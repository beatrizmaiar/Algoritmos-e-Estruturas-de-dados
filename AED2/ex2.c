/*Nome: Beatriz Rodrigues Maia
Exercicio 2: comparacao com O(n²)*/

//bibliotecas
#include <stdio.h>
#include <stdlib.h>

//funcao insertion sort para ordenar os numeros de forma crescente
void ordenar(int *p, int n) {
    int i, j, aux;
    for (i = 1; i < n; i++) {
        aux = p[i];
        for (j = i; (j > 0) && (aux < p[j - 1]); j--) {
            p[j] = p[j - 1];
        }
        p[j] = aux;
    }
}

//funcao principal
int main(){

//n=quantidade de entradas, i=variavel iteradora, k=variavel para auxiliar na comparacao
int n, i, k;

//printf("digite a quantidade de entradas:");
scanf("%d", &n);
  //aloca a quantidade n de espacos desejada
   int* p = (int*) malloc(n * sizeof(int));
   int* r = (int*) malloc(n * sizeof(int));
   
//printf("digite a quantidade de microorganismos:");
   for(int i = 0; i<n; i++){
     scanf("%d", &p[i]);
   }

  //utiliza a funcao ordenar para ordenar os numeros de forma crescente
    ordenar(p,n);
  
  //printf("potencia de cada dose:");
   for(int i = 0; i<n; i++){
     scanf("%d ", &r[i]);
   }
   //ordena de forma crescente o segundo vetor
   ordenar(r,n);

   for(i=0;i<n;i++){
     //se caso a dose existente eh suficiente para curar o paciente
     if(r[i]>p[i]){
      k=n;
    }
  else{
    k=n-1;
  }
}
  //imprime "sim" para quando todas as comparacoes ficam maiores e "nao" caso contrario
   if(k==n){
     printf("sim");
   }else{
   printf("nao");
     }
   //desaloca o espaco alocado
free(p);
free(r);
    return 0;
}