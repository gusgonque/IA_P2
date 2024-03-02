#ifndef IA_P2_GRAFOFUNCOES_H
#define IA_P2_GRAFOFUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:/Program Files/Graphviz/include/graphviz/gvc.h"
// LEMBRAR DE MUDAR O INCLUDE, CASO NECESSÁRIO


// U -> V

typedef struct noListaAresta
{
    struct noListaVertice *v; // vertice alvo
    int peso; // peso da aresta
    int heuristica; // heuristica da aresta
    struct noListaAresta *prox; // proximo elemento da lista
} ListaAresta;
typedef struct noListaVertice
{
    char u[10]; // o vertice
    struct noListaAresta *listaAresta; // lista de arestas sem heuristica saindo desse vertice
    struct noListaVertice *prox; // proximo elemento da lista
} ListaVertice;

ListaAresta *alocaAresta();

ListaVertice *alocaVertice();

void desalocaAresta(ListaAresta *l);

void desalocaVertice(ListaVertice *l);

// entrada: a lista qual se deseja fazer a procura e o objeto a ser encontrado
// saida: se existir na lista retorna a posição, caso contrario retorna -1
int existeVertice(ListaVertice *grafo, char *no);

// Retorna o nó inserido
ListaVertice * insereVertice(ListaVertice *grafo, char *no);

// Função que representa o grafo em um arquivo .dot e .png
//void representaGrafo(ListaVertice *grafo, char *nomArq);

ListaVertice * leArquivo(char *inicio, char *fim, ListaVertice *grafo, char *nomArq);

#endif //IA_P2_GRAFOFUNCOES_H