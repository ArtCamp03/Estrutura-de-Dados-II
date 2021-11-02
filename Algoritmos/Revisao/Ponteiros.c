// Rrevisao de Ponteiros
#include <stdio.h>
#include <stdlib.h>

int main(){

    int p1;  //variavel tipo inteiro
    p1 = 10;
    // &pt retorna o endereço da posiçao de memoria da variavel pt
    int *pt;    // ponteiro do tipo inteiro
    pt = &p1;
    // *pt -> capta o conteudo qe esta no enderço da memoria

    printf("%i \n", *pt);

    *pt = 20;
    printf("%i \n", *pt);
    printf("%i \n", p1);


   
    return 0;
}