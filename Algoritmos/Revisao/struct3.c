// Exemplo com estruturas aninhadas

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ponto{
    float x;
    float y;
}Ponto ;

typedef struct circulo{
    float p;    //centro do circulo
    float r;    //raio do circulo
}Circulo;

/* funçao para calcular distancoa entre dois pontos
    entrada: ponteiros para ps pontos 
    saida:  distancia correspondente
*/

float distancia(Ponto* p, Ponto* q){
    float d = sqrt((q->x - p->x) * (q->x - p->x) + (q->y - p->y) * (q->y - p->y));
    return d;
}

/* Funçao qe determina se o ponto esta ou nao dentro de um circulo
    Entrada: ponteiros para um circulo e um ponto
    Saida: 1= ponto dentro do circulo
           0= ponto fora do circulo
*/

int inteiro(Circulo* c, Ponto* p){
    float d = distancia(&c->p, p);
    return (d < c->r);
}

int main()  {
    Circulo c;
    Ponto p;
    return 0;
    printf("Digite as coordenadas do centro e raio do circulo \n");
    scanf("%f %f %f ", &c.p.x,&, &c.p.y, &c.r);
    printf("Digite as coordenadas do ponto \n");
    scanf("%f %f", &p.x, &p.y);
    printf("Pertece ao interior %d \n", inteiro(&c,&p));
    return 0;
}