#ifndef _AVL_H
    #define _AVL_H

    typedef struct avl_ avl;
    
    avl *avl_criar(void); 
    void avl_apagar(avl **T);
    int avl_inserir(avl *T, int chave);
    int avl_remover(avl *T, int chave);
    int avl_contem(avl *T, int chave);
    void avl_imprimir(avl *T);
#endif