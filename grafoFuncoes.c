#include "grafoFuncoes.h"

ListaAresta *alocaAresta()
{
    ListaAresta *lAux = (ListaAresta *)malloc(sizeof(ListaAresta));
    lAux->peso = -1;
    lAux->heuristica = 0;
    lAux->prox = NULL;
    return lAux;
}

ListaVertice *alocaVertice()
{
    ListaVertice *lAux = (ListaVertice *)malloc(sizeof(ListaVertice));
    memset(lAux->u, 0, sizeof(lAux->u));
    lAux->prox = NULL;
    lAux->listaAresta = NULL;
    return lAux;
}

void desalocaAresta(ListaAresta *l)
{
    ListaAresta* aux;
    while (l->prox != NULL)
    {
        aux = l->prox;
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
        memset(l->u, 0, sizeof(l->u));
        desalocaAresta(l->listaAresta);
        free(l);
        l = aux;
    }
}

int existeVertice(ListaVertice *grafo, char *no)
{
    int i = 0;
    ListaVertice *aux = grafo;
    while (aux != NULL)
    {
        if (strcmp(aux->u, no) == 0)
            return i;
        else
        {
            i++;
            aux = aux->prox;
        }
    }
    return -1;
}

ListaVertice * insereVertice(ListaVertice *grafo, char *no)
{
    if (grafo == NULL)
    {
        grafo = alocaVertice();
        strcpy(grafo->u, no);
    }
    else
    {
        ListaVertice *aux = grafo;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = alocaVertice();
        strcpy(aux->prox->u, no);
    }
    return grafo;
}

ListaVertice *insereAresta(ListaVertice *grafo, char *u, char *v, int p, bool h)
{
    int aux = existeVertice(grafo, v);
    if (aux == -1)
    {
        grafo = insereVertice(grafo, v);
        aux = existeVertice(grafo, v);
    }
    ListaVertice *auxVerticeV = grafo;
    for (int i = 0; i < aux; ++i)
        auxVerticeV = auxVerticeV->prox;

    aux = existeVertice(grafo, u);
    if (aux == -1)
    {
        grafo = insereVertice(grafo, u);
        aux = existeVertice(grafo, u);
    }
    ListaVertice *auxVerticeU = grafo;
    for (int i = 0; i < aux; ++i)
        auxVerticeU = auxVerticeU->prox;

    if (auxVerticeU->listaAresta == NULL)
    {
        auxVerticeU->listaAresta = alocaAresta();
        auxVerticeU->listaAresta->v = auxVerticeV;
        if (h)
            auxVerticeU->listaAresta->heuristica = p;
        else
            auxVerticeU->listaAresta->peso = p;
    }
    else
    {
        ListaAresta *auxAresta = auxVerticeU->listaAresta;
        while (strcmp(auxAresta->v->u, auxVerticeV->u) != 0) // procura na lista de arestas de U, o vertice V
        {
            if (auxAresta->prox == NULL)
            {
                auxAresta->prox = alocaAresta();
                auxAresta->prox->v = auxVerticeV;
                if (h)
                    auxAresta->prox->heuristica = p;
                else
                    auxAresta->prox->peso = p;
            } else
                auxAresta = auxAresta->prox;
        }
        if (strcmp(auxAresta->v->u, auxVerticeV->u) == 0)
        {
            if (h)
                auxAresta->heuristica = p;
            else
                auxAresta->peso = p;
        }
    }
    return grafo;
}

int calculaNumeroVertices(ListaVertice *grafo)
{
    int i = 0;
    ListaVertice *aux = grafo;
    while (aux != NULL)
    {
        i++;
        aux = aux->prox;
    }
    return i;
}

