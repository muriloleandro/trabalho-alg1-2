#include <stdio.h>
#include <stdlib.h>
#include "sets.h"
#include "llrbt.h"
#include "avl.h"

// set = struct a qual armazenará dois ponteiros para as 2 estruturas de dados,
// e um int, responsável por informar qual delas utilizaremos;
struct set {
    llrbt *LLRBT;
    avl *AVL;
    int tipo;
};

SET *criar_set(unsigned char tipo) {
    // se o usuário não escolher uma estrutura de dados válida, retornar NULL;
    if ((tipo != 0) && (tipo != 1)){
        return NULL;
    }

    SET *conjunto = malloc(sizeof(SET));

    if (conjunto == NULL) {
        printf("falha na alocação de memória!\n");
        exit(1);
    }
    
    conjunto->tipo = tipo;

    // criar a estrutura de dados do conjunto e retorná-lo;
    if (tipo == 1) {
        conjunto->AVL = avl_criar();
        return conjunto;
    }
    conjunto->LLRBT = llrbt_criar();

    return conjunto;
}

// retornaremos true se pertencer, e false caso não;
bool set_pertence(SET *S, int elemento) {
    // checando se 'S' existe para não dar segmentation_fault;
    if (S == NULL) {
        return false;
    }

    // uso das funções já feitas para busca em àrvores,
    // no caso, as AVL ('avl_contem') e as LLRBT ('llrbt_contem');
    if (S->tipo == 1) {
        if (avl_contem(S->AVL, elemento) == 1) {
            return true;
        } else {
            return false;
        }
    } else {
        if (llrbt_contem(S->LLRBT, elemento) == 1) {
            return true;
        } else {
            return false;
        }
    }
}

// o booleano anuncia o sucesso ou fracasso da inserção;
bool set_inserir(SET *S, int elemento) {
    // se o set não existe, a inserção não será possível, e, portanto, retornará false; 
    if (S == NULL) {
        return false;
    }

    int check; // variável para checar se as inserções serão ou não bem sucedidas;
    if (S->tipo == 1) {
        check = avl_inserir(S->AVL, elemento);
        if (check == 1) {
            return true;
        }
        return false;
    } else {
        check = llrbt_inserir(S->LLRBT, elemento);
        if (check == 1) {
            return true;
        }
        return false;
    }
}

// mesmo raciocínio de 'set_inserir', porém para a remoção agora;
bool set_remover(SET *S, int elemento) {
    if (S == NULL) {
        return false;
    }

    int check;
    if (S->tipo == 1) {
        check = avl_remover(S->AVL, elemento);
        if (check == 1) {
            return true;
        }
        return false;
    } else {
        check = llrbt_remover(S->LLRBT, elemento);
        if (check == 1) {
            return true;
        }
        return false;
    }
}

void set_apagar(SET **S) {
    if (*S == NULL) return;

    // apagando as estruturas de dados;
    if ((*S)->tipo == 1) {
        avl_apagar(&((*S)->AVL));
    } else {
        llrbt_apagar(&((*S)->LLRBT));
    }

    free (*S);
    *S = NULL;
    // liberando na memória o espaço alocado para a struct 'S';
    // settando o ponteiro para NULL (boa prática);
}

void set_imprimir(SET *S) {
    if (S == NULL) return;

    // basta utilizar as funções dos TAD's das árvores;
    if (S->tipo == 1) {
        avl_imprimir(S->AVL);
    } else {
        llrbt_imprimir(S->LLRBT);
    }    
}

SET *set_uniao(SET *A, SET *B) {
    // checando, obviamente, se ambos os sets existem de fato antes de tentar uni-los;
    if ((A == NULL) || (B == NULL)) {
        return NULL;
    }

    // em ambos os casos, o raciocínio é o mesmo, sendo apenas trocadas as funções
    // (pois as estrutras de dados são distintas): cria-se o set uniao,
    // faz-se com que ele contenha a ED com o conjunto união, e retorna-se ele;
    if (A->tipo == 1) {
        avl *union_tree = avl_uniao(A->AVL, B->AVL);
        SET *union_set = criar_set(1);
        union_set->AVL = union_tree;
        return union_set;
    } else {
        llrbt *union_tree = llrbt_uniao(A->LLRBT, B->LLRBT);
        SET *union_set = criar_set(0);
        union_set->LLRBT = union_tree;
        return union_set;
    }
}

// essa função é análoga à acima, porém para a interssecção;
SET *set_interseccao(SET *A, SET *B) {
    if ((A == NULL) || (B == NULL)) {
        return NULL;
    }

    if (A->tipo == 1) {
        avl *interssection_tree = avl_interseccao(A->AVL, B->AVL);
        SET *interssection_set = criar_set(1);
        interssection_set->AVL = interssection_tree;
        return interssection_set;
    } else {
        llrbt *interssection_tree = llrbt_interseccao(A->LLRBT, B->LLRBT);
        SET *interssection_set = criar_set(0);
        interssection_set->LLRBT = interssection_tree;
        return interssection_set;
    }
}