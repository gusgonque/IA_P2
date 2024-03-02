#ifndef IA_P2_GRAFOFUNCOES_H
#define IA_P2_GRAFOFUNCOES_H

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
    struct noListaAresta *listaAresta; // lista de arestas sem heuristica saindo desse vertice
    struct noListaAresta *listaHeuristica; // lista de arestas com heuristica saindo desse vertice
    struct noListaVertice *prox; // proximo elemento da lista
} ListaVertice;

ListaAresta *alocaAresta();

ListaVertice *alocaVertice();

void desalocaAresta(ListaAresta *l);

void desalocaVertice(ListaVertice *l);

// entrada: a lista q se deseja fazer a procura e o objeto a ser encontrado
// saida: se existir na lista devolve a posição caso ao contrario devolve -1
bool existeVertice(ListaVertice *grafo, char *no);

// Retorna o nó inserido
void insereVertice(ListaVertice *grafo, char *no);

ListaAresta *auxInsereAresta(ListaAresta *listaAresta, char *v, int peso);

// Retorna o nó inserido
void insereAresta(ListaVertice * grafo, char* u, char *v, int peso, bool heuristica);

// Função que representa o grafo em um arquivo .dot e .png
//void representaGrafo(ListaVertice *grafo, char *nomArq);

int leArquivo(char *inicio, char *fim, ListaVertice *grafo, char *nomArq);

#endif //IA_P2_GRAFOFUNCOES_H