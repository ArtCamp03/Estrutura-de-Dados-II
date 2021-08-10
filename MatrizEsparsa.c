/*

UNIVERSIDADE FEDERAL DE MATO GROSSO
ESTRUTURA DE DADOS II
ALUNO: Artur Roza Campos


1 - Implemente as funções básicas de manipulação em uma matriz esparsa (representada pela estrutura de múltiplas listas ligadas): inserção; retorno de um valor; remoção; e impressão. Considere um arquivo como entrada para a inserção dos elementos da matriz.

2 - Implemente uma função que receba um número inteiro como parâmetro e multiplique este número a todos os valores diferentes de zero presente na matriz.

3 - Implemente uma função que retorne o somatório de todos os valores presentes na matriz.

4 - Implemente uma função que receba 2 matrizes e execute a soma dessas matrizes, retornando uma 3ª matriz como resultado.

5 - Implemente uma função que receba 2 matrizes e retira os elementos da primeira, onde há elementos na segunda.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>

typedef struct tempNo{
    float valor;
    int coluna;
    struct tempNo *prox;
}NO;

typedef NO* PONT;

typedef struct mat{
    PONT* A;
    int linhas;
    int colunas;
}MATRIZ;

// funçoes da Matriz Esparça
MATRIZ* inicializarMatriz(MATRIZ* m, int lin, int col);
bool Inserir_na_Matriz(MATRIZ* m,int lin, int col,float val);
float Busca_na_Matriz(MATRIZ* m, int lin, int col);
void Remocao_na_Matriz(MATRIZ* m, int lin, int col);
void Impressao_da_Matriz(MATRIZ* m);
float Impressao_de_Valor(MATRIZ* m, int lin, int col);
// Manipulaçao de arquivo
void CarregaArquivo(MATRIZ *m,char *nome);
// funçoes Complementares
float MultiplicaMatriz(MATRIZ* m,int lin,int col,int num);
float SomatorioMatriz(MATRIZ* m,int lin, int col);
MATRIZ* Soma_entre_Matrizes(MATRIZ* m, MATRIZ* m2);
MATRIZ* Retira_elementos(MATRIZ* m, MATRIZ* m2);


int main()  {
    int op = -1;
    int lin=0,col=0;
    int i=0,j=0,num=0;
    char nome[20],nome2[20];
    float val=0,result= 0.0;
    FILE *arq;
    MATRIZ *mat,*mat1,*mat2;

    mat = (MATRIZ*)malloc(sizeof(MATRIZ));

    printf("Nome do arquivo: \n");
    // Ex: Entrada
    scanf("%s",&nome);
    strcat(nome,".txt");
    //printf("%s \n",nome);

    printf("Numero de linhas e colunas matriz \n");
    scanf("%d",&lin); // numero de linhas
    scanf("%d",&col); // numero de colunas

    //printf("%d %d \n",lin, col); 

    // inicializa matrizes;
    mat = inicializarMatriz(mat,lin,col);

    // Carrega Matriz com elementos do arquivo
    CarregaArquivo(mat,nome);
    Impressao_da_Matriz(mat);

    while(op != 0 ){
        printf(" ************ MENU ************ \n");
        printf("1 - multiplicar todos os valores. \n");
        printf("2 - Somatorio da matriz. \n");
        printf("3 - Soma entre duas matrizes. \n");    
        printf("4 - Retirar elementos da primeira matriz. \n");
        printf("0 - Sair !! \n"); 
        printf("============================================ \n");  
        scanf("%d",&op);
        switch(op){
            case 1:
                printf("Multiplicao: \n");
                printf("Digite um numero para multiplicar: \n");
                scanf("%d",&num);
                
                for(i=0; i < lin; i++){
                    for(j=0; j < col; j++){
                        result = MultiplicaMatriz(mat,i,j,num);
                        printf(" %.2f [%d] [%d] \n",result,i,j);
                    }
                }
                
                break;
            case 2:
                printf("Somatorio: \n");
                result  = SomatorioMatriz(mat,lin,col);
                
                printf("Resultado do somatorio: %.2f \n",result);
                
                break;
            case 3:
            
                // A soma entre duas matrizes so existe se forem de mesma ordem como a entrada sera apenas de um arquivo os dados do arquivo sera duplicado para a segunda matriz de msm ordem. Com um segundo arquivo e msm ordem de matriz tambem é possivel deixarei esse codigo comentado.
                

                mat1 = (MATRIZ*)malloc(sizeof(MATRIZ));
                 // inicializa matrizes;
                mat1 = inicializarMatriz(mat1,lin,col);
                printf("Arquivo Matriz 2: \n");
                // digite o nome da arquivo onde esta a segunda matriz
                // ex: Entrada2
                scanf("%s",nome2);
                strcat(nome2,".txt");

                CarregaArquivo(mat1,nome2);

               printf("Soma entre duas Matrizes: \n");

               mat2 = Soma_entre_Matrizes(mat,mat1);
                    printf("Matriz 1: \n");
                    Impressao_da_Matriz(mat);
                    printf("Matriz 2: \n");
                    Impressao_da_Matriz(mat1);
                    printf("Matriz Somada: \n");
                    Impressao_da_Matriz(mat2);
                break;
            case 4:
                printf("Retirar elemento da Matriz: \n");

                    mat1 = (MATRIZ*)malloc(sizeof(MATRIZ));
                    // inicializa matrizes;
                    mat1 = inicializarMatriz(mat1,lin,col);
                    printf("Arquivo Matriz 2: \n");
                    // digite o nome da arquivo onde esta a segunda matriz
                    // ex: Entrada2
                    scanf("%s",nome2);
                    strcat(nome2,".txt");

                    CarregaArquivo(mat1,nome2);

                    printf("Soma entre duas Matrizes: \n");

                    mat2 = Retira_elementos(mat, mat1);
                    printf("Matriz 1: \n");
                    Impressao_da_Matriz(mat);
                    printf("Matriz 2: \n");
                    Impressao_da_Matriz(mat1);
                    printf("Matriz 1: \n");
                    Impressao_da_Matriz(mat2);
                break;
            case 0:
                printf("PROCESSO ENCERRADO ...");
                break;
            default:
                break;
        }
    }
    return 0;
}

void CarregaArquivo(MATRIZ *m,char nome[]){
	int i,j;
    float val; 
    FILE *arq;	

	arq = fopen(nome,"rt");
	
	if(arq == NULL){
		printf("\nErro no arquivo\n");
	}
	
	for(i=0; i<m->linhas; i++){
		for(j=0; j<m->colunas; j++){	
			fscanf(arq,"%f \n",&val);	
			Inserir_na_Matriz(m,i,j,val);
		}
	}
	fclose(arq);
    printf("Carregamento de arquivo concluido !! \n");
}

MATRIZ* inicializarMatriz(MATRIZ* m, int lin, int col){
    int i;
    m->linhas = lin;
    m->colunas = col;
    m->A = (PONT*)malloc(lin*sizeof(PONT));
    for(i=0; i < lin; i++){
        m->A[i] = NULL;
    }
    return m;
}

// Insere elemento na matriz
bool Inserir_na_Matriz(MATRIZ* m,int lin, int col,float val){
    if(lin<0 || lin >= m->linhas || col<0 || col >= m->colunas){
        return false;
    }
    PONT ant = NULL;
    PONT atual = m->A[lin];

    while (atual != NULL && atual->coluna<col){
        ant = atual;
        atual = atual->prox;
    }

    if(atual != NULL && atual->coluna == col){
        if(val == 0){ // se o valor é igual a azero
            if(ant==NULL){
                m->A[lin] = atual->prox;
            }else{
                ant->prox = atual->prox;
            } 
        free(atual);
        }else{ // no recebe valor
            atual->valor = val;
        } 
        
    }else if(val != 0){ // se valor é diferente de zero
        PONT novo = (PONT)malloc(sizeof(NO));
        novo->coluna = col;
        novo->valor = val;
        novo->prox = atual;
        if(ant == NULL){ // se no for o primeiro elemento da lista
            m->A[lin] = novo;
        }else{
            ant->prox = novo;
        } 
    }
    return true;    // se o valor for colocado

}

// Busca nó da matriz
float Busca_na_Matriz(MATRIZ* m, int lin, int col){
    if(lin<0 || lin>=m->linhas || col<0 || col >= m->colunas){ 
        return 0;   // se nao existe no
    } 
    
    PONT atual = m->A[lin];
    while(atual != NULL && atual->coluna < col){
        atual = atual->prox;
    }

    if(atual !=NULL && atual->coluna == col){
        return atual->valor;    // retorna o valor do no na posiçao
    }

    return 0;   // se o no nao for encontrado

}

// Remoçao de elemento
void Remocao_na_Matriz(MATRIZ* m, int lin, int col){
    PONT ant;
    if(lin<0 || lin>=m->linhas || col<0 || col >= m->colunas){ 
        printf("Posicao nao existe!! \n");
    } 
    
    PONT atual = m->A[lin];
    while(atual != NULL && atual->coluna < col){
        ant = atual;
        atual = atual->prox;
    }

    if(atual !=NULL && atual->coluna == col){
        ant = atual->prox;
        free(atual);
        atual = ant;
    }
    printf("Remocao concluida!! \n");
}

void Impressao_da_Matriz(MATRIZ* m){
	int i,j;

    PONT novo;
	for(int i=0;i<m->linhas;i++){
		for(int j=0;j<m->colunas;j++){
			printf(" [%.1f] ",Impressao_de_Valor(m,i,j));
		}
		printf("\n");
	}

}

float Impressao_de_Valor(MATRIZ* m, int lin, int col){

	if(lin < 0 || lin >= m->linhas || col < 0  || col >= m->colunas){
		return 0;
	}
	
	PONT atual = m->A[lin];
	while(atual != NULL && atual->coluna < col){
		atual = atual->prox;
	}
	if(atual != NULL && atual->coluna == col){
		return atual->valor;
	}else{
		return 0;
	}
}


float MultiplicaMatriz(MATRIZ* m,int lin, int col,int num){
    float result = 0;

    if(lin < 0 || lin >= m->linhas || col < 0 || col >= m->colunas){ 
        return 0;
    } 
    
    PONT atual = m->A[lin];
    while(atual != NULL && atual->coluna <= col){
        if(atual != NULL && atual->coluna == col){
            if(atual->valor == 0 ){ 
                return 0;
            }else if(atual->valor != 0){
                result = atual->valor * num;
            }
        }
        atual = atual->prox;
    }
    
    return result;
}

float SomatorioMatriz(MATRIZ* m,int lin, int col){
    float result = 0;
    int i,j;

    for(i=0;i<lin; i++){
         for(j=0;j<lin; j++){
             if(i < 0 || i >= m->linhas || j < 0 || j >= m->colunas){ 
                 return result;
                } 

            PONT atual = m->A[i];
            while(atual != NULL && atual->coluna < j){
                atual = atual->prox;
            }

            if(atual != NULL && atual->coluna == j){
                result += atual->valor;
            }
         }
    }

    return result;
}

MATRIZ* Soma_entre_Matrizes(MATRIZ* m, MATRIZ* m2){
    int i,j;
    float soma;
    MATRIZ* m3;
    m3 = (MATRIZ*)malloc(sizeof(MATRIZ));

    inicializarMatriz(m3,m->linhas,m->colunas);

    //verifica tamanho das matrizes
	if((m->linhas != m2->linhas) && (m->colunas != m2->colunas)){
		printf("Operaçao nao realizada \n");
        printf("Matrizes de tamanhos diferentes! \n");
		return 0;
	}
            
    for(i=0; i<m->linhas; i++){
		for(int j=0; j<m->colunas; j++){	
			soma = Impressao_de_Valor(m,i,j) + Impressao_de_Valor(m2,i,j);
			Inserir_na_Matriz(m3,i,j,soma);
		}
	}

    return m3;
}

MATRIZ* Retira_elementos(MATRIZ* m, MATRIZ* m2){
    int i,j;

    //verifica tamanho das matrizes
	if((m->linhas != m2->linhas) && (m->colunas != m2->colunas)){
		printf("Operaçao nao realizada \n");
        printf("Matrizes de tamanhos diferentes! \n");
        return 0;
	}

    for(i=0; i<m->linhas; i++){
		for(int j=0; j<m->colunas; j++){	
			if(Impressao_de_Valor(m2,i,j) != 0){
                Inserir_na_Matriz(m,i,j,0);             
            }
		}
	}
    return m;
}
