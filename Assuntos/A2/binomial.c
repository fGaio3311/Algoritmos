#include <stdio.h>

long binomialR2(int n, int k) 
{
    if (k == 1) return n;
    return binomialR2(n-1, k-1) * n / k;
}


int main()
{
    printf("%ld",binomialR2(30,10));
    return 0;
}