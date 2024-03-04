#include "DFS.h"

int DFS_BuscaVertice (GrafoDFS *gDFS, char *no, int nmrVertices) {
    for (int i = 0; i < nmrVertices; ++i) {
        if (strcmp(gDFS[i].u->u, no) == 0)
            return i;
    }
    return -1;
}

void DFS_visit(GrafoDFS *gDFS, char *u, char *pFim, int *t, int *pesoTotal, int nmrVertices) {
    int i = DFS_BuscaVertice(gDFS, u, nmrVertices);
    ListaAresta *auxAresta = gDFS[i].listaArestaAdj;

    gDFS[i].cor = 'C';
    printf(" [%s] ", u);

    (*t) ++;
    gDFS[i].d = *t;
    (*pesoTotal) += gDFS[i].listaArestaAdj->peso;

    if (strcmp(u, pFim) == 0) {
        wprintf(L"\nVértice [%s] encontrado. T = %d, Peso Total = %d.\n", pFim, *t, *pesoTotal);
        *t = -1;
        return;
    }

    while (auxAresta != NULL){
        int j = DFS_BuscaVertice(gDFS, auxAresta->v->u, nmrVertices);

        if (j == -1) {
            wprintf(L"\nErro ao buscar o vértice [%s] no grafo DFS.\n", auxAresta->v->u);
            return;
        }

        if(auxAresta->peso != -1){

            if(gDFS[j].cor == 'B'){
                printf("-");
                strcpy(gDFS[j].pi, u);
                DFS_visit(gDFS, auxAresta->v->u, pFim, t, pesoTotal, nmrVertices);
            }

            if(*t == -1) return;
        }
        auxAresta = auxAresta->prox;
    }

    gDFS[i].cor = 'P';
    (*t) ++;
    gDFS[i].f = *t;
}

void DFS(ListaVertice *grafo, char *pInicio, char *pFim) {
    int *t = malloc(sizeof(int)); // Timestamp
    *t = 0;
    int *pesoTotal = malloc(sizeof(int));
    *pesoTotal = 0;

    int nmrVertices = calculaNumeroVertices(grafo);

    GrafoDFS *gDFS = malloc(nmrVertices * sizeof (GrafoDFS)); // Vetor para indicar cada vértice do grafo.
    ListaVertice *auxVerticeGrafo = grafo;

    for (int i = 0; i < nmrVertices; ++i) {

        gDFS[i].u = auxVerticeGrafo;
        gDFS[i].cor = 'B';

        memset(gDFS[i].pi, 0, sizeof(gDFS[i].pi));
        gDFS[i].f = -1;
        gDFS[i].d = -1;
        gDFS[i].listaArestaAdj = auxVerticeGrafo->listaAresta;

        auxVerticeGrafo = auxVerticeGrafo->prox;
    }
    DFS_visit(gDFS, pInicio, pFim, t,pesoTotal, nmrVertices);

    if(*t != -1)
        wprintf(L"\nVértice [%s] não encontrado.\n", pFim);

    free(gDFS);
    free(t);
}
