#include "guloso.h"

MenorCaminho *alocaCaminhos()
{
    MenorCaminho *aux = (MenorCaminho *)malloc(sizeof(MenorCaminho));
    aux->no = NULL;
    aux->total = -1;
    return aux;
}

CaminhoFinal *alocaFinal(){
    CaminhoFinal *aux = (CaminhoFinal *)malloc(sizeof(CaminhoFinal));
    aux->no = NULL;
    aux->prox = NULL;
    return aux;
}


void guloso(ListaVertice *inicio, ListaVertice *fim)
{
    ListaAresta *auxAresta = inicio->listaAresta;
    MenorCaminho *menorCaminho = alocaCaminhos();
    menorCaminho->no = inicio;
    int heuristicaFinal = 0;
    int atual = 0;
    CaminhoFinal *final = alocaFinal();
    final->no = inicio;

    CaminhoFinal *auxf = final;
    _Bool p = 0;

    while (strcmp(menorCaminho->no->u, fim->u) != 0)
    {
        while (auxAresta != NULL) // enquanto houver arestas, procura a menor
        {
            ListaAresta *auxAH = auxAresta->v->listaAresta; // ARESTAS DO NO q conecta a aresta atual

            if (auxAresta->heuristica == -1)
            {
                auxAresta = auxAresta->prox;
            }
            else
            { // soma heuristica da aresta atual + heuristica do proximo nó ao nó final
                while (auxAH != NULL && (strcmp(auxAH->v->u, fim->u) != 0)) // procura se tem heuristica ate o ponto final
                {
                    auxAH = auxAH->prox;
                }
                if (auxAH == NULL) // n tem heuristica até o ponto final
                {
                    atual = auxAresta->heuristica;
                }
                else // tem heuristica até o ponto final
                {
                    atual = auxAresta->heuristica + auxAH->heuristica;
                }
                if (menorCaminho->total == -1) // primeiro caso
                {
                    menorCaminho->total = atual;
                    menorCaminho->no = auxAresta->v;
                }
                if (menorCaminho->total > atual) // substitui se necessario pelo novo menor caminho
                {
                    menorCaminho->total = atual;
                    menorCaminho->no = auxAresta->v;
                }
            }

            auxAresta = auxAresta->prox;
        }
        if (auxAresta != NULL && strcmp(menorCaminho->no->u, fim->u) != 0)
        {
            printf("Caminho nao Encontrado: [%s]", final->no->u);
            final = final->prox;
            while (final != NULL)
            {
                printf("->[%s]", final->no->u);
                final = final->prox;
            }
            printf("->[]\nHeuristica Total = %d", heuristicaFinal);
            p = 1;
            break;
        }
        auxAresta = menorCaminho->no->listaAresta;
        menorCaminho->total = -1;
        heuristicaFinal += atual;
        auxf->prox = alocaFinal();
        auxf = auxf->prox;
        auxf->no = menorCaminho->no;
        printf("->[%s] h: %d", menorCaminho->no->u, atual);
        atual = 0;
    }
    if (p == 0)
    {
        printf("Caminho Encontrado: [%s]", final->no->u);
        final = final->prox;
        while (final != NULL)
        {
            printf("->[%s]", final->no->u);
            final = final->prox;
        }
        printf("\nHeuristica Total = %d", heuristicaFinal);
    }
}
