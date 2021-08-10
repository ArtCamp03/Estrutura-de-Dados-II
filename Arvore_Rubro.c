/*
UNIVERSIDADE FEDERAL DE MATO GROSSO
ESTRUTURA DE DADOS II
ALUNO: Artur Roza Campos

Implemente as funções básicas de manipulação em árvore rubro negra 
- inserção de uma valor, 
- busca de uma valor, 
- remoção de um valor, 
- impressão. 
Considere um arquivo como entrada para a inserção dos elementos na árvore.
*/

#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
//#include <stdbool.h>

#define VERM 1
#define PRETO 0


typedef struct No{
    int valor;
    int cor;
    struct No* esq;
    struct No* dir;
    struct No* pai;
}No;

//prototipo das principais funcoes Arvore Rubro Negra
No* cria_ArvRB();
No* insere_ArvRB(No* raiz, int valor);
No* insereNo(No* no, int valor, int* result);
int remove_ArvRB(No* raiz,int valor);
No* removeNo(No* no, int valor);
No* removeMenor(No* no);
No* procuraMenor(No* atual);
int busca_Valor(No* raiz,int valor);
void Imprime_emOrdem(No *raiz);
// Rotaçoes
No* rotacaoDireita(No* no);
No* rotacaoEsquerda(No* no);
// Balanceamento
No* dRotacaoEsqVerm(No* no);
No* dRotacaoDirVerm(No* no);
No* Balancear(No* no);
//Funçoes auxiliares
int cor(No* F);
No* MudaCor(No *F);
// Manipulaçao de arquivo
No* CarregaArqv(No* railz,char nome[20]);


int main(){
    // inicializando a arvore com Raiz igaual  a NULL
    int op = -1; 
    int val, Rno,resp;
    char nome[20];
    No* no;
    No* raiz = cria_ArvRB();

    printf("Nome do arquivo de entrada: \n");
    scanf("%s",nome);

    strcat(nome,".txt");
    no = CarregaArqv(raiz,nome);

    if(no == NULL){
        printf("Sistema encerrrado...\n");
        op = 0;
    }

    while(op != 0){
        printf(" *********** MENU *********** \n");
        printf("1 - Inserir elemento \n2 - Buscar Elemento \n3 - Remover elemento \n4 - Visualizar arvore \n0 - Sair\n");
        scanf("%d", &op);
         switch(op) {
            case 1:
                printf("****** Insercao ******\n\n");
                printf("Elemento a inserir:\n");
                scanf("%d", &val);

                no =  insereNo(no,val,&resp);
                if(no != NULL){
                    printf("Elemento inserido com sucesso! \n");
                }else{
                    printf("Erro ao inserir elemento \n");
                }
                break;
            case 2:
                printf("****** Busca de elemento ******\n\n");
                
                printf("Buscar elemento: \n");
                scanf("%d",&val);

                if(busca_Valor(no,val)){
                    printf("Elemento encontrado \n");
                }

                break;
            case 3:
                printf("****** Remocao ******\n\n");
                printf("Elemento a remover:\n");
                scanf("%d", &val);

                no = removeNo(no,val);
                if(no != NULL){
                    printf("Elemento removido! \n",val);
                }else{
                    printf("Falha na remocao !\n");
                }
                
                break;
            case 4:
                printf("****** Impressao ******\n\n");
                
                Imprime_emOrdem(no);

                break;
            case 0:
                printf("Sistema encerrrado...\n");
                op = 0;
                break;
            default:
                printf("Nao existe esta opcao.\n");
        }
                printf("************\n");
    }
    return 0;
}

No *cria_ArvRB(){
    No *raiz = (No*)malloc(sizeof(No));
    if(raiz != NULL){
        raiz->pai = NULL;
        raiz = NULL;
    }
    return raiz;
}

No* CarregaArqv(No* raiz,char nome[20]){
    FILE *arqv;
    arqv = fopen(nome,"rt");
    int valor;
    int result=0;
    No* no;
    if(!arqv){
        printf("Arquivo nao existe! \n");
        return 0;
    }
    no = raiz;
    while(fscanf(arqv,"%d",&valor) != EOF){
        if(no == NULL){
            no = insere_ArvRB(no,valor);
            printf("No %p valor: %d \n",no,valor);
        }else{
            no = insereNo(no,valor,&result);
        }
    }
    Imprime_emOrdem(no);

    if(no == NULL){
        printf("Carregamento do arquivo concluido! \n\n");
    }else{
        printf("Falha no carregamento do arquivo! \n\n");
    }

    return no;
}

No* insere_ArvRB(No *raiz, int valor){
    int result;
    // Responsavel pela busca do local deinserçao do No
    raiz = insereNo(raiz,valor,&result);
    
    if(raiz != NULL){
       raiz->cor = PRETO;
    }

    if(result == 1){
        printf("no inserido: %p\n",raiz);
    }else{
        printf("erro na insercao do no \n");
    }
    
    return raiz;

}

No* insereNo(No* no, int valor, int* result){

    if(no == NULL){
        No *novo = (No*)malloc(sizeof(No));
        if(novo == NULL){
            *result = 0;
            //printf("Erro na alocacao do No \n");
            return NULL;
        }
        novo->valor = valor;
        novo->cor = VERM;
        novo->dir = NULL;
        novo->esq = NULL;
        novo->pai = no;
        *result = 1;
        //printf("No criado com sucesso! \n");
        return novo;
    }

    if(valor == no->valor){
        *result = 0 ;
    }else{
        if(valor < no->valor){
            no->esq = insereNo(no->esq,valor,result);
            no->esq->pai = no;
        }else{
            no->dir = insereNo(no->dir,valor,result);
            no->dir->pai = no;
        }
    }

    if(cor(no->dir) == VERM && cor(no->esq) == PRETO){
        no = rotacaoEsquerda(no);
    }

     if(cor(no->esq) == VERM && cor(no->esq->esq) == VERM){
        no = rotacaoDireita(no);
    }

     if(cor(no->esq) == VERM && cor(no->dir) == VERM){
        no = MudaCor(no);
    }
    return no;
}

