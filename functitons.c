#include "functitons.h"

ListaAresta *alocaAresta()
{
    ListaAresta *lAux = (ListaAresta *)malloc(sizeof(ListaAresta));
    lAux->prox = NULL;
    lAux->peso = 0;
    memset(lAux->v, 0, sizeof(lAux->v));
    return lAux;
}

ListaVertice *alocaVertice()
{
    ListaVertice *lAux = (ListaVertice *)malloc(sizeof(ListaVertice));
    memset(lAux->v, 0, sizeof(lAux->v));
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
        memset(l->v, 0, sizeof(l->v));
        free(l);
        l = aux;
    }
    free(l->v);
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
        memset(l->v, 0, sizeof(l->v));
        free(l);
        l = aux;
    }
}

void representaGrafo(ListaVertice *cabListaV, char *nomArq) {
    ListaVertice *auxV = cabListaV;
    if (auxV == NULL) {
        printf("Grafo vazio\n");
        return;
    }

    GVC_t *gvc;
    gvc = gvContext();

    Agraph_t *g;
    g = agopen("Grafo", Agdirected, NULL);

    // Cria os nós no agraph
    for (int i = 0; auxV != NULL ; i++, auxV = auxV->prox) {
        char nome[20];
        sprintf(nome, "%d", i);
        agnode(g, nome, 1);
    }

    auxV = cabListaV;

    // Cria as arestas no agraph
    while(auxV != NULL) {
        for (ListaAresta* auxA = auxV->listaAresta; auxA != NULL; auxA = auxA->prox) {
            char peso[20];
            sprintf(peso, "%d", auxA->peso);
            Agnode_t* node1 = agnode(g, auxV->v, 0);
            Agnode_t* node2 = agnode(g, auxA->v, 0);
            Agedge_t *edge = agedge(g, node1, node2, NULL, 1);
            agsafeset(edge, "label", peso, "");
        }
        auxV = auxV->prox;
    }

    char *nomArqDot = malloc(50 * sizeof(char));
    strcpy(nomArqDot, nomArq);
    strcat(nomArqDot, ".dot");

    char *nomArqPng = malloc(50 * sizeof(char));
    strcpy(nomArqPng, nomArq);
    strcat(nomArqPng, ".png");

    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "dot", nomArqDot);
    gvFreeLayout(gvc, g);

    agclose(g);

    gvFreeContext(gvc);

    char comando[100];
    sprintf(comando, "dot -Tpng %s -o %s", nomArqDot, nomArqPng);
    system(comando);

    wprintf(L" Arquivos criados com sucesso, com os nomes '%s' e '%s'!\n\n",nomArqDot,nomArqPng);

    free(nomArqDot);
    free(nomArqPng);
}