#include <stdio.h>
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
    llrbt_inserir(arvore, 8);
    llrbt_inserir(arvore, 30);
    llrbt_inserir(arvore, 40);
    llrbt_inserir(arvore, 35);
    llrbt_inserir(arvore, 50);
    llrbt_inserir(arvore, 45);
    llrbt_inserir(arvore, 55);
    llrbt_inserir(arvore, 51);
    llrbt_inserir(arvore, 100);

    llrbt_imprimir(arvore);
    printf("%d %d %d\n", llrbt_contem(arvore, 51), llrbt_contem(arvore, 100), llrbt_contem(arvore, 69));

    llrbt_remover(arvore, 100);
    llrbt_remover(arvore, 55);
    llrbt_remover(arvore, 55);
    llrbt_remover(arvore, 30);
    llrbt_remover(arvore, 30);
    llrbt_remover(arvore, 1);
    llrbt_remover(arvore, 1);

    llrbt_imprimir(arvore);
    printf("%d %d %d\n", llrbt_contem(arvore, 51), llrbt_contem(arvore, 100), llrbt_contem(arvore, 69));

    llrbt_apagar(&arvore);
    
    return 0;
}
