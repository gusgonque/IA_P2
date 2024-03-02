#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafoFuncoes.h"

int main(){
    char pontoInicial[20];
    char pontoFinal[20];
    ListaVertice *grafo;
    grafo = alocaVertice();
    leArquivo(pontoInicial, pontoFinal, grafo, "exemplo.txt");


    printf("pI = %s\n", pontoInicial);
    printf("pF = %s\n", pontoFinal);


}

