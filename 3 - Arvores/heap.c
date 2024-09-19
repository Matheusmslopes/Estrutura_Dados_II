#include <stdio.h>

int filhoEsquerda(int ind_parent){
    return (2 * ind_parent + 1);
}

int filhoDireita(int ind_parent){
    return (2 * ind_parent + 2);
}

int pai(int heap){
    return (int)(heap-1)/2;
}

int main()
{
    int vetor[7] = {30, 15, 25, 12, 10, 21, 23};
    int isHeap = 0;
    
    for (int i = 0; i < (int)(sizeof(vetor)/ sizeof(int))/2; i++){
        int pai = vetor[i];
        int filhoEsq = vetor[filhoEsquerda(i)];
        int filhoDir = vetor[filhoDireita(i)];
        
        if (pai < filhoEsq || pai < filhoDir)
            isHeap++;
        
        printf("Pai - %i, Filho Esquerda - %i, Filho DIreita - %i \n", pai, filhoEsq, filhoDir);
    }
    
    if (isHeap == 0)
        printf("Heap");
    else
        printf("Não Heap");
    
    return 0;
}
