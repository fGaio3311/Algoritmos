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

  ep4.c

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma referência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:

  -
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 256 /* Tamanho do nome do arquivo */

/*  INFO
    Meu labirinto possui moldura */

/* PROTÓTIPOS */

void hebert(char **lab, int **cen, int qcen, int *pos, int m, int n);
int acharCenoura(char **lab, char **posPassos, int *pos);
void menu();

char **criaMatriz(int m, int n);
void leMatriz(FILE *arq, int m, int n, char **res);
void printMatriz(char **a, int m, int n);
void freeMatrizChar(char **a, int m);
void freeMatrizInt(int **a, int m);

void cleanLine();
void readLine(char a[]);
static void *mallocSafe(unsigned int n);

/* --------------------------------- */

/* MAIN */
int main()
{
    int i, j;
    int op, m, n, qcen;
    char nome[MAX];
    char **lab = NULL;
    int pos[2], **cen = NULL;
    FILE *arq;

    printf("*************************\n");
    printf("Carrotsvile search engine\n");
    printf("*************************\n");

    while (1)
    {
        menu();
        scanf("%d", &op);
        cleanLine();

        switch (op)
        {
        case 0:
            printf("\nDigite o nome do arquivo com o labirinto: ");
            readLine(nome);

            arq = fopen(nome, "r");
            if (arq == NULL)
                break;

            /* Libera matriz antiga */
            freeMatrizChar(lab, m);
            freeMatrizInt(cen, qcen);

            /* Matriz labirinto */
            fscanf(arq, "%d %d", &m, &n);
            lab = criaMatriz(m, n);
            leMatriz(arq, m, n, lab);

            /* Matriz cenouras */
            fscanf(arq, "%d", &qcen);
            cen = mallocSafe(qcen * sizeof(int *));
            for (i = 0; i < qcen; i++)
                cen[i] = mallocSafe(2 * sizeof(int));
            for (i = 0; i < qcen; i++)
                for (j = 0; j < 2; j++)
                    fscanf(arq, "%d", &cen[i][j]);

            fclose(arq);

            printf("\nLabirinto:\n");
            printMatriz(lab, m, n);
            break;

        case 2:
            printf("\nTchau, Herbert!");
            freeMatrizChar(lab, m);
            freeMatrizInt(cen, qcen);
            return 1;
            break;

        default:
            break;
        }

        printf("\nDigite a posicao inicial do Herbert: ");
        scanf("%d %d", &pos[0], &pos[1]);

        hebert(lab, cen, qcen, pos, m, n);
    }

    return 0;
}

/* --------------------------------- */

/* FUNÇÕES */

/*  Executa o procedimento de achar a cenoura mais próxima do Hebert no labirinto;
    Recebe uma matriz do labirinto, uma matriz com a posição das cenouras, a posição do hebert e o tamanho das matrizes */
void hebert(char **lab, int **cen, int qcen, int *pos, int m, int n)
{
    int i, j;
    int passos, **posPassos = NULL;
    char **labFim;

    /* Cria matrizes */
    labFim = criaMatriz(m, n);

    /* Copia matriz de labirinto */
    for (i = 0; i < (m+2); i++)
        for (j = 0; j < (n+2); j++)
            labFim[i][j] = lab[i][j];

    /* Hebert */
    labFim[pos[0]][pos[1]] = 'H';

    passos = acharCenoura(labFim, posPassos, pos); /* TODO: verificar se não precisa de mais termos */

    /* Passos */
    for (i = 0; i < passos; i++)
        labFim[posPassos[i][0]][posPassos[i][1]] = '*';

    /* Cenouras */
    for (i = 0; i < qcen; i++)
        labFim[cen[i][0]][cen[i][1]] = 'C';

    if (passos != 0)
        printf("\nO Herbert achou uma cenoura em %d passos!\n\n", passos);
    else
        printf("\nO Herbert nao achou nenhuma cenoura!!! :(\n\n");

    printMatriz(labFim, m, n);
    freeMatrizInt(posPassos, passos);
    freeMatrizChar(labFim, m);
    printf("\n");
}

/*  Procura o o caminho com menor número de passos que leva até uma cenoura
    Recebe o labirinto com cenouras e um endereço para criar a matriz do local dos passos
    Devolve o número inteiro de passos */
int acharCenoura(char **lab, char **posPassos, int *pos)
{
    int passos;
    int i;

    if (passos > 0)
    {
        posPassos = mallocSafe(passos * sizeof(int *));
        for (i = 0; i < passos; i++)
            posPassos[i] = mallocSafe(2 * sizeof(int));
    }

    return passos;
}

/* Menu de opções */
void menu()
{
    printf("\n0: carregar um novo labirinto e posicao inicial do Herbert\n");
    printf("1: dar nova posicao inicial do Herbert no mesmo labirinto\n");
    printf("2: sair do programa\n\n");
    printf("Digite a opcao desejada: ");
}

/* --------------------------------- */

/* Cria e lê uma matriz de tamanho m x n */
char **criaMatriz(int m, int n)
{
    char **res;
    int i;

    /* Aloca matriz */
    res = mallocSafe((m+2) * sizeof(char *));
    for (i = 0; i < (m+2); i++)
        res[i] = mallocSafe((n+2) * sizeof(char));

    return res;
}

/* Recebe arquivo e uma matriz, lê o arquivo e guarda na matriz com moldura */
void leMatriz(FILE *arq, int m, int n, char **res)
{
    int i, j;
    int num;
    /* Com moldura */
    for (i = 0; i < m+2; i++)
        for (j = 0; j < n+2; j++)
        {
            if(i == 0 || i == m+1 || j == 0 || j == n+1)
                res[i][j] = '1';
            else
            {
                fscanf(arq, "%d", &num);
                res[i][j] = num + '0';
            }
        }
}

/* Imprime Matriz */
void printMatriz(char **a, int m, int n)
{
    int i, j;
    /* Matriz com moldura */
    for (i = 1; i < m+1; i++)
    {
        for (j = 1; j < n+1; j++)
            printf("%c ", a[i][j]);
        printf("\n");
    }
}

/* Libera Matriz de char */
void freeMatrizChar(char **a, int m)
{
    int i;
    if (a != NULL)
    {
        for (i = 0; i < (m+2) && a[i] != NULL; i++)
        {
            free(a[i]); /* libera a linha i */
            a[i] = NULL;
        }
        free(a);
        a = NULL;
    }
}

/* Libera Matriz de int */
void freeMatrizInt(int **a, int m)
{
    int i;
    if (a != NULL)
    {
        for (i = 0; i < m && a[i] != NULL; i++)
        {
            free(a[i]); /* libera a linha i */
            a[i] = NULL;
        }
        free(a);
        a = NULL;
    }
}

/* --------------------------------- */

/* Limpa o resto da linha*/
void cleanLine()
{
    char a = 0;
    while (a != '\n')
        scanf("%c", &a);
}

/* Le uma linha do terminal e devolve-a em vec[]; */
void readLine(char vec[])
{
    int i = 0;
    do
        scanf("%c", &vec[i++]);
    while (vec[i - 1] != '\n' && vec[i - 1] != EOF);
    vec[--i] = 0;
}

/* MallocSafe para allocar memória */
static void *mallocSafe(unsigned int n)
{
    void *p;

    p = malloc(n);
    if (p == NULL)
        exit(-1);
    return p;
}