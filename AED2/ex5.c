#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para trocar o conteúdo de dois ponteiros de char
void swap(char** a, char** b)
{
    char* temp = *a;
    *a = *b;
    *b = temp;
}

// Função que ajusta um heap a partir de um nó dado
void heapify(char** arr, int n, int i, char* chave, int posChave)
{
    int maior = i;
    int tamChave = strlen(chave);

    for (int j = posChave; j < tamChave; j++) {
        // Verifica se o caractere da palavra i é menor que o da palavra maior, de acordo com a ordem da chave
        if (strncmp(&arr[i][j], &arr[maior][j], tamChave-j) < 0) {
    maior = i;
    break;
}
        // Verifica se o caractere da palavra i é maior que o da palavra maior, de acordo com a ordem da chave
        else if (arr[i][j] - 'a' > arr[maior][j] - 'a') {
            break;
        }
        // Se as letras correspondentes à chave forem iguais,
        // compara as próximas letras das palavras
        else if (j == tamChave - 1 && arr[i][j] == arr[maior][j]) {
            int k = tamChave;
            while (k < strlen(arr[i]) && k < strlen(arr[maior])) {
                // Verifica se o caractere da palavra i é menor que o da palavra maior, de acordo com a ordem da chave
                if (arr[i][k] - 'a' < arr[maior][k] - 'a') {
                    maior = i;
                    break;
                }
                // Verifica se o caractere da palavra i é maior que o da palavra maior, de acordo com a ordem da chave
                else if (arr[i][k] - 'a' > arr[maior][k] - 'a') {
                    break;
                }
                k++;
            }
            // Se todas as letras correspondentes à chave forem iguais
            // e as palavras tiverem o mesmo prefixo, a palavra menor
            // é aquela que tem menos caracteres
            if (k == strlen(arr[i]) && k < strlen(arr[maior])) {
                maior = i;
                break;
            }
            else if (k == strlen(arr[maior]) && k < strlen(arr[i])) {
                break;
            }
        }
    }
    if (maior != i) {
        swap(&arr[i], &arr[maior]);
        heapify(arr, n, maior, chave, posChave);
    }
}

// Função que implementa o heapsort
void heapsort(char** arr, int n, char* chave)
{
    // Constrói o heap a partir do vetor de palavras
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i, chave, strlen(chave));

    // Extrai os elementos do heap um por um
    for (int i = n-1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0, chave, strlen(chave));
    }
}

int main()
{
    int qtdePalavras, tamChave;
    char chave[100];
    char** palavras;

    // Solicita a quantidade de palavras e o tamanho da chave
   // printf("Digite a quantidade de palavras: ");
    scanf("%d %d", &qtdePalavras, &tamChave);

    // Aloca memória para o vetor de palavras e para a string da chave
    palavras = (char**)malloc(qtdePalavras * sizeof(char*));
    for (int i = 0; i < qtdePalavras; i++)
        palavras[i] = (char*)malloc((tamChave+1) * sizeof(char));
    //printf("Digite a chave: ");
    scanf("%s", chave);

    // Solicita as palavras ao usuário
    for (int i = 0; i < qtdePalavras; i++) {
        //printf("Digite a palavra %d: ", i+1);
        scanf("%s", palavras[i]);
    }

    // Ordena as palavras usando heapsort
    heapsort(palavras, qtdePalavras, chave);

    // Imprime as palavras ordenadas
    //printf("Palavras ordenadas:\n");
    for (int i = 0; i < qtdePalavras; i++)
        printf("%s ", palavras[i]);

    // Libera a memória alocada
    for (int i=0; i < qtdePalavras; i++)
        free(palavras[i]);
    free(palavras);

    return 0;
}

    
