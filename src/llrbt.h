#ifndef _LLRBT_H
    #define _LLRBT_H

    typedef struct llrbt_ llrbt;
    
    llrbt *llrbt_criar(void); 
    void llrbt_apagar(llrbt **T);
    int llrbt_inserir(llrbt *T, int chave);
    int llrbt_remover(llrbt *T, int chave);
    int llrbt_contem(llrbt *T, int chave);
    void llrbt_imprimir(llrbt *T);
    int llrbt_tamanho(llrbt *T);
#endif