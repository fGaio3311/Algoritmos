#include <stdio.h>

int qnt (int n, int x, int V)
{
    int i = n;
    if (n!=0)
    {
        return qnt(i,x,V)
    }
    return 
}

int main()
{
    int n, V[50], x, i;

    printf("Digite n: ");
    scanf("%d",&n);
    printf("Digite o vetor: ");

    for (i=0; i < n; i++)
    {
        scanf("%d", &V[i]);
    }
    
    printf("%d", qnt(n,x,V));

    return 0;
}