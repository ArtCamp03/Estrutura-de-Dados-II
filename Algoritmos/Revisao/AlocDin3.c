// calculando amedia de n numeros reais 

#include <stdio.h>
#include <stdlib.h>

float media(int n, float *v){
    int i;
    float s = 0.0;
    for(i=0; i<n; i++)
        s += v[i];

    return s/n;
}

int main()  {
    int i,n;
    float *v;
    float med;

    scanf("%d",&n); //leitura do numeor de n valores
    v = (float*) malloc(n * sizeof(float));

    if(v == NULL){
        printf("MNemoria insuficiente");
        return 1;
    }

    for(i=0; i<n; i++)
        scanf("%f", &v[i]);

    med = media(n,v); //chamna a funçao qe calcula a media
    printf("Media igual :%.2f \n ", med);

    free(v); //libera memoria;

    return 0;
}