/* Escreva uma função recursiva com protótipo
int conta (int n, int v[], int x);
que recebe um inteiro n, um vetor v com n números inteiros e um inteiro x, e devolve o número de vezes que x ocorre no vetor v.
 */

int conta(int n, int v[], int x);

#include <stdio.h>

int main()
{
    int n, v[100], x, i;

    printf("Digite um numero n: ");
    scanf("%d", &n);

    printf("Digite um numero x: ");
    scanf("%d", &x);

    for (i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    printf("O numero %d aparece %d vezes", x, conta(n, v, x));
    return 0;
}

int conta(int n, int v[], int x)
{
    if (n == 0)
        return 0;
    if (v[n-1] != x)
        return 0 + conta(n - 1, v, x);
    return 1 + conta(n - 1, v, x);
}