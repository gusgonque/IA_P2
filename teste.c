#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functitons.h"

void insereAresta(ListaAresta *aresta, char *vertice, char *peso){
    aresta = alocaAresta();
    strcpy(aresta->v, vertice);
    aresta->peso = atoi(peso);
}

void insereNo(ListaVertice *no, char *verticeIni, char *verticeFim, char *peso)
{
    strcpy(no->v, verticeIni);
    insereAresta(no->listaAresta, verticeFim, peso);
}

int leArquivo(char *inicio, char *fim, ListaVertice *grafo)
{
    FILE *f = fopen("exemplo.txt", "r");

    if (f == NULL)
    {
        perror("Erro abrindo arquivo");
        return 1;
    }

    char linha[50], comando[20], conteudo[10];
    ListaVertice *cabecaGrafo = grafo;
    int pos;

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
        else if (strcmp(comando, "pode_ir") == 0)
        {
            char *tokenV = strtok(conteudo, ",");
            char *tokenA = strtok(NULL, ",");
            char *tokenP = strtok(NULL, ",");
            if (grafo->v == '\0') // grafo vazio
            {
                insereNo(grafo, tokenV, tokenA, tokenP);
            }
            else // tem grafo
            {
                ListaVertice *anterior;

                while (grafo != NULL && grafo->v != tokenV) // procura no
                {
                    anterior = grafo;
                    grafo = grafo->prox;
                }
                if (grafo == NULL) // n achou o no
                {
                    grafo = anterior;
                    grafo->prox = alocaVertice();

                    insereNo(grafo->prox, tokenV, tokenA, tokenP);
                }
                else //achou o no
                {
                    if (grafo->listaAresta == NULL) // n tem aresta
                    {
                        insereAresta(grafo->listaAresta, tokenA, tokenP);
                    }
                    else // tem aresta
                    {
                        ListaAresta *cabecaAresta = grafo->listaAresta;
                        while (grafo->listaAresta->prox != NULL)
                        {
                            grafo->listaAresta = grafo->listaAresta->prox;
                        }
                        insereAresta(grafo->listaAresta->prox, tokenA, tokenP);
                        grafo->listaAresta = cabecaAresta;
                    }
                }
                 grafo = cabecaGrafo;
            }
        }
        else if (strcmp(comando, "h") == 0)
        {
            char *tokenV = strtok(conteudo, ",");
            char *tokenA = strtok(NULL, ",");
            char *tokenP = strtok(NULL, ",");
            while (grafo != NULL && grafo->v != tokenV) // procura no
            {
                grafo = grafo->prox;
            }
            if (grafo == NULL) // n tem no
            {
                printf("Erro! No nao existe.\n");
                return 1;
            }
            else // tem no
            {
                ListaAresta *anterior;
                ListaAresta *cabecaAresta = grafo->listaAresta;
                while (grafo->listaAresta != NULL && grafo->listaAresta->v != tokenA)
                {
                    anterior = grafo->listaAresta;
                    grafo->listaAresta = grafo->listaAresta->prox;
                }    
                if (grafo->listaAresta == NULL)
                {
                    grafo->listaAresta = anterior;
                    grafo->listaAresta = alocaAresta();
                }
                grafo->listaAresta->heuristica = tokenP;
                grafo->listaAresta = cabecaAresta;
            }
        }
        else
        {
            printf("Comando desconhecido\n");
            return 1;
        }
        memset(linha, 0, sizeof(linha));
        memset(conteudo, 0, sizeof(conteudo));
        memset(comando, 0, sizeof(comando));
    }

    fclose(f);

    return 0;
}


int main(){
    char pontoInicial[20];
    char pontoFinal[20];
    ListaVertice *grafo;
    grafo = alocaVertice();
    leArquivo(pontoInicial, pontoFinal, grafo);


    printf("pI = %s\n", pontoInicial);
    printf("pF = %s\n", pontoFinal);
}

