/* Considere uma sequência de elementos entre {, }, [, ], ( e ). Dizemos que uma tal sequência é bem formada se

ela é vazia ou 
ela é {S}R ou [S]R ou (S)R, onde S e R são sequências bem formadas.

Escreva uma função que recebe como parâmetros um inteiro n e string com uma sequência de n elementos entre {, }, [, ], ( e ), e devolve 1 se tal sequência é bem formada, 0 caso contrário.

Exemplos:{[()[]]()}({}) é bem formada, enquanto que {[}], {()}[(), (}{) e {()}] não são bemformadas.

Reescreva a sua função acima para que ela use a biblioteca "stack.h" vista em aula.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

#define MAX 30

int bemFormada(char *expr)
{
    int i;

    /* Se o número for impar, ja indica má formação */
    if (strlen(expr)%2 != 0)
        return 0;

    stackInit(strlen(expr));

    for (i = 0; i < strlen(expr); i++)
    {
        switch (expr[i])
        {
        case '(':
            stackPush(expr[i]);
            break;
        case '{':
            stackPush(expr[i]);
            break;
        case '[':
            stackPush(expr[i]);
            break;
        case ')':
            /* Se a stack está vazia ou topo não é o complementar, certamente é mal formado */
            if (stackEmpty() == 0 && stackTop() == '(')
                stackPop();
            else
                return 0;
            break;
        case '}':
            if (stackEmpty() == 0 && stackTop() == '{')
                stackPop();
            else
                return 0;
            break;
        case ']':
            if (stackEmpty() == 0 && stackTop() == '[')
                stackPop();
            else
                return 0;
            break;
        default:
            break;
        }
    }

    if (stackEmpty())
    {
        stackFree();
        return 1;
    }
    stackFree();
    return 0;
}

int main()
{
    char texto[MAX];
    int i;

    printf("Considere uma sequencia de elementos entre {, }, [, ], ( e ).\n");
    printf("Dizemos que uma tal sequencia e bem formada se\n");
    printf("    - ela e vazia ou\n");
    printf("    - ela e {S}R ou [S]R ou (S)R, onde S e R sao sequencias bem formadas.\n");
    printf("\nO programa devolve 1 se a sequencia e bem formada, 0 caso contrario.\n");

    do
    {
        for (i = 0; i < MAX; i++)
            texto[i] = 0;
        printf("\nSequencia: ");
        scanf("%29s", texto);
        printf("Resultado: %d\n", bemFormada(texto));
    } while (texto[0] != '0');
    return 0;
}