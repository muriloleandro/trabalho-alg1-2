#ifndef _SET_H
    #define _SET_H

    #include <stdbool.h>
    #include "avl.h" 
    #include "llrbt.h" 

    typedef struct set SET;

    // abaixo, para as complexidades calculadas, considere 'n' como o 
    // número de elementos do conjunto (quando o que ele signifca não 
    // for explicitado);

    /*
    a função 'set_criar' recebe como argumento um unsigned char (ocupa
    menos espaço na memória se comparado ao int), o qual dirá qual das
    estruturas de dados o usuário deseja utilizar, criando cada uma 
    conforme ele requisitar; a função possui tratamento de erro para caso 
    o usuário coloque um número diferente de 1 ou 0, retornando NULL;

    COMPLEXIDADE: O(1); 
    */
    SET *criar_set (unsigned char tipo);

    /*
    essa função tem como argumento um elemento e um set, no qual esse 
    elemento será buscado; ela retorna falso caso o set seja nulo, e, 
    do contrário, retornará 'true' se o elemento pertencer a ele e 'false' 
    caso esse não seja o caso; a busca por uma ABB, por ser binária, é
    uma operação que tem como pior caso o elemento ser inserido no fim 
    de uma árvore de altura log(n), justificando sua complexidade abaixo;

    COMPLEXIDADE: O(log(n));
    */
    bool set_pertence (SET *S, int elemento);

    /*
    'set_inserir' tem como objetivo inserir um elemento em um set 
    não nulo; caso isso não seja bem-sucedido, a função retornará 
    falso; do contrário, ela retornará verdadeiro; como, para esse
    fim, é necessário efetuar uma busca, e a inserção é de complexidade
    constante, o big Oh será idêntico ao de 'set_pertence';

    COMPLEXIDADE: O(log(n));
    */
    bool set_inserir (SET *S, int elemento);

    /*
    'set_remover' segue a mesma lógica de 'set_inserir', porém para 
    a remoção: caso ela seja bem sucedida, retornamos true, do 
    contrário, false;

    COMPLEXIDADE: O(log(n));
    */
    bool set_remover (SET *S, int elemento);

    /*
    nessa função, um ponteiro para ponteiro para 'set' é recebido, 
    sendo necessário apagar seu conteúdo; para isso, é necessário 
    apagar a estrutura de dados contida nessa struct (percorrendo todos
    os nós), além de também liberar na memória o espaço ocupado por 
    ela, setando seu ponteiro para nulo após tal;

    COMPLEXIDADE: O(n);
    */
    void set_apagar (SET **S);

    /*
    'set_imprimir' imprimirá o conteúdo presente nos sets ao percorrer
    todos os elementos, permitindo ao usuário visualizar exatamente isso;

    COMPLEXIDADE: O(n);
    */
    void set_imprimir (SET *S);

    /*
    recebe como argumento os sets A e B, produzindo um set novo (o qual
    será retornado) que contém a união de ambos os conjuntos de input; 
    'set_uniao' funciona ao percorrer os dois, aplicando uma função de 
    inserção para cada elemento, inserindo-o caso ele não esteja presente
    em 'uniao', ou não o fazendo, do contrário;

    quanto à complexidade: tomando em conta as ED utilizadas (AVL e LLRBT),
    nota-se que percorrer ambas as árvores de A e de B envolve atravessar 
    no total 'n' + 't' elementos, sendo que, para cada um, é preciso tentar 
    inserí-lo na nova árvore criada (complexidade de log (x), sendo 'x' o
    número de elementos dela); no pior caso, A e B são disjuntos, e, desse 
    modo, a complexidade se torna O ((n + t)*(log (x))) = O ((n + t)*(log (n + t)));

    COMPLEXIDADE: O((n + t)*(log (n + t)));  ['n' e 't', respectivamente, n° de elementos de A e B]
    */
    SET *set_uniao (SET *A, SET *B);

    /*
    é produzido um set interssecção contendo os elementos comuns de A e B,
    que é o output da função; percorre-se o menor set dentre os dois, 
    inserindo seus elementos se e somente se eles estiverem presentes no 
    outro set; desse modo, será sempre necessário percorre um set por completo,
    e, no outro, buscar um número de vezes equivalente ao tamanho do primeiro, 
    inserindo os elementos comuns no novo conjunto criado;

    aqui cabe explicar a complexidade da operação interssecção para as duas 
    ED implementadas (árvores LLRBT e AVLR): note que o que é feito é basicamente 
    percorrer o menor set inteiro ('n' elementos) e, a cada elemento, percorrer 
    também o maior set ('t' elementos), e, caso ele seja comum a ambos, inserí-lo 
    no novo set criado; no pior caso, os dois sets são idênticos (n = t), o que 
    resultará em percorrer um set e, a cada vez, buscar no outro (n*log(n)) e inserir 
    o elemento no novo set (n*log(n)); portanto complexidade = O (2*n*log(n)) = O (n*log(n)); 

    COMPLEXIDADE: O(n*log(n));  ['n' = n° de elementos do menor conjunto]
    */
    SET *set_interseccao (SET *A, SET *B);
  
#endif
