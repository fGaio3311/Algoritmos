/*
  Hilbert.c
  Programa para desenhar curvas de Hilbert,
  com animação em OpenGL
 */

#include "hilbert-gl.h"

typedef enum 
  {
    DIREITA, 
    ESQUERDA, 
    CIMA, 
    BAIXO
  } Direcao;

/* 
 * P R O T O T I P O S 
 */

void linha (int *x, int *y, Direcao direcao, int comprimento);
void  a (int k, int *x, int *y, int comprimento);
void  b (int k, int *x, int *y, int comprimento);
void  c (int k, int *x, int *y, int comprimento);
void  d (int k, int *x, int *y, int comprimento);

/* 
 * M A I N 
 *
 */

int main(int argc, char** argv)
{
  int delay = DEFAULT_DELAY;

  if (argc == 2) delay = atoi(argv[1]);
  
  glutInit(&argc, argv);
  myInit ( delay );
  glutMainLoop();
  return 0;
}

/*
 * I M P L E M E T A C A O   D A S   F U N C O E S
 */

/*
 *  A : dado k, e posicao (*x,*y) da pena e o comprimento 
 *     dos segmentos, desenha a curva A_k
 */
void  a (int k, int *x, int *y, int comprimento) 
{
  if (k > 0) 
    {
      d(k-1, x, y, comprimento);
      linha (x, y, ESQUERDA, comprimento);
      a(k-1, x, y, comprimento);
      linha (x, y, BAIXO   , comprimento);
      a(k-1, x, y, comprimento);
      linha (x, y, DIREITA , comprimento);
      b(k-1, x, y, comprimento);
    }
}

/*
 *  B : dado k, e posicao (*x,*y) da pena e o comprimento 
 *     dos segmentos, desenha a curva B_k
 */
void  b (int k, int *x, int *y, int comprimento) {
  if (k > 0) 
    {
      c(k-1, x, y, comprimento);
      linha (x, y, CIMA   , comprimento);
      b(k-1, x, y, comprimento);
      linha (x, y, DIREITA, comprimento);
      b(k-1, x, y, comprimento);
      linha (x, y, BAIXO  , comprimento);
      a(k-1, x, y, comprimento);
    }
}

/*
 *  C : dado k, e posicao (*x,*y) da pena e o comprimento 
 *     dos segmentos, desenha a curva C_k
 */
void  c (int k, int *x, int *y, int comprimento) 
{
  if (k > 0) 
    {
      b(k-1, x, y, comprimento);
      linha (x, y, DIREITA, comprimento);
      c(k-1, x, y, comprimento);
      linha (x, y, CIMA    , comprimento);
      c(k-1, x, y, comprimento);
      linha (x, y, ESQUERDA, comprimento);
      d(k-1, x, y, comprimento);
    }
}

/*
 *  D : dado k, e posicao (*x,*y) da pena e o comprimento 
 *     dos segmentos, desenha a curva D_k
 */
void  d (int k, int *x, int *y, int comprimento) 
{
  if (k > 0) 
    {
      a(k-1, x, y, comprimento);
      linha (x, y, BAIXO   , comprimento);
      d(k-1, x, y, comprimento);
      linha (x, y, ESQUERDA, comprimento);
      d(k-1, x, y, comprimento);
      linha (x, y, CIMA    , comprimento);
      c(k-1, x, y, comprimento);
    }
}

/* 
 * linha(*x,*y,direcao,comprimento): recebe a posicao (*x,*y) 
 *   da 'pena', uma direcao e um valor comprimento e    
 *   desenha uma linha a partir da posicao da pena na 
 *   direcao dada e do comprimento dado. A posicao da 
 *   pena e' atualizada.
 *
 */

void linha (int *x, int *y, Direcao direcao, int comprimento)
{
  switch (direcao) 
    {
    case DIREITA  : *x = *x + comprimento;
      break;
    case ESQUERDA : *x = *x - comprimento;
      break;
    case CIMA     : *y = *y + comprimento;
      break;
    case BAIXO    : *y = *y - comprimento;
      break;
    }
  
  desenhaLinha(*x, *y);
}
