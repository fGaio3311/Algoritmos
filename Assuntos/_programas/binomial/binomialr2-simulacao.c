#include <stdio.h>
#include <stdlib.h>

long binomialr2(int n, int k, int profundidade);

int main(int argc, char *argv[]) {
  int n, k;

  if (argc < 3) {
    fprintf(stdout,"%s: uso: %s n k\n.", argv[0], argv[0]); 
    return -1;
  } 

  n = atoi (argv[1]);
  k = atoi (argv[2]);
  
  if (k < 0 || n < 0) {
    fprintf(stdout,"%s: argumentos devem ser inteiros nao-negativos.\n", argv[0]);
    return -2;
  }
  
  fprintf(stdout,"binom(%d,%d)=%ld.\n", n, k, binomialr2(n, k, 0));
  return 0;
}

long binomialr2(int n, int k, int profundidade) {
  int i;
  
  for (i = 0; i < profundidade; i++) fprintf(stdout,"  ");
  fprintf(stdout,"binomialr2(%d,%d)\n", n, k);

  if (n < k) return 0;
  if (n == k || k == 0) return 1;  
  if (k == 1) return n;
  return (binomialr2(n-1, k-1, profundidade+1)*n) / k;
}
