#include <stdlib.h>
#include <stdio.h>
#include "llrbt.h"

// retornando o máx entre dois dados do tipo int;
#define max(a, b) ((a > b) ? a : b)
#define RUBRO 1
#define NEGRO 0

typedef struct node_ node;

// o nó da llrbt precisa guardar a cor da aresta que seu pai incide sobre ele,
// ponteiros para seus 2 filhos, e o conteúdo (chave);
struct node_ {
    node *esq;
    node *dir;
    int chave;
    unsigned char cor;
};

struct llrbt_ {
    node *raiz;
    int tam; // número de nós na àrvore;
};

// retorna ponteiro para uma struct 'llrbt', devidamente alocada;
llrbt *llrbt_criar(void) {
    llrbt *T = malloc(sizeof(llrbt));

    if (T != NULL) {
        // manejo adequado da memória:
        // checando se a alocação foi bem sucedida ou não;
        T->raiz = NULL;
        T->tam = 0;
    }

    return T;
}

void llrbt_apagar_no(node **no) {
    // apaga-se pai, e propaga-se recursivamente a deleção para os filhos,
    // sendo que o ciclo acaba nas folhas NULLs da llrbt;
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
    // liberando também na memória o espaço alocado para a struct 'llrbt',
    // que é apontado pelo ponteiro *T;
    *T = NULL;
}

node *llrbt_cria_no(int chave) {
    node *no = malloc(sizeof(node));

    if (no != NULL) {
        no->dir = NULL;
        no->esq = NULL;
        no->chave = chave;
        no->cor = RUBRO;
        // segundo as regras da ED, todo nó é criado com uma aresta rubra
    }

    return no;
}

/* 
  rotação esquerda:
      a                b
     / \              / \
    X    b    =>     a   W
        / \         / \
       Y   W       X   Y 

  rotação direita:
      a          b
     / \        / \
    b   W  =>  X   a 
   / \            / \
  X   Y          Y   W

 É importante também ressaltar que, quando rotacionamos nesse tipo de àrvore, as cores das arestas que ligam os nós permanecem
as mesmas que anteriormente, isto é, se na rotação A e B são trocados de posição, a aresta que os liga e as que os ligam aos demais
nós preservam suas cores originais;
*/
node *rotacao_esquerda(node  *no) {
    node *dir = no->dir;
    node *dir_esq = dir->esq;
	
    dir->esq = no;
    no->dir = dir_esq;

    dir->cor = no->cor;
    no->cor = RUBRO;

    return dir;
}

// O contrário da rotação esquerda, a lógica é a mesma;
node *rotacao_direita(node *no) {
    node *esq = no->esq;
    node *esq_dir =  esq->dir;

    esq->dir = no;
    no->esq = esq_dir;

    esq->cor = no->cor;
    no->cor = RUBRO;

    return esq; 
}

// inverte cor do nó e dos filhos;
void inverter(node *no) {
    no->cor = !no->cor;
    if (no->esq != NULL) no->esq->cor = !no->esq->cor;
    if (no->dir != NULL) no->dir->cor = !no->dir->cor;
}

// checa se um nó é vermelho, valida casos que nó é NULL
// (se for null, retorna que sua aresta é negra);
int rubro(node *no) {
    if (no == NULL) return 0;
    return (no->cor == RUBRO);
}

/*
  a função consertar tem como papel ajustar a àrvore para que, na volta das
  chamadas recursivas nas funções 'inserir()' e 'remover()', cada nó  que foi
  atravessado seja analisado para ver se as mudanças que a inserção e a remoção
  trouxeram afetaram as propriedades de balanceamento da llrbt, caso esse em que
  rotações e inversões serão utilizados para garantir a preservação delas; 
*/
node *consertar(node *no) {
    // caso 1
    if (rubro(no->dir) && !rubro(no->esq)) {
        no = rotacao_esquerda(no);
    }
     
    // caso 2
    if (rubro(no->esq) && rubro(no->esq->esq)) {   
        no = rotacao_direita(no);
    }
    
    // caso 3
    if (rubro(no->esq) && rubro(no->dir)) {
        inverter(no);
    }

    return no;
}

