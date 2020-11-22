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
    Meu labirinto possui moldura
    Usei uma FILA SEM lista ligada, somente com matriz para guardar as posições
    
    */

/* PROTÓTIPOS */

void hebert(char **lab, int **cen, int qcen, int *pos, int m, int n);
int acharCenoura(char **lab, int *pos, int **cen, int qcen, int m, int n);
void menu();

char **criaMatriz(int m, int n);
void leMatriz(FILE *arq, int m, int n, char **res);
void printMatriz(char **a, int m, int n);
void freeMatrizChar(char **a, int m);
void freeMatrizInt(int **a, int m);

void cleanLine();
void readLine(char a[]);
static void *mallocSafe(unsigned int n);

void addFila(int **fila, int x, int y, int *ini);
void remFila(int **fila, int *x, int *y, int *fim);

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

        if (lab != NULL)
        {
            printf("\nDigite a posicao inicial do Herbert: ");
            scanf("%d %d", &pos[0], &pos[1]);

            hebert(lab, cen, qcen, pos, m, n);
        }
    }

    return 0;
}

/* --------------------------------- */

/* FUNÇÕES */

/*  Executa o procedimento de achar a cenoura mais próxima do Hebert no labirinto e imprimi-lô;
    Recebe uma matriz do labirinto, uma matriz com a posição das cenouras, a posição do hebert e o tamanho das matrizes */
void hebert(char **lab, int **cen, int qcen, int *pos, int m, int n)
{
    int i, j;
    int passos;
    char **labFim;

    /* Cria matrizes */
    labFim = criaMatriz(m, n);

    /* Copia matriz de labirinto */
    for (i = 0; i < (m + 2); i++)
        for (j = 0; j < (n + 2); j++)
            labFim[i][j] = lab[i][j];

    /* Teste se o coelho não ta em cima da cenoura */
    passos = 1;
    for (i = 0; i < qcen && passos != 0; i++)
    {
        if (pos[0] == cen[i][0] && pos[1] == cen[i][1])
            passos = 0;
    }

    if (passos)
        passos = acharCenoura(labFim, pos, cen, qcen, m, n);

    /* Cenouras */
    for (i = 0; i < qcen; i++)
        labFim[cen[i][0]][cen[i][1]] = 'C';

    /* Hebert */
    labFim[pos[0]][pos[1]] = 'H';

    if (passos != m * n)
        printf("\nO Herbert achou uma cenoura em %d passos!\n\n", passos);
    else
        printf("\nO Herbert nao achou nenhuma cenoura!!! :(\n\n");

    printMatriz(labFim, m, n);
    freeMatrizChar(labFim, m);
    printf("\n");
}

/*  Procura o o caminho com menor número de passos que leva até uma cenoura
    Recebe o labirinto com cenouras e um endereço para criar a matriz do local dos passos
    Devolve o número inteiro de passos */
