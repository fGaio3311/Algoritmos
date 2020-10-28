/* Escreva uma função recursiva com protótipo
void remove (int *n, int v[], int x);
que recebe um inteiro *n, um vetor v com *n números inteiros e um inteiro x, e remove todas as cópias de x do vetor v, ajustando o valor de *n de acordo.
*/

#include <stdio.h>
#define MAX 100

void remove(int *n, int v[], int x);

int main()
{
    int n, v[MAX], x, i;

    printf("Digite um numero n: ");
    scanf("%d", &n);

    printf("Digite um numero x: ");
    scanf("%d", &x);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }

    remove(&n, v, x);

    for (i = 0; i < n; i++)
    {
        printf("%d", v[i]);
    }

    return 0;
}

void remove(int *n, int v[], int x)
{
    if (v[*n-1]==x)
    {
        v[*n-1]= v[*n-2]
    }
}