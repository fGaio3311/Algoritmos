#include <stdio.h>
#include <stdlib.h>

/* 
 * P R O T O T I P O S
 */
long fibonacci_i(long n);

/* 
 * M A I N 
 */

int main(int argc, char *argv[]) {
  long n;

  if (argc < 2) {
    printf("Uso: %s <numero>\n.",  argv[0]); 
    return -1;
  } 

  n = atol (argv[1]);

  if (n < 0) {
    printf("%s: argumento deve ser um inteiro nao-negativo.\n", argv[0]);
    return -2;
  }

  printf("fibonacci(%ld) = %ld.\n", n, fibonacci_i(n));
  return 0;
}

/* 
 * I M P L E M E N T A C A O 
 */
long fibonacci_i(long n) {
  long anterior = 0, atual = 1, proximo;
  long i;

  if (n == 0) return 0;
  if (n == 1) return 1;

  for (i = 1; i < n; i++) {
    proximo = atual + anterior;
    anterior = atual;
    atual = proximo;
  }
  
  return atual;
}
