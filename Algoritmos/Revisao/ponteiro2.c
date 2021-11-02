#include <stdio.h>
#include <stdlib.h>

void troca(int *px, int *py){
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}

int main()  {
    int a = 5, b= 7;
    troca(&a, &b);   //passando os endereços das variaveis

    printf("valor de a = %d, valor b= %d \n", a,b);
    return 0;
}