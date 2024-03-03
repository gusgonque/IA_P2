#ifndef IA_P2_DFS_H
#define IA_P2_DFS_H

#include <stdio.h>
#include "grafoFuncoes.h"

typedef struct GrafoDFS {
    ListaVertice *u;    // Ponteiro para o vértice.
    char cor;           // Usado para indicar em que etapa se econtra aexploração do vértice.
                        // B: não explorado.
                        // C: explorado, mas ainda sem explorar os adjacentes.
                        // P: explorado e vértices adjacentes também explorados.

    char pi[10];           // Indica quem prescede esse nó no grafo de busca.
    int d;              // Timestamp de descoberta desse nó.
    int f;              // Timestamp de término da exploração desse nó e dos vértices adjacentes a esse.
    ListaAresta *listaArestaAdj;   // Ponteiro para a lista de arestas saindo desse nó;
}GrafoDFS;

// Visita o grafo na posição u, e visita os vértices adjacentes a ele, que estão com a cor = 'B'.
void DFS_visit(GrafoDFS *gDFS, char *u, char *pFim, int *t, int *pesoTotal, int nmrVertices);

// Inicia um GrafoDFS vazio, e a partir do vértice inicial v, percorre o grafo a partir do algoritmo de busca em profundidade.
void DFS(ListaVertice *grafo, char *pInicio, char *pFim);

#endif //IA_P2_DFS_H
