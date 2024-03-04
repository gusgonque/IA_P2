#include "BFS.h"

ListaVertice *removeCabecaListaVertices (ListaVertice *l){
    if(l != NULL) {
        ListaVertice *lAux = l->prox;
        free(l);
        return lAux;
    }
    return l;
}

int BFS_BuscaVertice (GrafoBFS *gBFS, char *no, int nmrVertices) {
    for (int i = 0; i < nmrVertices; ++i) {
        if (strcmp(gBFS[i].u->u, no) == 0)
            return i;
    }
    return -1;
}

void BFS_visit(ListaVertice *grafo, char *pontoInicial, char *pontoFinal) {
    ListaVertice *Q = NULL;
    int nmrVertices = calculaNumeroVertices(grafo);
    GrafoBFS *gBFS = malloc(nmrVertices * sizeof  (GrafoBFS));
    ListaAresta *auxAresta = NULL;
    ListaVertice *auxVerticeGrafo = grafo;

    int t = 0;
    int pesoTotal = 0;

    for (int i = 0; i < nmrVertices; ++i) {
        gBFS[i].u = auxVerticeGrafo;
        gBFS[i].cor = 'B';

        memset(gBFS[i].pi, 0, sizeof(gBFS[i].pi));
        gBFS[i].d = -1;
        gBFS[i].f = -1;
        gBFS[i].listaArestaAdj = auxVerticeGrafo->listaAresta;

        auxVerticeGrafo = auxVerticeGrafo->prox;
    }

    int i = BFS_BuscaVertice(gBFS, pontoInicial, nmrVertices);

    gBFS[i].cor = 'C';
    printf(" [%s] ", pontoInicial);
    gBFS[i].d = 0;
    memset(gBFS[i].pi, 0, sizeof(gBFS[i].pi));
    Q = insereVertice(Q, pontoInicial);
    while (Q != NULL){
        strcpy(pontoInicial, Q->u);

        i = BFS_BuscaVertice(gBFS, pontoInicial, nmrVertices);
        auxAresta = gBFS[i].listaArestaAdj;
        while (auxAresta != NULL){
            int j = BFS_BuscaVertice(gBFS, auxAresta->v->u, nmrVertices);

            if (j == -1) {
                wprintf(L"\nErro ao buscar o vértice [%s] no grafo DFS.\n", auxAresta->v->u);
                return;
            }

            if(auxAresta->peso != -1){
                if(gBFS[j].cor == 'B'){
                    gBFS[j].cor = 'C';
                    printf("- [%s] ", auxAresta->v->u);

                    pesoTotal += auxAresta->peso;
                    t++;

                    if(strcmp(auxAresta->v->u, pontoFinal) == 0){
                        wprintf(L"\nVértice [%s] encontrado. T = %d, Peso Total = %d.\n", pontoFinal, t, pesoTotal);
                        return;
                    }

                    strcpy(gBFS[j].pi, pontoInicial);
                    gBFS[j].d = gBFS[i].d + 1;
                    Q = insereVertice(Q, auxAresta->v->u);
                }
            }

            auxAresta = auxAresta->prox;
        }
        Q = removeCabecaListaVertices(Q);
        gBFS[i].cor = 'P';
    }
    printf("\n");

    free(gBFS);
}