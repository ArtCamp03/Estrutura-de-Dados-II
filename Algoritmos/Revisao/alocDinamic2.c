#include <stdio.h>
#include <stdlib.h>

int main()  {
    float v[10];
    float med = 0.0;

    int i;
    // leitura dos valores

    for(i=0; i<10 ; i++)
    scanf("%f", &v[i]);
    // Calculo da media

    for(i=0; i<10 ; i++)
        med = med + v[i];
    med = med/10;
    // exibiçao do resultado

    printf("Media = %f \n",med);

    return 0;
}