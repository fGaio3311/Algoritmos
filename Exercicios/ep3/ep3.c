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

  - StackS de:

       https://www.ime.usp.br/~cris/mac0122/programas/polonesa/

  - infixa para posfixa de:

       http://www.vision.ime.usp.br/~pmiranda/mac122_2s14/aulas/aula13/aula13.html


 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "polinomios.h"

#define maxLeia 200 /* Numero máximo de caracteres lidos */
#define maxPol 26

/* Typedef */
typedef void *Stack;
typedef struct stack *TStack;
typedef struct stacknode *Link;

/* Células */
struct stacknode
{
    char conteudo;
    Link prox;
};
struct stack
{
    Link topo;
};

/* Protótipos */
void printMenu();
void convertPostfix(char op[], Stack posfixa);
int prioridade(char a, char b);
polinomio calculadora(Stack pilha, polinomio pol[], char operation);
polinomio comparaELibera(polinomio pol[], polinomio j);

/* StackS */
Stack stackInit(int);
int stackEmpty(Stack);
void stackPush(Stack, char);
char stackPop(Stack);
char stackTop(Stack);
void stackFree(Stack);
static void *mallocSafe1(unsigned int n);

/* MAIN */
int main()
{

    int i, num;
    char op[maxLeia];
    polinomio var[maxPol], temp;
    Stack opPosf;

    /* Cria polinomios do vetor var */
    for (i = 0; i < maxPol; i++)
        var[i] = cria();

    printf("*************************\n");
    printf("Calculadora de polinomios\n");
    printf("*************************\n");

    while (1)
    {
        printMenu();
        for (i = 0; i < 2; i++)
        {
            scanf("%c", &op[i]);
            if (op[i] == ' ' || op[i] == '\n')
                i--;
        }
        op[i] = 0;

        /* quit */
        if (!strcmp(op, "qu"))
            break;

        /* Verifica se é uma opção válida e lê até o final da linha*/
        if (op[0] < 'a' || op[0] > 'z' || (op[1] != '?' && op[1] != ':' && op[1] != '='))
        {
            printf("Opcao invalida\n");
            while (op[0] != '\n') /* Limpa o resto da linha */
                scanf("%c", &op[0]);
            op[0] = 0;
        }
        else
        {
            num = op[0] - 'a';

            /* Switch entre ? : = */
            switch (op[1])
            {
            case '?': /* Imprime polinomio */
                break;

            case ':': /* Atribui expressão ao polinomio */
                temp = var[num];
                var[num] = leia();
                libera(temp);
                break;

            case '=': /* Faz operação com o polinomio */

                /* Le o resto */
                for (i = 2; op[i - 1] != '\n' && op[i - 1] != EOF && i < maxLeia; i++)
                {
                    scanf("%c", &op[i]);
                    if (op[i] == ' ')
                        i--;
                }
                i--;       /* i guarda o tamanho da string */
                op[i] = 0; /* Finaliza a string retirando o \n dela */

                if (i == 3 && op[2] >= 'a' && op[2] <= 'z')
                {
                    temp = var[num];
                    var[num] = copia(var[op[2] - 'a']);
                    libera(temp);
                }
                else
                {
                    /* Cria pilha e converte para posfixa */
                    opPosf = stackInit(strlen(op) - 2);
                    convertPostfix(op, opPosf);

                    /* Faz operações e libera pilhas e polinomios temporários */
                    temp = var[num];
                    var[num] = calculadora(opPosf, var, stackPop(opPosf));
                    if (!stackEmpty(opPosf) || var[num] == NULL)
                    {
                        printf("Operacao nao permitida ou expressao mal escrita\n");
                        var[num] = temp;
                    }
                    else
                        libera(temp);
                    stackFree(opPosf);
                }
                break;

            default:
                break;
            }
            impr(op[0], var[num]);
        }
    }
    printf("\nTchau!");

    /* Libera polinomios do vetor var */
    for (i = 0; i < maxPol; i++)
        libera(var[i]);

    return 0;
}

/* FUNÇÕES AUXILIARES */

/* Imprime menu */
void printMenu()
{
    printf("\n");
    printf("Digite uma expressao ou quit para sair do programa:\n");
    printf("> ");
}

/* Converte expressões infixas para posfixas
Recebe uma expressão num vetor de caracteres
Devolve ela numa pilha */
void convertPostfix(char op[], Stack posfixa)
{
    int i;
    char a, b;
    Stack temp;

    temp = stackInit(strlen(op) - 2);
    stackPush(temp, '(');

    i = 2;

    do
    {
        a = op[i];
        i++;
        if (a >= 'a' && a <= 'z')
            stackPush(posfixa, a);
        else if (a == '(')
            stackPush(temp, '(');
        else if (a == ')' || a == 0)
        {
            do
            {
                b = stackPop(temp);
                if (b != '(')
                    stackPush(posfixa, b);
            } while (b != '(');
        }
        else if (a == '+' || a == '-' || a == '*' || a == '/' || a == '%' || a == '~')
        {
            while (1)
            {
                b = stackPop(temp);
                if (prioridade(a, b))
                {
                    stackPush(temp, b);
                    stackPush(temp, a);
                    break;
                }
                else
                    stackPush(posfixa, b);
            }
        }
    } while (a != 0);
    stackFree(temp);
}

