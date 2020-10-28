#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  mostrePilha    =  FALSE;

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
 * infixaParaPosfixa: recebe uma expressão infixa apontada por `infixa' e 
 *         devolve o endereco de um vetor que contem a correspondente 
 *         expressão polonesa.
 *
 * ATENCAO: a funcao supoe que a expressao infixa esta sintaticamente correta.
 *          Se a expressao for, digamos, "A+B)", ocorrera' "segmentation fault". 
 */
char *infixaParaPosfixa (char *infixa) {
  char *polonesa; /* apontador para a expressao polonesa */
  int  n = strlen(infixa); /* comprimento da expressao infixa */
  int  i; /* percorre a expressao infixa */
  int  j; /* percorre a expressao posfixa */
  char *s; /* guarda os elementos da pilha */
  int   topo; /* indice to topo da pilha */      
  
  /* aloca area para guardar a expresao polonesa */
  polonesa = mallocSafe ((n + 1) * sizeof(char));
  /* O '+1' e' para o \0 */
  
  /* stackInit(n): inicializa a pilha */
  s = mallocSafe (n * sizeof(char));
  topo = 0;
  
  /* examina cada item da expressao infixa */
  j = 0;
  for (i = 0; i < n; i++) {
    if (mostreItem) 
      fprintf(stdout,"item   : '%c'\n", infixa[i]);
    
    switch (infixa[i]) {
      char item; /* auxiliar, recebe o elemento do topo da pilha */

    case '(': 
      /* stackPush(infixa[i]) */
      s[topo++] = infixa[i];    
      break;
    case ')':
      /* item = stackPop() */
      while ((item = s[--topo]) != '(')  
	polonesa[j++] = item;
      break;
      
    case '+': 
    case '-': 
      /* !stackEmpty() && (stackTop() != '(') */ 
      while (topo !=0 && (item = s[topo-1]) != '(') 
	polonesa[j++] = s[--topo];  /* stackpop() */
      
      /* stackPush(infica[i]*/
      s[topo++] = infixa[i];
      break;
      
    case '*':
    case '/': 
      /* !stackEmpty() && precedencia(stackTop()) <= precedencia(infixa[i]) */
      while (topo != 0 && (item = s[topo-1]) != '(' && item != '+' && item != '-') 
	polonesa[j++] = s[--topo];
      
      /* stackPush(infica[i]) */
      s[topo++] = infixa[i];
      break;
      
    default:  
      if (infixa[i] != ' ') 
	polonesa[j++] = infixa[i];
    }

    if (mostrePilha) {
      /* stackDump() */
      int k; /* usado para imprimir o conteudo da pilha */
      
      fprintf(stdout,"pilha  : ");
      if (topo == 0) fprintf(stdout, "vazia.");
      for (k = 0; k < topo; k++) 
	fprintf(stdout, "%c ", s[k]);
      fprintf(stdout,"\n");
    }
    
    if (mostrePosfixa) {	  
      int k; /* usado para imprimir a expressao */
      
      fprintf(stdout,"posfixa: ");
      for (k = 0; k < j; k++)
	fprintf(stdout, "%c ", polonesa[k]);
      fprintf(stdout, "\n");
    }

    if (mostreItem || mostrePosfixa || mostrePilha)
      printf("\n");
  }
  
  /* desempilha todos os operandos que restaram */
  /* !stackempty() */
  while (topo != 0) 
    polonesa[j++] = s[--topo];     /* stackpop()  */
  
  polonesa[j] = '\0'; /* fim da expressao polonesa */
  
  /* stackfree() */
  free(s);
  
  return polonesa;
}  

/*
 * mostra a maneira de usar programa
 */
void mostreUso (char *nomeProg) {
  fprintf(stdout,"Uso: %s \"<expressao infixa>\" [-i] [-e] [-p]\n"
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
