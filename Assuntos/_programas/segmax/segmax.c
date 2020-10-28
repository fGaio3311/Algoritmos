#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#define frand() ((double) rand() / (RAND_MAX+1.0))
#define PNEG 0.5

typedef enum {
  FALSE,
  TRUE
} Boolean;

enum {
  NMIN = 0x0100, 
  NMAX = 0x20000000,
  SEMENTE = 1234567,  /* semente default para o gerador de no. aleatorios */
  NO_EXPERIMENTOS = 1, /* no. de experimentos default. */
  DEBUG = 0, 
  MAX = 1024
};

char *nomeProg;  /* nome do programa */

/* 
 * P R O T Ó T I P O S   
 */

/* Funcoes auxiliares */
void *mallocSafe (unsigned int n); 

void vetorRand (int n, int *v, float pNeg);

void mostreVetor (int n, int *v);

void mostreUso (char *nomePrograma);

double segMax (void (*sortprog)(), int *v, int n, int *e, int *d, long *soma);

/* Algoritmos */
void segMax1(int v[], int n, int *e, int *d, long *soma);

void segMax2(int v[], int n, int *e, int *d, long *soma);

void segMax3(int v[], int n, int *e, int *d, long *soma);

/* 
 * M A I N 
 */

int main(int argc, char *argv[]) {
  register int n;     /* numero de items do vetor */
  int min;            /* numero minimo de elementos da sequencia */
  int max;            /* numero maximo de elementos da sequencia */

  long int semente;    /* para o gerador de numeros aleatorios */
  int no_experimentos; /* numero de repeticoes de uma ordenacao para um 
                        * dado tamanho de vetor */
  Boolean linear;      /* para executar algoritmo linear */
  Boolean quadratico;  /* para executar algoritmo quadratico */
  Boolean cubico;      /* para executar os algoritmo cubico */

  float pNeg;          /* probabilidade de um número ser negativo */ 

  int *v; /* vetor que guarda v gerada */

  nomeProg = argv[0];  /* nome do programa */
  
  /* uso do programa */
  if (argc == 1) {
    mostreUso(nomeProg);
    return 0;
  }
  
  /* valores default para os parametros */
  semente = SEMENTE;
  no_experimentos = 1;
  linear     = FALSE;
  quadratico = FALSE;
  cubico     = FALSE;
  max        = NMAX;
  min        = NMIN;
  pNeg       = PNEG;
  
  /* examina os argumentos na linha de comando */
  while (--argc) {
    if (sscanf(argv[argc],"-m%d", &max)==1);
    else if (sscanf(argv[argc],"-v%d", &max)==1) min = max;
    else if (sscanf(argv[argc],"-p%f", &pNeg)==1) ;
    else if (sscanf(argv[argc],"-s%ld", &semente)==1) ;
    else if (sscanf(argv[argc],"-e%d", &no_experimentos)==1);
    else if (strncmp(argv[argc],"-l",2)==0) linear = TRUE;
    else if (strncmp(argv[argc],"-q",2)==0) quadratico = TRUE;
    else if (strncmp(argv[argc],"-c",2)==0) cubico = TRUE;
    else {
      mostreUso(nomeProg);
      return EXIT_FAILURE;
    }
  }

  /* inicializa a semente do gerador de numeros aleatorios */
  srand(semente);

  fprintf(stdout,"Inicializando o vetor para os testes. .  .\n");
  /* alocar vetor */
  v = (int*) mallocSafe(max*sizeof(int));

  /* inicializa vetor com a sequencia */
  vetorRand(max,v,pNeg);
  fprintf(stdout,"Vetor inicializado.\n\n");

  if (DEBUG) {
    fprintf(stdout,"semente = %ld\n", semente);
    mostreVetor (max,v);
  }
  
  fprintf(stdout,"         n ");

  if (linear) {
    fprintf(stdout,"      linear ");
  }
  
  if (quadratico) {
    fprintf(stdout,"  quadratico ");
  }
  
  if (cubico) {
    fprintf(stdout,"      cubico ");
  }
  
  fprintf(stdout,"\n");

  for (n = min ; n <= max; n *= 2) {
    int i;
    double t_linear      = 0;
    int e1 = 0, d1 = 0;
    long soma1 = -1;
    
    double t_quadratico  = 0;
    int e2 = 0, d2 = 0;
    long soma2 = -2;
    
    double t_cubico      = 0;
    int e3 = 0, d3 = 0;
    long soma3 = -3;
    
    for (i = 0; i < no_experimentos; i++) {
	
      /* algoritmo linear */
      if (linear) {
	t_linear     += segMax(segMax1,v,n,&e1,&d1,&soma1);
      }
      
      if (quadratico) {
	t_quadratico += segMax(segMax2,v,n,&e2,&d2,&soma2);
      }
      
      if (cubico) {
	t_cubico     += segMax(segMax3,v,n,&e3,&d3,&soma3);
      }
      
      if (DEBUG || (linear && quadratico && soma1 != soma2)
	        || (linear && cubico  && soma1 != soma3)
	        || (quadratico && cubico && soma2 != soma3)) { 
	fprintf(stdout,
		"\n O vetor contem %d numeros.\n"
		" Foi encontrada uma subsequencia de soma maxima com\n"
		" Inicio: (%d ,  %d,  %d)\n"
		"  Final: (%d ,  %d,  %d)\n"
		"   Soma: (%ld, %ld, %ld)\n\n"
		,n, e1, e2, e3, d1, d2, d3, soma1, soma2, soma3);
	/* return EXIT_FAILURE; */
      }
    }
    
    fprintf(stdout,"%10d", n);
    if (linear)	{
      fprintf(stdout,"%12.2f ", t_linear/no_experimentos);
    }
    if (quadratico) {
      fprintf(stdout,"%12.2f ", t_quadratico/no_experimentos);
    }
    if (cubico) {
      fprintf(stdout,"%12.2f ", t_cubico/no_experimentos);
    }
    fprintf(stdout,"\n");
  }

  fprintf(stdout,"Tempos em segundos.\n");
  return 0;
}

