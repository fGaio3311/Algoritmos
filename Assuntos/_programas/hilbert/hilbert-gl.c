/*
    hilbert-gl.h
    Encapsula as rotinas gráficas para desenhar as curvas de Hilbert

*/

/* #include "hilbert-gl.h" */
#include "hilbert.c"

#ifndef HILBERT_GL_H_INCLUDED
#define HILBERT_GL_H_INCLUDED

#define WIDTH  900
#define HEIGHT 900

#define LADOQUADRADO 1540
#define MAX_POINTS 100000
#define MAX_STEP 9

#define BACKGROUND_COLOR 0.8, 0.8, 0.8, 1.0

/*************************************************************/
/*         prototipo e funcoes da parte grafica            */

void myReshape(int w, int h);
void myKeyboard (unsigned char key, int x, int y);
void myDisplay(void);
void myAnim (int fim);
void myInit(int delay);

/*
   Variáveis globais
 */

float gX[MAX_POINTS], gY[MAX_POINTS];
int gNivel[MAX_STEP];
int gAltura, gLargura;
int gLadoQuadrado;
int gNumPoints;
int gX0, gY0;
int gStep;
int gDelay;

float COLOR[11][3]=
{
    {1.0, 0.0, 0.0}, // red
    {0.0, 0.8, 0.0}, // green
    {0.0, 0.0, 1.0}, // blue
    {1.0, 1.0, 0.0}, // yellow
    {1.0, 0.0, 1.0}, // magenta
    {1.0, 1.0, 1.0},  // white
    {0.2, 0.7, 0.4}, // green 2
    {0.7, 0.4, 0.2}, // red 2 - marrom
    {0.0, 1.0, 1.0}, // cyan
    {0.5, 0.5, 0.5}, // cinza
    {0.0, 0.0, 0.0} // black
};
/* ****************************************************** */
/* Coloca um ponto (x,y) no vetor para ser desenhado      */

void desenhaLinha(int x, int y)
{
    /*delay(comprimento);*/
    gX[gNumPoints] = x;
    gY[gNumPoints] = y;
    gNumPoints++;

    glutPostRedisplay(); // request redisplay
}

/* ********************************************* */
/* Chamada quando a janela muda de tamanho       */

void myReshape(int w, int h)
{
#if 0
    gX0 = w / 2;
    gY0 = h / 2;
#else
    gX0 = 50;
    gY0 = 0;
#endif
    gAltura = h;
    gLargura = w;
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h); // map drawing area to viewport
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay(); // request redisplay
}

/* ********************************************* */
/* Chamada quando uma tecla é apertada           */

void myKeyboard (unsigned char key, int mx, int my)
{
  int x, y;
  switch (key)
    {
    case 'q':
    case 'Q':
      exit(0);
      break;
    case ' ':
      if (gStep < MAX_STEP)
        {
	  gLadoQuadrado = gLadoQuadrado/2;
	  x = gX0  = gX0 + gLadoQuadrado/2;
	  y = gY0  = gY0 + gLadoQuadrado/2;
	  gX[gNumPoints] = x;
	  gY[gNumPoints] = y;
	  gNumPoints++;
	  a(gStep, &x, &y, gLadoQuadrado);
	  
	  gNivel[gStep] = gNumPoints;
	  gStep++;
	  printf("Passo: %d com %d pontos. Origem = (%4d x %4d) \n", gStep, gNumPoints-1, gX0, gY0);
        }
      else
	printf("Passo max: %d com %d pontos\n", gStep, gNumPoints);
      break;
      
    case 'a':
    case 'A':
      gDelay += 10;
      printf("Delay = %d\n", gDelay);
      break;
      
    case 's':
    case 'S':
      gDelay -= 10;
      if (gDelay < 0) gDelay = 0;
      printf("Delay = %d\n", gDelay);
      break;
      
    default:
      break;
    }
}

/* ******************************************************
   myAnim: rotina de desenho de linhas com delay para visualizar
    a trajetória do cursor
 */

void myAnim (int fim)
{
    int i, n=0;
    if (fim >= gNumPoints) {
        return;
    };

    glColor3fv( COLOR [n] );
    glBegin(GL_LINE_STRIP);
    for (i = 0; i <= fim; i++)
    {
        if (i >= gNivel[n])
        {
            glColor3fv( COLOR [n] );
            n++;
        }
        glVertex2f( gX[i], gY[i] );
    }
    glEnd();

    i--;
    printf("     Nivel %3d Linha %3d ate %4.f x %4.f\n", n, i, gX[i], gY[i]);

    glutSwapBuffers(); 

    glutTimerFunc(gDelay, myAnim, fim+1);
}

/* ******************************************************
   myDisplay: rotina de callback para desenho da curva
 */
void myDisplay(void)
{
    /* glClearColor( BACKGROUND_COLOR ); */
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(2.0);

    if (gStep < 2)
        glutTimerFunc(gDelay, myAnim, 1);
    else if (gDelay == 1)
        glutTimerFunc(gDelay, myAnim, gNumPoints-1);
    else
        glutTimerFunc(gDelay, myAnim, gNivel[gStep-2]);
    glutSwapBuffers();
}
/*
void myInit()
*/
void myInit ( int delay )
{
    gDelay = delay;
    gLadoQuadrado = LADOQUADRADO;
    gNumPoints = 0;
    gStep = 0;

    /* GLUT */
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize ( WIDTH, HEIGHT );
    glutInitWindowPosition (100, 100);

    glutCreateWindow ("Curvas de Hilbert");
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    // glutMouseFunc(mouse);
    glutKeyboardFunc(myKeyboard);

}

#endif // HILBERT-GL_H_INCLUDED
