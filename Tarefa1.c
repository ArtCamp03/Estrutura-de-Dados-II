/* Universidade Federal de Mato Grosso
    Bacharelado em Ciencia da Computaçao
    Disciplina : Estrutura de Dados II
    Aluno: Artur Roza Campos
*/

// Lista Encadeada Simples

#include <stdlib.h>
#include <stdio.h>

typedef struct lista{
    int info;
    struct lista* prox;
}Lista;

// Iniciando Funçoes
int lista_vazia(Lista* li);
Lista* cria_lista();
Lista* insere_ini(Lista* li, int i);
void imprime(Lista* li);
Lista* insere_fim_recursivo(Lista*li, int i);
Lista* insere_ordenado_recursivo(Lista*li, Lista* ant, int i);
Lista* exclui(Lista* li, int i);
Lista* altera(Lista* li, int vantigo, int vnovo);

int main()  {
    // cria lista 
    Lista *list;

    // Cria lista
    list = cria_lista();

     // funçao verifica se a lista esta vazia;
    lista_vazia(list);

    // Insere no Inicio da Lista
    list = insere_ini(list,20);
    printf("Elemento inserido no inicio: %d\n",list->info);

    // Insere no Fim da Lista recursiva
    list = insere_fim_recursivo(list, 34);
    list = insere_fim_recursivo(list, 10);

    // Inserçao ordenada recursiva
    list = insere_ordenado_recursivo(list,list,23);
    
    // Exclui da Lista
    list = exclui(list,10);

    // Altera valor da lista
    list = altera(list,23,11);

    imprime(list);

    return 0;
}

// Verifica se a lista esta vazia
int lista_vazia(Lista* li){
    if(li == NULL){
        printf("Lista vaiza");
    }
    return 1;
}

// Funçao cria lista vazia 
Lista* cria_lista(){
    printf("Lista criada com sucesso !! \n");
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

    if(lista_vazia(li));

    for(p = li; p != NULL; p = p->prox){
        printf("info = %d \n", p->info);
    }
}

// funçao recursiva inserçao no Fim
Lista* insere_fim_recursivo(Lista* li, int i){    
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->info = i;
    novo->prox = NULL;

    // Encontra o fim
    if(li->prox == NULL){
        li->prox = novo;
    }else{
        // chama a funçao na proxima lista
        insere_fim_recursivo(li->prox,i);
    }  
    return li;
}

//Inserçao Ordenada Recursiva
Lista* insere_ordenado_recursivo(Lista* li, Lista* ant, int i){
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    Lista* p = li;
    if(p != NULL){
        if(p->info < i){
            novo->info = i;
            if(ant == NULL){
                novo->prox = p;
                p = novo;
            }else{
                novo->prox = ant->prox;
                ant->prox = novo;
            }
        }else{
            insere_ordenado_recursivo(p->prox,p,i);
        }
    }else{
        insere_ordenado_recursivo(p->prox,p,i);
    }
    return p;
}

// Exclui da Lista
Lista *exclui(Lista *li, int i){
    Lista *p;
    Lista *q;
    p = li;
    while(p->prox != NULL){
        q = p;
        p = p->prox;
        if(p->info == i){
            q->prox = p->prox;
            printf("%d excluido comsucesso \n",i);
        }        
    }
    return li;
}

// Altera lista
Lista *altera(Lista *li, int vantigo, int vnovo){
    Lista *p = li;
    while(p->prox != NULL){
        p = p->prox;
        if(p->info == vantigo){
            p->info = vnovo;
            printf("%d -> %d alterado com sucesso !! \n",vantigo,vnovo);
        }
    }  
    return li;
}