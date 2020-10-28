/*
 *  polonesa.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "stackS.h"

typedef enum {
  FALSE,
  TRUE
} Boolean;

int mostreItem;    /* indica se o item sendo examinado deve ser exibido */
int mostrePosfixa; /* indica se expressao em notacao posfixa deve ser 
		    * exibida depois de um item ser examinado
		    */
int mostrePilha;    /* indica se o conteudo da pilha deve ser exibido 
		     * depois de um item ser examinado
		     */

char *nomeProg;  /* nome do programa */

void mostreUso (char *nomeProg);

void *mallocSafe (unsigned int n); 

char *infixaParaPosfixa (char *infixa);

/* 
 * M A I N 
 */
int main(int argc, char *argv[]) {  
  nomeProg = argv[0];
  
  if (argc == 1) {
    mostreUso(nomeProg);
    return 0;
  }

  /* 
   * Valores "default"
   */
  mostreItem     = FALSE;
  mostrePosfixa  = FALSE;
  mostrePilha    = FALSE;

  /* examina os argumentos na linha de comando */
  while (--argc > 1) {
    if (strncmp(argv[argc],"-i",2)==0) mostreItem = TRUE;
    else if (strncmp(argv[argc],"-p",2)==0) mostrePosfixa = TRUE;
    else if (strncmp(argv[argc],"-s",2)==0) mostrePilha = TRUE;
    else {
      mostreUso(nomeProg);
      return EXIT_FAILURE;
    }
  }
  
  printf("polonesa: %s\n", infixaParaPosfixa(argv[1]));

  return 0;
}

/*
 * para_polonesa: recebe uma express�o infixa apontada por `infixa' e 
 *         devolve o endereco de um vetor que contem a correspondente 
 *         express�o polonesa.
 *
 * ATENCAO: a funcao supoe que a expressao infixa esta sintaticamente correta.
 *          Se a expressao for, digamos, "A+B)", ocorrera' "segmentation fault". 
 */
char *infixaParaPosfixa (char *infixa) {
  char *polonesa; /* apontador para a expressao polonesa */
  int  n = strlen(infixa); /* comprimento da expressao infixa */
  int  i; /* percorre a expressao infixa */
  int  j; /* percorre a expressao posfixa */
  Stack s; /* declaracao de uma pilha */
  
  /* aloca area para guardas a expresao polonesa */
  polonesa = (char *) mallocSafe((n + 1) * sizeof(char));

  s = stackInit(n); /* inicializa a pilha */

  /* examina cada item da expressao infixa */
  j = 0;
  for (i = 0; i < n; i++) {
    if (mostreItem) 
      fprintf(stdout,"item: '%c'\n", infixa[i]);
    
    switch (infixa[i]) {
      char item; /* auxiliar, recebe o elemento do topo da pilha */
      
    case '(': 
      stackPush(s, '('); /* empilha */
      break;
      
    case ')':
      while ((item = stackPop(s)) != '(')  /* desempilha */
	polonesa[j++] = item;
      break;
      
    case '+': 
    case '-': 
      while (!stackEmpty(s) && (item = stackTop(s)) != '(')
	polonesa[j++] = stackPop(s);
      stackPush(s, infixa[i]);
      break;
      
    case '*':
    case '/': 
      while (!stackEmpty(s) && (item = stackTop(s)) != '(' 
	     && item != '+' && item != '-') 
	polonesa[j++] = stackPop(s);
      stackPush(s, infixa[i]);
      break;
      
    default:  
      if (infixa[i] != ' ') 
	polonesa[j++] = infixa[i];
    }

    if (mostrePilha) 
      stackDump(s);
    
    if (mostrePosfixa) {	  
      int k; /* usado para imprimir a expressao */
      
      fprintf(stdout,"posfixa: ");
      for (k = 0; k < j; k++)
	fprintf(stdout, "%c ", polonesa[k]);
      fprintf(stdout, "\n");
    }  
  }
  
  /* desempilha todos os operandos que restaram */
  while (!stackEmpty(s)) 
    polonesa[j++] = stackPop(s);
  
  polonesa[j] = '\0'; /* fim da expressao polonesa */
  
  stackFree(s);
  
  return polonesa;
}  

/*
 * mostra a maneira de usar programa
 */
void mostreUso (char *nomeProg) {
  fprintf(stdout,"Uso: %s \"<expressao infixa>\" [-i] [-p] [-s]\n"
	  " -i mostra o item sendo examinado\n"
	  " -p mostra a expressao posfixa sendo construida\n"
	  " -s mostra o conteudo da pilha\n" 
	  , nomeProg);
}

void *mallocSafe (unsigned int n) {
  void *p;

  p = malloc(n);
  if (p == NULL) {
    fprintf(stderr,"%s, malloc de %u bytes falhou.\n", nomeProg, n);
    exit (-1);
  }
  return p;
}

