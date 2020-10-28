/* stack.c: IMPLEMENTACAO DA PILHA */

/* malloc precisa stdlib */
#include <stdlib.h>

/* fprintf precisa stdio.h */
#include <stdio.h>

/* interface da pilha */
#include "stack.h"

static void * mallocSafe (unsigned int n); 
/*
 * PILHA: implementacao em vetor
 */

static char   *s; /* guarda os elementos da pilha */
static int  topo; /* indice do topo da pilha, s[topo] 
                   * e' a 1a. posicao vaga da pilha 
	           */  

void stackInit(int n) { 
  s = (Item*) mallocSafe(n*sizeof(Item)); 
  topo = 0; 
}

int stackEmpty() { 
  return topo == 0; 
}

void stackPush(Item item) { 
  s[topo++] = item; 
}

Item stackPop() { 
  return s[--topo]; 
}

Item stackTop() {
  return s[topo-1];
}

void stackFree() {
  free(s);
}

void stackDump() {
  int k;  /* usado para imprimir o conteudo da pilha */
  
  fprintf(stdout,"pilha  : ");
  if (topo == 0) fprintf(stdout, "vazia.");
  for (k = 0; k < topo; k++)
    fprintf(stdout, "%c ", s[k]);
  fprintf(stdout,"\n");
}

static void *mallocSafe (unsigned int n) {
  void *p;

  p = malloc(n);
  if (p == NULL) {
    fprintf(stderr,"stack: malloc de %u bytes falhou.\n", n);
    exit (-1);
  }
  return p;
}
