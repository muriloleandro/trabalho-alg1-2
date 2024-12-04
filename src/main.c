#include <stdio.h>
#include "avl.h"

int main(void) {
    avl *arvore = avl_criar();
    // 10, 5, 20, 1, 3, 4, 8, 30, 40, 35, 50, 45, 55, 51, 100
    avl_inserir(arvore, 10);
    avl_inserir(arvore, 5);
    avl_inserir(arvore, 20);
    avl_inserir(arvore, 1);
    avl_inserir(arvore, 3);
    avl_inserir(arvore, 4);
    avl_inserir(arvore, 8);
    avl_inserir(arvore, 30);
    avl_inserir(arvore, 40);
    avl_inserir(arvore, 35);
    avl_inserir(arvore, 50);
    avl_inserir(arvore, 45);
    avl_inserir(arvore, 55);
    avl_inserir(arvore, 51);
    avl_inserir(arvore, 100);

    avl_remover(arvore, 51);
    avl_remover(arvore, 3);
    avl_remover(arvore, 3);

    avl_imprimir(arvore);
    avl_apagar(&arvore);
    
    return 0;
}
