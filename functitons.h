#ifndef IA_P2_FUNCTITONS_H
#define IA_P2_FUNCTITONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:/Program Files/Graphviz/include/graphviz/gvc.h"
// LEMBRAR DE MUDAR O INCLUDE, CASO NECESSÁRIO

typedef struct noListaAresta
{
    char v[10]; // vertice alvo
    unsigned int peso; // peso da aresta
    struct noListaAresta *prox; // proximo elemento da lista
} ListaAresta;

typedef struct noListaVertice
{
    char v[10]; // o vertice
    struct noListaAresta *listaAresta; // lista de arestas saindo desse vertice
    struct noListaAresta *listaHeuristica; // lista de arestas com heuristica saindo desse vertice
    struct noListaVertice *prox; // proximo elemento da lista
} ListaVertice;

ListaAresta *alocaAresta();

ListaVertice *alocaVertice();

void desalocaAresta(ListaAresta *l);

void desalocaVertice(ListaVertice *l);

// Função que representa o grafo em um arquivo .dot e .png
void representaGrafo(ListaVertice *cabListaV, char *nomArq);

#endif //IA_P2_FUNCTITONS_H