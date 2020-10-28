#include <stdio.h>
#include <stdlib.h>

#define min(m,n) ((m) < (n) ? (m) : (n))

/* 
 * P R O T O T I P O S 
 */ 
int mdc(int m, int n);

/* 
 * M A I N 
 */
int main(int argc, char *argv[]) {
  int m,n;
  
  if (argc < 3) {
    printf("Uso: %s m n\n.\n   m e n sao inteiros nao-negativos.", argv[0]); 
    return -1;
  } 

  m = atol (argv[1]);
  n = atol (argv[2]);
  
  if (n < 0 || m < 0) {
    printf("%s: argumentos devem ser inteiros nao-negativos.\n", argv[0]);
    return -2;
  }

  if (n == 0 && m == 0) {
    printf("%s: ambos argumentos nao podem ser nulos.\n", argv[0]);
    return -3;
  }
  
  printf("mdc(%d,%d) = %d.\n", m, n, mdc(m, n));
  return 0;
}

/*
 * I M P L E M E N T A C A O 
 */

int mdc(int m, int n) {
  int candidato;

  candidato =  min(abs(m),abs(n));
  
  while (m % candidato != 0 || n % candidato != 0)
     candidato--;
  
  return candidato;
}