node *llrbt_inserir_aux(node *no, int chave, llrbt *T) {
    // caso base
    if (no == NULL) {
        T->tam += 1;
	    return llrbt_cria_no(chave);
	}  
 
    // inserção normal de uma ABB;
    if (chave < no->chave) {
        no->esq = llrbt_inserir_aux(no->esq, chave, T);
    } else if (chave > no->chave) {
        no->dir = llrbt_inserir_aux(no->dir, chave, T);
    } else {   
        return no;
    }
    
    // balanceamento;
    no = consertar(no);
    return no;
}

int llrbt_inserir(llrbt *T, int chave) {
    if (T == NULL) return 0;
    // cobre o caso em que a raíz não foi criada ainda
    if (T->raiz == NULL) {
        T->raiz = llrbt_cria_no(chave);
        T->raiz->cor = NEGRO;
        T->tam += 1;
        return 1;
    }

    T->raiz = llrbt_inserir_aux(T->raiz, chave, T);
    return 1;
}

/*
  as funções 'rubro_pra_esquerda' e 'rubro_pra_direita' garantem a propagação da
  aresta rubra pelos nós conforme as chamadas recursivas para remoção ocorrem 
  (respectivamente, para o nó-fiho esquerdo e direito), dado que somente removem-se
  nós com incidência rubra; para esse fim, é necessário, em cada uma das 2, 
  checar com qual caso se está lidando, a fim de se decidir o que fazer;
*/
node *rubro_pra_esquerda(node *no) {
    inverter(no);
    if ((no->dir != NULL) && rubro(no->dir->esq)) {
        no->dir = rotacao_direita(no->dir);
        no = rotacao_esquerda(no);
        inverter(no);
    }
    return no;
}

node *rubro_pra_direita(node *no) {
    inverter(no);
    if ((no->esq != NULL) && rubro(no->esq->esq)) {
        no = rotacao_direita(no);
        inverter(no);
    }
    return no;
}

/*
  tal qual na ABB padrão, aplica-se essa função para remover da sub-àrvore direita
  (do nó cuja chave deseja-se remover) o nó cuja chave foi trocada, respeitando-se
  a propagação do nó vermelho até a aresta a ser removida;
*/
node *deletar_min(node *no) {
    if (no == NULL) return NULL;
    if (no->esq == NULL) {
        llrbt_apagar_no(&no);
        return NULL;
    }
    if (!rubro(no->esq) && !rubro(no->esq->esq)) {
        no = rubro_pra_esquerda(no);
    }
    no->esq = deletar_min(no->esq);
    return consertar(no);
}

// anda para a esquerda até chegar no final da árvore, obtendo a menor chave;
// aplicado para a remoção no caso em que há 2 subàrvores;
node *menor(node *no) {
    if (no == NULL) return NULL;
    if (no->esq == NULL) return no;
    return menor(no->esq);
}

node *llrbt_remover_aux(node *no, int chave, llrbt *T) {
    if (no == NULL) return NULL;
    if (chave < no->chave) {
        // direção a ser propagada a aresta rubra = esquerda;
        if ((no->esq == NULL) || (!rubro(no->esq) && !rubro(no->esq->esq))) {
            no = rubro_pra_esquerda(no);
        }
        no->esq = llrbt_remover_aux(no->esq, chave, T);
    } else {
        // ou achamos o nó, ou vamos à direita agora;
        if (rubro(no->esq)) {
            // propagando a aresta rubra pra direita;
            no = rotacao_direita(no);
        }
        if (chave == no->chave && (no->dir == NULL)) {
            // chegou-se na extremidade esquerda da àrvore (retorna NULL após apagar o nó);
            llrbt_apagar_no(&no);
            T->tam -= 1;
            return NULL;
        }
        if ((no->dir == NULL) || (!rubro(no->dir) && !rubro(no->dir->esq))) {
            // garantindo novamente que a aresta rubra será propagada à direita;
            no = rubro_pra_direita(no);
        }
        if (chave == no->chave) {
            // removendo o nó e ajustando a àrvore se necessário (tal qual ABB, 3 casos de remoção);
            T->tam -= 1;
            no->chave = menor(no->dir)->chave;
            no->dir = deletar_min(no->dir);
        } else {
            // indo à direita da àrvore;
            no->dir = llrbt_remover_aux(no->dir, chave, T);
        }
    }

    // arrumando a àrvore na volta da recursão, rebalanceando-a após
    // alterarmos toda sua estrutura para propagar a aresta rubra;	
    return consertar(no);
}

