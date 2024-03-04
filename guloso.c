#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "grafoFuncoes.h"

typedef struct caminho
{
    int total;
    ListaVertice *no;
} MenorCaminho;

MenorCaminho *alocaCaminhos()
{
    MenorCaminho *aux = (MenorCaminho *)malloc(sizeof(MenorCaminho));
    aux->no = NULL;
    aux->total = -1;
    return aux;
}

typedef struct cfinal
{
    ListaVertice *no;
    struct cfinal *prox;
}CaminhoFinal;

CaminhoFinal *alocaFinal(){
    CaminhoFinal *aux = (CaminhoFinal *)malloc(sizeof(CaminhoFinal));
    aux->no = NULL;
    aux->prox = NULL;
    return aux;
}


void guloso(ListaVertice *inicio, ListaVertice *fim)
{
    ListaAresta *auxA = inicio->listaAresta;
    MenorCaminho *menorCaminho = alocaCaminhos();
    int heuristicaFinal = 0;
    int atual = 0;
    CaminhoFinal *final = alocaFinal();
    CaminhoFinal *auxf = final;
    _Bool p = 0;

    while (strcmp(menorCaminho->no->u, fim->u) != 0)
    {
        MenorCaminho *menorCaminho = alocaCaminhos();
        while (auxA != NULL) // enquanto houver arestas, procura a menor
        {
            ListaAresta *auxAH = auxA->v->listaAresta; // ARESTAS DO NO q conecta a aresta atual

            if (auxA->heuristica == -1)
            {
                auxA = auxA->prox;
            }
            else
            { // soma heuristica da aresta atual + heuristica do proximo nó ao nó final
                while (auxAH != NULL && strcmp(auxAH->v->u, fim->u) != 0) // procura se tem heuristica ate o ponto final
                {
                    auxAH = auxAH->prox;
                }
                if (auxAH == NULL) // n tem heuristica até o ponto final
                {
                    atual = auxA->heuristica;
                }
                else // tem heuristica até o ponto final
                {
                    atual = auxA->heuristica + auxAH->heuristica;
                }
                if (menorCaminho->total == -1) // primeiro caso
                {
                    menorCaminho->total = atual;
                    menorCaminho->no = auxA->v;
                }
                if (menorCaminho->total > atual) // substitui se necessario pelo novo menor caminho
                {
                    menorCaminho->total = atual;
                    menorCaminho->no = auxA->v;
                }
            }
        }
        if (auxA != NULL && strcmp(menorCaminho->no->u, fim->u) != 0)
        {
            printf("Caminho nao Encontrado: [%s]", final->no->u);
            do
            {
                final = final->prox;
                printf("->[%s]", final->no->u);
            } while (final != NULL);
            printf("->[]\nHeuristica Total = %d", heuristicaFinal);
            p = 1;
            break;
        }
        auxA = menorCaminho->no->listaAresta;
        menorCaminho->total = -1;
        heuristicaFinal += atual;
        auxf->prox = menorCaminho->no;
        printf("->[%s] h: %d", menorCaminho->no, atual);
        atual = 0;
    }
    if (p = 0)
    {
        printf("Caminho Encontrado: [%s]", final->no->u);
        do
        {
            final = final->prox;
            printf("->[%s]", final->no->u);
        } while (final != NULL);
        printf("\nHeuristica Total = %d", heuristicaFinal);
    }
}
