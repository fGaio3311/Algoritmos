#include <stdio.h>
#include <stdlib.h>

typedef struct celula Celula;
struct celula {
  int conteudo;
  Celula *prox;
};

enum operacao {
  INSERCAO,
  REMOCAO,
  SAIR
};

/*
 * P R O T O T I P O S   D A S   F U N C O E S  
 */
void remova(Celula *p);

void imprima(Celula *ini);

void insira(int x, Celula *p);

int buscaRemova(int x, Celula *ini);

void *mallocSafe(size_t nbytes);

/* 
 * M A I N 
 */
int main() {
  Celula *ini;
  int x;
  int opcao;
  
  /* aloca a celula cabeca */
  ini = (Celula *)mallocSafe(sizeof(Celula));
  ini->prox = NULL;
  
  do {
    printf("Escolha um opcao: 0 (inserir), 1 (remover), 2 (sair): ");
    scanf("%d", &opcao);
    
    switch (opcao) {
    case INSERCAO:
      printf("Digite elemento a ser inserido: ");
      scanf("%d",&x);
      
      insira(x,ini);
      imprima(ini);
      break;
      
    case REMOCAO:
      printf("Digite elemento a ser removido: ");
      scanf("%d",&x);
      
      if (buscaRemova(x,ini))
	printf("Elemento removido\n");
      else
	printf("Elemento nao encontrada\n");
      
      imprima(ini);
      break;
      
    case SAIR: break;
      
    default: break ;
    }
  } while (opcao != SAIR);
  
  /* Libera o que sobrou da lista */
  while (ini->prox != NULL)
    remova(ini);
  
  free(ini);
  
  return 0;
}

/*
 * I M P L E M E N T A C A O  D A S   F U N C O E S  
 */

/* A funcao remove recebe um apontador p para uma celula e'
 * remove da lista ligada a celula apontada por p->prox.
 * A funcao suponhe que p != NULL e que p->prox != NULL.
 */
void remova(Celula *p) {
  Celula *morta;
  
  morta = p->prox;
  p->prox = morta->prox;
  free(morta);
}

/*
 * A funcao imprime recebe o apontador para a celula cabeca de 
 * uma lista ligada e imprime o endereco, campo conteudo, e campo prox,
 * de cada celula da lista ligada, exceto a celula cabeca.
 */
void imprima(Celula *ini) {
  if (ini->prox == NULL)
    printf("A lista esta vazia.\n");
  else {
    printf("Conteudo da lista:\n");
    printf("endereco      elemento   prox\n");
    for (ini=ini->prox; ini != NULL; ini=ini->prox)
      printf("%p     %5d      %p\n", 
	     (void*)ini, ini->conteudo, (void*)ini->prox);
    printf("\n");
  }
}

/* Cria uma celula para guardar um elemento x e insere esta 
 * celula depois da celula que tem endereco em p.
 */
void insira(int x, Celula *p) {
  Celula *nova;
  
  nova = (Celula *)mallocSafe(sizeof(Celula));
  nova->conteudo=x;
  nova->prox=p->prox;
  p->prox=nova;
}

/* Remove, caso exista, a primeira celula da lista com cabeca apontada
 * por ini que contem o elemento x.
 */
int buscaRemova (int x, Celula *ini) {
  Celula *ant;
  
  for (ant = ini; ini != NULL && ini->conteudo != x; ini=ini->prox)
    ant=ini;
  if (ini == NULL)  return 0;
  remova(ant);
  return 1;
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
