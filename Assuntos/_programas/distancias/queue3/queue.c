/* queue.c: IMPLEMENTACAO DA FILA */

#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "queue.h"

static void *mallocSafe (unsigned int n); 

/*
 * FILA: uma implementacao com lista encadeada
 */

typedef struct queueNode* Link;
struct queueNode { 
  Item conteudo; 
  Link prox; 
};

static Link inicio;
static Link fim;

static Link new(Item conteudo, Link prox) { 
  Link p =  mallocSafe(sizeof(struct queueNode));
  p->conteudo = conteudo; 
  p->prox = prox;     
  return p;                         
} 

void queueInit(int n) { 
  inicio = NULL; 
}

int queueEmpty() { 
  return inicio == NULL; 
}

void queuePut(Item conteudo) { 
  if (inicio == NULL) { 
    inicio = fim = new(conteudo, NULL); 
    return; 
  }
  fim->prox = new(conteudo, NULL); 
  fim = fim->prox;
}

Item queueGet() { 
  Item conteudo = inicio->conteudo;
  Link t = inicio->prox; 
  free(inicio); 
  inicio = t;
  return conteudo;
}

void queueFree() { 
  while (inicio != NULL) { 
    Link t = inicio->prox;
    free(inicio);
    inicio = t;
  }
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
