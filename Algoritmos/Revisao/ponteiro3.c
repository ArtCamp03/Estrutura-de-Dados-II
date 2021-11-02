//calculo da media de 10 numeros reais

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
    float v[10];
    float med;
    int i;

    for(i=0; i<10; i++)
        scanf("%f", &v[i]);
    
    med = media(10,v);
    printf("media= %.2f \n",med);
    return 0;
}