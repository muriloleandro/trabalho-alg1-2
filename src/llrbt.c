#include <stdlib.h>
#include <stdio.h>
#include "llrbt.h"

#define max(a, b) ((a > b) ? a : b)
#define BLACK 0
#define RED 1

typedef struct node_ node;

struct node_ {
    node *esq;
    node *dir;
    int chave;
    unsigned char cor;
};

struct llrbt_ {
    node *raiz;
};

llrbt *llrbt_criar(void) {
    avl *T = malloc(sizeof(llrbt));

    if (T != NULL) {
        T->raiz = NULL;
    }

    return T;
}

void llrbt_apagar_no(node **no) {
    if (*no == NULL) {
        return;
    }

    llrbt_apagar_no(&((*no)->esq));
    llrbt_apagar_no(&((*no)->dir));

    free(*no);
    *no = NULL;
}

void llrbt_apagar(llrbt **T) {
    llrbt_apagar_no(&((*T)->raiz));
    free(*T);
    *T = NULL;
}

int llrbt_inserir(llrbt *T, int chave);

int llrbt_remover(llrbt *T, int chave);

int llrbt_contem_aux(node *no, int chave) {
    if (no == NULL) return 0;
    if (no->chave == chave) return 1;
    if (no->chave > chave) return llrbt_contem_aux(no->esq, chave);
    return llrbt_contem_aux(no->dir, chave);
}

int llrbt_contem(llrbt *T, int chave) {
    if (T == NULL) return 0;

    return llrbt_contem_aux(T->raiz, chave);
}

void llrbt_imprimir_aux(node *no) {
    if (no != NULL) {
        llrbt_imprimir_aux(no->esq);
        printf("%d ", no->chave);
        llrbt_imprimir_aux(no->dir);
    }
}

void llrbt_imprimir(llrbt *T) {
    if (T != NULL && T->raiz != NULL) {
        llrbt_imprimir_aux(T->raiz);
        printf("\n");
    }
}