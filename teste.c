#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafoFuncoes.h"

int main(){
    char pontoInicial[20];
    char pontoFinal[20];
    ListaVertice *grafo = NULL;
    grafo = leArquivo(pontoInicial, pontoFinal, grafo, "../exemplo.txt"); // Estou mudando o caminho devido à minha IDE


    printf("pI = %s\n", pontoInicial);
    printf("pF = %s\n", pontoFinal);
    printf("Primeiro vertice do grafo = %s\n", grafo->v);


}

