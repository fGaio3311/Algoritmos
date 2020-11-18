#include <stdlib.h>
#include <stdio.h>

void *mallocSafe (int nbytes) {

    void *ptr;

    ptr = malloc(nbytes);

    if (ptr == NULL) {
        printf("Socorro! malloc devolveu NULL!\n");
        exit(EXIT_FAILURE);
    }

    return ptr;
}


int main()
{
    int *v; int i, n;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    v = mallocSafe(n*sizeof(int));

    for (i = 0; i < n; i++)
        *(v+i) = i*2; /* v[i] = i; */
    
    for (i = 0; i < n; i++)
        printf("end. v[%d] = %p cont v[%d] = %d\n", i, (void*)(v+i), i, v[i]);
    
    free(v);

    return 0;
}