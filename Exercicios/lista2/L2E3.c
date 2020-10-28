/* Considere as declarações

#define FALSE 0
#define TRUE  1
Escreva uma função com protótipo

int crescente (Celula *ini);

que recebe uma lista encadeada ini de números inteiros e devolve TRUE se a lista está em ordem crescente e FALSE caso contrário. Suponha que a lista encadeada não tem cabeça de lista e que contém pelo menos um elemento.
 */

#include <stdio.h>

#define FALSE 0
#define TRUE 1

struct cel
{
    int conteudo;
    struct cel *prox;
};

typedef struct cel Celula;

/* Recebe uma lista encadeada
 * devolve TRUE se a lista está em ordem crescente e FALSE caso contrário */
int crescente(Celula *ini)
{
    if (ini->prox == NULL)
        return TRUE;
    if (ini->prox->conteudo < ini->conteudo)
        return FALSE;
    return crescente(ini->prox);
}

int main() {
  Celula a, b, c, d;
  a.conteudo = 1;
  a.prox = &b;
  b.conteudo = 3;
  b.prox = &c;
  c.conteudo = 5;
  c.prox = &d;
  d.conteudo = 13;
  d.prox = NULL;
  
  printf("%d\n", crescente(&a));
}