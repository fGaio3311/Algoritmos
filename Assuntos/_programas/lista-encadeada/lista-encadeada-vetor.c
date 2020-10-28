/*
 * Este programa e' um exemplo de lista encadeada implementada em 
 * um vetor. Quando utilizarmos alocacao dinamica de memoria
 * os indices do vetor serao substituidos por ponteiros
 */ 

#include <stdio.h>
#include <stdlib.h>

#define MAX  100
#define NULO -1

enum operacao {
  INSERCAO,
  REMOCAO,
  SAIR
};

struct celula {
  int conteudo; /* conteudo e' um elemento da lista */
  int prox;     /* variavel utilizada para o encadeamento */
};
typedef struct celula Celula;

/*
 * P R O T O T I P O S   D A S  F U N C O E S
 */

void imprima(int inicio, Celula v[]);

void remova(int p, int *inicio, Celula v[], int *livre);

void insira(int x, int *inicio, Celula v[], int *livre);

int buscaRemove(int x, int *inicio, Celula v[], int *livre);

void *mallocSafe(size_t nbytes);

/*
 * P R O T O T I P O S   D A S   F U N C O E S   Q U E 
 * M A N I P U L A M   A   L I S T A   L I V R E
 */

void inicializaListaLivre (int *livre, int n, Celula v[]);

int extraiCelula (int *livre, Celula v[]);

void devolveCelula (int p, int *livre, Celula v[]);

/* 
 * M A I N 
 */
int main() {
  int inicio;    /* inicio da lista encadeada */
  int livre;     /* inicio da lista com celulas livres */
  Celula *v;     /* celulas da lista encadeada */
  int n;         /* numero maximo de elementos na lista */
  int x;

  int opcao;

  printf("Digite o numero maximo de elementos da lista: ");
  scanf("%d", &n);

  /* aloca as celulas */
  v = mallocSafe(n*sizeof(Celula));

  /* inicializa a lista de celulas livres */
  inicializaListaLivre(&livre,n,v);

  /* inicialemente a lista esta vazia */
  inicio = NULO;
  
  do {
    printf("Escolha um opcao: 0 (inserir), 1 (remover), 2 (sair): ");
    scanf("%d", &opcao);
    
    switch (opcao) {
    case INSERCAO:
      printf("Digite elemento a ser inserido: ");
      scanf("%d",&x);
      
      insira(x,&inicio,v,&livre);
      imprima(inicio,v);
      break;
      
    case REMOCAO:
      printf("Digite elemento a ser removido: ");
      scanf("%d",&x);
      
      if (buscaRemove(x,&inicio,v,&livre))
	printf("Elemento removido\n");
      else
	printf("Elemento nao encontrado\n");
      
      imprima(inicio,v);
      break;
      
    case SAIR: break;
      
    default: break ;
      
    }
  } while (opcao != SAIR);
  
  /* Libera o que sobrou da lista */
  while (inicio != NULO) {
    int p = v[inicio].prox;
    devolveCelula(inicio,&livre,v);
    inicio = p;
  }

  imprima(inicio,v);
  return 0;
}

/* 
 * I M P L E M E N T A C A O   D A S   F U N C O E S
 * 
 */

/*
 * A funcao imprime recebe o apontador para a celula cabeca de 
 * uma lista ligada e imprime o endereco, campo conteudo, e campo prox,
 * de cada celula da lista ligada, exceto a celula cabeca.
 */
void imprima(int inicio, Celula v[]) {
  int i;

  if (inicio == NULO)
    printf("A lista esta vazia.\n");
  else {
    printf("Conteudo da lista:\n");
    printf("indice   elemento   prox\n");
    for (i=inicio; i != NULO; i=v[i].prox)
     printf("%3d      %5d      %3d\n",i, v[i].conteudo, v[i].prox);
    printf("\n\n");
  }
}

/* A funcao remove recebe um indice p para uma celula e'
 * remove da lista ligada a celula de indice v[p].prox.
 * Se p == NULO a celula removida sera a do inicio da
 * lista encadeada. A funcao supoe que *inicio != NULO
 * e que v[p].prox != NULO
 */
void remova(int p, int *inicio, Celula v[], int *livre) {
  int morta;
  
  if (p == NULO)  /* remove do inicio da lista */
    {
      morta = *inicio;
      *inicio = v[morta].prox;
    }
  else
    {
      morta = v[p].prox;
      v[p].prox = v[morta].prox;
    }

  devolveCelula(morta,livre,v);
}

/* Cria uma celula para guardar um elemento x e insere esta 
 * celula no inicio da lista encadeada
 */
void insira(int x, int *inicio, Celula v[], int *livre) {
  int nova, p;

  nova = extraiCelula(livre,v);
  v[nova].conteudo = x;
  p = *inicio;
  *inicio = nova;
  v[nova].prox = p;
}

/* Remove, caso exista, a primeira celula da lista com cabeca 
 * apontada por ini que contem o elemento x. A funcao 
 * devolve 1 se o elemento foi encontrado e removido e 
 * devolve 0 em caso contrario.
 */
int buscaRemove(int x, int *inicio, Celula v[], int *livre) {
  int atual; /* celula atual */
  int ant;   /* celula anterior */

  ant   = NULO;
  atual = *inicio;

  while (atual != NULO && v[atual].conteudo != x) {
    ant = atual;
    atual = v[atual].prox;
  }

  if (atual == NULO) return 0;
  remova(ant,inicio,v,livre);
  return 1;
}

/*
 * I M P L E M E N T A C A O   D A S   F U N C O E S   Q U E 
 * M A N I P U L A M   A   L I S T A   L I V R E
 */

/* A funcao inicializaListaLivre cria o encadeamos 
 * das de n celulas que estao no vetor v. A
 * variavel *livre recebe o valor 0 que sera o 
 * inicio das lista encadeada de celulas livres
 */
void inicializaListaLivre(int *livre, int n, Celula v[]) {
  int i;

  for (i = 0; i < n-1; i++)
    v[i].prox = i+1;

  v[n-1].prox = NULO;
  *livre = 0;
}

/*
 * Funcao que estrai uma celula da lista livre e devolve 
 * o seu indice. Se a lista livre esta vazia a funcao 
 * termina a execucao do programa
 */

int extraiCelula(int *livre, Celula v[]) {
  int p = *livre;

  if (p == NULO) {
    fprintf(stderr,"Socorro! A lista livre esta vazia!\n");
    exit(EXIT_FAILURE); /* equivalente a exit(1); */
  }
  
  *livre = v[p].prox;
  return p;
}

void devolveCelula(int p, int *livre, Celula v[]) {
  v[p].prox = *livre;
  *livre = p;
}

/*
 * Funcao das notas de aula de Paulo Feofiloff
 * http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html
 */
void *mallocSafe (size_t nbytes) {
   void *ptr;
   ptr = malloc (nbytes);
   if (ptr == NULL) {
      printf ("Socorro! malloc devolveu NULL!\n");
      exit (EXIT_FAILURE);
   }
   return ptr;
}
