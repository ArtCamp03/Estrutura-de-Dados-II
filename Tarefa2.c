/*  BACHARELADO EM CIENCIA DA COMPUTAÇÃO  UFMT
    Artur Roza Campos
    Estrutura de Dados II

Trabalho 02 – Tabela Hash

Etapa 1:

Elabore um algoritmo que crie um arquivo de entrada com um conjunto de valores e suas respectivas chaves, para serem inseridos em uma tabela Hash. Este algoritmo recebe como parâmetro o número de elementos, o tipo das entradas e o nome do arquivo resultante.

Cada registro é posto em uma linha do arquivo e deve conter uma chave inteira com valor entre 0 e 1023, e um valor composto por 3 letras. Estes valores serão definidos aleatoriamente, mas garanta que não exitem chaves com valores repetidos.

São dois tipos de arquivos de entrada possíveis: 1) todas as chaves geradas têm valor par; 2) sem restrição.

Etapa 2:

Implemente uma tabela Hash, uma que trate as colisões com encadeamento externo. Desenvolva todas as funções necessárias para manipulação da estrutura (inserção, busca, etc).

Etapa 3:

Desenvolva um sistema para avaliação da função Hash. Implemente 2 funções Hash distintas. Este sistema irá utilizar uma tabela Hash de tamanho 100. A avaliação deverá executar um mesmo aquivo de entrada para cada função Hash implementada.

Para cada execução, contabilize o número de colisões que ocorreram.

Gere 10 entradas com 20, com 50 e 80 registros (total de 30 arquivos) diferentes que serão utilizadas nos testes. Em cada conjunto de 10 arquivos, 5 são do tipo 1 e 5 do tipo 2.

Ao final, elabore um relatório contendo a média do número de colisões entre os elementos para cada contexto avaliado (sugestão: utilize uma planilha eletrônica para tabular os resultados).
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

// estrutura tabela Hash
typedef struct Encade{
    int chave;
    //char Elemnt[3];
}Tab;
// vetor de alocaçao dinamica
typedef Tab *Hash;

// Estrutura para guarda dados de Saida
typedef struct Planilha{
    char nomeARQV[20];
    int chave;
    int posicao;
    int colisao;
    struct Planilha *prox;
}planilha;
// vetor de arquivos para  planilha
typedef planilha *ListaP;

// inicializando funçoes
// Cria Arquivo
int Cria_arqv(int num, int tipo, char nome[20]);
void Gera_Arq20(int num);
void Gera_Arq50(int num);
void Gera_Arq80(int num);
// Funçoes Hash
void CarregaHash(int tam,char entrd[20], int num,int tipo);
void inicia(Hash *tab, int m);
Tab *aloca(int chave);
int insere(Hash *tab, int num, int chave,int tipo);
void imprime(Hash *tab, int num);
int busca(Hash *tab, int num, int chave);
void libera(Hash *tab, int num);

int main()  {
    int num=100, entrd, op=-1, i=0;
    FILE *arqv;
    //char nome[20] = "EntrdHas";
    //char nome1[20] = "EntrdHas";
    // Tamanho da tabela 100;
    Tab *tabe[100];
    /*
    //numero de elementos do arquivo
    //printf("Digite o numero de elementos: \n");
    //scanf("%d", &num);

    //tipo de entrada
    //printf("Tipo: \n 1-chaves pares  2-sem restricao \n");
    //scanf("%d", &entrd);

    // arquiv de entrada Par
        strcat(nome, "_Par");
        strcat(nome, ".txt");
        
    // arquiv de entrada Sem Restriçao
        strcat(nome1, "_SemRestri");
        strcat(nome1, ".txt");
    */

    while(op != 0){
        printf("Carregar arquivos de entradas existentes? \n 1-Sim 2-Nao 0-Sair \n");
        scanf("%d",&op);
            switch(op){
        case 1:
            arqv = fopen("Arquivos.txt","r");
            char name[20];

            int tipo,tam;

            printf("Escolha o tipo Hash 1-tipo1 2-tipo2 0-sair\n");
            scanf("%d",&tipo);
            
            if(tipo != 0){
                inicia(tabe,num);
                printf("Carregando arquivos de entrada ... \n");
                int cont=0;
                /*
                while(fgets(name,sizeof(name),arqv) != NULL){
                    //printf("%s \n",name);
                    CarregaHash(tam,name,cont,tipo);
                    cont++;
                }
                */
               CarregaHash(20,"Arq20_0Par.txt",0,tipo);
               CarregaHash(20,"Arq20_5SemRes.txt",6,tipo);
               CarregaHash(50,"Arq50_0Par.txt",11,tipo);
               CarregaHash(50,"Arq50_5SemRes.txt",16,tipo);
               CarregaHash(80,"Arq80_0Par.txt",21,tipo);
               CarregaHash(80,"Arq80_5SemRes.txt",26,tipo);

            fclose(arqv);
            printf("Carregamento concluido \n");

            }
            
            break;
        case 2:
            printf("Gerando novos arquivos de entrada ... \n");
        
        /*
            // arquivo registros pares
            if(Cria_arqv(num,1, nome)){
                printf("Arquivo criado com sucesso!! %s \n",nome);
            }

            // arquivo registros semr restriçao
            if(Cria_arqv(num,2, nome1)){
                printf("Arquivo criado com sucesso!! %s \n",nome1);
            }
            */

           remove("Arquivos.txt");
            // crinado arquivo com 20 registros
                Gera_Arq20(20);
            // lst20 recebe cabeça do vetor com nomes dos arquivos de 20

            // crinado arquivo com 50 registros
                Gera_Arq50(50);
            // lst50 recebe cabeça do vetor com nomes dos arquivos de 50

            // crinado arquivo com 80 registros
                Gera_Arq80(80);
            // lst80 recebe cabeça do vetor com nomes dos arquivos de 80

            printf("Lista de arquivos carregada com sucesso !!!\n \n");
            break;
        case 0:
            printf("Sistema Encerrado! \n");
            break;
        default:
            printf("Opicao Invalida \n");
            break;
        }
    }
    
    return 0;
}

