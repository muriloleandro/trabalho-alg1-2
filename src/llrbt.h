#ifndef _LLRBT_H
    #define _LLRBT_H

    typedef struct llrbt_ llrbt;
    //seja 'n' o número de nós na llrbt;

    //a função, quando chamada, aloca espaço para a struct 'llrbt' (checando se isso foi bem sucedido ou não), retornando
    //um ponteiro para a recém-criada estrutura;
    //COMPLEXIDADE = O(1);
    llrbt *llrbt_criar(void); 

    //recebe como argumento double pointer para uma llrbt, e apaga a ED via processos recursivos, liberando a memória ocupada pelos nós
    //na memória do computador ao percorrer cada um deles, apagando-os;
    //COMPLEXIDADE = O(n);
    void llrbt_apagar(llrbt **T);

    //dados uma àrvore e uma chave, a função cria um nó que contenha ela e decide onde inseri-lo na àrvore, preservando a estrutura da llrbt;
    //retorna '1' caso isso tenha dado certo, e '0' do contrário;
    //COMPLEXIDADE = O(log(n));
    int llrbt_inserir(llrbt *T, int chave);

    //dados uma àrvore e uma chave, busca-se um nó nela que contenha esse valor, retornando '1' se ele foi encontrado e removido, e '0' do contrário;
    //COMPLEXIDADE = O(log(n));
    int llrbt_remover(llrbt *T, int chave);

    //busca na àrvore 'T' um nó que contenha a chave providenciada, sendo '1' retornado se ele existe, e '0' do contrário;
    //COMPLEXIDADE = O(log(n));
    int llrbt_contem(llrbt *T, int chave);

    //imprime o conteúdo presente nos nós da àrvore via in-order traversal, ou seja, em ordem crescente;
    //COMPLEXIDADE = O(log(n));
    void llrbt_imprimir(llrbt *T);

    //acessa a struct 'llrbt' e retorna o número de nós;
    //COMPLEXIDADE = O(1);
    int llrbt_tamanho(llrbt *T);

    //retornará um ponteiro para uma terceira àrvore (do tipo llrbt) que contém a união dos elementos contidos nas duas llrbt's no argumento da função, criando-a e
    //preenchendo-a na própria função;
    //COMPLEXIDADE = O(n + t + log(n*t)) [sendo 't' o tamanho da àrvore B, e 'n' o da A];
    llrbt *llrbt_uniao(llrbt *A, llrbt *B);

    //retorna ponteiro para llrbt cujos elementos são introduzidos via o critério de pertencerem simultaneamente às árvores A e B;
    //COMPLEXIDADE = O(nlog(t)) [sendo 't' o tamanho da àrvore B, e 'n' o da A];
    llrbt *llrbt_interseccao(llrbt *A, llrbt *B);
#endif
