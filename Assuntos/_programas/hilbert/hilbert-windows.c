#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>

/* Programa para desenhar curvas de Hilbert.   */
/* Suponhe que estamos usando o Turbo C ou Borland C
 */

typedef enum {DIREITA, ESQUERDA, CIMA, BAIXO} umadirecao;

/*
 *  Prototipos das funcoes.
 */
void a (int k, int *x, int *y, int comprimento) ;
void b (int k, int *x, int *y, int comprimento) ;
void c (int k, int *x, int *y, int comprimento) ;
void d (int k, int *x, int *y, int comprimento) ;

void linha (int *x, int *y, umadirecao direcao, int comprimento) {
  switch (direcao) {
	case DIREITA  : *x = *x + comprimento;
			break;
	case ESQUERDA : *x = *x - comprimento;
			break;
	case CIMA     : *y = *y - comprimento;
			break;
	case BAIXO    : *y = *y + comprimento;
			break;
  }
  /*delay(comprimento);*/
  lineto (*x,*y);
}
/*
 *  A
 */
void  a (int k, int *x, int *y, int comprimento) {
  if (k > 0) {
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
 *  B
 */
void  b (int k, int *x, int *y, int comprimento) {
  if (k > 0) {
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
 *  C
 */
void  c (int k, int *x, int *y, int comprimento) {
  if (k > 0) {
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
 *  D
 */
void  d (int k, int *x, int *y, int comprimento) {
  if (k > 0) {
        a(k-1, x, y, comprimento);
        linha (x, y, BAIXO   , comprimento);
        d(k-1, x, y, comprimento);
        linha (x, y, ESQUERDA, comprimento);
        d(k-1, x, y, comprimento);
        linha (x, y, CIMA    , comprimento);
        c(k-1, x, y, comprimento);
  }
}

int main(void) {
  /* request auto detection */
  int gdriver = VGA, gmode = VGAHI, errorcode;
  int i, x0, y0, x, y, altura, largura, ladoquadrado;
  char msg[80];

  /* initialize graphics and local variables */
  initgraph(&gdriver, &gmode, "");

  /* read result of initialization */
  errorcode = graphresult();
  if (errorcode != grOk) {
    printf("Graphics error: %s\n", grapherrormsg(errorcode));
    printf("Press any key to halt:");
    getch();
    return(1);
  }


  /* create and output a  message at (20, 30) */
  sprintf(msg, "Curvas de Hilbert:");
  outtextxy(20, 30, msg);

  altura  = getmaxy();
  largura = getmaxx();

  ladoquadrado  =  400;
  x0 = largura/2;
  y0 = altura /2;

  for (i = 1; i <= 7; i++) {
    setcolor(i);
    ladoquadrado= ladoquadrado/2;
    x0  = x0 + ladoquadrado/2;
    y0  = y0 - ladoquadrado/2;
    x = x0;
    y = y0;
    moveto(x,y);
    a(i, &x, &y, ladoquadrado);
    getch();
    cleardevice(); /* limpa a tela, pode ser interessante nao
                    * limpar a tela e sobrepor as figuras
                    */
    outtextxy(20, 30, msg);
  }

  closegraph();
  return 0;
}
