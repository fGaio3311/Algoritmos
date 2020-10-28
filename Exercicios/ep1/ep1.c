/*    
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO-PROGRAMA (EP) FORAM 
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
  E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
  POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM 
  REPROVAÇÃO DIRETA NA DISCIPLINA.

  Nome: Lucas Ventura Monegatto
  NUSP: 10731901

  main.c

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma referência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:

  - função mallocSafe copiada de: 

       http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdio.h>

#define FNMAX 200

/* ---------------------------------------- */
/* ---------------PROTÓTIPOS--------------- */
/* ---------------------------------------- */

/* Função recursiva que desenha a estrela de Koch */
void Koch(int ordem, FILE *arq, int *fim, double len);

/* Função recursiva que desenha a árvore de Koch */
void Arvore(int ordem, FILE *arq, double len, double centroX, double centroY);

/* Função recursiva que desenha o meu fractal personalizado */
void MeuFrac(int ordem, FILE *arq, int *fim, double len);

/* Abre arquivos */
FILE *open(char nomearq[FNMAX]);

/* Fecha arquivos */
void close(FILE *arq);

/* ---------------------------------------- */
/* ------------------MAIN------------------ */
/* ---------------------------------------- */

int main()
{

    int num, ordem, i, fim;
    double len;
    char nome[FNMAX];
    FILE *arq;

    printf("0 - Estrela de Koch\n");
    printf("1 - Arvore H\n");
    printf("2 - Fractal\n");

    printf("Digite um numero: ");
    scanf("%d", &num);

    printf("Ordem: ");
    scanf("%d", &ordem);

    printf("Nome do arquivo: ");
    arq = open(nome);

    fprintf(arq, "<< /PageSize [595 842] >> setpagedevice\n");

    if (num == 0)
    {
        /*
        515 é o lado do triangulo inicial
        595 x 842 é o tamanho da página
        Essa parte do código permite que mudando apenas o lado, o desenhe fique centralizado
         */

        len = 515.0;

        fprintf(arq, "595 %.1lf sub 2 div 842 %.1lf 0.86 mul sub 1.5 div moveto\n", len, len);

        for (i = 0; i < ordem; i++)
        {
            len /= 3.0;
        }

        for (i = 0; i < 3; i++)
        {
            fim = ordem;
            fprintf(arq, "%.3lf 0\n", len);
            if (ordem != 0)
                Koch(ordem, arq, &fim, len);
            else
                fprintf(arq, "rlineto\n");
            if (i != 2)
                fprintf(arq, "120 rotate\n");
        }
    }

    if (num == 1)
    {
        len = 190.0;
        Arvore(ordem, arq, len, 595/2, 842/2);
    }

    if (num == 2)
    {
        /*
        290 é o lado do quadrado inicial
        595 x 842 é o tamanho da página
        Essa parte do código permite que mudando apenas o lado, o desenhe fique centralizado
         */

        len = 290.0;

        fprintf(arq, "595 %.3lf sub 2 div 842 %.3lf sub 2 div moveto\n", len, len);

        for (i = 0; i < ordem; i++)
        {
            len /= 3.0;
        }

        for (i = 0; i < 4; i++)
        {
            fim = ordem;
            fprintf(arq, "\n%.3lf 0\n", len);
            if (ordem != 0)
                MeuFrac(ordem, arq, &fim, len);
            else
                fprintf(arq, "rlineto\n");
            if (i != 3)
                fprintf(arq, "90 rotate\n");
        }
    }

    fprintf(arq, "\nstroke");

    fclose(arq);

    return 0;
}

/* --------------------------------------- */
/* ----------------FUNÇÕES---------------- */
/* --------------------------------------- */

void Koch(int ordem, FILE *arq, int *fim, double len)
{
    int i;

    /* 1 linha de Koch */
    if (*fim == 1)
    {
        fprintf(arq, "\n%.3lf 0\n", len);
        fprintf(arq, "2 1 roll dup dup dup 5 -1 roll dup dup dup 7 1 roll 5 1 roll 3 1 roll\n");
        fprintf(arq, "rlineto -60 rotate rlineto 120 rotate rlineto -60 rotate rlineto\n");
    }

    /* Construção das diversas linhas */
    for (i = 0; i < 4 && *fim != 0; i++)
    {
        if (i == 1)
            fprintf(arq, "-60 rotate ");
        if (i == 2)
            fprintf(arq, "120 rotate ");
        if (i == 3)
            fprintf(arq, "-60 rotate ");
        if (*fim != 1)
        {
            *fim -= 1;
            Koch(ordem, arq, &*fim, len);
        }
        if (i == 3)
            *fim += 1;
    }
}

void Arvore(int ordem, FILE *arq, double len, double centroX, double centroY)
{
    double finalEsq, finalDir, topoY, baseY;

    /* Coordenadas */
    finalEsq = centroX - (len / 2.0);
    finalDir = centroX + (len / 2.0);
    topoY = centroY + (len / 2.0);
    baseY = centroY - (len / 2.0);

    /* Uma árvore */
    fprintf(arq, "%.3lf %.3lf moveto %.3lf %.3lf lineto\n", finalEsq, baseY, finalEsq, topoY);
    fprintf(arq, "%.3lf %.3lf moveto %.3lf %.3lf lineto\n", finalEsq, centroY, finalDir, centroY);
    fprintf(arq, "%.3lf %.3lf moveto %.3lf %.3lf lineto\n", finalDir, baseY, finalDir, topoY);

    /* Ramificações */
    if (ordem > 0)
    {
        Arvore(ordem-1, arq, len / 2, finalEsq, topoY);
        Arvore(ordem-1, arq, len / 2, finalEsq, baseY);
        Arvore(ordem-1, arq, len / 2, finalDir, topoY);
        Arvore(ordem-1, arq, len / 2, finalDir, baseY);
    }
}

void MeuFrac(int ordem, FILE *arq, int *fim, double len)
{
    int i;

    /* 1 linha de MeuFrac */
    if (*fim == 1)
    {
        fprintf(arq, "%.3lf 0\n", len);
        fprintf(arq, "2 1 roll dup dup dup dup 7 -1 roll dup dup dup dup 9 1 roll 7 1 roll 5 1 roll 3 1 roll\n");
        fprintf(arq, "rlineto -90 rotate rlineto 90 rotate rlineto 90 rotate rlineto -90 rotate rlineto\n");
    }

    /* Construção das diversas linhas */
    for (i = 0; i < 5 && *fim != 0; i++)
    {
        if (i == 1)
            fprintf(arq, "-90 rotate ");
        if (i == 2)
            fprintf(arq, "90 rotate ");
        if (i == 3)
            fprintf(arq, "90 rotate ");
        if (i == 4)
            fprintf(arq, "-90 rotate ");
        if (*fim != 1)
        {
            *fim -= 1;
            MeuFrac(ordem, arq, &*fim, len);
        }
        if (i == 4)
            *fim += 1;
    }
}

FILE *open(char nomearq[FNMAX])
{
    scanf("%199s", nomearq);
    return fopen(nomearq, "w");
}

void close(FILE *arq)
{
    fclose(arq);
}