No *rotacaoDireita(No *no){
    No *Dir = no->esq;

    no->esq = Dir->dir;
    Dir->dir = no;
    Dir->cor = no->cor;
    no->cor = PRETO;

    return Dir;

}

No *rotacaoEsquerda(No *no) {
    No *Esq = no->dir;

    no->dir = Esq->esq;
    Esq->esq = no;
    Esq->cor = no->cor;
    no->cor = VERM;

    return Esq;
}

// Dupla rotaçao a esrquerda
No *dRotacaoEsqVerm(No *no){
    no = MudaCor(no);
    if(no->dir != NULL){
        if(cor(no->dir->esq) == VERM){
            no->dir = rotacaoDireita(no->dir);
            no = rotacaoEsquerda(no);
            no = MudaCor(no);
        }
    }
    return no;
}

// Dupla rotaçao a direita
No *dRotacaoDirVerm(No *no){
    no = MudaCor(no);
    if(no->esq != NULL){
        if(cor(no->esq->esq) == VERM){
            no = rotacaoDireita(no);
            no = MudaCor(no);
        }
    }
    return no;
}

No *Balancear(No *no){
   // No vermelho ,sempre filho a esquerda
   if(cor(no->dir) == VERM){
       no = rotacaoEsquerda(no);
   }
   // Filho da direita e neto da esquerda sao vermelhos
   if(no->esq != NULL && cor(no->dir) == VERM && cor(no->esq->esq) == VERM){
       no = rotacaoDireita(no);
   }
   // 2 filhos vermelhos, troca cor
   if(cor(no->esq) == VERM && cor(no->dir) == VERM){
       no = MudaCor(no);
   }
   return no;
}

int remove_ArvRB(No *raiz,int valor){
    if(busca_Valor(raiz,valor)){
        // funçao que busca o no a ser removido
        No* no = raiz;
        raiz = removeNo(no,valor);
        if(raiz != NULL){
            raiz->cor = PRETO;
        }
        return 1;
    }else{
        return 0;
    }
}

No* removeNo(No *no, int valor){
    if(valor < no->valor){
        if(cor(no->esq) == PRETO && cor(no->esq->esq) == PRETO){
            no = dRotacaoEsqVerm(no);
        }
        no->esq = removeNo(no->esq,valor);
    }else{
        if(cor(no->esq) == VERM){
            no = rotacaoDireita(no);
        }
        
        if(valor == no->valor && (no->dir == NULL)){
            free(no);
            printf("Retorna null \n");
            return NULL;
        }
        
        if(cor(no->dir) == PRETO && cor(no->dir->esq) == PRETO){
            no = dRotacaoDirVerm(no);
        }
        
        if(valor == no->valor){
            No* x = procuraMenor(no->dir);
            no->valor = x->valor;
            no->dir = removeMenor(no->dir);
        }else{
            no->dir = removeNo(no->dir,valor);
        }
    }
    
    return Balancear(no);
}

No *removeMenor(No *no){
    if(no->esq == NULL){
        free(no);
        return NULL;
    }

    if(cor(no->esq) == PRETO && cor(no->esq->esq) == PRETO){
        no = dRotacaoEsqVerm(no);
    }

    no->esq = removeMenor(no->esq);
    return Balancear(no);
}

No *procuraMenor(No *atual){
    No *no1 = atual;
    No *no2 = atual->esq;

    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int busca_Valor(No *raiz,int valor){

    if(raiz == NULL){
        printf("elemento nao encontrado \n");
        return 0;
    }

    No *atual = raiz;
    while(atual != NULL){
        if(valor == atual->valor){
            return 1;
        }

        if(valor > atual->valor){
            atual = atual->dir;
        }else{
            atual = atual->esq;
        }
    }
    printf("elemento nao encontrado! \n");
    return 0;
}

void Imprime_emOrdem(No *raiz) {
    if (raiz == NULL){
        return;
        //printf("arvore vazia! \n");
    }
	
    Imprime_emOrdem(raiz->esq);
    printf("No pai: %p\nNo: %p\nValor: %d, Cor: %d\nEsq: %p\nDir: %p\n\n",raiz->pai, raiz, raiz->valor, raiz->cor, raiz->esq, raiz->dir);
    Imprime_emOrdem(raiz->dir);
}


// Funçoes Auxiliares
int cor(No *F){
    if(F == NULL){
        return PRETO;
    }else{
        return F->cor;
    }
}

// inverte a cor do pai e de seus filhos
No* MudaCor(No *F){

    if(F == NULL){
        printf("Erro \n");
        return 0;
    }

    if(F != NULL){
        if(F->cor == PRETO){
            F->cor = VERM;
        }else{
            F->cor = PRETO;
        }
    }

    if(F->esq != NULL){
        if(F->esq->cor == PRETO){
            F->esq->cor = VERM;
        }else{
            F->esq->cor = PRETO;
        }
    }

    if(F->dir != NULL){
        if(F->dir->cor == PRETO){
            F->dir->cor = VERM;
        }else{
            F->dir->cor = PRETO;
        }
    }
    return F;
}