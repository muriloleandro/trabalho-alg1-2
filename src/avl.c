#include <stdlib.h>
#include <stdio.h>
#include "avl.h"
//função que, para dois inteiros 'a' e 'b', retorna o maior entre ambos;
#define max(a, b) ((a > b) ? a : b)

typedef struct node_ node;

/*
  estrutura básica da implementação encadeada de àrvores, os nós;
  no caso da AVL, há 2 ponteiros para os nós 'esquerdo' e 'direito',
  além de 3 inteiros: 'chave' (elemento do conjunto), 'altura'
  (altura da àrvore em que esse nó está), e 'fb' (fator de balanceamento);
*/
struct node_ {
    node *esq;
    node *dir;
    int chave;
    int altura;
    int fb;
};

struct avl_ {
    node *raiz; // ponteiro para o 1° nó;
    int tam; // quantos nós há na àrvore;
};

avl *avl_criar(void) {
    avl *T = malloc(sizeof(avl));

    if (T != NULL) {
        T->raiz = NULL;
        T->tam = 0;
    }

    return T; // retornando uma a struct 'avl' devidamente alocada;
}

void avl_apagar_no(node **no) {
    if (*no == NULL) {
        return;
        // se chegou em nó nulo (impossível de apagar), encerrar recursão nesse caminho;
    }

    // recursivamente apagando os nós da àrvore;
    avl_apagar_no(&((*no)->esq));
    avl_apagar_no(&((*no)->dir));

    // liberando a memória e settando o ponteiro para nulo;
    free(*no);
    *no = NULL;
}

void avl_apagar(avl **T) {
    avl_apagar_no(&((*T)->raiz));
    free(*T); // liberando também o conteúdo contido na struct 'avl';
    *T = NULL;
}

// retorna a altura em que um determinado nó se encontra na AVL, caso ele exista;
int avl_altura_no(node* no) {
    if (no == NULL) {
        return -1;
    } else {
        return no->altura;
    }
}

//dado um inteiro, criaremos um nó que o possua como chave, retornando-o;
node *avl_cria_no(int chave) {
    node *no = malloc(sizeof(node));
 
    // todo nó criado para as àrvores AVL tem filhos inicialmente nulos,
    // uma chave, e altura e fb a serem determinados durante sua inserção na àrvore
    // (inicialmente ambos são 0);
    if (no != NULL) {
        no->dir = NULL;
        no->esq = NULL;
        no->chave = chave;
        no->altura = 0;
        no->fb = 0;
    }

    return no;
}

/*
  função básica da rotação à esquerda e à direita: recebem o nó mais jovem
  desbalanceado (ponto de partida) e modificam a àrvore para garantir balanceamento,
  de modo que a altura da sub-àrvore resultante é a mesma da sub-àrvore original,
  o que não afeta o fb de nenhum nó fora desse conjunto; as funções retornam o novo
  nó que ocupa a posição original do prévio, introduzindo na AVL a nova subàrvore,
  agora balanceada; ambas as operações tomam tempo constante (O(1)),
  considerando o fato de serem somente um conjunto de operações fixas que tomam tempo
  constante, repetidas sempre que a função é chamada;
*/
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

/*
  rotações duplas servem o mesmo propósito das rotações simples, isto é,
  balancear a àrvore; elas serão necessárias em alguns casos;
  as funções por elas responsáveis recebem, tais quais as simples,
  o nó mais jovem a estar desbalanceado, e devolvem um ponteiro para
  a sub-àrvore (agora balanceada) inicial, com mudanças em suas estruturas;
*/
node *rodar_esquerda_direita(node *a) {
    a->esq = rodar_esquerda(a->esq);
    return rodar_direita(a);
}

node *rodar_direita_esquerda(node *a) {
    a->dir = rodar_direita(a->dir);
    return rodar_esquerda(a);
}

