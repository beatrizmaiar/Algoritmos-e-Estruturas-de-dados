#include <stdio.h>

int buscaBinariaRecursiva(int arr[], int esquerda, int direita, int x) {
    if (direita >= esquerda) {
        int meio = esquerda + (direita - esquerda) / 2;

        if (arr[meio] == x) {
            return meio;
        }

        if (arr[meio] > x) {
            return buscaBinariaRecursiva(arr, esquerda, meio - 1, x);
        }

        return buscaBinariaRecursiva(arr, meio + 1, direita, x);
    }

    return -1;
}

int main() {
    int *arr;
    int n, x, resultado;
    arr = (int*) malloc(n * sizeof(int));

    //printf("Digite o tamanho do array: ");
    scanf("%d", &n);

    //printf("Digite os elementos do array em ordem crescente:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    //printf("Digite o elemento que deseja buscar: ");
    scanf("%d", &x);

    resultado = buscaBinariaRecursiva(arr, 0, n - 1, x);

    if (resultado == -1) {
        printf("%d nao foi encontrado\n", x);
    } else {
        printf("%d\n", resultado+1);
    }

    return 0;
}