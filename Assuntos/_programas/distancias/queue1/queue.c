/* queue.c: IMPLEMENTACAO DA FILA */

#include <stdio.h>
#include <stdlib.h>
#include "item.h"

static void *mallocSafe (unsigned int n); 

/*
 * FILA: implementacao em vetor
 */

static Item *q;    /* armazena os elementos da fila */
static int inicio; /* indice do inicio da fila */
static int fim;    /* indice do fim da fila */

void queueInit(int n) { 
  q = (Item*) mallocSafe(n*sizeof(Item)); 
  inicio = 0; 
  fim = 0; 
}

int queueEmpty() { 
  return inicio == fim; 
}

void queuePut(Item item) { 
  q[fim++] = item; 
}

Item queueGet() { 
  return q[inicio++]; 
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

