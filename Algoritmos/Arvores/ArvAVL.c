#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct sNoA
{
    int chave;
    int fb;        // fator de balanceamento
    int h;
    struct sNoA* esq;
    struct sNoA* dir;
}TNoA;


int maior(int x, int y){
    if( x > y)
        return x;
    else
        return y;
}

int altura_NO(TNoA *no){
    if( no == NULL)
        return -1;
    else
        return no->h;
}

int fatorBalanceamento_NO(TNoA *no){
    return (altura_NO(no->dir) - altura_NO(no->esq));
}

TNoA* rotacao_direita(TNoA* pt){
    TNoA *ptu;
    ptu        = pt->esq;
    pt->esq        = ptu->dir;
    ptu->dir     = pt;
    pt->h         =   maior( altura_NO(pt->esq),altura_NO(pt->dir))+1;
    ptu->h         =     maior( altura_NO(ptu->esq), pt->h) +1 ;
    pt             = ptu;
    return pt;
}

TNoA* rotacao_esquerda(TNoA* pt){
    TNoA *ptu;
    ptu            = pt->dir;
    pt->dir        = ptu->esq;
    ptu->esq     = pt;
    pt->h         = maior( altura_NO(pt->esq),altura_NO(pt->dir))+1;
    ptu->h         =     maior( altura_NO(ptu->dir), pt->h) +1 ;
    pt             = ptu;
    return pt;
}

TNoA* rotacao_dupla_direita(TNoA* pt){
    pt->esq    = rotacao_esquerda(pt->esq);
    pt         = rotacao_direita(pt);
    return pt;
}

TNoA* rotacao_dupla_esquerda(TNoA* pt){
    pt->dir = rotacao_direita(pt->dir);
    pt         = rotacao_esquerda(pt);
    return pt;
}

TNoA* insere(TNoA *no,int chave){
    TNoA* u;
    
    if(no == NULL){
        no        = (TNoA *) malloc(sizeof(TNoA));
        no->chave    = chave;
        no->esq     = no->dir = NULL;
        no->h        = 0;
        no->fb         = 0;
    }else if(chave < (no->chave)){
        no->esq    = insere(no->esq, chave);
        no->h     = no->esq->h + 1;
        no->fb     = fatorBalanceamento_NO(no);
        
        if (no->fb <= -2){
            
            u = no->esq;        /* Recebe filho a esquerda */
            u->fb = fatorBalanceamento_NO(u);

            if (u->fb == -1){        /* Caso de sinais iguais e negativos: RD*/
                printf("RSD(%d)\n",no->chave);
                no = rotacao_direita(no);

            }
            else{    /* Caso de sinais diferentes: Rotacao dupla direita */
                printf("RDD(%d)\n",no->chave);
                no = rotacao_dupla_direita(no);
            }

            no->fb = 0;
        }
    
        
    }else if(chave > (no->chave)){
        
        no->dir    = insere(no->dir, chave);
        no->h     = no->dir->h + 1;
        no->fb     = fatorBalanceamento_NO(no);
        
        if (no->fb >= 2){
            
            u = no->dir;        /* Recebe filho a esquerda */
            u->fb = fatorBalanceamento_NO(u);

            if (u->fb == 1){        /* Caso de sinais iguais e negativos: RD*/
                printf("RSD(%d)\n",no->chave);
                no = rotacao_esquerda(no);

            }
            else{    /* Caso de sinais diferentes: Rotacao dupla direita */
                printf("RDD(%d)\n",no->chave);
                no = rotacao_dupla_esquerda(no);
            }

            no->fb = 0;
        }
        
    }else {
        printf("Insercao invalida\n");
        exit(1);
    }
    
    return no;
    
}

void imprime(TNoA* no, int tab){

    if(no!=NULL){
        tab += 10;
        imprime(no->dir,tab);
        printf("\n");
        for (int i = 10; i < tab; i++)
              printf(" ");

        printf("%d (%d)\n",no->chave,no->h);

        imprime(no->esq,tab+2);
    }
}

int main(void){

    TNoA *tree;
    
    tree = NULL;
    
    tree = insere(tree, 50);
    tree = insere(tree, 40);
    tree = insere(tree, 30);
    tree = insere(tree, 45);
    tree = insere(tree, 47);
    tree = insere(tree, 55);    
    tree = insere(tree, 56);
    tree = insere(tree, 1);
    tree = insere(tree, 2);
    imprime(tree,0);
    
    return 0;
}