/*
  recursivamente, de baixo para cima, traça-se um caminho pela àrvore,
  até achar-se a ponta ideal para inserir o novo nó (faz-se isso com base
  em comparações de chaves, dado o fato da AVL ser uma ABB), ponto em que
  as chamadas recursivas vão sendofinalizadas, rotacionando a àrvore conforme
  for necessário no caminho inverso à ida (bottom -> up) para rebalanceá-la;
*/
node *avl_inserir_no(node *raiz, int chave, avl *T) {
    if (raiz == NULL) {
        raiz = avl_cria_no(chave);
        T->tam += 1;
    } else if (chave < raiz->chave) {
        raiz->esq = avl_inserir_no(raiz->esq, chave, T);
    } else if (chave > raiz->chave) {
        raiz->dir = avl_inserir_no(raiz->dir, chave, T);
    }

    //cálculo do novo fb dos nós, a fim de rotacionar conforme necessário;
    int he = avl_altura_no(raiz->esq);
    int hd = avl_altura_no(raiz->dir);
    raiz->altura = 1+max(he, hd);
    raiz->fb = he - hd;

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

    // a função retorna nó raíz, a fim de justamente deixar bem
    // delimitado esse 'path' pela àrvore;
    return raiz;
}

int avl_inserir(avl *T, int chave) {
    if (T == NULL) return 0;
    T->raiz = avl_inserir_no(T->raiz, chave, T);
    if (T->raiz == NULL) return 0;
    return 1;
}

/*
  função necessária para a remoção nas ABB's, pois, no caso em que o nó a ser
  removido tiver duas sub-àrvores, será preciso encontrar o nó com maior chave
  na sub-àrvore esquerda para trocar sua chave com ele (poderíamos também procurar
  o de menor valor na sub-àrvore direita);
*/
void troca_max_esq(node *troca, node *raiz, node *ant) {
    if (troca->dir != NULL) {
        troca_max_esq(troca->dir, raiz, troca);
        return;
    }

    if (raiz == ant) {
        ant->esq = troca->esq;
    } else {
        ant->dir = troca->esq;
    }

    raiz->chave = troca->chave; // troca das chaves nos nós;
    free(troca); // eliminação do nó-folha com o maior valor da àrvore esquerda;
    troca = NULL;
}

/*
  função recursiva para a remoção, a qual, tal como a inserção, traça um
  caminho pela àrvore até encontrar o nó a ser removido (encaixa-se em um
  dos 3 casos da remoção), removendo-o e dando ré para ir rebalanceando a
  àrvore via as rotações;
*/
node *avl_remover_aux(node **raiz, int chave, avl *T) {
    if (*raiz == NULL) {
        return NULL;
    }

    node *r = *raiz;
    if (chave == r->chave) {
        T->tam -= 1;
        // se o nó não tiver nenhuma sub-àrvore, ele só será apagado; 
        // com uma sub-àrvore, o filho substituirá o pai;
        // com 2, a 'troca_max_esq' deve ser chamada;
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
        r->esq = avl_remover_aux(&r->esq, chave, T);
    } else if (chave > r->chave) {
        r->dir = avl_remover_aux(&r->dir, chave, T);
    }

    r = *raiz;
    if (r == NULL) {
        return NULL;
    }

    // rebalanceamento necessário no back-tracking pela àrvore;
    int he = avl_altura_no(r->esq);
    int hd = avl_altura_no(r->dir);
    r->altura = 1+max(he, hd);
    r->fb = he - hd;
    if (r->fb == 2) {
        if (r->esq->fb >= 0) {
            *raiz = rodar_direita(r);
        } else {
            *raiz = rodar_esquerda_direita(r);
        }
    }
    if (r->fb == -2) {
        if (r->dir->fb <= 0) {
            *raiz = rodar_esquerda(r);
        } else {
            *raiz = rodar_direita_esquerda(r);
        }
    }

    return *raiz;
}

