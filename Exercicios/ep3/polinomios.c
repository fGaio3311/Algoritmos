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
    - função BuscaEInsere adaptada de:
        Paulo Feofiloff, Algoritmos em linguagem C
    - estrutura da divisão polinomial de:
        https://en.wikipedia.org/wiki/Polynomial_long_division

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdio.h>
#include <stdlib.h>

#include "polinomios.h"

#define IDquoc 1
#define IDrest 0

/* declaracao da celula das listas encadeadas */
struct celula
{
    float coef;
    int expo;
    struct celula *prox;
};

typedef struct celula cel;

/* INFO POLINOMIO
*  As listas encadeadas POSSUEM cabeça
*  A lista é ordenada em ordem DECRESCENTE dos expoentes
*/

/* prototipo de eventuais funcoes auxiliares */

void *mallocSafe(size_t nbytes);
void BuscaEInsere(float numCoef, int numExpo, polinomio p);
polinomio divisao(polinomio p, polinomio q, int id);

/* implementacao das funcoes da biblioteca polinomios.h */

/* Cria um polinomio com cabeça e endereço da próxima = NULL */
polinomio cria()
{
    cel *poliCel;

    poliCel = mallocSafe(sizeof(cel));
    poliCel->prox = NULL;

    return poliCel;
}

polinomio leia()
{
    polinomio resultado;
    float numCoef;
    int numExpo;

    resultado = cria();

    do
    {
        scanf("%f", &numCoef);
        if (numCoef != 0.0)
        {
            scanf("%d", &numExpo);
            BuscaEInsere(numCoef, numExpo, resultado);
        }
    } while (numCoef != 0.0);

    return resultado;
}

polinomio copia(polinomio p)
{
    polinomio resCopia = cria();
    cel *ori;

    for (ori = p, ori = ori->prox; ori != NULL; ori = ori->prox)
        BuscaEInsere(ori->coef, ori->expo, resCopia);

    return resCopia;
}

void impr(char c, polinomio p)
{
    cel *ori = p;

    printf("%c(x) = ", c);

    if (ori->prox == NULL)
        printf("0.00");
    else
        for (ori = ori->prox; ori != NULL; ori = ori->prox)
        {
            printf("%.2f ", ori->coef);
            if (ori->expo != 0)
                printf("x^%d", ori->expo);
            if (ori->prox != NULL)
                printf(" + ");
        }
    printf("\n");
}

/* Soma o polinomio monômio a monômio não inserindo células que zeram */
polinomio soma(polinomio p, polinomio q)
{
    polinomio resSoma = cria();
    cel *oriA, *oriB;

    for (oriA = p, oriA = oriA->prox; oriA != NULL; oriA = oriA->prox)
        BuscaEInsere(oriA->coef, oriA->expo, resSoma);
    for (oriB = q, oriB = oriB->prox; oriB != NULL; oriB = oriB->prox)
        BuscaEInsere(oriB->coef, oriB->expo, resSoma);

    return resSoma;
}

/* Subtrai o polinomio monômio a monômio não inserindo células que zeram */
polinomio subt(polinomio p, polinomio q)
{
    polinomio resSubt = cria();
    cel *oriA, *oriB;

    for (oriA = p, oriA = oriA->prox; oriA != NULL; oriA = oriA->prox)
        BuscaEInsere(oriA->coef, oriA->expo, resSubt);
    for (oriB = q, oriB = oriB->prox; oriB != NULL; oriB = oriB->prox)
        BuscaEInsere(-oriB->coef, oriB->expo, resSubt);

    return resSubt;
}

/* Cria um polinomio com os coeficientes opostos do polinomio de entrada */
polinomio nega(polinomio p)
{
    polinomio resNega = cria();
    cel *ori;

    for (ori = p, ori = ori->prox; ori != NULL; ori = ori->prox)
        BuscaEInsere(-ori->coef, ori->expo, resNega);

    return resNega;
}

