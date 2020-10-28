/* LISTA 1 - EXERCÍCIO 3
#define FALSE 0
#define TRUE  1
Escreva uma função recursiva com protótipo
int crescente (int n, int v[]);
que recebe um inteiro n e um vetor v com n números inteiros, e devolve TRUE se o vetor v está em ordem crescente e FALSE caso contrário.

 */

#include <stdio.h>

#define FALSE 0
#define TRUE 1

/* Recebe um inteiro n e um vetor v com n números inteiros, e devolve TRUE se o vetor v está em ordem crescente e FALSE caso contrário. */
int crescente(int n, int v[]);

int main()
{
    int v[10], n, i;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }

    i = crescente(n,v);
    printf("%d", i);

    return 0;
}

int crescente(int n, int v[])
{
    if (n == 1)
        return TRUE;
    if (v[n - 1] < v[n - 2])
        return FALSE;
    return crescente(n - 1, v);
}