/* 
 * F U N C O E S    S E G M A X 
 * 
 */

/*
 * S E G M A X 1: A funcao segMax recebe:
 *
 *          - um inteiro positivo n e 
 *          - um vetor de inteiros v[0..n-1]
 *
 * e devolve:
 *
 *          - apontadores de inteiros e, d e soma, tais que 
 *            
 *            (1) o valor de *e e *d esta entre -1 e n-1
 *
 *            (2) o valor
 *
 *            *soma = v[*e] + v[*e+1] + ... +
 *                                     sequancia[*d]         
 *
 *            e' maximo. 
 * 
 *            Caso o vetor v so' tenha inteiros
 *            nao-positivos a funcao devolve *e = *lr = -1 e 
 *            *soma = 0.
 *
 * Esta funcao consome uma quantidade de tempo proporcional a n.
 */
void segMax1(int v[], int n, int *e, int *d, long *soma) {
  register int i, j;
  int l, r;
  register long s;    /* soma do segmento sob consideracao */
  register long smax; /* maior soma de um segmento ate' o momento */
  
  s = smax = 0; 
  l = r = -1; 
  i = 0;

  for (j = 0; j < n; j++) {
    /* Neste ponto do programa vale que:
     * 
     * (1) s = v[i] + ... + v[j-1];
     *
     * (2) v[i] + ... + v[k] >= 0
     *     para todo k, i <= k < j-1;
     *
     * (3) smax = v[l] + v[l+1] + ... + v[r] e' o segmento de soma 
     *     maxima de v[0..j-1]. 
     */
    if (s < 0) { 
      /*
       * Nenhum segmento de soma maxima pode ter um prefixo
       * de soma negativa.
       * 
       * Neste ponto vale que 
       *
       *    v[i] + ... + v[j-1] < 0  (4)
       * 
       * De (4) e (2) tem-se que
       *
       *    v[k] + ... + v[j-1] < 0 
       *
       * para todo k, i <= k <= j.
       */  
      i = j;
      s = v[j];
    }
    else 
      /* if (v[j] > LONG_MAX - s) {
  	   fprintf(stderr,"ERRO: ocorreu overflow.\n");
	   exit(-1);
	 }
	 else */
      s += v[j];
    
    if (s > smax) {
      smax = s;
      l = i;
      r = j;
    }
  }
  
  *e = l;
  *d = r;
  *soma = smax;
}

/*
 * A funcao segMax2 recebe:
 *          - um inteiro positivo n e 
 *          - um vetor de inteiros v[0..n-1]
 *
 * e devolve:
 *
 *          - apontadores de inteiros e, d e soma, tais que 
 *            
 *            (1) o valor de *e e *d esta entre -1 e n-1
 *
 *            (2) o valor
 *
 *            *soma = v[*e] + v[*e+1] + ... +
 *                                     sequancia[*d]         
 *
 *            e' maximo. 
 * 
 *            Caso o vetor v so' tenha inteiros
 *            nao-positivos a funcao devolve *e = *lr = -1 e 
 *            *soma = 0.
 *
 * Esta funcao consome uma quantidade de tempo proporcional a
 *   n * n.
 */