/* Multiplica o polinomio monômio a monômio */
polinomio mult(polinomio p, polinomio q)
{
    polinomio resMult = cria();
    cel *oriA, *oriB;

    for (oriA = p, oriA = oriA->prox; oriA != NULL; oriA = oriA->prox)
        for (oriB = q, oriB = oriB->prox; oriB != NULL; oriB = oriB->prox)
            BuscaEInsere(oriA->coef * oriB->coef, oriA->expo + oriB->expo, resMult);

    return resMult;
}

polinomio quoc(polinomio p, polinomio q)
{
    return divisao(p, q, IDquoc);
}

polinomio rest(polinomio p, polinomio q)
{
    return divisao(p, q, IDrest);
}

/* Libera cada célula de um polinômio */
void libera(polinomio p)
{
    cel *proxima, *atual;

    proxima = p;
    atual = p;

    while (proxima != NULL)
    {
        if (atual->prox != NULL)
            proxima = atual->prox;
        else
            proxima = NULL;
        free(atual);
        if (proxima != NULL)
            atual = proxima;
    }
}

/* Implementacao das funcoes auxiliares */

/* Assegura que há espaço para alocação dinâmica */
void *mallocSafe(size_t nbytes)
{
    void *ptr;
    ptr = malloc(nbytes);
    if (ptr == NULL)
    {
        printf("MallocNULL\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/* Busca e ordena em ordem decrescente pelos expoentes:
*  Se expo ==, soma os coef, se !=, cria uma célula e adiciona coef e expo;
*  Se essa soma der 0, apaga a célula
*/
void BuscaEInsere(float numCoef, int numExpo, polinomio p)
{
    cel *endAnt, *endPos, *novo, *poli = p;

    endAnt = poli;
    for (endPos = poli->prox; endPos != NULL && endPos->expo > numExpo; endPos = endPos->prox)
        endAnt = endPos;
    
    if (endPos != NULL && endPos->expo == numExpo)
    {
        if (endPos->coef == -numCoef)
        {
            endAnt->prox = endPos->prox;
            free(endPos);
        }
        else
            endPos->coef += numCoef;
    }
    else if (numCoef != 0.0)
    {
        novo = mallocSafe(sizeof(cel));
        novo->coef = numCoef;
        novo->expo = numExpo;
        novo->prox = endPos;
        endAnt->prox = novo;
    }
}

/* Realiza a divisão polinomial de A/B => A = B*quociente + resto
*  Devolve o polinomio quociente ou resto dependendo do id IDquoc ou IDrest
*/
polinomio divisao(polinomio p, polinomio q, int id)
{
    polinomio resQuoc = NULL, quocTemp, meio1, resResto = NULL, meio2;
    cel *oriB = q, *resto, *quoc;

    oriB = oriB->prox;

    /* Divisão por 0 */
    if (oriB == NULL)
        return cria();

    quocTemp = cria();
    quoc = quocTemp;
    quoc->prox = mallocSafe(sizeof(cel));
    quoc = quoc->prox;
    quoc->prox = NULL;

    meio2 = resto = resResto = copia(p);

    if (id == IDquoc)
        resQuoc = cria();

    /* Os polinomios intermediários servem para ser liberados pós operação */
    for (resto = resto->prox; (oriB != NULL) && (resto != NULL) && (resto->coef != 0.0) && (resto->expo >= oriB->expo); resto = resto->prox)
    {
        quoc->coef = resto->coef / (oriB->coef);
        quoc->expo = resto->expo - oriB->expo;
        if (id == IDquoc)
            BuscaEInsere(quoc->coef, quoc->expo, resQuoc);
        meio1 = mult(quocTemp, q);
        resResto = subt(meio2, meio1);
        libera(meio2);
        libera(meio1);
        meio2 = resto = resResto;
    }
    libera(quocTemp);

    if (id == IDrest)
        return resResto;

    libera(resResto);
    return resQuoc;
}