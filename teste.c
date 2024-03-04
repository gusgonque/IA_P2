#include <stdio.h>
#include "grafoFuncoes.h"
#include "BFS.h"
#include "DFS.h"
#include "guloso.h"

int main(){
    char pontoInicial[20];
    char pontoFinal[20];
    ListaVertice *grafo = NULL;
    grafo = lerArquivo(pontoInicial, pontoFinal, grafo, "../dados.txt"); // Estou mudando o caminho devido à minha IDE


    printf("pI = %s\n", pontoInicial);
    printf("pF = %s\n", pontoFinal);
    printf("Primeiro vertice do grafo = %s\n", grafo->u);

    ListaVertice *auxInicio = grafo;
    int j = existeVertice(auxInicio, pontoInicial);
    for (int i = 0; i < j; ++i) {
        auxInicio = auxInicio->prox;
    }

    ListaVertice *auxFim = grafo;
    j = existeVertice(auxFim, pontoFinal);
    for (int i = 0; i < j; ++i) {
        auxFim = auxFim->prox;
    }

    guloso(auxInicio, auxFim);

}