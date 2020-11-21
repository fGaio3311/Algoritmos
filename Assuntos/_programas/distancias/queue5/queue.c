/*
 *  distancias.c
 */
#include <stdio.h>
#include <stdlib.h>

static void *mallocSafe (unsigned int n);

/*
 * FILA: uma implementacao com lista encadeada sem cabeca
 */

/* item.h */
typedef int Item;

typedef struct queueNode* Link;
struct queueNode { 
  Item conteudo; 
  Link prox; 
};

struct queue { 
  Link inicio;
  Link fim;    
}; 

typedef struct queue *Queue;

static Link new(Item conteudo, Link prox) { 
  Link x = (Link) mallocSafe(sizeof *x);
  x->conteudo = conteudo; x->prox = prox;     
  return x;                         
}

Queue queueInit(int maxN) { 
  Queue q = (Queue) mallocSafe(sizeof *q); 
  q->inicio = NULL; 
  q->fim = NULL; 
  return q;
}

int queueEmpty(Queue q) { 
  return q->inicio == NULL; 
}

void queuePut(Queue q, Item conteudo) { 
  if (q->inicio == NULL) { 
    q->fim = new(conteudo, NULL);
    q->inicio = q->fim; 
    return; 
  }
  q->fim->prox = new(conteudo, NULL); 
  q->fim = q->fim->prox;
}

Item queueGet(Queue q) { 
  Item conteudo = q->inicio->conteudo;
  Link t = q->inicio->prox;
  free(q->inicio); 
  q->inicio = t;
  return conteudo;
}

void queueFree(Queue q) { 
  while (q->inicio != NULL) { 
    Link t = q->inicio->prox;
    free(q->inicio);
    q->inicio = t;
  }
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

int main()
{
  Queue a;
  a = queueInit(5);

  Item *teste;

  teste = mallocSafe(2*sizeof(int));
  
  teste[0] = 1;
  teste[1] = 3;

  queuePut(a, teste);

  teste[0] = 7;
  teste[1] = 2;

  queuePut(a, teste);

  teste = queueGet(a);

  printf("%d %d", teste[0], teste[1]);

  return 0;
}