void segMax2(int v[], int n, int *e, int *d, long *soma) {
  register int i, j;
  int l, r;
  register long s;    /* soma do segmento sob consideracao */
  register long smax; /* maior soma de um segmento ate' o momento */
  
  s = smax = 0; 
  l = r = -1; 

  for (i = 0; i < n; i++) {
    s = 0;
    for (j = i; j < n; j++) { 
      s += v[j];
	  
      /* 
       * s = v[i] + v[i+1] + ... + v[j]
       */
      
      if (s > smax) {
	smax = s;
	l = i;
	r = j;
      }
    }
  }
  
  *e = l;
  *d = r;
  *soma = smax;
}

/*
 * A funcao segMax3 recebe:
 *          - um inteiro positivo n e 
 *          - um vetor de inteiros v[0..n-1]
 *
 * e devolve:
 *
 *          - apontadores de inteiros e, d e soma, tais que 
 *            
 *            (1) o valor de *e e *d esta entre -1 e n-1
 *
 *            (2) o valor
 *
 *            *soma = v[*e] + v[*e+1] + ... +
 *                                     sequancia[*d]         
 *
 *            e' maximo. 
 * 
 *            Caso o vetor v so' tenha inteiros
 *            nao-positivos a funcao devolve *e = *lr = -1 e 
 *            *soma = 0.
 *
 * Esta funcao consome uma quantidade de tempo proporcional a
 *   n * n * n.
 */

void segMax3(int v[], int n, int *e, int *d, long *soma) {
  register int i, j, k;
  int l, r;
  register long s;    /* soma do segmento sob consideracao */
  register long smax; /* maior soma de um segmento ate' o momento */
  
  s = smax = 0; 
  l = r = -1; 

  for (i = 0; i < n; i++)
    for (j = i; j < n; j++) {
      s = 0;
      for (k = i; k <= j; k++)  
	s += v[k];
      
      /* 
       * s = v[i] + v[i+1] + ... + v[j]
       */
      
      if (s > smax) {
	smax = s;
	l = i;
	r = j;
      }
    }
  
  *e = l;
  *d = r;
  *soma = smax;
}

/* 
 *  F U N C O E S    A U X I L I A R E S 
 *
 */

/*
 *
 */
double segMax (void (*segMaxX)(), int *v, int n, int *e, int *d, long *soma) {
  clock_t start, end; /* usadas para medir tempo de processamento */
  double elapsed;

  /* comeca a cronometrar */
  start = clock(); 

  /* ordena a v */
  (*segMaxX)(v, n, e, d, soma); 

  /* trava o cronometro */  
  end = clock();

  /* printf("start=%e end = %e\n", (double)start, (double)end); */
  
  /* calcula o tempo */
  elapsed = ((double) (end - start)) / CLOCKS_PER_SEC; 

  return elapsed;
}

/*
 * mostra a meneira de usar programa
 */
void mostreUso (char *nomePrograma) {
  fprintf(stdout,
	  "Uso: %s [-l] [-q] [-c] [-m<tam>] [-v<tam>] [-s<semente>] [-e<no. experimentos>].\n"
	  "     -l  executa algoritmo linear\n"
	  "     -q  executa algoritmo quadratico\n"
	  "     -c  executa algoritmo cubico\n"
	  "     -m<tam> testa com vetores com 2^k <= <tam> elementos\n"
          "     -v<tam> testa apenas com 1 vetor com <tam> elementos\n"
	  "     -s<semente>  para o gerar sequencias aleatorias\n"
	  "     -e<no. experimentos> indica o numero de repeticoes de cada exp.\n"
	  , nomePrograma);
}

/* 
 * vetor_rand: gera um vetor v[0..n-1] de numeros inteiros.
 */
void vetorRand (int n, int *v, float pNeg) {
  register int i;

  for (i = 0; i < n; i++) {
    v[i] = frand() * MAX;
    if (DEBUG) printf("frand() = %f\n", frand());
    if (frand() < pNeg)
      v[i] = -v[i];      
  }
}

/*
 * mostre_vetor: escreve o conteudo do vetor v
 */
void mostreVetor (int n, int *v) {
  register int i;
  
  fprintf(stdout,"Vetor: \n");
  for (i = 0; i < n; i++) 
    fprintf(stdout,"%8d: %d\n", i, v[i]);
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
