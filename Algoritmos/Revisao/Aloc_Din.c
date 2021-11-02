// Alocaçao Dinamica
// sizaof(tipo)  funçao qe pegar tipo qe vaiu ser alocado
// malloc(tamanho) funçao qe alocar a regia da memoria

int main()  {
    int *p;
    // alocaçao dinamica de um inteiro de 10 elementos
    p = (int*) malloc(10 * sizeof(int));

    if(p == NULL){
        printf("Nao a memoria suficiente");

    }
    
    return 0;
}