int llrbt_remover(llrbt *T, int chave) {
    // não pode remover nada se não houver algo para remover
    if (T == NULL || T->raiz == NULL) return 0;

    T->raiz = llrbt_remover_aux(T->raiz, chave, T);

    if (T->raiz == NULL) return 0;
    return 1;
}

// recursivamente vai propagando a busca por um caminho na àrvore,
// até cair em um dois 2 casos-base: encontrou (retorna 1) ou não (retorna 0);
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

// imprime o contéudo dos nós em order, devido ao in-order-traversal da llrbt;
void llrbt_imprimir_aux(node *no) {
    if (no != NULL) {
        llrbt_imprimir_aux(no->esq);
        printf("%d, ", no->chave);
        llrbt_imprimir_aux(no->dir);
    }
}

void llrbt_imprimir(llrbt *T) {
    if (T != NULL && T->raiz != NULL) {
        llrbt_imprimir_aux(T->raiz);
        printf("\n");
    }
}

// retorna a quantidade de nós na àrvore;
int llrbt_tamanho(llrbt *T) {
    if (T == NULL) return -1;
    return T->tam;
}

/*
  temos que percorrer uma árvore para comparar seus elementos
  aos da outra; para isso, será usada a in-order traversal,
  por nenhum motivo em especial (a post-order e pre-order
  também percorrem a árvore inteira);
*/
void llrbt_intersseccao_aux(llrbt *arvore, node *raiz, llrbt *inter){
    if (raiz != NULL){
        llrbt_intersseccao_aux(arvore, raiz->esq, inter);
        
        int elemento = raiz->chave;

        // somente inserimos caso o elemento esteja presente em
        // AMBOS os conjuntos, isto é, armazenado em AMBAS as estruturas de dados;
        if (llrbt_contem(arvore, elemento) == 1){
            llrbt_inserir(inter, elemento);
        }

        llrbt_intersseccao_aux(arvore, raiz->dir, inter);
    }
}

llrbt *llrbt_interseccao(llrbt *A, llrbt *B){
    // não será possível efetuar a operação 'união'
    // caso um dos sets (ou ambos) não exista;
    if ((A == NULL) || (B == NULL)){
        return NULL;
    }

    // àrvore llrbt que guardará os conjuntos da união;
    llrbt *intersseccao = llrbt_criar();

    /*
      no caso da interssecção, para economizar tempo de operação,
      faz mais sentido percorrer o menor conjunto entre os dois,
      dado que o set da interssecção terá, no máximo,
      um número de elementos equivalente ao do menor entre ambos;
    */
    if ((A->tam) >= (B->tam)) {
        llrbt_intersseccao_aux(A, B->raiz, intersseccao);
    } else {
        llrbt_intersseccao_aux(B, A->raiz, intersseccao);
    }

    return intersseccao;
}

void llrbt_uniao_aux(node *raiz, llrbt *uniao){
    if (raiz != NULL) {
        llrbt_uniao_aux(raiz->esq, uniao);
        llrbt_inserir(uniao, raiz->chave);
        llrbt_uniao_aux(raiz->dir, uniao);
    }
} 

llrbt *llrbt_uniao(llrbt *A, llrbt *B){
    if ((A == NULL) || (B == NULL)){
        return NULL;
    }

    llrbt *uniao = llrbt_criar();

    /*
      ideia básica: percorrer ambos os sets e ir inserindo os elementos em uniao;
      do modo como as estruturas de dados operam, se um elemento já estiver inserido,
      o set uniao meramente não mudará, evitando a repetição de elementos;
    */
    llrbt_uniao_aux(A->raiz, uniao);
    llrbt_uniao_aux(B->raiz, uniao);

    return uniao;
}
