/*algoritmo para descobrir o tamanho do pé em centímetros*/

#include <stdio.h>
#include <math.h>

int main(void) {
  int L, N ,i, G, CVm = 0, CVf = 0;
  float cmm, vi, vd;

  printf("Digite a quantidade de sapatos: ");
  scanf("%d", &L);

  for(i = 1; i <= L; i++) {
    printf("Digite a numeração e o gênero (masculino=0 feminino=1) do sapato %d: ", i);
    scanf("%d %d", &N, &G);

    cmm = N * 6.67;
    if(G == 0) {
      CVm = ((((cmm + 19) / 25.4) * 3) - 24);
    } else {
      CVf = ((((cmm + 19) / 25.4) * 3) - 23);
    }
  }

  printf("Tamanho do sapato feminino: %d\n", CVf);
  printf("Tamanho do sapato masculino: %d\n", CVm);

  return 0;
}
