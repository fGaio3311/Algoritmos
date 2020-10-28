#include <stdio.h>
#include <stdlib.h>

/*
 * PARTE I.  P R O T O T I P O S   D A S   F U N C O E S
 */

long fatorial(long n, int profundidade);

/*
 * PARTE II. M A I N 
 */

int main(int argc, char *argv[]) {
  long n;

  if (argc < 2) {
    fprintf(stdout,"%s: uso: %s <numero>\n.", argv[0], argv[0]); 
    return -1;
  } 

  n = atol (argv[1]);

  if (n < 0) {
    fprintf(stdout,"%s: argumento deve ser um inteiro nao-negativo.\n", argv[0]);
    return -2;
  }

  fprintf(stdout,"fatorial de %ld e' %ld.\n", n, fatorial(n,0));
  return 0;
}

/* 
 *  PARTE III. D E T A L H A M E N T O   D A S   F U N C O E S
 */

long fatorial(long n, int profundidade) {
  int i;
  
  for (i = 0; i < profundidade; i++) fprintf(stdout,"  ");
  fprintf(stdout,"fatorial(%ld)\n", n);

  if (n == 0) return 1;
  return n * fatorial(n-1, profundidade+1);
}