/* Verifica a prioridade dos operandos ~ / % * + - 
Recebe dois caracteres
Devolve 1 se a prioridade de a for maior que a de b  */
int prioridade(char a, char b)
{
    int pa = 0, pb = 0;

    if (a == '~')
        pa = 4;
    else if (a == '*' || a == '/' || a == '%')
        pa = 2;
    else if (a == '+' || a == '-')
        pa = 1;
    else if (a == '(')
        pa = 4;

    if (b == '~')
        pb = 3;
    else if (b == '*' || b == '/' || b == '%')
        pb = 2;
    else if (b == '+' || b == '-')
        pb = 1;
    else if (b == '(')
        pb = 0;

    return (pa > pb);
}

/* Faz operações de forma recursiva entre polinomios usando a biblioteca polinomios.h;
uma pilha, um vetor de polinomios e um char que define a operação em curso;
Devolve o polinomio resultante das operações*/
polinomio calculadora(Stack pilha, polinomio pol[], char operation)
{
    polinomio res = NULL, i, j;
    char a, b;

    if (stackEmpty(pilha))
        return NULL;

    a = stackPop(pilha);

    /* Se o item a não for um polinomio e sim uma operação, calcula ela recursivamente */
    if (a < 'a' || a > 'z')
        j = calculadora(pilha, pol, a);
    else
        j = pol[a - 'a'];

    /* Operação nega */
    if (operation == '~')
    {
        res = nega(j);
        comparaELibera(pol, j);
        return res;
    }

    if (stackEmpty(pilha))
        return comparaELibera(pol, j);

    b = stackPop(pilha);

    /* Se o item b não for um polinomio e sim uma operação, calcula ela recursivamente */
    if (b < 'a' || b > 'z')
        i = calculadora(pilha, pol, b);
    else
        i = pol[b - 'a'];

    if (i == NULL || j == NULL)
    {
        comparaELibera(pol, i);
        return comparaELibera(pol, j);
    }

    /* Faz operações */
    switch (operation)
    {
    case '+':
        res = soma(i, j);
        break;
    case '-':
        res = subt(i, j);
        break;
    case '*':
        res = mult(i, j);
        break;
    case '/':
        res = quoc(i, j);
        break;
    case '%':
        res = rest(i, j);
        break;
    default:
        break;
    }

    /* Libera polinomios desde que eles não sejam os polinomios fixados de a-z */
    comparaELibera(pol, j);
    comparaELibera(pol, i);

    return res;
}

/* Compara se o polinomio j é algum dos polinomios prefixados e caso não for, os libera
Retorna NULL para fins de utilização diretamente no return */
polinomio comparaELibera(polinomio pol[], polinomio j)
{
    int i;
    for (i = 0; i < maxPol && pol[i] != j; i++)
        ;
    if (i == maxPol)
        libera(j);
    return NULL;
}

/* ----StackS---- */

/* inicia a pilha */
Stack stackInit(int n)
{
    TStack s = (TStack)mallocSafe1(sizeof *s);
    s->topo = NULL;
    return (Stack)s;
}

/* Retorna 1 se a pilha está vazia */
int stackEmpty(Stack s)
{
    return ((TStack)s)->topo == NULL;
}

/* Adiciona um item na pilha */
void stackPush(Stack s, char conteudo)
{
    Link p = (Link)mallocSafe1(sizeof *p);
    p->conteudo = conteudo;
    p->prox = ((TStack)s)->topo;
    ((TStack)s)->topo = p;
}

/* Tira um item da pilha e retorna esse item */
char stackPop(Stack s)
{
    Link p = ((TStack)s)->topo;
    char conteudo;

    if (p == NULL)
        exit(-1);
    conteudo = p->conteudo;
    ((TStack)s)->topo = p->prox;
    free(p);
    return conteudo;
}

/* Retorna um item da pilha sem o retirar */
char stackTop(Stack s)
{
    if (((TStack)s)->topo == NULL)
        exit(-1);
    return ((TStack)s)->topo->conteudo;
}

/* Libera uma pilha */
void stackFree(Stack s)
{
    while (((TStack)s)->topo != NULL)
    {
        Link p = ((TStack)s)->topo;
        ((TStack)s)->topo = ((TStack)s)->topo->prox;
        free(p);
    }
    free(s);
}

/* Aloca uma posição na pilha */
static void *mallocSafe1(unsigned int n)
{
    void *p;

    p = malloc(n);
    if (p == NULL)
        exit(-1);
    return p;
}