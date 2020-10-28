#include <stdio.h>
#include <stdlib.h>

#define MAX 100

long binomiali(int n, int k);

int main(int argc, char *argv[]) {
  int n, k;

  if (argc < 3) {
    fprintf(stdout,"%s: uso: %s m n\n.", argv[0], argv[0]); 
    return -1;
  } 

  n = atoi (argv[1]);
  k = atoi (argv[2]);
  
  if (n < 0 || k < 0) {
    fprintf(stdout,"%s: argumentos devem ser inteiros nao-negativos.\n", argv[0]);
    return -2;
  }
  
  fprintf(stdout,"binom(%d,%d)=%ld.\n", n, k, binomiali(n, k));
  return 0;
}

long binomiali(int n, int k) {
  int i, j, bin[MAX][MAX];
  
  for (j = 1; j <= k; j++)
    bin[0][k] = 0;
  
  for (i = 0; i <= n; i++)
    bin[i][0] = 1;
  
  for (i = 1; i <= n; i++)
    for (j = 1; j <= k; j++)
      bin[i][j] = bin[i-1][j] + bin[i-1][j-1];
  
  return bin[n][k];
}
