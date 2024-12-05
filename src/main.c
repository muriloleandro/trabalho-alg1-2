#include <stdio.h>
#include "avl.h"
#include "llrbt.h"

int main(void) {
    llrbt *arvore = llrbt_criar();
    // 10, 5, 20, 1, 3, 4, 8, 30, 40, 35, 50, 45, 55, 51, 100
    llrbt_inserir(arvore, 10);
    llrbt_inserir(arvore, 5);
    llrbt_inserir(arvore, 20);
    llrbt_inserir(arvore, 1);
    llrbt_inserir(arvore, 3);
    llrbt_inserir(arvore, 4);

    llrbt_remover(arvore, 20);
    llrbt_remover(arvore, 4);

    llrbt_imprimir(arvore);
    printf("Tamanho: %d\n", llrbt_tamanho(arvore));
    llrbt_apagar(&arvore);
    
    return 0;
}
