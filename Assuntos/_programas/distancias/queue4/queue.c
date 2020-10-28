/* queue.c: IMPLEMENTACAO DA FILA */

#include <stdio.h>
#include <stdlib.h>
#include "item.h"

static void *mallocSafe (unsigned int n);

/*
 * FILA: uma implementacao com lista encadeada circular com 
 *       cabeca de lista
 */

typedef struct queueNode* Link;
struct queueNode { 
  Item conteudo; 
  Link prox; 
};

static Link inicio;

void queueInit(int n) { 
  inicio = (Link) mallocSafe(sizeof *inicio);
  inicio->prox = inicio;
}

int queueEmpty() { 
  return inicio == inicio->prox; 
}

void queuePut(Item conteudo) { 
  Link nova = (Link) mallocSafe(sizeof *nova);
  nova->prox = inicio->prox;
  inicio->prox = nova;
  inicio->conteudo = conteudo;
  inicio = nova; 
}

Item queueGet() { 
  Item conteudo;
  Link t = inicio->prox; 
  conteudo = t->conteudo;
  inicio->prox = t->prox;  
  free(t); 
  return conteudo;
}

void queueFree() { 
  Link p = inicio->prox;
  while (p != inicio) { 
    Link t = p->prox;
    free(p);
    p = t;
  }
  free(inicio);
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
