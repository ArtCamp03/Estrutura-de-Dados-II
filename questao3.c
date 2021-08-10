#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

#define maxV 1024
#define BRANCO 0
#define CINZA 1
#define PRETO 2

static int dist[maxV], cor[maxV], pred[maxV];

int *vetor;
int inicio,fim;

typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia{
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice{
    
    ADJACENCIA *cab;
}VERTICE;


typedef struct grafo{
    int vertices;
    int arestas;
    VERTICE *adj;
}GRAFO;


/* Criando um grafo */
GRAFO *criarGrafo(int v){
    GRAFO *g = (GRAFO *) malloc(sizeof(GRAFO));
    
    g->vertices = v;
    g->arestas  = 0;
    g->adj      = (VERTICE *) malloc(v*sizeof(VERTICE));
    
    for(int i=0; i<v; i++){
        g->adj[i].cab = NULL;
    }
    
    return g;
}

ADJACENCIA *criarAdj(int v, int peso){
    ADJACENCIA *temp = (ADJACENCIA *) malloc(sizeof(ADJACENCIA));
    temp->vertice   = v;
    temp->peso      = peso;
    temp->prox      = NULL;
    return temp;
}


bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p){
    
    if(!gr)        
        return(false);
    if( (vf < 0) || (vf>= gr->vertices))
        return (false);
    if( (vi < 0) || (vi>= gr->vertices))
        return (false);
    
    ADJACENCIA *novo = criarAdj(vf,p);
    
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab = novo;
    
    
    ADJACENCIA *novo2 = criarAdj(vi,p);
    novo2->prox = gr->adj[vf].cab;
    gr->adj[vf].cab = novo2;
    
    gr->arestas++;
    
    return true;
}


void imprime(GRAFO *gr){
    
    printf("vertices %d. Arestas: %d \n", gr->vertices, gr->arestas);
    
    for(int i=0; i < gr->vertices; i++){
        printf("v %d", i);
        ADJACENCIA *ad = gr->adj[i].cab;
        while(ad){
            printf(" adj[%d,%d]", ad->vertice, ad->peso);
            ad = ad->prox;
        }
        
        printf("\n");
    }
}

void init(int maxN){
    vetor = (int *) malloc(maxN*sizeof(int));
    inicio = 0;
    fim = 0;
}


int empty(){
    return inicio == fim;
}

void put(int item){
    vetor[fim++] = item;
}

int get(){
    return vetor[inicio++];
}

void funcaox(GRAFO *gr, int raiz){

    int u;
    init(gr->vertices);

    for(int v=0; v < gr->vertices; v++){
        dist[v] = maxV;
        cor[v] = BRANCO;
        pred[v] = -1;
    }

    dist[raiz] = 0;
    cor[raiz] = CINZA;
    pred[raiz] = -1;

    put(raiz);

    while(!empty()){

        u = get();
        ADJACENCIA *v = gr->adj[u].cab;
        while(v){
            if(cor[v->vertice] == BRANCO){
                dist[v->vertice] = dist[u]+1;
                pred[v->vertice] = u;
                cor[v->vertice] = CINZA;

                put(v->vertice);
            }
            v = v->prox;
        }
        cor[u] = PRETO;
    }
}


void imprime2(GRAFO *gr){
    for(int v=0; v < gr->vertices; v++){
        printf("(%d,%d)\n",pred[v],v);
    }
}
int main(){
    
    GRAFO *gr = criarGrafo(12);
    
    criaAresta(gr,0,1,1);
    criaAresta(gr,0,2,1);
    criaAresta(gr,1,3,1);
    criaAresta(gr,1,6,1); 
    criaAresta(gr,1,7,1);
    criaAresta(gr,2,3,1);
    criaAresta(gr,2,4,1);
    criaAresta(gr,3,4,1);
    criaAresta(gr,3,8,1);
    criaAresta(gr,3,9,1);
    criaAresta(gr,4,9,1);
    criaAresta(gr,4,8,1);
    criaAresta(gr,8,9,1);
    criaAresta(gr,6,7,1);
    criaAresta(gr,6,10,1);
    criaAresta(gr,5,11,1);
    imprime(gr);
    funcaox(gr,0);
    printf("impressao: ");
    imprime2(gr);
    return 0;
}