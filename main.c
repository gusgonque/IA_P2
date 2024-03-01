#include <stdio.h>

void menu (){
    int x;
    wprintf(L"Selecione um algoritmo: ");
    wprintf(L"1 - Algoritmo 1\n"); // Todo: Implementar algoritmo 1

    wprintf(L"Digite a opção desejada: ");
    scanf("%d", &x);
    switch (x) {
        case 1:
            wprintf(L"Algoritmo 1 selecionado.\n");

        default:
            wprintf(L"Opção inválida.\n");
            break;
    }
}

int main() {
    int x;
    wprintf(L"Digite um número: ");
    scanf("%d", &x);
    wprintf(L"O número digitado foi: %d\n", x);
    return 0;
}