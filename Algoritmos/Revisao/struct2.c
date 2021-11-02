// captura e imprime as coordenadas de um ponto qualquer
#include <stdio.h>
#include <stdlib.h>

struct ponto{
    float x;
    float y;
};

//ponteiro para acessar as estruturas 
/*
  struct ponto *pp;   
  ...
  *(pp).x = 12.0;  fomras esquivalentes de acessar um valor no ponto x
  *(pp).y = 10.0;
*/

//Alocaçao Dinamica de Estruturas
/*
    struct ponto* p;
    p = (struct ponto*) malloc(sizeof(struct ponto));
    p.x = 12.0;
*/

//Mudando nome da estrutura
/*
    typedef struct ponto pont; //pont representa a estrutura ponto
    typedef struct ponto *pont; // *pont representa o tipo de ponteiro para a estrutra ponto
*/

// MANEIRAS PRATICAS
/*
    struct ponto{
        float x;
        float y;
    };
    typedef struct ponto p;
*/

/*
    typedef struct ponto{
        float x;
        float y;
    }p ;
*/

int main()  {
    struct ponto p;
    printf("Digite as coordenadas dos pontos (x,y \n");
    scanf(" %f %f", &p.x, &p.y);
    printf("O ponto fornecido foi (%.2f,%.2f) \n",p.x, p.y);

    return 0;
}

