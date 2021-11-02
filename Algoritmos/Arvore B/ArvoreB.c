#include <stdio.h>
#include <stdlib.h>

const int d = 2;

typedef struct No{
    int m; //quantidade de chaves
    int *s; // array de chaves
    struct No *pont_pai;
    struct No **p;
}TNo;

TNo *inicializa(){
    return NULL;
}

TNo *cria(){
    TNo *novo = (TNo*) malloc(sizeof(TNo));
    novo->m = 0;
    novo->pont_pai = NULL;
    novo->s = (int*)malloc(sizeof(int*) * (d*2));
    novo->p = (TNo**)malloc(sizeof(TNo*) * (d * 2) + 1);
    for(int i=0;i < (d*2+1);i++){
        novo->p[i] = NULL;
    }
    return novo;
}

TNo *busca(TNo *no,int ch){
    if(no != NULL){
        int i=0;
        while(i<no->m && ch> no->s[i]){
            i++;
        }
        if(i< no->m && ch==no->s[i]){
            return no;
        }else if(no->p[i] != NULL){
            return busca(no->p[i],ch);
        }else{
            return no;
        }
    }else{
        return NULL;
    }
}

TNo *particiona(TNo *raiz,TNo *P,int ch, TNo *pt){
    TNo *Q = cria();
    Q->m = d;
    Q->pont_pai = P->pont_pai;

    int pos = -1;
    for(int i =0; i < P->m; i++){
        if(ch > P->s[i]){
            pos = i + 1;
        }
    }

    if(pos == -1){
        // a chave a ser inserida e a menor de todas , logo sera inserida na posiçao 0.
        pos = 0;
    }

    int chave_d;
    TNo *pt_chave_d = 0;

    if(pos != d && pos < d){
        chave_d = P->s[d - 1];
    }else if(pos != d){
        chave_d = P->s[d];
    }else{
        chave_d = ch;
    }

    int i = (d*2) - 1;
    int j = (d - 1);

    while(j >= 0){
        if(j != pos - d - 1){
            Q->s[j] = P->s[i];
            Q->p[j+1] = P->p[i+1];
            i--;
        }else{
            //insere chem Q na posicao correta
            Q->s[j] = ch;
            Q->p[j+1] = pt;
        }
        j--;
    }

    Q->p[0] = P->p[d];
    j = d;
    while(i > pos){
        P->s[i] = P->s[i-1];
        P->p[i+1] = P->p[i];
        i--;
    }
    if(pos <= d){
        P->s[pos] = ch;
        P->p[pos + 1] = pt;
    }
    P->m = d;
    TNo *pai = insere(P->pont_pai,0,chave_d,pt_chave_d);

    if(P->pont_pai == NULL){
        P->pont_pai = pai;
        Q->pont_pai = pai;
        pai->p[0] = P;
        pai->p[1] = Q;
    } 
    raiz = pai;
    return raiz;
}

TNo *insere(TNo *raiz,int folha, int ch,TNo *pt){
    TNo *no;
    if(folha){
        no = busca(raiz,ch);
        if(no != NULL){
            for(int i=0; i< no->m;i++){
                if(no->s[i] == ch){
                    return raiz;
                }
            }
        }
    }else{
        no = raiz;
    }
    if(raiz == NULL){
        raiz = cria();
        raiz->s[0] = ch;
        raiz->m = 1;
        //atualzia raiz da arvore
        return raiz;
    }else{
        if(no->m == (2*d)){
            raiz = particiona(raiz,no,ch,pt);
        }else{
            int i = no->m;
            while(i>=0 && ch < no->s[i - 1]){
                no->s[i] = no->s[i - 1];
                no->p[i + 1] = no->p[i];
                i++;
            }
            if(i == -1){
                i = 0;
            }
            no->s[i] = ch;
            no->p[i+1] = pt;
            no->m++;
        }
    }
}

void imprime(TNo *a,int nivel){
    if(a != NULL){
        if(nivel >= 0){
            printf("Nivel %d:\n",nivel);
        }
        for(int i=0;i < a->m; i++){
            printf("%d",a->s[i]);
        }
        printf("\n");
        //imprime filhos recursivamente
        if(a->p[0] != NULL){
            for(int i=0;i<=a->m;i++){
                imprime(a->p[i],nivel+1);
            }
        }
    }
}

int main(){
    TNo *raiz = inicializa();

    raiz = insere(raiz,1,10,NULL);
    raiz = insere(raiz,1,20,NULL);
    raiz = insere(raiz,1,15,NULL);
    raiz = insere(raiz,1,11,NULL);
    raiz = insere(raiz,1,6,NULL);
    raiz = insere(raiz,1,3,NULL);

}