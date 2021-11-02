#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
    int matricula;
    float Cr;
}TAluno;

typedef TAluno *Hash;  // Hash é um vetor qe sera alocado dinamicamente

void inicializa(Hash *tab, int m){
    int i;
    for(i=0; i<m; i++){
        tab[i] = NULL;
    }
}

TAluno *aloca(int mat,float cr){
    TAluno *novo = (TAluno*) malloc(sizeof(TAluno));
    novo->matricula = mat;
    novo->Cr = cr;
    return novo;
}

int hash(int mat, int m){
    return mat % m;
}

void insere(Hash *tab, int m, int mat,float cr){
    int ini = hash(mat,m);
    if(tab[ini] == NULL){
        tab[ini] = aloca(mat,cr);
    }else{
        printf("Posiçao ja esta ocupada");
    }

}

void imprime(Hash *tab, int m){
    int i;
    for (i=0; i<m; i++){
        printf("%d: \n",i);

        if(tab[i] != NULL){
            TAluno *p = tab[i];
            printf("\t mat: %d \t cr: %f \n",p->matricula, p->Cr);
        }
    }
    
}

int busca(Hash *tab,int m, int mat){
    int pos = hash(mat, m);
    if(tab[pos] != NULL){
        TAluno *resp = tab[pos];
        if(resp->matricula == mat){
            return pos;
        }
    }
    return -1;
}

void libera(Hash *tab, int m){
    int i;
    for(i=0; i<m; i++){
        if(tab[i]){
            free(tab[i]);
        }
    }
}

int main()  {
    int n,m;

    printf("Digite m ... (tamanho da tabela Hash) \n");
    scanf("%d", &m);
    printf("Digite n...  (quantidade de matriculas) \n");
    scanf("%d", &n);

    if((n <= 1) || (m <= 1))
        return 0;

    Hash *tab[m];
    inicializa(tab,m);
    
    int i,mat;
    float cr;
    for(i=0; i<n; i++){
        printf("Digite a matricula: ");
        scanf("%d",&mat);
        printf("Digite o coeficiente regular:");
        scanf("%d",&cr);
        insere(tab,m, mat, cr);
    }


    char resp;
    do{
        printf("Digite a matricula a ser procurada: \n");
        scanf("%d",&mat);
        int ind = busca(tab, m, mat);
        if(ind == -1){
            printf("Elemento nao encontrado !!");
        }else{
            TAluno *p = tab[ind];
            printf("%d \t %.2f \n",p->matricula, p->Cr);
        }
        printf("Quer continuar ?? \n");
        scanf("%c",&resp);
    }while((resp != 'N') && (resp != 'n'));
        imprime(tab,m);

        libera(tab,m);
}