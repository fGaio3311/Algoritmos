/* Considere uma sequência de elementos entre {, }, [, ], ( e ). Dizemos que uma tal sequência é bem formada se

ela é vazia ou 
ela é {S}R ou [S]R ou (S)R, onde S e R são sequências bem formadas.

Escreva uma função que recebe como parâmetros um inteiro n e string com uma sequência de n elementos entre {, }, [, ], ( e ), e devolve 1 se tal sequência é bem formada, 0 caso contrário.

Exemplos:{[()[]]()}({}) é bem formada, enquanto que {[}], {()}[(), (}{) e {()}] não são bemformadas.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 30

void *mallocSafe(int nbytes)
{

    void *ptr;

    ptr = malloc(nbytes);

    if (ptr == NULL)
    {
        printf("Socorro! malloc devolveu NULL!\n");
        exit(EXIT_FAILURE);
    }

    return ptr;
}

int seq(int n, char str[])
{
    char *pilha;
    int T;
    char itemT;

    /* Não otimizado */
    int i, pass1, pass2, pass3;

    pass1 = pass2 = pass3 = 0;

    pilha = mallocSafe(n * sizeof(char));
    T = 0;

    for (i = 0; i < n; i++)
    {
        switch (str[i])
        {
        case '(':
            pilha[T++] = str[i];
            pass1++;
            break;
        case '{':
            pilha[T++] = str[i];
            pass2++;
            break;
        case '[':
            pilha[T++] = str[i];
            pass3++;
            break;
        case ')':
            if ((itemT = pilha[T - 1]) == '(')
                T--;
            pass1--;
            break;
        case '}':
            if ((itemT = pilha[T - 1]) == '{')
                T--;
            pass2--;
            break;
        case ']':
            if ((itemT = pilha[T - 1]) == '[')
                T--;
            pass3--;
            break;
        default:
            break;
        }
    }
    if (T == 0 && pass1 == 0 && pass2 == 0 && pass3 == 0)
        return 1;
    return 0;
}

int main()
{
    char texto[MAX];
    int i;

    do
    {
        for (i = 0; i < MAX; i++)
        {
            texto[i] = 0;
        }
        scanf("%29s", texto);
        printf("%d\n", seq(sizeof(texto), texto));
    } while (texto[0] != '0');
    return 0;
}