#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

void counting_sort(char **A, int n, int d, int k) {
    int i, j;
    char **B = malloc(n * sizeof(char *));
    int *C = malloc((k+1) * sizeof(int));

    for (i = 0; i <= k; i++) {
        C[i] = 0;
    }
    for (j = 0; j < n; j++) {
        int index = A[j][d] - 'a';
        if (index < 0 || index > 25) index = 26; // For non-alphabetic characters
        C[index]++;
    }
    for (i = 1; i <= k; i++) {
        C[i] += C[i-1];
    }
    for (j = n-1; j >= 0; j--) {
        int index = A[j][d] - 'a';
        if (index < 0 || index > 25) index = 26;
        B[C[index]-1] = A[j];
        C[index]--;
    }
    for (i = 0; i < n; i++) {
        A[i] = B[i];
    }

    free(B);
    free(C);
}


void radix_sort(char **A, int n, int max_length) {
    int i;
    for (i = max_length-1; i >= 0; i--) {
        counting_sort(A, n, i, 26);
    }
    char **B = malloc((n+1) * sizeof(char *));
    for (i = 0; i < n; i++) {
        B[i] = A[i];
    }
    for (i = 0; i < n; i++) {
        A[i] = B[n-i-1];
    }
    free(B);
}

int main() {
    char **A = malloc(10 * sizeof(char *));
    A[0] = "hello";
    A[1] = "world";
    A[2] = "counting";
    A[3] = "sort";
    A[4] = "radix";
    A[5] = "algorithm";
    A[6] = "computer";
    A[7] = "science";
    A[8] = "programming";
    A[9] = "language";

    int n = 10;
    int max_length = MAX_LENGTH;
    int i;

    printf("Before sorting:\n");
    for (i = 0; i < n; i++) {
        printf("%s\n", A[i]);
    }

    radix_sort(A, n, max_length);

    printf("After sorting:\n");
    for (i = 0; i < n; i++) {
        printf("%s\n", A[i]);
    }

    free(A);
    return 0;
}
