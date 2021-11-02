// Lista Encadeada

#include <stdlib.h>
#include <stdio.h>

typedef struct lista{
    int info;
    struct lista* prox;
}Lista;

// Funçao cria lista vazia 
Lista* cria_lista(){
    return NULL;
}

//Insere no Inicio da lista
Lista* insere_ini(Lista* li, int i){
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->info = i;
    novo->prox = li;
    return novo;
}

// Imprime elemento da Lista
void imprime(Lista* li){
    Lista* p;
    for(p = li; p != NULL; p = p->prox){
        printf("info = %d", p->info);
    }
}

// Insere Fim da Lista
Lista* insere_fim(Lista* li, int i){
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->info = i;
    novo->prox = NULL;
    Lista* p = li;
    Lista* q = li;
    while(p != NULL){ //encontra o ultimo elemento
        q = p;
        p = p->prox;
    }
    if(q != NULL)  //se a lsita original nao estiver vazia
        q->prox = novo;
    else
        li = novo;

    return 1;
}

Lista* insere_ordenado(Lista* li, int i){
    Lista* novo;
    Lista* ant = NULL;  //ponteiro para elemento anterior
    Lista* p = li;      //ponteiro para percorrer a lista
    // Procura posiçao de inserçao
    while(p != NULL && p->info < i){
        ant = p;
        p = p->prox;
    }
    // Cria novo elemento
    novo = (Lista*) malloc(sizeof(Lista));
    novo->info = i;
    // Encadeia elemento
    if(ant == NULL){    //insere elemento no inicio
        novo->prox = li;
        li = novo;
    }else{      //insere elemento no meio da lista
        novo->prox = ant->prox;
        ant->prox = novo;
    }
    
    return 1;
}

int main()  {

    return 0;
}