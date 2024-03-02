#include <stdio.h>
#include "grafoFuncoes.h"

int main(){
    char pontoInicial[20];
    char pontoFinal[20];
    ListaVertice *grafo = NULL;
    grafo = leArquivo(pontoInicial, pontoFinal, grafo, "../exemplo.txt"); // Estou mudando o caminho devido à minha IDE


    printf("pI = %s\n", pontoInicial);
    printf("pF = %s\n", pontoFinal);
    printf("Primeiro vertice do grafo = %s\n", grafo->u);
    while (grafo != NULL)
    {
        printf("no = %s\n", grafo->u);
        while (grafo->listaAresta != NULL)
        {
            printf("aresta = %s, peso = %d , heuristica = %d\n", grafo->listaAresta->v->u, grafo->listaAresta->peso, grafo->listaAresta->heuristica);
            grafo->listaAresta = grafo->listaAresta->prox;
        }
        grafo = grafo->prox;
    }


}

