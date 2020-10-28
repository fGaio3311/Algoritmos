#include <stdio.h>
#include <stdlib.h>

long binomialR1(int n, int k);

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

  fprintf(stdout,"binom(%d,%d)=%ld.\n", n, k, binomialR1(n, k));
  return 0;
}

long binomialR1(int n, int k) {
  if (n <  k) return 0;
  if (n == k || k == 0) return 1; 
  return binomialR1(n-1, k) + binomialR1(n-1, k-1);
}
