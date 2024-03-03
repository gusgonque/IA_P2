#include <stdio.h>
#include <locale.h>
#include "grafoFuncoes.h"
#include "DFS.h"

void menu (char *pontoInicial, char *pontoFinal, ListaVertice *grafo){
    int x;

    wprintf(L"Selecione uma opção:\n");
    wprintf(L"1 - Carregar arquivo de dados.\n");
    wprintf(L"2 - Busca em Profundidade. (Depht First Search)\n");

    //wprintf(L"X - Representar grafo\n"); //TODO: Implementar função para desenhar grafo
    wprintf(L"0 - Finalizar programa.\n");


    wprintf(L"Digite a opção desejada:");
    scanf("%d", &x);
    switch (x) {
        case 1:
            wprintf(L"Digite o nome do arquivo de dados. (Ex: 'dados.txt'):");
            char nomeArquivo[50];
            scanf("%s", nomeArquivo);
            grafo = lerArquivo(pontoInicial, pontoFinal, grafo, nomeArquivo);
            menu(pontoInicial, pontoFinal, grafo);
            break;

        case 2:
            if (grafo == NULL) {
                wprintf(L"Erro: Grafo não carregado.\n");
                menu(pontoInicial, pontoFinal, grafo);
                break;
            }
            DFS(grafo, pontoInicial, pontoFinal);
            menu(pontoInicial, pontoFinal, grafo);
            break;

        case 0:
            wprintf(L"Finalizando programa.\n");
            break;

        default:
            wprintf(L"Opção inválida.\n");
            menu(pontoInicial, pontoFinal, grafo);
            break;
    }
}

int main() {
    setlocale(LC_ALL,"Portuguese");


    ListaVertice *grafo = NULL;
    char pontoInicial[10];
    memset(pontoInicial, 0, sizeof(pontoInicial));
    char pontoFinal[10];
    memset(pontoFinal, 0, sizeof(pontoFinal));

    menu(pontoInicial, pontoFinal, grafo);
    return 0;
}