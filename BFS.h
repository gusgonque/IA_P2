#ifndef PAA_TRAB2_BFS_H
#define PAA_TRAB2_BFS_H

#include <stdio.h>
#include "grafoFuncoes.h"

typedef struct GrafoBFS {
    ListaVertice *u;   // Ponteiro para o Grafo usado.
    char cor;   // Usado para indicar em que etapa se econtra aexploração do vértice.
    // B: não explorado.
    // C: explorado, mas ainda sem explorar os adjacentes.
    // P: explorado e vértices adjacentes também explorados.

    char pi[10];     // Indica quem prescede esse nó no grafo de busca.
    int d;      // Distância do vértice inicial até esse vértice.
    int f;      // Timestamp de término da exploração desse nó e dos vértices adjacentes a esse.
    ListaAresta *listaArestaAdj; // Ponteiro para a lista de vértices adjacentes a esse;
}GrafoBFS;

// Remove a cabeça da lista de vértices
// Retorna a nova cabeça da lista.
ListaVertice *removeCabecaListaVertices (ListaVertice *l);

// Busca um vértice no grafo, pelo nome do vértice.
// Retorna a posição do vértice no grafo.
int BFS_BuscaVertice (GrafoBFS *gBFS, char *no, int nmrVertices);

// Faz a visita pelo algoritmo BFS
// Recebe o grafo, o ponto inicial e o ponto final da busca.
void BFS_visit(ListaVertice *grafo, char *pontoInicial, char *pontoFinal);

#endif //PAA_TRAB2_BFS_H
