#include <stdio.h>
#include <stdlib.h>

/* 
 * P R O T O T I P O S 
 */
long fibonacci_r(long n, int profundidade);

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
  
  printf("fibonacci(%ld) = %ld.\n", n, fibonacci_r(n, 0));
  return 0;
}

/* 
 *  I M P L E M E N T A C A O
 */
long fibonacci_r(long n, int profundidade) {
  int i;
  
  for (i = 0; i < profundidade; i++) fprintf(stdout,"  ");
  fprintf(stdout,"fibonaccir(%ld)\n", n);
  
  if (n == 0) return 0;
  if (n == 1) return 1;
  return fibonacci_r(n-1, profundidade+1) + fibonacci_r(n-2, profundidade+1);
}
