//
// Created by Gustavo on 03/03/2024.
//

#ifndef IA_P2_GULOSO_H
#define IA_P2_GULOSO_H

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

typedef struct cfinal
{
    ListaVertice *no;
    struct cfinal *prox;
}CaminhoFinal;

MenorCaminho *alocaCaminhos();

CaminhoFinal *alocaFinal();

void guloso(ListaVertice *inicio, ListaVertice *fim);

#endif //IA_P2_GULOSO_H