int hash1(int chave, int num){
    return chave % num;
}

int hash2(int chave){
    return chave / 10.5;
}

int Cria_arqv(int num, int tipo, char nome[]){
    int chave, element, cont, n;
    char c[2];
    // criaçao do arquivo
    FILE *arqv;
    srand(time(NULL));
    // nome do arquivo resultante
        arqv = fopen(nome, "w+");

        if(arqv == NULL){
        printf("ERRO! O arquivo não foi aberto!\n");
        return 0;
        }else{
            while (num > 0){
            // gerando valores aleatórios na faixa de 0 a 1023
            chave = rand() % 1023;
            cont = 0;
            while(cont < 3){
                element = rand() % 90;
                if (element > 64 && element < 91){
                    if (tipo == 1){
                        if (chave % 2 == 0){
                            c[cont] = element;
                        }else{
                            chave = chave / 2;
                            cont--;
                        }
                    }else if(tipo == 2){
                        c[cont] = element;
                    }else{
                        printf("Tipo Errado !!");
                    }
                    cont++;
                }
            }
            fprintf(arqv, "%d  %s \n", chave, c);
            num--;
            }
        }
        printf("//////");
    fclose(arqv);
    printf("\n");
    return 1;
}

// Inicializa
void inicia(Hash *tab, int m){
    int i;
    for (i = 0; i < m; i++){
        tab[i] = NULL;
    }
}

// Aloca
Tab *aloca(int chave){ //char letra[3]
    //int cont = 0;
    Tab *novo = (Tab *)malloc(sizeof(Tab));
    novo->chave = chave;
    /*while (cont < 3){
        novo->Elemnt[cont] = letra[cont];
        cont++;
    }
    */
    return novo;
}