//void representaGrafo(ListaVertice *grafo, char *nomArq)
//{
//    ListaVertice *auxV = grafo;
//    if (auxV == NULL)
//    {
//        printf("Grafo vazio\n");
//        return;
//    }
//
//    GVC_t *gvc;
//    gvc = gvContext();
//
//    Agraph_t *g;
//    g = agopen("Grafo", Agdirected, NULL);
//
//    // Cria os nós no agraph
//    for (int i = 0; auxV != NULL ; i++, auxV = auxV->prox)
//    {
//        char nome[20];
//        sprintf(nome, "%d", i);
//        agnode(g, nome, 1);
//    }
//
//    auxV = grafo;
//
//    // Cria as arestas no agraph
//    while(auxV != NULL)
//    {
//        for (ListaAresta* auxA = auxV->listaArestaAdj; auxA != NULL; auxA = auxA->prox) {
//            char peso[20];
//            sprintf(peso, "%d", auxA->peso);
//            Agnode_t* node1 = agnode(g, auxV->u, 0);
//            Agnode_t* node2 = agnode(g, auxA->v->u, 0);
//            Agedge_t *edge = agedge(g, node1, node2, NULL, 1);
//            agsafeset(edge, "label", peso, "");
//        }
//        auxV = auxV->prox;
//    }
//
//    char *nomArqDot = malloc(50 * sizeof(char));
//    strcpy(nomArqDot, nomArq);
//    strcat(nomArqDot, ".dot");
//
//    char *nomArqPng = malloc(50 * sizeof(char));
//    strcpy(nomArqPng, nomArq);
//    strcat(nomArqPng, ".png");
//
//    gvLayout(gvc, g, "dot");
//    gvRenderFilename(gvc, g, "dot", nomArqDot);
//    gvFreeLayout(gvc, g);
//
//    agclose(g);
//
//    gvFreeContext(gvc);
//
//    char comando[100];
//    sprintf(comando, "dot -Tpng %s -o %s", nomArqDot, nomArqPng);
//    system(comando);
//
//    wprintf(L" Arquivos criados com sucesso, com os nomes '%s' e '%s'!\n\n",nomArqDot,nomArqPng);
//
//    free(nomArqDot);
//    free(nomArqPng);
//}

ListaVertice * lerArquivo(char *inicio, char *fim, ListaVertice *grafo, char *nomArq)
{
    if (grafo != NULL) {
        wprintf(L"Desalocando grafo antigo...\n");
        memset(inicio, 0, sizeof(*inicio));
        memset(fim, 0, sizeof(*fim));
        desalocaVertice(grafo);
    }

    FILE *f = fopen(nomArq, "r");

    if (f == NULL)
    {
        perror("Erro abrindo arquivo!");
        return grafo;
    }

    char linha[50], comando[20], conteudo[10];

    int i = 0;
    while (fgets(linha, sizeof(linha), f) != NULL)
    {
        i++;
        sscanf(linha, "%20[^()]", comando);
        sscanf(linha, "%*[^(](%10[^)])", conteudo);

        if (strcmp(comando, "ponto_inicial") == 0)
        {
            strcpy(inicio, conteudo);
        }
        else if (strcmp(comando, "ponto_final") == 0)
        {
            strcpy(fim, conteudo);
        }
        else
        {
            char *tokenU = strtok(conteudo, ",");
            char *tokenV = strtok(NULL, ","); // NULL para continuar a string anterior
            char *tokenP = strtok(NULL, ","); // NULL para continuar a string anterior
            if (strcmp(comando, "pode_ir") == 0)
            {
                grafo = insereAresta(grafo, tokenU, tokenV, atoi(tokenP), false);

            }
            else if (strcmp(comando, "h") == 0)
            {
                grafo = insereAresta(grafo, tokenU, tokenV, atoi(tokenP), true);
            }
            else
            {
                wprintf(L"Comando desconhecido no arquivo. (Linha %d)\n", i);
            }
        }

        memset(linha, 0, sizeof(linha));
        memset(conteudo, 0, sizeof(conteudo));
        memset(comando, 0, sizeof(comando));
    }

    wprintf(L"Arquivo lido com sucesso!\n");
    fclose(f);

    return grafo;
}