int avl_remover(avl *T, int chave) {
    if (T == NULL) return 0;
    T->raiz = avl_remover_aux(&T->raiz, chave, T);
    return 1;
}

// vai buscando recursivamente por meio de comparações da chave buscada com as
// dos nós, até que ou não encontre-o (retorna 0), ou encontre-o (retorna 1);
int avl_contem_aux(node *no, int chave) {
    if (no == NULL) return 0;
    if (no->chave == chave) return 1;
    if (no->chave > chave) return avl_contem_aux(no->esq, chave);
    return avl_contem_aux(no->dir, chave);
}

int avl_contem(avl *T, int chave) {
    if (T == NULL) return 0;
    return avl_contem_aux(T->raiz, chave);
}

/*
  optou-se por fazer o percurso em-ordem, para poder imprimir os valores
  da àrvore em ordem, por pura questão estética, considerando o fato do
  professor não ter requisitado a exibição dos elementos do conjunto em ordem;
*/
void avl_imprimir_aux(node *no) {
    if (no != NULL) {
        avl_imprimir_aux(no->esq);
        printf("%d, ", no->chave);
        avl_imprimir_aux(no->dir);
    }
}

void avl_imprimir(avl *T) {
    if (T != NULL && T->raiz != NULL) {
        avl_imprimir_aux(T->raiz);
        printf("\n");
    }
}

int avl_tamanho(avl *T) {
    if (T == NULL) return -1;
    return T->tam;
}

/*
  temos que percorrer uma árvore (via 'node *raiz') para comparar seus elementos aos
  da outra ('avl *arvore'); para isso, será usada a in-order traversal, por nenhum
  motivo em especial (a post-order e pre-order também percorrem a árvore inteira);
*/
void avl_intersseccao_aux(avl *arvore, node *raiz, avl *inter){
    if (raiz != NULL) {
        avl_intersseccao_aux(arvore, raiz->esq, inter);
        
        int elemento = raiz->chave;

        // somente inserimos em 'avl *inter' caso o elemento esteja presente
        // em AMBOS os conjuntos, isto é, armazenado em AMBAS as estruturas de dados;
        if (avl_contem(arvore, elemento) == 1) {
            avl_inserir(inter, elemento);
        }

        avl_intersseccao_aux(arvore, raiz->dir, inter);
    }
}

avl *avl_interseccao(avl *A, avl *B){
    // não será possível efetuar a operação caso um dos sets (ou ambos) não exista;
    if ((A == NULL) || (B == NULL)) {
        return NULL;
    }

    avl *intersseccao = avl_criar(); // àrvore avl que guardará os conjuntos da união;

    // no caso da interssecção, para economizar tempo de operação,
    // faz mais sentido percorrer o menor conjunto entre os dois,
    // dado que o set da interssecção terá, no máximo, um número
    // de elementos equivalente ao do menor entre ambos;
    if ((A->tam) >= (B->tam)) {
        avl_intersseccao_aux(A, B->raiz, intersseccao);
    } else {
        avl_intersseccao_aux(B, A->raiz, intersseccao);
    }

    return intersseccao;
}

void avl_uniao_aux(node *raiz, avl *uniao){
    if (raiz != NULL) {
        avl_uniao_aux(raiz->esq, uniao);

        avl_inserir(uniao, raiz->chave);

        avl_uniao_aux(raiz->dir, uniao);
    }
} 

avl *avl_uniao(avl *A, avl *B){
    if ((A == NULL) || (B == NULL)) {
        return NULL;
    }

    avl *uniao = avl_criar();

    // ideia básica: percorrer ambos os sets e ir inserindo os elementos em uniao;
    // do modo como as estruturas de dados operam, se um elemento já estiver inserido,
    // o set uniao meramente não mudará, evitando a repetição de elementos;
    avl_uniao_aux(A->raiz, uniao);
    avl_uniao_aux(B->raiz, uniao);

    return uniao;
}