// Insere na tabela
int insere(Hash *tab, int num, int chave,int tipo){
    int colisao = 0;
    int inic;
    if(tipo == 1){
        inic = hash1(chave, num);
    }else if(tipo ==2){
        inic = hash2(chave);
    }

    if(tab[inic] == NULL){
        tab[inic] = aloca(chave);
        return inic;
        //printf("Alocada \n");
    }else{
        return 1;
        //printf("posicao ja esta ocupada! \n");
    }

}

/*
// Imprime tabela
void imprime(Hash *tab, int num){
    int i;
    for (i = 0; i < num; i++){
        printf("%d: \n", i);
        if (tab[i] != NULL){
            Tab *p = tab[i];
            printf("\t chave: %d \t \n", p->chave);
        }
    }
}

// Busca elemento da tabela
int busca(Hash *tab, int num, int chave){
    int pos = hash(chave, num);
    if (tab[pos] != NULL){
        Tab *resp = tab[pos];
        if (resp->chave == chave){
            return pos;
        }
    }
    return -1;
}

// libera elemento
void libera(Hash *tab, int num){
    int i;
    for (i = 0; i < num; i++){
        if (tab[i]){
            free(tab[i]);
        }
    }
}
*/

// Gera arquivos

// Funçao pega 20 registros do arquivo e entrada
void Gera_Arq20(int num){
    FILE *arqv;
    arqv = fopen("Arquivos.txt","a+");
    char cont[2];
    int i;
    char ArqNome[10][20]; // vetor de nomes de Arquivos [qtd de posiçoes][tamanho]
    for (i = 0; i < 10; i++){
    char nome[20] = "Arq20_";
        itoa(i,cont,10);
        strcat(nome, cont);
        if (i < 5){    
            strcat(nome, "Par.txt");
            strcpy(ArqNome[i],nome);
            Cria_arqv(num,1,nome);
        }else if (i >= 5){
            strcat(nome, "SemRes.txt");
            strcpy(ArqNome[i],nome);
            Cria_arqv(num,2,nome);
        }
        fprintf(arqv,"%s\n",ArqNome[i]);
    }
    fclose(arqv);
    //printf("Processo Arq20 Concluido !! \n");
}

// Funçao pega 50 registros do arquivo e entrada
void Gera_Arq50(int num){
    FILE *arqv;
    arqv = fopen("Arquivos.txt","a+");
    char cont[2];
    int i;
    char ArqNome[10][20]; // vetor de nomes de Arquivos [qtd de posiçoes][tamanho]
    for (i = 0; i < 10; i++){
    char nome[20] = "Arq50_";
        itoa(i,cont,10);
        strcat(nome, cont);
        if (i < 5){
            strcat(nome, "Par.txt");
            strcpy(ArqNome[i],nome);
            Cria_arqv(num,1,nome);
        }else if (i >= 5){
            strcat(nome, "SemRes.txt");
            strcpy(ArqNome[i],nome);
            Cria_arqv(num,2,nome);
        }
        fprintf(arqv,"%s\n",ArqNome[i]);
    }
        fclose(arqv);
    //printf("Processo Arq50 Concluido !! \n");
}

// Funçao pega 80 registros do arquivo e entrada
void Gera_Arq80(int num){
    FILE *arqv;
    arqv = fopen("Arquivos.txt","a+");
    char cont[2];
    int i;
    char ArqNome[10][20]; // vetor de nomes de Arquivos [qtd de posiçoes][tamanho]

    for (i = 0; i < 10; i++){
    char nome[20] = "Arq80_";
        itoa(i,cont,10);
        strcat(nome, cont);
        if (i < 5){
            strcat(nome, "Par.txt");
            strcpy(ArqNome[i],nome);
            Cria_arqv(num,1,nome);
        }else if (i >= 5){
            strcat(nome, "SemRes.txt");
            strcpy(ArqNome[i],nome);
            Cria_arqv(num,2,nome);
        }
        fprintf(arqv,"%s\n",ArqNome[i]);
    }
    fclose(arqv);
    //printf("Processo Arq80 Concluido !! \n");
}

