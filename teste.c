#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafoFuncoes.h"

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
            char *token = strtok(conteudo, ",");
            if (grafo->v == '\0')
            {
                strcpy(grafo->v, token);
                grafo->listaAresta = alocaAresta();
                token = strtok(NULL, ",");
                strcpy(grafo->listaAresta->v, token);
                token = strtok(NULL, ",");
                grafo->listaAresta->peso = atoi(token);
            }
            else
            {
                pos = existeVertice(grafo, token);
                if (pos == -1)
                {
                    while (grafo->prox != NULL)
                    {
                        grafo = grafo->prox;
                    }
                    grafo->prox = alocaVertice();
                    strcpy(grafo->v, token);
                    grafo->listaAresta = alocaAresta();
                    token = strtok(NULL, ",");
                    strcpy(grafo->listaAresta->v, token);
                    token = strtok(NULL, ",");
                    grafo->listaAresta->peso = atoi(token);
                    grafo = cabecaGrafo;
                }
                else
                {
                    for (int i = 0; i != pos; i++)
                    {
                        grafo = grafo->prox;
                    }
                    if (grafo->listaAresta->prox == NULL)
                    {
                        grafo->listaAresta->prox = alocaAresta();
                        token = strtok(NULL, ",");
                        strcpy(grafo->listaAresta->prox->v, token);
                        token = strtok(NULL, ",");
                        grafo->listaAresta->prox->peso = atoi(token);
                    }
                    else
                    {
                        ListaAresta *cabecaAresta = grafo->listaAresta;
                        while (grafo->listaAresta->prox != NULL)
                        {
                            grafo->listaAresta = grafo->listaAresta->prox;
                        }
                        grafo->listaAresta->prox = alocaAresta();
                        token = strtok(NULL, ",");
                        strcpy(grafo->listaAresta->prox->v, token);
                        token = strtok(NULL, ",");
                        grafo->listaAresta->prox->peso = atoi(token);
                        grafo->listaAresta = cabecaAresta;
                    }
                    grafo = cabecaGrafo;
                }
            }
        }
        else if (strcmp(comando, "h") == 0)
        {
            // TODO heuristica
        }
        else
        {
            wprintf(L"Comando desconhecido no arquivo.\n");
            return 1;
        }
        memset(linha, 0, sizeof(linha));
        memset(conteudo, 0, sizeof(conteudo));
        memset(comando, 0, sizeof(comando));
    }//

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

