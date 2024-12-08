 Trabalho de Algoritmos e Estruturas de Dados I
=====================================================

    TAD de conjuntos com duas estruturas de dados (AVL e LL-RBT).
    Além das operações básicas de criação, inserção, remoção e deleção,
    foram implementadas as operações de conjuntos: união e interseccção.

 Compilação
----------------------

    Rode no terminal o seguinte comando:
    $ make all
    O arquivo binário será compilado na pasta 'bin' com nome 'main'.

 Execução
----------------------

    É possível executar o programa das de formas:
    $ make run
    $ ./bin/

    Você pode usar o redirecionador de stdin (<) para passar um arquivo como entrada
    do programa:
    $ make run < cases/2.in
    $ ./bin/main < cases/2.in

    A entrada do programa tem a seguinte forma:
    tipo (0 = llrbt, 1 = avl)
    tamanho do conjunto A
    tamanho do conjunto B
    elementos do conjunto A
    elementos do conjunto B
    operação

    O valor da operação é o seguinte:
    1 = pertencimento. Neste caso, a entrada é seguida de mais um número a ser
        checado se pertence no conjunto A.
    2 = união. Retorna o conjunto A | B.
    3 = interseccção. Retorna o conjunto A & B.
    4 = remoção. Neste caso, a entrada é seguida de mais um número a ser removido
        do conjunto A.

    Exemplo:
    0
    3
    5
    1 2 3
    2 3 4 5 6
    4
    3

    Cujo retorno seria:
    1, 2, 

 Scripts
----------------------

    Foram feitos dois scripts de python. O primeiro, gen_test.py, gera 100 casos
    testes na paste 'cases' e suas saídas esperadas.
    É possível editar as variáveis para modificar como é gerado os casos testes.

    O segundo, runcodes.py, automaticamente executa o programa para cada arquivo
    de entrada (cases/*.in) e compara a saída com a a saída esperada (cases/*.out).
    Os casos que derem errados serão listados.

 Valgrind
----------------------

    Foi criado um script do make para rodar o valgrind. De preferência, passe um
    caso de teste para não digitar manualmente:
    $ make valgrind < cases/2.in
    Será criado um arquivo 'valgrind-out.txt' dizendo possível alocações não 
    liberadas na memória.