#ifndef _AVL_H
    #define _AVL_H

    typedef struct avl_ avl;
    // seja 'n' o número de nós na llrbt, quando esse valor
    // não tiver significado explicitado;

    /*
    quando chamada, essa função retorna um ponteiro para a struct
    AVL (se o 'malloc()' foi bem-sucedido) ou um ponteiro para 
    NULL (do contrário);

    COMPLEXIDADE = O(1);  
    */
    avl *avl_criar(void); 

    /*
    recebe como argumento um ponteiro duplo para a árvore AVL, e
    vai internamente percorrendo cada nó da árvore e apagando-os,
    liberando o espaço na memória que antes ocupavam;

    COMPLEXIDADE = O(n);
    */
    void avl_apagar(avl **T);

    /*
    dada uma chave e uma árvore, cria um nó para armazenar esse valor
    e busca na árvore, pelo algoritmo padrão de inserção de uma ABBA,
    um local adequado para inserí-lo (altura de log(h) base 2, sendo
    'h' o valor da chave); inserir toma tempo constante; retorna '1'
    se inseriu, e '0' do contrário;

    COMPLEXIDADE = O(log(n));
    */
    int avl_inserir(avl *T, int chave);

    /*
    busca pela árvore o nó com a chave correspondente e remove-o, tal 
    que a remoção pode requerir mais uma busca por 'T' (2 sub-árvores 
    atreladas ao nó que se deseja tirar); se a chave não está na árvore,
    a remoção é impossível, e o valor de retorno é '0', sendo '1' no
    caso contrário;

    COMPLEXIDADE = O(log(n));
    */
    int avl_remover(avl *T, int chave);
    
    /*
    busca na árvore dada um nó com a chave descrita, somente retornando
    caso ele existe em 'T' (return '1') ou não (return '0'); não afeta 
    em absolutamente nada a árvore;

    COMPLEXIDADE = O(log(n)); 
    */
    int avl_contem(avl *T, int chave);
    
    /*
    percorre em-ordem a árvore, printando as chaves de cada nó que está
    nela presente (em ordem crescente, já que a AVL é um tipo de ABB);

    COMPLEXIDADE = O(n);
    */
    void avl_imprimir(avl *T);

    /*
    dada uma árvore, retorna seu número de nós;

    COMPLEXIDADE = O(1);
    */
    int avl_tamanho(avl *T);

    /*
    recebe duas árvores AVL, A e B, e percorre ambas por completo, 
    tentando sempre inserir os elementos de cada uma em uma terceira
    árvore criada pela função, cujo ponteiro a ela será retornado;
    isso tem como efeito a operação matemática 'união' entre as chaves
    de A e B;
    complexidade explicada em 'sets.h';

    COMPLEXIDADE = O((n + t)*log(n + t)); ['n' e 't'tamanhos de A e B]
    */
    avl *avl_uniao(avl *A, avl *B);

    /*
    dadas duas árvores AVL de entrada, identifica qual das duas tem
    menos elementos, e percorre-a inteira, buscando para cada chave
    desta uma equivalente na outra, e, caso encontrando-a, inserindo
    esse valor em uma terceira AVL criada pela função, retornando no fim
    um ponteiro a esta, cujo conteúdo corresponde à interssecção de A e B;
    complexidade explicada em 'sets.h';

    COMPLEXIDADE = O(n*log(n)); ['n' tamanho da menor árvore entre A e B]
    */
    avl *avl_interseccao(avl *A, avl *B);
#endif