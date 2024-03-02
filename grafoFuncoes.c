#include "grafoFuncoes.h"

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

int existeVertice(ListaVertice *grafo, char *no)
{
    int i = 0;
    ListaVertice *aux = grafo;
    while (aux != NULL)
    {
        if (strcmp(aux->v, no) == 0)
        {
            return i;
        }
        else
        {
            i++;
            aux = aux->prox;
        }
    }
    return -1;
}

void insereVertice(ListaVertice *grafo, char *no)
{
    ListaVertice *aux = grafo;
    if (aux == NULL)
    {
        aux = alocaVertice();
        strcpy(aux->v, no);
    }
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    aux->prox = alocaVertice();
    strcpy(aux->prox->v, no);
}

ListaAresta *auxInsereAresta(ListaAresta *listaAresta, char *v, int peso)
{
    ListaAresta *aux = listaAresta;
    if (aux == NULL)
    {
        aux = alocaAresta();
        strcpy(aux->v, v);
        aux->peso = peso;
    }
    else
    {
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = alocaAresta();
        strcpy(aux->prox->v, v);
        aux->prox->peso = peso;
    }
    return aux;
}

void insereAresta(ListaVertice * grafo, char* u, char *v, int peso, bool heuristica)
{
    ListaVertice *auxV = grafo;
    int aux = existeVertice(auxV, u);
    if (aux == -1)
    {
        insereVertice(auxV, u);
    }
    else
    {
        for (int i = 0; i < aux; ++i) {
            auxV = auxV->prox;
        }
    }
    if (heuristica)
    {
        auxInsereAresta(auxV->listaHeuristica, v, peso);
    }
    else
    {
        auxInsereAresta(auxV->listaAresta, v, peso);
    }
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
//        for (ListaAresta* auxA = auxV->listaAresta; auxA != NULL; auxA = auxA->prox) {
//            char peso[20];
//            sprintf(peso, "%d", auxA->peso);
//            Agnode_t* node1 = agnode(g, auxV->v, 0);
//            Agnode_t* node2 = agnode(g, auxA->v, 0);
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

int leArquivo(char *inicio, char *fim, ListaVertice *grafo, char *nomArq)
{
    FILE *f = fopen(nomArq, "r");

    if (f == NULL)
    {
        perror("Erro abrindo arquivo");
        return 1;
    }

    char linha[50], comando[20], conteudo[10];

    while (fgets(linha, sizeof(linha), f) != NULL)
    {
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
            char *tokenV = strtok(conteudo, ",");
            char *tokenA = strtok(NULL, ","); // NULL para continuar a string anterior
            char *peso = strtok(NULL, ","); // NULL para continuar a string anterior
            if (strcmp(comando, "pode_ir") == 0)
            {
                insereVertice(grafo, tokenV);
                insereAresta(grafo, tokenV, tokenA, atoi(peso), false);

            }
            else if (strcmp(comando, "h") == 0)
            {
                insereVertice(grafo, tokenV);
                insereAresta(grafo, tokenV, tokenA, atoi(peso), true);
            }
            else
            {
                wprintf(L"Comando desconhecido no arquivo.\n");
                return 1;
            }
        }

        memset(linha, 0, sizeof(linha));
        memset(conteudo, 0, sizeof(conteudo));
        memset(comando, 0, sizeof(comando));
    }//

    fclose(f);

    return 0;
}