// Carrega arquivos de entradas, ja existentes 
void CarregaHash(int tam,char entrd[], int num,int tipo){
    Tab *tabe[100]; 
    char vetc[10];
    int cont=0,x,i=0;
    int result=0, posicao[100],colisao[100];
    FILE *arqv1;
    arqv1 = fopen(entrd,"r");

    inicia(tabe,tam);
    
    if(arqv1 == NULL){
        printf("problema na abertura %s \n", entrd);
    }else{
        int qtd=0;
        printf("Arqv : %s \n",entrd);
        while(fscanf(arqv1,"%d",&x) != EOF){
        cont = strlen(fgets(vetc,10,arqv1));

        if(num < 5){
            tam = 20;
        }else if(num >=5 && num < 10){
            tam = 20;
        }else if(num >=10 && num < 15){
            tam = 50;
        }else if(num >=15 && num < 20){
            tam = 50;
        }else if(num >=20 && num < 25){
            tam = 80;
        }else if(num >=25 && num < 30){
            tam = 80;
        }

        result =  insere(tabe,tam,x,tipo);
        posicao[i] = 0;
        colisao[i] = 0;

        if(result > 1){
            posicao[i] = result;
            colisao[i] = 0;
        }else if(result == 1){
            posicao[i] = result;
            colisao[i] = 1;
            qtd ++;
        }

        //fuçao que pula linhas no arquivo
        fseek(arqv1,0 * cont,SEEK_CUR);
        i++;
        }
        printf("colisao %d \n",qtd);
    }

    fclose(arqv1);
    /*
    float coliPar = 0, coliImpar = 0;
    // Grava Dados de Saida no Arquivo
    printf("RELATORIO DE COLISOES \n");
        if(num < 5){
            printf("Arquivos Pares\n");
            printf("%s \n",entrd);
            for(i=0;i<20 ;i++){
                printf("posicao: %d ",posicao[i]);
                printf("colisao: %d \n",colisao[i]);
                coliImpar += colisao[i];
            }
            printf(" Media de colisoes Arq20: %d\n",coliImpar/20);
        }else if(num >= 5 && num < 10){
            printf("Arquivos Sem Restricao \n");
            printf("%s \n",entrd);
            for(i=0;i<20 ;i++){
                printf("posicao: %d ",posicao[i]);
                printf("colisao: %d \n",colisao[i]);
                coliImpar += colisao[i];
            }
            printf(" Media de colisoes Arq20: %d\n",coliImpar/20);
        }else if(num >= 10 && num < 15){
          printf("Arquivos Pares\n");
            printf("%s \n",entrd);
            for(i=0;i<50 ;i++){
                printf("posicao: %d ",posicao[i]);
                printf("colisao: %d \n",colisao[i]);
                coliImpar += colisao[i];
            }
            printf(" Media de colisoes Arq50: %d\n",coliImpar/50);
        }else if(num >= 15 && num < 20){
            printf("Arquivos Sem Restricao \n");
            printf("%s \n",entrd);
            for(i=0;i<50 ;i++){
                printf("posicao: %d ",posicao[i]);
                printf("colisao: %d \n",colisao[i]);
                coliImpar += colisao[i];
            }
            printf(" Media de colisoes Arq50: %d\n",coliImpar/50);
        }else if(num >= 20 && num < 25){
            printf("Arquivos Pares\n");
            printf("%s \n",entrd );
            for(i=0;i<80 ;i++){
                printf("posicao: %d ",posicao[i]);
                printf("colisao: %d \n",colisao[i]);
                coliImpar += colisao[i];
            }
            printf(" Media de colisoes Arq80: %d\n",coliPar/80);
        }else if(num >= 25 && num < 30){
            printf("Arquivos Sem Restricao \n");
            printf("%s \n",entrd);
            for(i=0;i<80 ;i++){
                printf("posicao: %d ",posicao[i]);
                printf("colisao: %d \n",colisao[i]);
                coliImpar += colisao[i];
            }
            printf(" Media de colisoes Arq80: %d\n",coliImpar/80);
        }
        printf("Processo Finalizado!! \n\n\n");
        */
}