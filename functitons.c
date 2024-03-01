#include "functitons.h"

ListaAresta *alocaAresta()
{
    ListaAresta *lAux = (ListaAresta *)malloc(sizeof(ListaAresta));
    lAux->prox = NULL;
    lAux->peso = 0;
    memset(lAux->u, 0, sizeof(lAux->u));
    memset(lAux->v, 0, sizeof(lAux->v));
    return lAux;
}

ListaVertice *alocaVertice()
{
    ListaVertice *lAux = (ListaVertice *)malloc(sizeof(ListaVertice));
    memset(lAux->u, 0, sizeof(lAux->u));
    lAux->prox = NULL;
    lAux->listaAresta = NULL;
    lAux->listaHeuristica = NULL;
    return lAux;
}

void desalocaAresta(ListaAresta *l)
{
    ListaAresta* aux;
    while (l->prox != NULL)
    {
        aux = l->prox;
        memset(l->u, 0, sizeof(l->u));
        memset(l->v, 0, sizeof(l->v));
        free(l);
        l = aux;
    }
    free(l->u);free(l->v);
    free(l);
}

void desalocaVertice(ListaVertice *l)
{
    ListaVertice *aux;
    while (l != NULL)
    {
        aux = l->prox;
        desalocaAresta(l->listaAresta);
        desalocaAresta(l->listaHeuristica);
        memset(l->u, 0, sizeof(l->u));
        free(l);
        l = aux;
    }
}