int acharCenoura(char **lab, int *pos, int **cen, int qcen, int m, int n)
{
    int i, j;
    int ncen = 0, passos;

    /* Matriz de calculo */
    int **labCont;
    int p[2]; /* Posição de estudo */

    /* FILA */
    int **fila, ini = 0, fim = 0;

    /* Aloca fila */
    fila = mallocSafe((m * n) * sizeof(int *));
    for (i = 0; i < m * n; i++)
        fila[i] = mallocSafe(2 * sizeof(int));

    /* Aloca matriz de calculo */
    labCont = mallocSafe((m + 2) * sizeof(int *));
    for (i = 0; i < (m + 2); i++)
        labCont[i] = mallocSafe((n + 2) * sizeof(int));

    /* Cria Matriz de calculo */
    for (i = 0; i < (m + 2); i++)
        for (j = 0; j < (n + 2); j++)
        {
            if ((lab[i][j] - '0') == 0)
                labCont[i][j] = m * n;
            else
                labCont[i][j] = -1;
        }

    /* Posição do hebert */
    addFila(fila, pos[0], pos[1], &fim);
    labCont[pos[0]][pos[1]] = 0;

    /* Processa fila */
    while (ini != fim)
    {
        remFila(fila, &p[0], &p[1], &ini);

        /* Testa acima, abaixo, esquerda, direita */
        if (labCont[p[0] - 1][p[1]] > labCont[p[0]][p[1]] + 1 && labCont[p[0] - 1][p[1]] != -1)
        {
            labCont[p[0] - 1][p[1]] = labCont[p[0]][p[1]] + 1;
            addFila(fila, p[0] - 1, p[1], &fim);
        }
        if (labCont[p[0] + 1][p[1]] > labCont[p[0]][p[1]] + 1 && labCont[p[0] + 1][p[1]] != -1)
        {
            labCont[p[0] + 1][p[1]] = labCont[p[0]][p[1]] + 1;
            addFila(fila, p[0] + 1, p[1], &fim);
        }
        if (labCont[p[0]][p[1] - 1] > labCont[p[0]][p[1]] + 1 && labCont[p[0]][p[1] - 1] != -1)
        {
            labCont[p[0]][p[1] - 1] = labCont[p[0]][p[1]] + 1;
            addFila(fila, p[0], p[1] - 1, &fim);
        }
        if (labCont[p[0]][p[1] + 1] > labCont[p[0]][p[1]] + 1 && labCont[p[0]][p[1] + 1] != -1)
        {
            labCont[p[0]][p[1] + 1] = labCont[p[0]][p[1]] + 1;
            addFila(fila, p[0], p[1] + 1, &fim);
        }
    }

    /* Acha cenoura mais próxima */
    for (i = 0; i < qcen; i++)
    {
        if (labCont[cen[i][0]][cen[i][1]] < labCont[cen[ncen][0]][cen[ncen][1]] && labCont[cen[i][0]][cen[i][1]] != -1)
            ncen = i;
    }

    /* Registra número de passos */
    passos = labCont[cen[ncen][0]][cen[ncen][1]];

    /* Caso não for impossível, escreve na matriz os passos até a cenoura */
    if (passos != m * n)
    {
        p[0] = cen[ncen][0];
        p[1] = cen[ncen][1];

        while (labCont[p[0]][p[1]] != 0)
        {
            if (labCont[p[0] - 1][p[1]] == labCont[p[0]][p[1]] - 1)
            {
                lab[p[0] - 1][p[1]] = '*';
                p[0] = p[0] - 1;
            }
            else if (labCont[p[0] + 1][p[1]] == labCont[p[0]][p[1]] - 1)
            {
                lab[p[0] + 1][p[1]] = '*';
                p[0] = p[0] + 1;
            }
            else if (labCont[p[0]][p[1] - 1] == labCont[p[0]][p[1]] - 1)
            {
                lab[p[0]][p[1] - 1] = '*';
                p[1] = p[1] - 1;
            }
            else if (labCont[p[0]][p[1] + 1] == labCont[p[0]][p[1]] - 1)
            {
                lab[p[0]][p[1] + 1] = '*';
                p[1] = p[1] + 1;
            }
        }
    }

    /* Libera matrizes */
    freeMatrizInt(fila, m * n);
    freeMatrizInt(labCont, m + 2);

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
    res = mallocSafe((m + 2) * sizeof(char *));
    for (i = 0; i < (m + 2); i++)
        res[i] = mallocSafe((n + 2) * sizeof(char));

    return res;
}

/* Recebe arquivo e uma matriz, lê o arquivo e guarda na matriz com moldura */
void leMatriz(FILE *arq, int m, int n, char **res)
{
    int i, j;
    int num;
    /* Com moldura */
    for (i = 0; i < m + 2; i++)
        for (j = 0; j < n + 2; j++)
        {
            if (i == 0 || i == m + 1 || j == 0 || j == n + 1)
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
    for (i = 1; i < m + 1; i++)
    {
        for (j = 1; j < n + 1; j++)
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
        for (i = 0; i < (m + 2) && a[i] != NULL; i++)
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

/* --------------------------------- */

/* Adiciona item à fila */
void addFila(int **fila, int x, int y, int *fim)
{
    fila[*fim][0] = x;
    fila[*fim][1] = y;
    *fim += 1;
}

/* Remove um item da fila */
void remFila(int **fila, int *x, int *y, int *ini)
{
    *x = fila[*ini][0];
    *y = fila[*ini][1];
    *ini += 1;
}
