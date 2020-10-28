#include <stdio.h>
#include <stdlib.h>

int euclides_r(int m, int n, int profundidade);

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
 
  printf("mdc(%d,%d) = %d.\n", m, n, euclides_r(m, n, 0));
  return 0;
}

int euclides_r(int m, int n, int profundidade) {
  int i;

  for (i = 0; i < profundidade; i++) fprintf(stdout,"  ");
  fprintf(stdout,"mdc(%d,%d)\n", m, n);
  
  if (n == 0) return m;
  return euclides_r (n, m % n, profundidade + 1);
}
