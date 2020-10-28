/* queue.c: IMPLEMENTACAO DA FILA */

#include <stdio.h>
#include <stdlib.h>
#include "item.h"

static void *mallocSafe (unsigned int n); 

/*
 * FILA: uma implementacao circular
 */

static Item  *q;
static int    n;   /* tamanho da fila */ 
static int inicio; /* indice do inicio da fila */
static int fim;    /* indice do fim da fila */

/*
 * Teremos que 0 <= inicio < n e 0 <= fim < n, mas em geral nao teremos 
 * que inicio <= fim 
 */

void queueInit(int N) { 
  n = N+1; /* necessitamos de uma posicao extra */
  q = (Item*) mallocSafe(n*sizeof(Item));
  inicio = 0; 
  fim = 0;
}

int queueEmpty() { 
  return inicio == fim; 
}

void queuePut(Item conteudo) {
  if ((fim+1) % n == inicio) {
    fprintf (stderr,"Fila vai transbordar!\n");
    exit (-1);
  }
  q[fim++] = conteudo;
  if (fim == n) fim = 0; 
}

Item queueGet() {
  int i = inicio;
  inicio = (inicio + 1) % n;
  return q[i]; 
}

void queueFree() {
  free(q);
}

static void *mallocSafe (unsigned int n) {
  void *p;
  
  p = malloc(n);
  if (p == NULL) {
    fprintf(stderr,"queue: malloc de %u bytes falhou.\n", n);
    exit (-1);
  }
  return p;
}
