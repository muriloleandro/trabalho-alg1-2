#include <stdlib.h>
#include <stdio.h>
#include "avl.h"
#define max(a, b) ((a > b) ? a : b)

typedef struct node_ node;

struct node_ {
    node *esq;
    node *dir;
    int chave;
    int altura;
    int fb;
};

struct avl_ {
    node *raiz;
    int tam;
};

avl *avl_criar(void) {
    avl *T = malloc(sizeof(avl));

    if (T != NULL) {
        T->raiz = NULL;
        T->tam = -1;
    }

    return T;
}

void avl_apagar_no(node **no) {
    if (*no == NULL) {
        return;
    }

    avl_apagar_no(&((*no)->esq));
    avl_apagar_no(&((*no)->dir));

    free(*no);
    *no = NULL;
}

void avl_apagar(avl **T) {
    avl_apagar_no(&((*T)->raiz));
    free(*T);
    *T = NULL;
}

int avl_altura_no(node* no) {
    if (no == NULL) {
        return -1;
    } else {
        return no->altura;
    }
}

node *avl_cria_no(int chave) {
    node *no = malloc(sizeof(node));

    if (no != NULL) {
        no->dir = NULL;
        no->esq = NULL;
        no->chave = chave;
        no->altura = 0;
        no->fb = 0;
    }

    return no;
}

node *rodar_direita(node *a) {
    node *b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    a->fb = b->fb = 0;

    a->altura = max(avl_altura_no(a->esq), avl_altura_no(a->dir)) + 1;
    b->altura = max(avl_altura_no(b->esq), a->altura) + 1;

    return b;
}

node *rodar_esquerda(node *a) {
    node *b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    a->fb = b->fb = 0;

    a->altura = max(avl_altura_no(a->esq), avl_altura_no(a->dir)) + 1;
    b->altura = max(avl_altura_no(b->dir), a->altura) + 1;

    return b;
}

node *rodar_esquerda_direita(node *a) {
    a->esq = rodar_esquerda(a->esq);
    return rodar_direita(a);
}

node *rodar_direita_esquerda(node *a) {
    a->dir = rodar_direita(a->dir);
    return rodar_esquerda(a);
}

node *avl_inserir_no(node *raiz, int chave) {
    if (raiz == NULL) {
        raiz = avl_cria_no(chave);
    } else if (chave < raiz->chave) {
        raiz->esq = avl_inserir_no(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = avl_inserir_no(raiz->dir, chave);
    }

    raiz->fb = avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir);

    if (raiz->fb == -2) {
        if (raiz->dir->fb <= 0) {
            raiz = rodar_esquerda(raiz);
        } else {
            raiz = rodar_direita_esquerda(raiz);
        }
    }

    if (raiz->fb == 2) {
        if (raiz->esq->fb >= 0) {
            raiz = rodar_direita(raiz);
        } else {
            raiz = rodar_esquerda_direita(raiz);
        }
    }

    return raiz;
}

int avl_inserir(avl *T, int chave) {
    if (T == NULL) return 0;
    T->raiz = avl_inserir_no(T->raiz, chave);
    if (T->raiz == NULL) return 0;
    return 1;
}

void troca_max_esq(node *troca, node *raiz, node *ant) {
    if (troca->dir != NULL) {
        troca_max_esq(troca->dir, raiz, troca);
    }

    if (raiz == ant) {
        ant->esq = troca->esq;
    } else {
        ant->dir = troca->esq;
    }

    raiz->chave = troca->chave;
    free(troca);
    troca = NULL;
}

node *avl_remover_aux(node **raiz, int chave) {
    if (*raiz == NULL) {
        return NULL;
    }

    node *r = *raiz;
    if (chave == r->chave) {
        if (r->esq == NULL) {
            *raiz = r->dir;
            free(r); r = NULL;
        } else if (r->dir == NULL) {
            *raiz = r->esq;
            free(r); r = NULL;
        } else {
            troca_max_esq(r->esq, r, r);
        }
    } else if (chave < r->chave) {
        r->esq = avl_remover_aux(&r->esq, chave);
    } else if (chave > r->chave) {
        r->dir = avl_remover_aux(&r->dir, chave);
    }

    r = *raiz;
    if (r == NULL) {
        return NULL;
    }

    r->fb = avl_altura_no(r->esq) - avl_altura_no(r->dir);
    if (r->fb == 2) {
        if (r->esq->fb >= 0) {
            *raiz = rodar_direita(r);
        } else {
            *raiz = rodar_esquerda_direita(r);
        }
    }
    if (r->fb == -2) {
        if (r->dir->fb <= 0) {
            *raiz = rodar_direita(r);
        } else {
            *raiz = rodar_direita_esquerda(r);
        }
    }

    return *raiz;
}

int avl_remover(avl *T, int chave) {
    if (T == NULL) return 0;
    T->raiz = avl_remover_aux(&T->raiz, chave);
    return 1;
}

int avl_contem_aux(node *no, int chave) {
    if (no == NULL) return 0;
    if (no->chave == chave) return 1;
    if (no->chave < chave) return avl_contem_aux(no->esq, chave);
    return avl_contem_aux(no->dir, chave);
}

int avl_contem(avl *T, int chave) {
    if (T == NULL) return 0;

    return avl_contem_aux(T->raiz, chave);
}

void avl_imprimir_aux(node *no) {
    if (no != NULL) {
        avl_imprimir_aux(no->esq);
        printf("%d ", no->chave);
        avl_imprimir_aux(no->dir);
    }
}

void avl_imprimir(avl *T) {
    if (T != NULL && T->raiz != NULL) {
        avl_imprimir_aux(T->raiz);
        printf("\n");
    }
}