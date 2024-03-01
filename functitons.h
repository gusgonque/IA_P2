#ifndef IA_P2_FUNCTITONS_H
#define IA_P2_FUNCTITONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noListaAresta
{
    char u[10], v[10];
    unsigned int peso;
    struct noListaAresta *prox;
} ListaAresta;

typedef struct noListaVertice
{
    char u[10]; // a
    struct noListaAresta *listaAresta;
    struct noListaAresta *listaHeuristica;
    struct noListaVertice *prox;
} ListaVertice;

ListaAresta *alocaAresta();

ListaVertice *alocaVertice();

// oi
void desalocaAresta(ListaAresta *l);

void desalocaVertice(ListaVertice *l);



#endif //IA_P2_FUNCTITONS_H