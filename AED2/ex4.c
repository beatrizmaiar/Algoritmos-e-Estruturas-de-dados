/*Nome: Beatriz Rodrigues Maia
programa utilizando quicksort*/

#include <stdio.h>
#include <stdlib.h>
 
//funcao quicksort recursiva que toma o pivo como o ultimo elemento do vetor e informa alturas dos nos
void quicksort(int vetor[], int i, int altura_atual, int *altura_min, int *altura_max) {
 
    int pivo = vetor[i-1];
    int j = 0;
    int aux;
 
    if (i > 1) {
        altura_atual++;
        for (int k = 0; k < i-1; k++) {
            if (vetor[k] < pivo) {
                aux = vetor[j];
                vetor[j] = vetor[k];
                vetor[k] = aux;
                j++;
            }
        }
 
        aux = vetor[j];
        vetor[j] = pivo;
        vetor[i-1] = aux;
        quicksort(vetor, j, altura_atual, altura_min, altura_max);
        quicksort(vetor+j+1, i-j-1, altura_atual, altura_min, altura_max);
 
    }
 
    else {
        if (altura_atual < *altura_min) {
            *altura_min = altura_atual;
        }
        if (altura_atual > *altura_max) {
            *altura_max = altura_atual;
        }
    }
}

//funcao para trocar o valor de duas variaveis
void troca(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}
 
//acha a mediana entre o primeiro, ultimo e elemento do meio
int mediana(int vetor[], int esq, int dir){
    int meio = (esq + dir)/2;
    if ((dir - esq) % 2 == 0 && (dir - esq) > 0) {
        if (vetor[esq + (dir - esq) / 2] < vetor[meio])
            meio = esq + (dir - esq) / 2;
    }
    if(vetor[esq] > vetor[meio])
        troca(&vetor[esq], &vetor[meio]);
    if(vetor[esq] > vetor[dir])
        troca(&vetor[esq], &vetor[dir]);
    if(vetor[meio] > vetor[dir])
        troca(&vetor[meio], &vetor[dir]);
    return meio;   
}

//funcao particiona do quicksort2
int particiona(int vetor[], int esq, int dir){
    int pivo = vetor[(esq + dir) / 2];
    int i = esq - 1;
    int j = dir + 1;
    while (1) {
        do {
            i++;
        } while (vetor[i] < pivo);
        do {
            j--;
        } while (vetor[j] > pivo);
        if (i >= j) {
            return j;
        }
        troca(&vetor[i], &vetor[j]);
    }
}

//quicksort recursiva que toma o pivo como a mediana entre o primeiro, ultimo e elemento do meio
void quicksort2(int vetor[], int esq, int dir, int altura, int* altura_max, int* altura_min){
    if(esq < dir){
        int pivo = particiona(vetor, esq, dir);
        quicksort2(vetor, esq, pivo-1, altura+1, altura_max, altura_min);
        quicksort2(vetor, pivo+1, dir, altura+1, altura_max, altura_min);
        
    }
    else{
        if(altura > *altura_max){
            *altura_max = altura;
        }
        if(altura < *altura_min){
            *altura_min = altura;
        }
    }
}
 
int main(){
    //n = numero de elementos do vetor
    int n;
    scanf("%d", &n);
    int vetor[n];
    //le o vetor
    for(int i=0; i<n; i++){
        scanf("%d", &vetor[i]);
    }
    //copia o vetor para o vetor2
    int vetor2[n];
    for(int i=0; i<n; i++){
        vetor2[i] = vetor[i];
    }
    
    
    int altura_atual = 0;
    int altura_min = n;
    int altura_max = 0;

    //chama a funcao quicksort
    quicksort(vetor, n, altura_atual, &altura_min, &altura_max);
    
    //imprime a altura maxima e minima
    printf("%d\n", altura_max - altura_min);
  
    //chama a funcao quicksort2
    int altura_max2 = 0;
    int altura_min2 = n; // altura máxima é 0, altura mínima é n
    quicksort2(vetor2, 0, n-1, 0, &altura_max2, &altura_min2);
 
    //imprime a altura maxima e minima
    printf("%d\n", altura_max2 - altura_min2);
 
    return 0;
}