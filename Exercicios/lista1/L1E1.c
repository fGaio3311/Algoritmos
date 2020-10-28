/* 
Escreva uma função recursiva com protótipo
int soma (int n, int v[]);
que recebe um inteiro n e um vetor v com n números inteiros, e devolve a soma dos n números no vetor v. */

#include <stdio.h>

/* Recebe um inteiro n e um vetor v com n números inteiros, e devolve a soma dos n números no vetor v */
int soma (int n, int v[]);

int main()
{
    int v[100], i, n;
    printf("Digite um numero: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }
    
    printf("%ld", soma(n,v));

    return 0;
}

int soma (int n, int v[])
{
    int sum=0;
    if (n == 0) return sum;
    return (v[n-1] + soma(n-1, v));
    
}