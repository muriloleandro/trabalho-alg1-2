#include <stdio.h>
#include <stdlib.h>
#include "sets.h"

int main (void){
    SET *A, *B;
    int tamA, tamB;
    int comando; //comando para o tipo de operação desejada pelo usuário;
    int tipo_arv; //0 = left_leaning_red black_tree; 1 = AVL_tree;
    int aux; //variável temporária, para armazenar os números que serão guardados nos conjuntos;

    scanf ("%d", &tipo_arv);

    A = criar_set (tipo_arv);
    B = criar_set (tipo_arv);

    scanf ("%d %d", &tamA, &tamB);

    //lendo o conteúdo dos conjuntos;
    for(int i = 0; i < tamA; i++){
        scanf("%d", &aux);
        set_inserir(A, aux);
    }

    for(int i=0; i < tamB; i++){
        scanf("%d",&aux);
        set_inserir(B, aux);

    }

    scanf ("%d", &comando);

    switch (comando){//usamos as operações básicas do TAD conjuntos para efetuar as operações específicas;
        case (1):{//pertence;
            int elemento;
            scanf ("%d", &elemento);

            if (set_pertence (A, elemento) == 1){
                printf ("Pertence\n");
            }else{
                printf ("Nao pertence\n");
            }

            break;
        }
        case (2):{//união;
            SET *uniao;

            if (tipo_arv == 1){
                uniao = criar_set (1);
            }else{
                uniao = criar_set (0);
            }

            uniao = set_uniao (A, B);

            set_imprimir (uniao);

            set_apagar (&uniao);

            break;
        }
        case (3):{//interssecção;
            SET *inter;

            if (tipo_arv == 1){
                inter = criar_set (1);
            }else{
                inter = criar_set (0);
            }

            inter = set_interseccao (A, B);

            set_imprimir (inter); 

            set_apagar (&inter);

            break;
        }
        case (4):{//remoção;
            int elemento;
            scanf ("%d", &elemento);

            set_remover (A, elemento);

            set_imprimir (A);

            break;
        }

    }

    set_apagar (&A);
    set_apagar (&B);

    return 0;
}
